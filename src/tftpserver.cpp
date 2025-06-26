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

#include <qlogging.h>
#include <QUdpSocket>
#include <qthread.h>
#include <tftpserver.h>

static char TAG[] = "[simptftp]";

TFTP::TFTP(uint16_t port, int tftp_block_size, QString target_dir)
    : _port{ port },
    _tftpBlockSize{tftp_block_size},
    _tftpDataSize{_tftpBlockSize + 4},
    _path{target_dir}
{
}

TFTP::~TFTP()
{
}

int TFTP::processWrite()
{
    int result = -1;
    int totalSize = 0;
    int nextBlockNum = 1;
    while (1)
    {
        if(false == _socket->waitForReadyRead(2000))
        {
            return -1;
        }

        if (_socket->hasPendingDatagrams())
        {
            _readSize = _socket->readDatagram((char*)_buffer, _tftpDataSize, &_clientAddr, &_clientPort);
            qDebug() << TAG << "Received packet from" << _clientAddr.toString() << ":" << _clientPort;
            qDebug() << TAG << "Data:" << _buffer; // Print the data in hex format
        }
        else
        {
            qDebug() << TAG << "No datagram inside received packat!!!";
            return -1;
        }

        if (_readSize < 0)
        {
            qDebug(TAG, "error on receive");
            break;
        }

        uint16_t code = ntohs(*(uint16_t*)(&_buffer[0]));
        if ( code != TFTP_CMD_DATA )
        {
            qDebug() << TAG << "not data packet received: [" << code << "]";
            qDebug() << TAG << _buffer << _readSize;
            if ( ( code == TFTP_CMD_WRQ ) && ( nextBlockNum == 1 ) )
            {
                // some clients repeat request several times
                sendAck(0);
                continue;
            }
            result = 1; // repeat
            break;
        }
        uint16_t blockNum = ntohs(*(uint16_t*)(&_buffer[2]));
        int dataSize = _readSize - 4;
        sendAck(blockNum);
        if ( blockNum < nextBlockNum )
        {
            // Maybe this is dup, ignore it
            qDebug() << TAG << "dup packet received: [" << blockNum << "], expected [" << nextBlockNum << "]";
        }
        else
        {
            nextBlockNum++;
            totalSize += dataSize;
            onWriteData(&_buffer[4], dataSize);
            qDebug() << TAG << "Block size: " <<  dataSize;
        }
        if (_readSize < _tftpDataSize)
        {
            qDebug() << TAG << "file received: (" << totalSize << " bytes)";
            result = 0;
            break;
        }
    }
    return result;
}

