#include "simpdhcp.h"
#include <cstring>
#include <qcoreapplication.h>
#include <qnetworkdatagram.h>
#include <qnetworkinterface.h>
#include <qprocess.h>
#include <qcommandlineparser.h>
#include <qtimer.h>
#include <qudpsocket.h>
#include <stdexcept>

char const* optTypeToStr(OpType type)
{
    switch (type) {
    case OpType::BOOTREPLY:
        return "OpType::BOOTREPLY";
    case OpType::BOOTREQUEST:
        return "OpType::BOOTREQUEST";
    default:
        return "Invalid Optype";
    }
}

char const* hardwareTypeToStr(HardwareType type)
{
    switch (type) {
    case HardwareType::ATM:
        return "HardwareType::ATM";
    case HardwareType::Ethernet:
        return "HardwareType::Ethernet";
    case HardwareType::Ethernet_II:
        return "HardwareType::Ethernet_II";
    case HardwareType::Experimental:
        return "HardwareType::Experimental";
    case HardwareType::TokenRing:
        return "HardwareType::TokenRing";
    case HardwareType::ProNET:
        return "HardwareType::ProNET";
    case HardwareType::PPP:
        return "HardwareType::PPP";
    case HardwareType::FDDI:
        return "HardwareType::FDDI";
    default:
        return "Invalid HardwareType";
    }
}

char const* dhcpMessageTypeToStr(DhcpMessageType type)
{
    switch (type) {
    case DhcpMessageType::DHCPDISCOVER:
        return "DhcpMessageType::DHCPDISCOVER";
    case DhcpMessageType::DHCPOFFER:
        return "DhcpMessageType::DHCPOFFER";
    case DhcpMessageType::DHCPREQUEST:
        return "DhcpMessageType::DHCPREQUEST";
    case DhcpMessageType::DHCPDECLINE:
        return "DhcpMessageType::DHCPDECLINE";
    case DhcpMessageType::DHCPACK:
        return "DhcpMessageType::DHCPACK";
    case DhcpMessageType::DHCPNAK:
        return "DhcpMessageType::DHCPNAK";
    case DhcpMessageType::DHCPRELEASE:
        return "DhcpMessageType::DHCPRELEASE";
    case DhcpMessageType::DHCPINFORM:
        return "DhcpMessageType::DHCPINFORM";
    default:
        return "Invalid DhcpMessageType";
    }
}

char const* optionTypeToStr(OptionType type)
{
    switch (type) {
    case OptionType::PAD:
        return "OptionType::PAD";
    case OptionType::SUBNET_MASK:
        return "OptionType::SUBNET_MASK";
    case OptionType::TIME_OFFSET:
        return "OptionType::TIME_OFFSET";
    case OptionType::ROUTERS:
        return "OptionType::ROUTERS";
    case OptionType::TIME_SERVERS:
        return "OptionType::TIME_SERVERS";
    case OptionType::NAME_SERVERS:
        return "OptionType::NAME_SERVERS";
    case OptionType::DOMAIN_NAME:
        return "OptionType::DOMAIN_NAME";
    case OptionType::HOSTNAME:
        return "OptionType::HOSTNAME";
    case OptionType::REQUESTED_IP:
        return "OptionType::REQUESTED_IP";
    case OptionType::IP_ADDRESS_LEASE_TIME:
        return "OptionType::IP_ADDRESS_LEASE_TIME";
    case OptionType::DHCP_MESSAGE_TYPE:
        return "OptionType::DHCP_MESSAGE_TYPE";
    case OptionType::SERVER_IDENTIFIER:
        return "OptionType::SERVER_IDENTIFIER";
    case OptionType::PARAMETER_REQUEST_LIST:
        return "OptionType::PARAMETER_REQUEST_LIST";
    case OptionType::DHCP_OPTION_OVERLOAD:
        return "OptionType::DHCP_OPTION_OVERLOAD";
    case OptionType::END:
        return "OptionType::END";
    default:
        return "Invalid OptionType";
    }
}

char const* dhcpFlagsToStr(DhcpFlags type)
{
    switch (type) {
    case DhcpFlags::UNICAST:
        return "DhcpFlags::UNICAST";
    case DhcpFlags::BROADCAST:
        return "DhcpFlags::BROADCAST";
    default:
        return "Invalid DhcpFlags";
    }
}

bool initSocket(void)
{
#ifdef _WIN32
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        qDebug() << "WSAStartup() failed with error:" << iResult;
        return false;
    }
#endif
    return true;
}

