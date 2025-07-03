#ifndef PRIVILIGEDPROCESS_H
#define PRIVILIGEDPROCESS_H

#include <qlocalserver.h>
#include <qstringlist.h>
#include <qprocess.h>

class PriviligedProcess: QObject
{
    Q_OBJECT
public:
    PriviligedProcess(QObject* parent = nullptr);
    ~PriviligedProcess();

    void setArguments(QStringList& args);
    QProcess* getQProcess();
    void start();
    bool waitForFinished(int msecs = 30000);
    QProcess::ExitStatus exitStatus();
    void kill();
    bool startCommunicationChannel(QByteArray channelName);
    bool waitForCommunicationChannelReady();
    bool sendMessage(QByteArray msg, int msecs = 1000);
    QByteArray getValue(QByteArray key, int msecs = 1000);
    bool checkValue(QByteArray key, QByteArray expected, int msecs = 1000);
    QByteArray recvMessage(int msec = 1000);

public slots:
    void onNewConnection();

private:
    QStringList _args;
    QProcess _proc;
    QByteArray _channelName;
    QLocalServer _server{this};
    QLocalSocket* _peer{nullptr};
};

#endif // PRIVILIGEDPROCESS_H