int TFTP::processRead()
{
    int result = -ERR_NOT_DEFINED;
    int blockNum = 1;
    int totalSize = 0;
    int count = 0;
    qDebug() << "process read loop started";

    for(;;)
    {
        *(uint16_t*)(&_buffer[0]) = htons(TFTP_CMD_DATA);
        *(uint16_t*)(&_buffer[2]) = htons(blockNum);

        if(_splittedFileMode && ((totalSize + _tftpBlockSize) > _splitModeSize))
        {
            _splittedFileMode = false;
            _readSize = 0;
        }
        else
        {
            _readSize = onReadData( &_buffer[4], _tftpBlockSize );
            if (_readSize < 0)
            {
                qDebug(TAG, "Failed to read data from file");
                sendError(ERR_ILLEGAL_OPERATION, "failed to read file");
                result = -ERR_ILLEGAL_OPERATION;
                break;
            }
        }


        // qDebug() << TAG <<  "Sending data to " << _clientAddr.toString().data() <<
        //         ", blockNumber=" << blockNum << ", size=" << dataSize;

        for(int r=0; r<3; r++)
        {
            auto sendSize = _readSize + 4;
            auto writeSize = _socket->writeDatagram((char*)_buffer, sendSize, _clientAddr, _clientPort);
            if(-1 == writeSize || writeSize != sendSize)
            {
                qDebug() << TAG << "_splittedFileMode: " << _splittedFileMode;
                qDebug() << TAG << "_tftpBlokSize: " << _tftpBlockSize;
                qDebug() << TAG << "_splitModeSize: " << _splitModeSize;
                qDebug() << TAG << "totalSize: " << totalSize;
                qDebug() << TAG << "sendSize: " << sendSize;
                qDebug() << TAG << "Extended block size request reject failed! Expected " << _readSize + 4 << "got " << writeSize;
                result = -1;
                break;
            }

            if (waitForAck(blockNum) == 0)
            {
                result = 0;
                break;
            }

            qDebug() << TAG << "No ack/wrong ack, retrying";
            result = -1;

            // TI ROM Bootloader do not send last ack ignore it
            if(writeSize < _tftpBlockSize && _tftpTIMode)
            {
                qDebug() << "TI Mode skipping last ack!";
                result = 0;
                break;
            }
        }
        if ( result < 0 )
        {
            break;
        }

        _progressUpdateCallback(_progress);
        totalSize += _readSize;

        // update progress
        if(_splittedFileMode)
        {
            _progress = (float)((float)(_splitModeSize * _seekPartPos) + (float)totalSize) / (float)_curFile.size();
        }
        else
        {
            _progress = (float)totalSize / (float)_curFile.size();
        }


        if (_readSize < _tftpBlockSize)
        {
            _lastFileName = QByteArray::fromStdString(std::filesystem::path( _curFile.fileName().toStdString()).filename().string());
            if(_lastFileName == "uniflash")
            {
                _lastFileName.append(std::to_string(_seekPartPos));
                qDebug() << "_lastFileName: " << _lastFileName;
            }

            qDebug() << TAG << "Sent file " << _lastFileName << "(" << totalSize << " bytes )";
            if(_lastFileName == "tiboot3.bin")
            {
                _tiboot3Sent = true;
            }

            totalSize = 0;
            result = 0;
            break;
        }
        blockNum++;
    }
    if (result >= 0 && _onReadSuccess != nullptr) _onReadSuccess(_lastFileName);
    return result;
}

void TFTP::sendAck(uint16_t blockNum)
{
    uint8_t data[4];

    *(uint16_t*)(&data[0]) = htons(TFTP_CMD_ACK);
    *(uint16_t*)(&data[2]) = htons(blockNum);
    qDebug() << TAG <<  "ack to " << _clientAddr.toString().data() << ", blockNumber=" << blockNum;

    auto sendSize = sizeof(data);
    auto writeSize = _socket->writeDatagram((char*)data, sendSize, _clientAddr, _clientPort);
    if(-1 == writeSize || writeSize != sendSize)
    {
        qDebug() << TAG << "Extended block size request reject failed! Expected " << sendSize << "got " << writeSize;
    }
}

void TFTP::sendError(uint16_t code, const char *message)
{
    *(uint16_t *)(&_buffer[0]) = htons(TFTP_CMD_ERROR);
    *(uint16_t *)(&_buffer[2]) = htons(code);
    strcpy((char *)(&_buffer[4]), message);
    auto sendSize = 4 + strlen(message) + 1;
    auto writeSize = _socket->writeDatagram((char*)_buffer, sendSize, _clientAddr, _clientPort);
    if(-1 == writeSize || writeSize != sendSize)
    {
        qDebug() << TAG << "Extended block size request reject failed! Expected " << sendSize + 4 << "got " << writeSize;
    }

    if(false == _socket->waitForBytesWritten())
    {
        qDebug() << TAG << "Extended block size request reject failed!";
    }
}

int TFTP::waitForAck(uint16_t blockNum)
{
    uint8_t data[4];
    qint64 readSize = 0;

    // qDebug() << TAG << "waiting for ack";

    if(false == _socket->waitForReadyRead(2000))
    {
        return -ERR_PROC_TIMEOUT;
    }

    if (_socket->hasPendingDatagrams())
    {
        readSize = _socket->readDatagram((char*)data, sizeof(data), &_clientAddr, &_clientPort);
        // qDebug() << TAG << "Received packet from" << _clientAddr.toString() << ":" << _clientPort;
        // qDebug() << TAG << "Data:" << data; // Print the data in hex format
    }
    else
    {
        qDebug() << TAG << "No datagram inside received packat!!!";
        return -ERR_NOT_DEFINED;
    }

    uint16_t cmd = ntohs(*(uint16_t *)(&data[0]));
    if (readSize != sizeof(data) || (cmd != TFTP_CMD_ACK))
    {
        qDebug() << TAG << "received wrong ack packet: " << cmd;
        sendError(ERR_NOT_DEFINED, "incorrect ack");
        return -ERR_NOT_DEFINED;
    }

    if (ntohs(*(uint16_t *)(&data[2])) != blockNum)
    {
        qDebug() << TAG << "received ack not in order";
        return 1;
    }
    return 0;
}

