/*
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2024 Raspberry Pi Ltd
 */

#ifndef DFUTHREAD_H
#define DFUTHREAD_H

#include "downloadextractthread.h"
#include <QTemporaryFile>

class DfuThread : public DownloadExtractThread
{
    Q_OBJECT
public:
    explicit DfuThread(const QByteArray &url, const QByteArray &localfilename,
                       const QByteArray &expectedHash, const QByteArray &tiboot3Hash, const QByteArray &tisplHash, const QByteArray &ubootHash, QObject *parent = nullptr);
    ~DfuThread();

    bool isImage() override;
    void cancelDownload() override;
    void setTempDirectory(const QString &dir);

signals:
    void dfuProgress(int percentage, QString statusMsg);

protected:
    void run() override;
    bool _openAndPrepareDevice() override;

private:
    QString _bootloaderFiles[3];
    QByteArray _expectedTiboot3Hash;
    QByteArray _expectedTisplHash;
    QByteArray _expectedUbootHash;
    QTemporaryFile *_tempImageFile;
    QString _tempImagePath;
    QString _tempDir;

    class DfuWrapper *_activeDfu;
    bool runDfu(const QString &altSetting, const QString &filePath, bool resetAfter);
    bool fetchBootloaderFiles();
    bool sendBootloaderFiles();
    bool sendImageToRawemmc();
    void onStreamProgress(qint64 bytesSent, qint64 totalBytes);
};

#endif // DFUTHREAD_H
