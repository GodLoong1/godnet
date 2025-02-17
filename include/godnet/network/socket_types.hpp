#pragma once

#ifndef GODNET_NETWORK_SOCKET_TYPES_HPP
#define GODNET_NETWORK_SOCKET_TYPES_HPP

#include "godnet/config.hpp"

#include <cstdint>

#if defined(GODNET_LINUX)
    #include <sys/socket.h>
    #include <sys/types.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
#elif defined(GODNET_WINDOWS)
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
#endif

namespace godnet
{

#if defined(GODNET_LINUX)
    using socket_t = std::int32_t;
    using sockaddr_t = struct sockaddr;
    using sockaddr_in4_t = struct sockaddr_in;
    using sockaddr_in6_t = struct sockaddr_in6;
    using socklen_t = socklen_t;
    static constexpr socket_t invalid_socket = -1;
#elif defined(GODNET_WINDOWS)
    using socket_t = SOCKET;
    using sockaddr_t = struct sockaddr;
    using sockaddr_in4_t = struct sockaddr_in;
    using sockaddr_in6_t = struct sockaddr_in6;
    using socklen_t = std::int32_t;
    static constexpr socket_t invalid_socket = INVALID_SOCKET;
#endif

}

#endif