int TFTP::parseWrq()
{
    uint8_t *ptr = (uint8_t*)(_buffer + 2);
    char *filename = (char *)ptr;
    ptr += strlen(filename) + 1;
    char *mode = (char *)ptr;
    ptr += strlen(mode) + 1;
    if ( onWrite(filename) < 0)
    {
        qDebug() << TAG << "failed to open file " <<  filename << " for writing";
        sendError(ERR_ACCESS_VIOLATION, "cannot open file");
        return -ERR_ACCESS_VIOLATION;
    }
    if ( (ptr - _buffer < _readSize) && !strcmp((char *)ptr, "blksize") )
    {
        uint8_t data[] = { 0, 6, 'b', 'l', 'k', 's', 'i', 'z', 'e', 0, '5', '1', '2', 0 };
        if(-1 == _socket->writeDatagram((char*)data, sizeof(data), _clientAddr, _clientPort))
        {
            qDebug() << TAG << "Extended block size request reject failed!";
            return -1;
        }

        qDebug() << TAG << "Extended block size is requested. rejecting";
    }
    else
    {
        sendAck(0);
    }
    qDebug() << TAG << "receiving file: " << filename;
    return 0;
}

int TFTP::parseRrq()
{
    uint8_t *ptr = _buffer + 2;
    char *filename = (char *)ptr;
    ptr += strlen(filename) + 1;
    char *mode = (char *)ptr;
    ptr += strlen(mode) + 1;
    if ( onRead(filename) < 0)
    {
        qDebug() << TAG << "failed to open file " << filename << "for reading";
        sendError(ERR_FILE_NOT_FOUND, "cannot open file");
        return -ERR_FILE_NOT_FOUND;
    }
    qDebug() << TAG << "sending file: " << filename;
    return 0;
}


int TFTP::parseRq()
{
    int result = ERR_ILLEGAL_OPERATION;
    for(;;)
    {
        qDebug() << TAG << _buffer << _readSize;
        uint16_t cmd = ntohs(*(uint16_t*)(&_buffer[0])); /* parse command */
        switch (cmd)
        {
            case TFTP_CMD_WRQ:
                result = parseWrq();
                if (result == 0)
                {
                    result = processWrite();
                    onClose();
                }
                else
                {
                    result = 0; // it is ok since parsing is not network issue
                }
                break;
            case TFTP_CMD_RRQ:
                result = parseRrq();
                if (result == 0)
                {
                    result = processRead();
                    onClose();
                }
                else
                {
                    result = 0; // it is ok since parsing is not network issue
                }
                break;
            default:
                qDebug() << TAG << "unknown command " << cmd;
        }
        if (result <= 0)
        {
            break;
        }
    }
    return result;
}

int TFTP::start()
{
    if (_socket.get() != nullptr)
    {
        qDebug() << TAG << "already started!";
        return 0;
    }
    _socket.reset(new QUdpSocket);

    if(_buffer != nullptr)
    {
        delete[] _buffer;
    }
    _buffer = new uint8_t[_tftpDataSize];

    if (false == _socket->bind(QHostAddress::AnyIPv4, _port, QUdpSocket::ReuseAddressHint))
    {
        qDebug() << TAG << "binding error";
        return -ERR_PORT_BIND_FAILED;
    }

    _socket->flush();

    qDebug() << TAG <<  "Started on port " << _port
             << ", blocksize " << _tftpBlockSize
             << ", directory " << _path.absolutePath();
    return 0;
}

int TFTP::run(bool waitFor)
{
    if(_quit)
        return 0;

    if(false == _socket->waitForReadyRead(_tftpCommandWaitTimeoutMilliSec))
    {
        // qDebug() << "[simptftp] No packet received";
        return -ERR_RECV_TIMEOUT;
    }
    else
    {
        qDebug() << "[simptftp] Packet received";
    }

    if (_socket->hasPendingDatagrams())
    {
        _readSize = _socket->readDatagram((char*)_buffer, _tftpDataSize, &_clientAddr, &_clientPort);
        qDebug() << TAG << "Received packet from" << _clientAddr.toString() << ":" << _clientPort;
        qDebug() << TAG << "Data:" << _buffer; // Print the data in hex format
    }
    else
    {
        qDebug() << TAG << "No datagram inside received packat!!!";
        return -1;
    }

    return parseRq();
}

