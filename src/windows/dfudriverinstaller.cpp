/*
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2024 T3 Foundation
 */

#include "dfudriverinstaller.h"
#include "dfuwrapper.h"

#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QDebug>

#include <windows.h>
#include <libusb.h>

bool DfuDriverInstaller::isDriverInstalled()
{
    libusb_context *ctx = nullptr;
    if (libusb_init(&ctx) != LIBUSB_SUCCESS)
        return true; // libusb başlatılamadı, driver kurulu varsay

    libusb_device **list = nullptr;
    ssize_t count = libusb_get_device_list(ctx, &list);

    bool deviceFound = false;
    bool deviceAccessible = false;

    for (ssize_t i = 0; i < count; i++) {
        struct libusb_device_descriptor desc;
        if (libusb_get_device_descriptor(list[i], &desc) != LIBUSB_SUCCESS)
            continue;

        if (desc.idVendor == DfuWrapper::TI_VENDOR_ID
                && desc.idProduct == DfuWrapper::TI_PRODUCT_ID) {
            deviceFound = true;
            libusb_device_handle *handle = nullptr;
            if (libusb_open(list[i], &handle) == LIBUSB_SUCCESS) {
                deviceAccessible = true;
                libusb_close(handle);
            }
            break;
        }
    }

    libusb_free_device_list(list, 1);
    libusb_exit(ctx);

    /* Cihaz bağlı değilse sorun yok; bağlıysa erişilebilir olmalı */
    return !deviceFound || deviceAccessible;
}


static bool runElevated(const QString &exe, const QString &params, int timeoutMs)
{
    QString exeNative = QDir::toNativeSeparators(exe);

    SHELLEXECUTEINFOW sei = {};
    sei.cbSize       = sizeof(sei);
    sei.lpVerb       = L"runas";
    sei.lpFile       = reinterpret_cast<LPCWSTR>(exeNative.utf16());
    sei.lpParameters = reinterpret_cast<LPCWSTR>(params.utf16());
    sei.fMask        = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_NOASYNC;
    sei.nShow        = SW_HIDE;

    if (!ShellExecuteExW(&sei)) {
        qWarning() << "DfuDriverInstaller: ShellExecuteExW başarısız:" << GetLastError();
        return false;
    }

    DWORD waitResult = WaitForSingleObject(sei.hProcess, static_cast<DWORD>(timeoutMs));
    DWORD exitCode = 1;
    if (waitResult == WAIT_OBJECT_0)
        GetExitCodeProcess(sei.hProcess, &exitCode);
    else
        qWarning() << "DfuDriverInstaller: zaman aşımı:" << exe;
    CloseHandle(sei.hProcess);
    return exitCode == 0;
}

bool DfuDriverInstaller::installDriver()
{
    /* NSIS installer normalde cert kurulumunu ve pnputil'i halleder.
     * Bu fonksiyon yalnızca runtime fallback olarak çalışır (örn. driver kaldırılmışsa).
     * t3-dfu.cer uygulama dizininde bulunmalıdır (NSIS tarafından kopyalanır). */
    QString appDir  = QCoreApplication::applicationDirPath();
    QString cerPath = QDir::toNativeSeparators(appDir + "/t3-dfu.cer");
    QString infPath = QDir::toNativeSeparators(appDir + "/gem-imager-dfu.inf");

    if (!QFile::exists(infPath)) {
        qWarning() << "DfuDriverInstaller: gem-imager-dfu.inf bulunamadı:" << infPath;
        return false;
    }

    /* Sertifikayı TrustedPublisher ve Root depolarına ekle (admin, dialog yok) */
    if (QFile::exists(cerPath)) {
        runElevated("certutil.exe",
                    QString("-addstore -f \"Root\" \"%1\"").arg(cerPath), 15000);
        runElevated("certutil.exe",
                    QString("-addstore -f \"TrustedPublisher\" \"%1\"").arg(cerPath), 15000);
    } else {
        qWarning() << "DfuDriverInstaller: t3-dfu.cer bulunamadı, pnputil başarısız olabilir";
    }

    /* pnputil ile driver'ı kur */
    wchar_t sysDir[MAX_PATH] = {};
    GetSystemDirectoryW(sysDir, MAX_PATH);
    QString pnputil = QString::fromWCharArray(sysDir) + "\\pnputil.exe";
    QString params   = QString("/add-driver \"%1\" /install").arg(infPath);

    if (!runElevated(pnputil, params, 30000)) {
        qWarning() << "DfuDriverInstaller: pnputil başarısız oldu";
        return false;
    }

    qDebug() << "DfuDriverInstaller: WinUSB sürücüsü başarıyla yüklendi";
    return true;
}
