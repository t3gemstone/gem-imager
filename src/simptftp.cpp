#include <QTimer>
#include <qcommandlineparser.h>
#include <qcoreapplication.h>
#include <qdir.h>
#include <tftpserver.h>

int main(int argc, char* argv[])
{
    QCoreApplication app{argc, argv};

    QCommandLineParser parser;
    parser.addOptions({
        {{"b", "blocksize"},
            QCoreApplication::translate("main", "TFTP block size"),
            QCoreApplication::translate("main", "blocksize")},
        // A boolean option with multiple names (-f, --force)
        {{"p", "port"},
            QCoreApplication::translate("main", "TFTP port."),
            QCoreApplication::translate("main", "port")},
        // An option with a value
        {{"t", "target-directory"},
            QCoreApplication::translate("main", "Copy all source files into <directory>."),
            QCoreApplication::translate("main", "directory")},
        {{"s", "single-run"},
            QCoreApplication::translate("main", "Serve only <filename> and exit."),
            QCoreApplication::translate("main", "filename")},
    });

    parser.addHelpOption();
    parser.process(app);

    uint16_t port = TFTP_DEFAULT_PORT;
    int32_t tftpBlocksize = TFTP_DEFAULT_BLOCK_SIZE;
    QString targetDirectory = app.applicationDirPath();

    if(parser.isSet("port"))
    {
        bool ok = false;
        port = parser.value("port").toInt(&ok);
        if(!ok || port > std::numeric_limits<uint16_t>::max())
        {
            port = TFTP_DEFAULT_PORT;
            qDebug() << "Port is not valid (" << parser.value("port") << ") using default port" << port;
        }
    }

    if(parser.isSet("blocksize"))
    {
        bool ok = false;
        tftpBlocksize = parser.value("blocksize").toInt(&ok);
        if(!ok)
        {
            tftpBlocksize = TFTP_DEFAULT_BLOCK_SIZE;
            qDebug() << "Blocksize is not valid (" << parser.value("blocksize") << ") using default blocksize " << tftpBlocksize;
        }
    }

    if(parser.isSet("target-directory"))
    {
        targetDirectory = parser.value("target-directory");
        if(!QDir{targetDirectory}.exists())
        {
            targetDirectory = app.applicationDirPath();
            qDebug() << "Target directory not valid (" << parser.value("target-directory")  << ") using default target directory" << targetDirectory;
        }
    }

    TFTP server{port, tftpBlocksize, targetDirectory};

    if(parser.isSet("single-run"))
    {
        QString f = parser.value("single-run");
        if(!QDir{targetDirectory}.exists())
        {
            qDebug() << "Single run file is not valid (" << f << ")";
            return -1;
        }
        server.setSingleRunFilename(f);
    }

    QTimer::singleShot(0, &app, [tftpBlocksize, port, targetDirectory, &server, &parser]()
    {
        if (0 > server.start())
        {
            qDebug() << "[simptftp]" << "server init failed!";
            return;
        }

        while (server.run() >= 0);
        server.stop();
        if(parser.isSet("single-run"))
        {
            QCoreApplication::exit(server.isClosedSuccessfully() ? 0: 1);
        }
        else
        {
            QCoreApplication::quit();
        }
    });

    return app.exec();
}
