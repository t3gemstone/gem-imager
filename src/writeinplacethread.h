#ifndef WRITEINPLACETHREAD_H
#define WRITEINPLACETHREAD_H

#include "downloadextractthread.h"
#include "config.h"
#include <QObject>

class _extractServeThreadClass;

class WriteInPlaceThread: public DownloadExtractThread
{
    Q_OBJECT
public:
    explicit WriteInPlaceThread(
        const QByteArray &url,
        const QByteArray &localfilename = "",
        const QByteArray &expectedHash = "",
        const QByteArray &board_name = "",
        QObject *parent = nullptr
    );
    ~WriteInPlaceThread();
    void setPortNames(QString selectedSerialPort, QString selectedEthernetPort);
    void setSerPortbaudRate(uint32_t newSerPortbaudRate);
    void run() override;
    bool waitForSendFileViaXModemCompleted(Transfer* transferInstance, uint32_t timeout = 50000);
    void sendFileViaXModem(Transfer* transfer, const QString& filePath);

private:
    _extractServeThreadClass *_extractThread;
    QString _selSerPort, _selEthPort;
    uint32_t _serPortbaudRate{UNIFLASH_BAUD_RATE};
    bool _isSendFileViaXModemCompleted{false};
    bool _isSendFileViaXModemCompletedSuccessfull{false};
    QByteArray _boardName;
    QString _lastErrorString;

private slots:
    void updateProgress(float progress); //Values [0.0 1.0]
    void onTransferCompleted();
    void onTransferFailed(QString reason);
};

#endif // WRITEINPLACETHREAD_H
