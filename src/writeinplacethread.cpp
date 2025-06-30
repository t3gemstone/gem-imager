#include "writeinplacethread.h"
#include "archive.h"

WriteInPlaceThread::WriteInPlaceThread(
    const QByteArray &url,
    const QByteArray &localfilename,
    const QByteArray &expectedHash,
    QObject *parent
)
    : DownloadExtractThread{url, localfilename, expectedHash, parent}
{
}

void WriteInPlaceThread::run()
{
    QScopedPointer<DownloadExtractThread> th{ new DownloadExtractThread(_url, _filename, _expectedHash) };

    QScopedPointer<PriviligedProcess> bootpProc{};
    bootpProc.reset(new PriviligedProcess);

#if defined(Q_OS_UNIX)
    bootpProc->setArguments(QStringList() << "./simpbootp" << "--interface" << _selEthPort << "--single-run" << "tiboot3.bin");
#elif defined(Q_OS_WIN)
    QString simpbootCommand = QString("powershell.exe -WindowStyle Hidden -ArgumentList \"-ExecutionPolicy Bypass \
                            -Command `\"./simpbootp.exe --interface Ethernet --single-run tiboot3.bin`\"\" -Verb RunAs");

    bootpProc->setArguments(QStringList() << simpbootCommand);
#endif
    if(false == bootpProc->startCommunicationChannel("SimpbootpCommChannel"))
    {
        emit error(tr("Error comm start with simpbootp server"));
        return;
    }

    bool isDownExtrSuccess{true};

    bootpProc->start();

    QEventLoop loop;
    QObject::connect(th.data(), &DownloadExtractThread::updateNumProgress, this, &WriteInPlaceThread::updateNumProgress);
    QObject::connect(th.data(), &DownloadExtractThread::success, &loop, &QEventLoop::quit);
    QObject::connect(th.data(), &DownloadExtractThread::error, &loop, [&loop, &isDownExtrSuccess](QString err_msg)
    {
        qDebug() << "Download extract failed: " << err_msg;
        isDownExtrSuccess = false;
        loop.quit();
    });

    QObject::connect(th.data(), &DownloadExtractThread::finalizing, this, &DownloadExtractThread::finalizing);
    QObject::connect(th.data(), &DownloadExtractThread::preparationStatusUpdate, this, &DownloadExtractThread::preparationStatusUpdate);
    th->setVerifyEnabled(_verifyEnabled);
    th->setUserAgent(QString("Mozilla/5.0 gem-imager/%1").arg("1.0").toUtf8());
    th->setImageCustomization(_config, _cmdline, _firstrun, _cloudinit, _cloudinitNetwork, _geminit, _initFormat);

    th->start();
    loop.exec();

    if(!isDownExtrSuccess)
    {
        emit error(tr("Download extract failed!"));
        return;
    }

    auto clean_up = QScopeGuard{[&bootpProc]()
    {
        if(false == bootpProc->sendMessage("quit")) qDebug() << "send quit failed!";
        if(false == bootpProc->waitForFinished(3000))
        {
            bootpProc->kill();
            bootpProc->waitForFinished(1000);
        }
    }};

    if(false == bootpProc->waitForCommunicationChannelReady())
    {
        emit error(tr("Error connecting Simpbootp server"));
        return;
    }

    if(false == bootpProc->checkValue("isSblUartReady", "ok"))
    {
        if(false == bootpProc->sendMessage("notifyFileSend")) qDebug() << "notify set send failed!";
        auto resp = bootpProc->recvMessage(50000);

        if(resp != "tiboot3.bin")
        {
            qDebug() << "resp: " << resp;
            emit error(tr("SBL Uart is not ready. Please power cycle the board!"));
            return;
        }
    }

    Transfer* transferInstance{ new Transfer(_selSerPort, _serPortbaudRate, _filename) };
    if(false == transferInstance->setSerialPortAndConfigure(_selSerPort, UNIFLASH_BAUD_RATE))
    {
        emit error(tr("Error starting communication with board"));
        return;
    }

    sendFileViaXModem(transferInstance, "./linux.appimage.hs_fs");
    if(false == waitForSendFileViaXModemCompleted(transferInstance))
    {
        emit error(tr("Error sending file with XMODEM"));
        return;
    }

    delete transferInstance;

    transferInstance =  new Transfer(_selSerPort, _serPortbaudRate, _filename);
    if(false == transferInstance->setSerialPortAndConfigure(_selSerPort, UNIFLASH_BAUD_RATE))
    {
        emit error(tr("Error starting communication with board"));
        return;
    }

    sendFileViaXModem(transferInstance, "./u-boot.img");
    if(false == waitForSendFileViaXModemCompleted(transferInstance))
    {
        emit error(tr("Error sending file with XMODEM"));
        return;
    }

    delete transferInstance;

    QTimer progressTimer;

    progressTimer.setInterval(1000);
    progressTimer.callOnTimeout([this, &progressTimer, &bootpProc, &loop](){
        auto progress_str = bootpProc->getValue("getFileSendProgress");
        float progress = progress_str.toFloat();
        updateNumProgress(progress);

        if(progress >= 1.0)
        {
            loop.quit();
        }

        if(_cancelled)
        {
            loop.quit();
        }
    });

    progressTimer.start();
    loop.exec();

    // En sonda olmali bu satir
    if(_cancelled)
    {
        emit error(tr("Process cancelled by user. Please power cycle the board before retrying!"));
        return;
    }

    emit success();
}

