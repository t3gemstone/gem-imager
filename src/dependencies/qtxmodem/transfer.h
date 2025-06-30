/* Copyright (C) 2020 J.Luis <root@heavydeck.net>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 */
#ifndef TRANSFER_H
#define TRANSFER_H

#include <QObject>
#include <QSerialPort>
#include <QThread>

class Transfer : public QThread
{
    Q_OBJECT
public:
    explicit Transfer(
            QString serialPortName,
            qint32 baudrate,
            QString filePath,
            QObject *parent = nullptr
            );

    void setParity(QSerialPort::Parity parirty);
    void setStopBits(QSerialPort::StopBits stopBits);
    void SetFlowControl(QSerialPort::FlowControl flowControl);
    void setBaudrate(uint32_t baudrate);
    void setPkcsPadding(bool enabled);
    void setDataBits(QSerialPort::DataBits bits);

    virtual ~Transfer();
    void launch();
    void cancel();

    void setFilePath(const QString &newFilePath);

    bool setSerialPortAndConfigure(QString serialPortName, uint32_t baudrate);
protected:
    //QThread method
    void run () override;

    static const quint32 timeoutRead      =  5000;
    static const quint32 timeoutFirstRead = 60000;

private:
    QSerialPort *serialPort{};
    QSerialPortInfo *serialPortInfo{};
    QString filePath{};
    bool usePkcsPadding{};
    bool cancelRequested{};
    uint32_t _baudrate{};

signals:
    void updateProgress(float);
    void transferCompleted();
    void transferFailed(QString);
};

#endif // TRANSFER_H
