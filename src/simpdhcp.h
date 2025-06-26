#ifndef SIMPDHCP_H
#define SIMPDHCP_H

#include <cstddef>
#include <qthread.h>
#include <stdint.h>
#include <vector>

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

enum class OpType : uint8_t {
    BOOTREQUEST = 1, // Client request for DHCP
    BOOTREPLY = 2    // Server reply to DHCP request
};

enum class HardwareType : uint8_t {
    Ethernet = 1,      // 10Mb Ethernet (IEEE 802.3)
    Experimental = 2,  // Experimental Ethernet
    TokenRing = 3,     // Token Ring (IEEE 802.5)
    ProNET = 4,        // ProNET Token Ring
    Ethernet_II = 6,   // Ethernet (802.3) with 802.2 LLC
    PPP = 0x20,        // Point-to-Point Protocol
    FDDI = 0x0F,       // Fiber Distributed Data Interface
    ATM = 0x10,        // Asynchronous Transfer Mode
    // Add other hardware types as needed
};

enum class OptionType : uint8_t {
    PAD = 0,
    SUBNET_MASK = 1,
    TIME_OFFSET = 2,
    ROUTERS = 3,
    TIME_SERVERS = 4,
    NAME_SERVERS = 5,
    DOMAIN_NAME_SERVER = 6,
    DOMAIN_NAME = 15,
    HOSTNAME = 12,
    BROADCAST_ADDRESS = 28,
    REQUESTED_IP = 50,
    IP_ADDRESS_LEASE_TIME = 51,
    DHCP_MESSAGE_TYPE = 53,
    SERVER_IDENTIFIER = 54,
    PARAMETER_REQUEST_LIST = 55,
    DHCP_OPTION_OVERLOAD = 52,
    TFTP_SERVER_NAME = 66,
    END = 255
};

enum class DhcpMessageType : uint8_t {
    DHCPDISCOVER = 1, // Client request for DHCP
    DHCPOFFER = 2,     // Server offer of an IP address
    DHCPREQUEST = 3,   // Client request for IP address or parameters
    DHCPDECLINE = 4,   // Client decline of an offered IP address
    DHCPACK = 5,       // Server acknowledgment of a client's request
    DHCPNAK = 6,       // Server negative acknowledgment
    DHCPRELEASE = 7,   // Client release of an IP address
    DHCPINFORM = 8     // Client request for information
};

enum class DhcpFlags : uint16_t {
    UNICAST = 0x0000,
    BROADCAST = 0x8000, // Broadcast flag (bit 15)
};

struct DhcpOption {
    OptionType type; // Option type
    uint8_t length;  // Length of the option value
    std::vector<uint8_t> value; // Option value
};

struct DhcpPacket {
    OpType op{};                            // Message op code / message type
    HardwareType htype{};                   // Hardware address type
    uint8_t hlen{};                         // Hardware address length
    uint8_t hops{};                         // Number of hops
    uint32_t xid{};                         // Transaction ID
    uint16_t secs{};                        // Seconds elapsed since the client began the address acquisition or renewal process
    DhcpFlags flags{};                      // Flags
    uint32_t ciaddr{};                      // Client IP address (if already in use)
    uint32_t yiaddr{};                      // 'Your' (client) IP address
    uint32_t siaddr{};                      // Server IP address
    uint32_t giaddr{};                      // Gateway IP address
    uint8_t chaddr[16]{};                   // Client hardware address
    char sname[64]{};                       // Server host name (optional)
    char file[128]{};                       // Boot file name (optional)
    uint8_t mcookie[4]{0x63, 0x82, 0x53, 0x63 }; // Magic
    uint8_t options[214];                   // Optional parameters field (variable length)
};

char const* optTypeToStr(OpType type);
char const* hardwareTypeToStr(HardwareType type);
char const* dhcpMessageTypeToStr(DhcpMessageType type);
char const* optionTypeToStr(OptionType type);
char const* dhcpFlagsToStr(DhcpFlags type);

DhcpPacket parseDhcpPacket(const uint8_t* data, size_t length);
DhcpPacket generateBootReply(const DhcpPacket& request, quint32 offeredIp, const char* serverIp, const char* serverName);
std::vector<DhcpOption> parseDhcpOptions(const uint8_t* options, size_t length);
bool initSocket(void);

#endif // SIMPDHCP_H