DhcpPacket parseDhcpPacket(const char* data, size_t length) {
    DhcpPacket packet{};
    uint32_t ofset = 0;

    if (length < (sizeof(DhcpPacket) - sizeof(DhcpPacket::options))) {
        return packet;
    }

    // Parse the DHCP packet
    packet.op = static_cast<OpType>(data[ofset++]);
    packet.htype = static_cast<HardwareType>(data[ofset++]);
    packet.hlen = data[ofset++];
    packet.hops = data[ofset++];
    packet.xid = (data[ofset] << 24) | (data[ofset + 1] << 16) | (data[ofset + 2] << 8) | data[ofset + 3];
    ofset += 4;
    packet.secs = (data[ofset] << 8) | data[ofset + 1];
    ofset += 2;
    packet.flags = static_cast<DhcpFlags>((data[ofset] << 8) | data[ofset + 1]);
    ofset += 2;
    packet.ciaddr = (data[ofset] << 24) | (data[ofset + 1] << 16) | (data[ofset + 2] << 8) | data[ofset + 3];
    ofset += 4;
    packet.yiaddr = (data[ofset] << 24) | (data[ofset + 1] << 16) | (data[ofset + 2] << 8) | data[ofset + 3];
    ofset += 4;
    packet.siaddr = (data[ofset] << 24) | (data[ofset + 1] << 16) | (data[ofset + 2] << 8) | data[ofset + 3];
    ofset += 4;
    packet.giaddr = (data[ofset] << 24) | (data[ofset + 1] << 16) | (data[ofset + 2] << 8) | data[ofset + 3];
    ofset += 4;

    // Copy the client hardware address
    memcpy(packet.chaddr, &data[ofset], sizeof(packet.chaddr));
    ofset += sizeof(packet.chaddr);

    // Copy the server name
    memcpy(packet.sname, &data[ofset], sizeof(packet.sname));
    ofset += sizeof(packet.sname);

    // Copy the boot file name
    memcpy(packet.file, &data[ofset], sizeof(packet.file));
    ofset += sizeof(packet.file);

    memcpy(packet.mcookie, &data[ofset], sizeof(packet.mcookie));
    ofset += sizeof(packet.mcookie);

    // Copy the options (if any)
    memcpy(packet.options, &data[ofset], std::min(sizeof(packet.options), length - ofset));

    return packet;
}

size_t generateBootReply(
    const DhcpPacket& request,
    QString& offeredIp,
    QString& bootFileName,
    QString& serverIp,
    QString& serverName,
    DhcpPacket& reply
)
{
    const uint32_t serverAddr{ inet_addr(serverIp.toStdString().c_str()) };
    const uint32_t serverBroadcastAddr{ serverAddr | inet_addr("0.0.0.255") };
    const uint32_t clientAddr { inet_addr(offeredIp.toStdString().c_str())};
    size_t len = 0;

    reply.op = OpType::BOOTREPLY;
    reply.htype = request.htype; // Use the same hardware type
    reply.hlen = request.hlen;   // Use the same hardware address length
    reply.hops = 0;              // No hops for the reply
    reply.xid = htonl(request.xid);     // Use the same transaction ID
    reply.secs = 0;              // Seconds elapsed
    reply.flags = request.flags;  // Use the same flags
    reply.ciaddr = request.ciaddr; // Client IP address (if already assigned)
    reply.yiaddr = clientAddr;     // 'Your' (client) IP address (the offered IP)
    reply.siaddr = serverAddr; // Server IP address
    reply.giaddr = request.giaddr; // Gateway IP address (if applicable)
    std::memcpy(reply.chaddr, request.chaddr, request.hlen); // Copy client hardware address

    len = std::min((qsizetype)sizeof(reply.sname) - 1, serverName.length());
    std::memcpy(reply.sname, serverName.toUtf8().data(), len);
    reply.sname[len] = 0;

    len = std::min((qsizetype)sizeof(reply.file), bootFileName.size());
    std::memcpy(reply.file, bootFileName.toUtf8().data(), len);
    reply.file[len] = 0;

    int indeks = 0;
    reply.options[indeks++] = static_cast<uint8_t>(OptionType::DHCP_MESSAGE_TYPE);
    reply.options[indeks++] = 1;
    reply.options[indeks++] = static_cast<uint8_t>(DhcpMessageType::DHCPOFFER);

    reply.options[indeks++] = static_cast<uint8_t>(OptionType::SUBNET_MASK);
    reply.options[indeks++] = 4;
    uint32_t* ip_cur = (uint32_t*)&reply.options[indeks];
    *ip_cur = serverAddr;
    indeks += 4;

    reply.options[indeks++] = static_cast<uint8_t>(OptionType::BROADCAST_ADDRESS);
    reply.options[indeks++] = 4;
    ip_cur = (uint32_t*)&reply.options[indeks];
    *ip_cur = serverBroadcastAddr;
    indeks += 4;

    reply.options[indeks++] = static_cast<uint8_t>(OptionType::DOMAIN_NAME_SERVER);
    reply.options[indeks++] = 4;
    ip_cur = (uint32_t*)&reply.options[indeks];
    *ip_cur = serverBroadcastAddr;
    indeks += 4;

    reply.options[indeks++] = static_cast<uint8_t>(OptionType::ROUTERS);
    reply.options[indeks++] = 4;
    ip_cur = (uint32_t*)&reply.options[indeks];
    *ip_cur = serverAddr;
    indeks += 4;

    const uint8_t serverIpStrSize = (uint8_t)serverIp.size();
    reply.options[indeks++] = static_cast<uint8_t>(OptionType::TFTP_SERVER_NAME);
    reply.options[indeks++] = serverIpStrSize;
    std::memcpy(reply.options + indeks, serverIp.toUtf8().data(), serverIpStrSize);
    indeks += serverIpStrSize;

    // End option
    reply.options[indeks] = static_cast<uint8_t>(OptionType::END);

    return (sizeof(DhcpPacket) - sizeof DhcpPacket::options) + indeks - 1;
}

