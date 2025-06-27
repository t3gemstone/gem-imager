#ifndef WRITEINPLACETHREAD_H
#define WRITEINPLACETHREAD_H

#include <QObject>
#include "downloadextractthread.h"
#include "config.h"

class _extractServeThreadClass;

class WriteInPlaceThread : public DownloadExtractThread
{
    Q_OBJECT
public:
    explicit WriteInPlaceThread(
        const QByteArray &url,
        const QByteArray &localfilename = "",
        const QByteArray &expectedHash = "",
        QObject *parent = nullptr
    );
    ~WriteInPlaceThread();
    void setPortNames(QString selectedSerialPort, QString selectedEthernetPort);
    void setSerPortbaudRate(uint32_t newSerPortbaudRate);
    void run() override;
    bool waitForSendFileViaXModemCompleted(Transfer* transferInstance, uint32_t timeout = 30000);
    void sendFileViaXModem(Transfer* transfer, const QString& filePath);

private:
    _extractServeThreadClass *_extractThread;
    QString _selSerPort, _selEthPort;
    uint32_t _serPortbaudRate{UNIFLASH_BAUD_RATE};
    bool _isSendFileViaXModemCompleted{false};
    bool _isSendFileViaXModemCompletedSuccessfull{false};

private slots:
    void updateProgress(float progress); //Values [0.0 1.0]
    void onTransferCompleted();
    void onTransferFailed(QString reason);
};

#endif // WRITEINPLACETHREAD_H