void TFTP::stop()
{
    if (_socket.get() != nullptr)
    {
        qDebug() << TAG << "Stopped";
        _socket.reset(nullptr);
        if(_buffer != nullptr)
        {
            delete[] _buffer;
        }
        _buffer = nullptr;
    }
}

void TFTP::setSingleRunFilename(QString filename)
{
    _singleRunFilename = filename;
}

bool TFTP::isClosedSuccessfully()
{
    // if _quit flag set process completed successfully
    return _quit;
}

void TFTP::setCommandWaitTimeout(uint32_t timeout)
{
    _tftpCommandWaitTimeoutMilliSec = timeout;
}

void TFTP::setTIMode(bool mode)
{
    _tftpTIMode = mode;
}

int TFTP::onRead(const char *file)
{
    if(_curFile.isOpen())
    {
        _curFile.close();
    }

    _curFile.setFileName(_path.absoluteFilePath(file));

    if(_curFile.fileName().contains("uniflash"))
    {
        qDebug() << "[simptftp] file mode is uniflash!";
        // file that needs to be splitted 1Gib parts
        QString filename{ _curFile.fileName().toUtf8() };
        size_t offset = filename.indexOf("uniflash");
        _curFile.setFileName(_path.absoluteFilePath("uniflash"));

        if(offset != -1)
        {
            offset += strlen("uniflash");
            _seekPartPos = std::stoi(filename.mid(offset).toStdString());
            qDebug() << "opening: " << _curFile.fileName();
            if(false == _curFile.open(QIODeviceBase::ReadOnly))
            {
                qDebug() << "file open failed: " << _curFile.errorString();
                return -ERR_FILE_NOT_FOUND;
            }

            _splitModeSize = _curFile.size() / 10;
            qDebug() << TAG << "current file is now: " << _curFile.fileName()
                     << "with offset: " << _seekPartPos
                     << "filesize: " << _curFile.size()
                     << "partsize: " << _splitModeSize;

            if(_splitModeSize % 512 != 0)
            {
                qDebug() << "image part size not multiples of 512 this cannot write to mmc";
                return -ERR_ILLEGAL_OPERATION;
            }

            qsizetype seekPos = _seekPartPos * _splitModeSize;
            if(false == _curFile.seek(seekPos))
            {
                qDebug() << "set file offset failed!";
            }

            _splittedFileMode = true;
            return 0;
        }
    }

    if(false == _curFile.open(QIODeviceBase::ReadOnly))
    {
        return -ERR_FILE_NOT_FOUND;
    }


    qDebug() << TAG << "current file is now: " << file;
    return 0;
}

int TFTP::onWrite(const char *file)
{
    qDebug() << "onWrite(): " << file;
    return -ERR_NOT_IMPLEMENTED;
}

int TFTP::onReadData(uint8_t *buffer, int len)
{
    return _curFile.read((char*)buffer, len);
}

int TFTP::onWriteData(uint8_t *buffer, int len)
{
    return -ERR_NOT_IMPLEMENTED;
}

void TFTP::onClose()
{
    _curFile.close();
    return;
}

void TFTP::setOnReadSuccess(const std::function<void (QByteArray)> &newOnReadSuccess)
{
    _onReadSuccess = newOnReadSuccess;
}

bool TFTP::isTiboot3BinSent()
{
    bool res = _tiboot3Sent;
    _tiboot3Sent = false;
    return res;
}

float TFTP::getProgress()
{
    return _progress;
}

void TFTP::setProgressUpdateCallback(std::function<void(float)> func)
{
    _progressUpdateCallback = func;
}

QByteArray TFTP::getLastFileName()
{
    return _lastFileName;
}

void TFTP::setTftpBlockSize(int newTftpBlockSize)
{
    _tftpBlockSize = newTftpBlockSize;
    _tftpDataSize = _tftpBlockSize + 4;
}

void TFTP::setSplitModeSize(uint32_t newSplitModeSize)
{
    _splitModeSize = newSplitModeSize;
}