enum ReturnCodes
{
    SUCCESS,
    INVALID_ARG,
    IFACE_SETUP_FAILED,
    SOCKET_INIT_FAILED,
    SOCKET_OPT_TIMEOUT_FAILED,
    SOCKET_OPT_BROADCAST_FAILED,
    SOCKET_OPT_BINDTODEV_FAILED,
    PORT_BIND_FAILED,
    DHCP_TIMEOUT,
    NO_DATAGRAM,
    SEND_REPLY_FAILED,
    SEND_REPLY_TIMEOUT,
};

bool setInterfaceSettings(const QString &interface, const QString ipAddr, const QString &speed, const QString &duplex)
{
#if defined(Q_OS_UNIX)
    QStringList args;
    QStringList ipArgs;
    QStringList netManArgs;

    QProcess ipProcess;
    QProcess process;
    QProcess netManKiller;

    netManArgs << "systemctl" << "stop" << "NetworkManager.service";
    netManKiller.start("pkexec", netManArgs);
    netManKiller.waitForFinished();

    args << "ethtool" <<"-s" << interface << "speed" << speed << "duplex" << duplex;
    qDebug() << args;

    ipArgs << "ip" << "addr" << "add" << (ipAddr + "/24") << "dev" << interface;
    qDebug() << ipArgs;


    process.start("pkexec", args);
    ipProcess.start("pkexec", ipArgs);
#elif defined(Q_OS_WIN)
    QString command = QString("powershell.exe \
        -ArgumentList \"-ExecutionPolicy Bypass -Command `\"Set-NetAdapterAdvancedProperty \
        -Name 'Ethernet' -DisplayName 'Link Speed & Duplex' -DisplayValue '%1 Mbps %2 Duplex'`\"\" -Verb RunAs")
           .arg(speed, duplex);
    QString ipCommand = QString("powershell.exe \
                              -ArgumentList \"-ExecutionPolicy Bypass -Command `\"Set-NetAdapterAdvancedProperty \
                              -Name 'Ethernet' -DisplayName 'Link Speed & Duplex' -DisplayValue '%1 Mbps %2 Duplex'`\"\" -Verb RunAs")
                          .arg(speed, duplex);
    QProcess process;
    QProcess ipProcess;

    process.start("powershell.exe", QStringList() << "Start" << command);
    ipProcess.start("powershell.exe", QStringList() << "Start" << ipCommand);
#else
#error "Unsupported platform";
    return;
#endif

    process.waitForFinished();
    ipProcess.waitForFinished();
    // Check for errors
    if (process.exitStatus() != QProcess::NormalExit || ipProcess.exitStatus() != QProcess::NormalExit) {
        qDebug() << "Command crashed.";
        return false;
    } else {
        qDebug() << "Command output:" << process.readAllStandardOutput();
        qDebug() << "Command error:" << process.readAllStandardError();
        return true;
    }
}

