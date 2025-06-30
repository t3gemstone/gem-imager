/*
    MIT License

    Copyright (c) 2018, Alexey Dynda

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#pragma once

// Windows
#ifdef _WIN32
#pragma comment(lib,"ws2_32.lib")
#define WIN32_LEAN_AND_MEAN
#undef TEXT
#include <winsock2.h>
#include <ws2tcpip.h>

// Linux
#else
#define sprintf_s sprintf
typedef int SOCKET;
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#endif

#include "downloadthread.h"
#include <qdir.h>
#include <qudpsocket.h>
#define TFTP_DEFAULT_PORT (69)
#define TFTP_DEFAULT_BLOCK_SIZE (512)

#include <stdint.h>

class TFTP
{
public:
    enum tftpCmd: uint16_t
    {
        TFTP_CMD_RRQ   = 1,
        TFTP_CMD_WRQ   = 2,
        TFTP_CMD_DATA  = 3,
        TFTP_CMD_ACK   = 4,
        TFTP_CMD_ERROR = 5,
    };

    enum errorCode
    {
        ERR_NOT_DEFINED          = 0,
        ERR_FILE_NOT_FOUND       = 1,
        ERR_ACCESS_VIOLATION     = 2,
        ERR_NO_SPACE             = 3,
        ERR_ILLEGAL_OPERATION    = 4,
        ERR_PORT_BIND_FAILED     = 5,
        ERR_UNKNOWN_TRANSFER_ID  = 6,
        ERR_FILE_EXISTS          = 7,
        ERR_NO_SUCH_USER         = 8,
        ERR_NOOP                 = 9,
        ERR_NOT_IMPLEMENTED      = 10,
        ERR_PROC_TIMEOUT         = 11,
        ERR_RECV_TIMEOUT         = 12,
    };

    TFTP(uint16_t port = TFTP_DEFAULT_PORT, int tftp_block_size = 512, QString target_dir = ".");
    ~TFTP();

    /**
     * Starts server.
     * Returns 0 if server is started successfully
     */
    int start();

    /**
     * Listens for incoming requests. Can be executed in blocking and non-blocking mode
     * @param waitFor true if blocking mode is required, false if non-blocking mode is required
     */
    int run(bool waitFor = true);

    /**
     * Stops server
     */
    void stop();

    void setSingleRunFilename(QString filename);

    bool isClosedSuccessfully();

    void setCommandWaitTimeout(uint32_t timeout);

    void setTIMode(bool mode);

    void setSplitModeSize(uint32_t newSplitModeSize);

    void setTftpBlockSize(int newTftpBlockSize);

    bool isTiboot3BinSent();

    float getProgress();

    void setProgressUpdateCallback(std::function<void(float)> func);

    QByteArray getLastFileName();

    void setOnReadSuccess(const std::function<void (QByteArray)> &newOnReadSuccess);

    bool hasError();

    void setError(bool error);

protected:
    void sendAck(uint16_t blockNum);
    void sendError(uint16_t code, const char *message);
    int waitForAck(uint16_t blockNum);

    /**
     * This method is called, when new read request is received.
     * Override this method and add implementation for your system.
     * @param file name of the file requested
     * @return return 0 if file can be read, otherwise return -1
     */
    virtual int onRead(const char *file);

    /**
     * This method is called, when new write request is received.
     * Override this method and add implementation for your system.
     * @param file name of the file requested
     * @return return 0 if file can be written, otherwise return -1
     */
    virtual int onWrite(const char *file);

    /**
     * This method is called, when new data are required to be read from file for sending.
     * Override this method and add implementation for your system.
     * @param buffer buffer to fill with data from file
     * @param len maximum length of buffer
     * @return return number of bytes read to buffer
     * @important if length of read data is less than len argument value, it is considered
     *            as end of file
     */
    virtual int onReadData(uint8_t *buffer, int len);

    /**
     * This method is called, when new data arrived for writing to file.
     * Override this method and add implementation for your system.
     * @param buffer buffer with received data
     * @param len length of received data
     * @return return number of bytes written
     */
    virtual int onWriteData(uint8_t *buffer, int len);

    /**
     * This method is called, when transfer operation is complete.
     * Override this method and add implementation for your system.
     */
    virtual void onClose();

private:
    uint16_t _port;
    std::unique_ptr<QUdpSocket> _socket{};
    QHostAddress _clientAddr;
    uint16_t _clientPort;
    uint8_t* _buffer{nullptr};
    uint32_t _readSize{0};
    QFile _curFile;
    QDir _path;
    bool _quit{false};
    QString _singleRunFilename{""};
    int _tftpBlockSize;
    int _tftpDataSize;
    uint32_t _splitModeSize{0x40000000}; // 1GiB
    // uint32_t _splitModeSize{10485760}; // 10MB
    uint32_t _tftpCommandWaitTimeoutMilliSec{30000};
    bool _tftpTIMode{false};
    bool _splittedFileMode{false};
    bool _tiboot3Sent{false};
    float _progress{0.0f};
    int _seekPartPos{0};
    bool _hasError{false};
    QByteArray _lastFileName;
    std::function<void(float)> _progressUpdateCallback;
    std::function<void(QByteArray)> _onReadSuccess;

    int processWrite();
    int processRead();
    int parseWrq();
    int parseRrq();
    int parseRq();
};