void WriteInPlaceThread::setSerPortbaudRate(uint32_t newSerPortbaudRate)
{
    _serPortbaudRate = newSerPortbaudRate;
}

void WriteInPlaceThread::setPortNames(QString selectedSerialPort, QString selectedEthernetPort)
{
    _selSerPort = selectedSerialPort;
    _selEthPort = selectedEthernetPort;
}

bool WriteInPlaceThread::waitForSendFileViaXModemCompleted(Transfer* transferInstance, uint32_t timeout)
{
    bool result{true};
    QEventLoop loop;
    QTimer timer;
    timer.setInterval(timeout);
    timer.callOnTimeout([&loop, &result]()
    {
        qDebug() << "waitForSendFileViaXModemCompleted timeout";
        result = false;
        loop.quit();
    });

    QObject::connect(transferInstance, &Transfer::transferCompleted, &loop, &QEventLoop::quit);
    QObject::connect(transferInstance, &Transfer::transferFailed, &loop, [&loop, &result](QString err)
    {
        qDebug() << err;
        result = false;
        loop.quit();
    });
    timer.start();
    loop.exec();

    return result;
}

void WriteInPlaceThread::sendFileViaXModem(Transfer* transferInstance, const QString& filePath){
    transferInstance->setPkcsPadding(true);
    transferInstance->setFilePath(filePath);
    _isSendFileViaXModemCompleted = false;

    //Connect to signals
    connect(transferInstance, SIGNAL(updateProgress(float)), this, SLOT(updateProgress(float)));
    connect(transferInstance, SIGNAL(transferCompleted(void)), this, SLOT(onTransferCompleted(void)));
    connect(transferInstance, SIGNAL(transferFailed(QString)), this, SLOT(onTransferFailed(QString)));

    //Launch
    transferInstance->launch();
}

void WriteInPlaceThread::updateProgress(float progress){
    {
        char progress_message[128];
        memset(progress_message, '\0', sizeof(progress_message));
        sprintf(progress_message, "(%f%%)", progress * 100);
        qDebug() << __FILE__ << __LINE__ << "--" << __func__ << progress_message;
    }
    progress = (progress > 1.0) ? 1.0 : progress;
    progress = (progress < 0.0) ? 0.0 : progress;
    emit updateNumProgress(progress);
}

void WriteInPlaceThread::onTransferCompleted(){
    _isSendFileViaXModemCompleted = true;
    _isSendFileViaXModemCompletedSuccessfull = true;
}

void WriteInPlaceThread::onTransferFailed(QString reason){
    _isSendFileViaXModemCompleted = true;
    _isSendFileViaXModemCompletedSuccessfull = false;
}

WriteInPlaceThread::~WriteInPlaceThread()
{
    _cancelled = true;
    _cancelExtract();
}