void revertInterfaceSettings(const QString &interface, const QString &ipAddr)
{
#if defined(Q_OS_UNIX)
    QStringList args;
    QStringList ipArgs;
    QStringList netManArgs;

    QProcess ipProcess;
    QProcess process;
    QProcess netManKiller;

    args << "ethtool" <<"-s" << interface << "autoneg" << "on";
    qDebug() << args;

    ipArgs << "ip" << "addr" << "del" << (ipAddr + "/24") << "dev" << interface;
    qDebug() << ipArgs;


    process.start("pkexec", args);
    ipProcess.start("pkexec", ipArgs);
#elif defined(Q_OS_WIN)
    QString command = QString("Start -FilePath powershell.exe \
                              -ArgumentList \"-ExecutionPolicy Bypass -Command `\"Set-NetAdapterAdvancedProperty \
                              -Name '%1' -DisplayName 'Link Speed & Duplex' -DisplayValue 'Auto Negotiation'`\"\" -Verb RunAs").arg(interface);
    QString ipCommand = QString("Start -FilePath powershell.exe \
                                -ArgumentList \"-ExecutionPolicy Bypass -Command `\"Set-NetAdapterAdvancedProperty \
                                -Name '%1' -DisplayName 'Link Speed & Duplex' -DisplayValue 'Auto Negotiation'`\"\" -Verb RunAs").arg(interface);
    QProcess ipProcess;
    QProcess process;

    process.start("powershell.exe", QStringList() << "-Command" << command);
    process.start("powershell.exe", QStringList() << "-Command" << command);
#else
    qDebug() << "Unsupported platform";
#endif

    process.waitForFinished();
    ipProcess.waitForFinished();

    netManArgs << "systemctl" << "start" << "NetworkManager.service";
    netManKiller.start("pkexec", netManArgs);
    netManKiller.waitForFinished();
    return;
}

void cleanSocket(int socket)
{
    if(!(socket <= 0))
    {
#if defined(Q_OS_UNIX)
        close(socket);
#elif defined(Q_OS_WIN)
        closesocket(socket);
        WSACleanup();
#else
#error "Unsupported platform!";
#endif
    }
}

ReturnCodes doWork(QString& interface, QString& speed, QString& duplex, QString& serverIp, QString& offeredIp, QString& bootFile, QString& serverName)
{
    quint16 senderPort;
    int sock = 0;
    struct sockaddr_in dest;
    char packet[4096];

    if(false == setInterfaceSettings(interface, serverIp, speed, duplex))
    {
        qDebug() << "setup interface failed!";
        return IFACE_SETUP_FAILED;
    }

    QScopeGuard guard {
        [serverIp, interface, sock]()
        {
            revertInterfaceSettings(interface, serverIp);
            cleanSocket(sock);
        }
    };

    if(false == initSocket())
    {
        qDebug() << "initSocket() failed!";
        return SOCKET_INIT_FAILED;
    }

    // Create a raw socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        qDebug() << "Socket creation failed";
        return SOCKET_INIT_FAILED;
    }

    struct timeval timeout;
    timeout.tv_sec = 60;
    timeout.tv_usec = 0;
    if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout)) < 0) {
        qDebug("Set socket option recv timeout failed");
        return SOCKET_OPT_TIMEOUT_FAILED;
    }

    uint32_t broadcast = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char*)&broadcast, sizeof(broadcast)) < 0)
    {
        qDebug() << "Set socket option broadcast enable failed: " << strerror(errno);
        return SOCKET_OPT_BROADCAST_FAILED;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(67);

    if(bind(sock, (struct sockaddr*)&addr, sizeof addr) < 0)
    {
        qDebug() << "Socket bind to port failed!" << strerror(errno);
        return PORT_BIND_FAILED;
    }

#if defined(Q_OS_LINUX)
    if(setsockopt(sock, SOL_SOCKET, SO_BINDTODEVICE, interface.toUtf8().data(), interface.size()) < 0)
    {
        qDebug() << "Socket bind to device failed!";
        return SOCKET_OPT_BINDTODEV_FAILED;
    }
#else
    // send empty packet to bind socket to interface
    char buf = 'G';
    struct sockaddr_in bcastAddr{
        AF_INET,
        htons(4096),
        inet_addr("10.42.0.255")
    };
    size_t bindSendSize = sendto(sock, &buf, sizeof(buf), 0, (struct sockaddr*)&bcastAddr, sizeof(bcastAddr));
    buf = 'F';

    if(1 != bindSendSize || 1 != recv(sock, &buf, sizeof(buf), 0))
    {
        qDebug() << "Socket bind to device failed!";
        return SOCKET_OPT_BINDTODEV_FAILED;
    }

    if(buf != 'G')
    {
        qDebug() << "Socket bind to device failed! Received packet not correct";
        return SOCKET_OPT_BINDTODEV_FAILED;
    }
#endif

    uint8_t retry = 5;
    while(retry-- > 0)
    {
        // Receive a packet
        char buffer[4096];
        struct sockaddr_in source;
        socklen_t addr_len = sizeof(source);

        // Receive a packet
        int bytes_received = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&source, &addr_len);
        if (bytes_received < 0) {
            qDebug() << "Packet receive failed";
            return DHCP_TIMEOUT;
        }

        DhcpPacket dpacket = parseDhcpPacket(buffer, bytes_received);
        DhcpPacket reply{};
        auto reply_size = generateBootReply(dpacket, offeredIp, bootFile, serverIp, serverName, reply);

        source.sin_addr.s_addr = htonl(INADDR_BROADCAST); // Change to your target IP

        auto sendSize = sendto(sock, (char*)&reply, reply_size, 0, (struct sockaddr*)&source, addr_len);
        if(sendSize == -1 || sendSize != reply_size)
        {
            qDebug() << "Send reply failed!";
            return SEND_REPLY_FAILED;
        }
    }

    return SUCCESS;
}

