#include "godnet/network/endpoint.hpp"

#include <stdexcept>

#if defined(GODNET_LINUX)
    #include <arpa/inet.h>
#endif

namespace god
{

class EndpointAddressException : std::runtime_error
{
public:
    using runtime_error::runtime_error;
};

Endpoint::Endpoint() noexcept
: data_()
{
    data_.v4.sin_family = AF_INET;
    data_.v4.sin_port = 0;
    data_.v4.sin_addr.s_addr = INADDR_ANY;
}

Endpoint::Endpoint(const std::string_view& address, std::uint16_t port)
: data_()
{
    if (::inet_pton(AF_INET, address.data(), &data_.v4.sin_addr) == 1)
    {
        data_.v4.sin_family = AF_INET;
        data_.v4.sin_port = ::htons(port);
    }
    else if (::inet_pton(AF_INET6, address.data(), &data_.v6.sin6_addr) == 1)
    {
        data_.v6.sin6_family = AF_INET6;
        data_.v6.sin6_port = ::htons(port);
    }
    else
    {
        throw EndpointAddressException("Invalid Address");
    }
}

std::uint16_t Endpoint::port() const noexcept
{
    return ::ntohs(isV4() ? data_.v4.sin_port : data_.v6.sin6_port);
}

std::string Endpoint::ip() const noexcept
{
    char ip[256]{};
    auto addr = isV4() ? (const void*)&data_.v4.sin_addr : (const void*)&data_.v6.sin6_addr;
    ::inet_ntop(family(), addr, ip, sizeof(ip));
    return ip;
}

std::size_t Endpoint::getSockLen() const noexcept
{
    return isV4() ? sizeof(data_.v4) : sizeof(data_.v6);
}

bool Endpoint::isV4() const noexcept
{
    return family() == AF_INET;
}

bool Endpoint::isV6() const noexcept
{
    return family() == AF_INET6;
}

bool Endpoint::isLoopback() const noexcept
{
    if (isV4())
    {
        return (::ntohl(data_.v4.sin_addr.s_addr) & 0xFF000000) == 0x7F000000;
    }
    return data_.v6.sin6_addr.s6_addr[0] == 0 &&
           data_.v6.sin6_addr.s6_addr[0] == 0 &&
           data_.v6.sin6_addr.s6_addr[1] == 0 &&
           data_.v6.sin6_addr.s6_addr[2] == 0 &&
           data_.v6.sin6_addr.s6_addr[3] == 0 &&
           data_.v6.sin6_addr.s6_addr[4] == 0 &&
           data_.v6.sin6_addr.s6_addr[5] == 0 &&
           data_.v6.sin6_addr.s6_addr[6] == 0 &&
           data_.v6.sin6_addr.s6_addr[7] == 0 &&
           data_.v6.sin6_addr.s6_addr[8] == 0 &&
           data_.v6.sin6_addr.s6_addr[9] == 0 &&
           data_.v6.sin6_addr.s6_addr[10] == 0 &&
           data_.v6.sin6_addr.s6_addr[11] == 0 &&
           data_.v6.sin6_addr.s6_addr[12] == 0 &&
           data_.v6.sin6_addr.s6_addr[13] == 0 &&
           data_.v6.sin6_addr.s6_addr[14] == 0 &&
           data_.v6.sin6_addr.s6_addr[15] == 1;
}

}
