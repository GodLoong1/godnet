#pragma once

#ifndef GODNET_NETWORK_ENDPOINT_HPP
#define GODNET_NETWORK_ENDPOINT_HPP

#include "godnet/config.hpp"
#include "socket_types.hpp"

#include <cstdint>
#include <string_view>
#include <string>

namespace godnet
{

class GODNET_EXPORT Endpoint
{
public:
    Endpoint() noexcept;

    Endpoint(const std::string_view& address, std::uint16_t port) noexcept(false);

    std::int32_t family() const noexcept
    {
        return data_.base.sa_family;
    }

    std::uint16_t port() const noexcept;

    std::string ip() const noexcept;

    const sockaddr_t* getSockAddr() const noexcept
    {
        return &data_.base;
    }

    sockaddr_t* mutSockAddr() noexcept
    {
        return const_cast<sockaddr_t*>(getSockAddr());
    }

    static constexpr socklen_t getSockLen() noexcept
    {
        return sizeof(data_.base);
    }

    bool isV4() const noexcept;

    bool isV6() const noexcept;

    bool isLoopback() const noexcept;

private:
    union SockAddrData
    {
        sockaddr_t base;
        sockaddr_in4_t v4;
        sockaddr_in6_t v6;
    } data_;
};

}

#endif