#if defined(Q_OS_UNIX)
#define DEFAULT_IFACE "eno1"
#elif defined(Q_OS_WIN)
#define DEFAULT_IFACE "Ethernet"
#else
#error "Unsupported platform!"
#endif
#define DEFAULT_SPEED "100"
#define DEFAULT_DUPLEX "full"
#define DEFAULT_SERVER_IP "10.42.0.11"
#define DEFAULT_CLI_IP "10.42.0.12"
#define DEFAULT_BOOTFILE "tiboot3.bin"
#define DEFAULT_SERVER_NAME ""

int main(int argc, char* argv[])
{
    QCoreApplication app{argc, argv};

    QCommandLineParser parser;
    parser.addOptions({
        {{"i", "interface"},
            QCoreApplication::translate("main", "Interface name (Ex: Ethernet)"),
            QCoreApplication::translate("main", "interface")},
        {{"s", "speed"},
            QCoreApplication::translate("main", "Interface speed (1/10/100/1000)."),
            QCoreApplication::translate("main", "speed")},
        {{"d", "duplex"},
            QCoreApplication::translate("main", "Duplex type (half/full)."),
            QCoreApplication::translate("main", "duplex")},
        {{"si", "server-ip"},
            QCoreApplication::translate("main", "Server ip (this pc) address (Ex: 10.42.0.1)."),
            QCoreApplication::translate("main", "server-ip")},
        {{"oi", "offered-ip"},
            QCoreApplication::translate("main", "Client ip (served pc) address (Ex: 10.42.0.2)."),
            QCoreApplication::translate("main", "offered-ip")},
        {{"sn", "server-name"},
            QCoreApplication::translate("main", "Server name"),
            QCoreApplication::translate("main", "server-name")},
        {{"f", "bootfile"},
            QCoreApplication::translate("main", "Bootfile name which will be pulled from tftp server (Ex: tiboot3.bin)."),
            QCoreApplication::translate("main", "bootfile")},
    });

    parser.addHelpOption();
    parser.process(app);

    QString speed { DEFAULT_SPEED };
    QString interface { DEFAULT_IFACE };
    QString duplex { DEFAULT_DUPLEX };
    QString serverIp { DEFAULT_SERVER_IP };
    QString offeredIp { DEFAULT_CLI_IP };
    QString bootFile { DEFAULT_BOOTFILE };
    QString serverName { DEFAULT_SERVER_NAME };

    if(parser.isSet("interface"))
    {
        interface = parser.value("interface");
    }

    if(parser.isSet("speed"))
    {
        speed = parser.value("speed");
    }

    if(parser.isSet("duplex"))
    {
        duplex = parser.value("duplex");
    }

    if(parser.isSet("server-ip"))
    {
        serverIp = parser.value("server-ip");
    }

    if(parser.isSet("offered-ip"))
    {
        offeredIp = parser.value("offered-ip");
    }

    if(parser.isSet("server-name"))
    {
        serverName = parser.value("server-name");
    }

    if(parser.isSet("bootfile"))
    {
        bootFile = parser.value("bootfile");
    }

    QTimer::singleShot(0, &app, [&interface, &speed, &duplex, &serverIp, &offeredIp, &bootFile, &serverName]()
    {
        QCoreApplication::exit(doWork(interface, speed, duplex, serverIp, offeredIp, bootFile, serverName));
    });

    return app.exec();
}
