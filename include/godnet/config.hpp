#pragma once

#ifndef GODNET_CONFIG_HPP
#define GODNET_CONFIG_HPP

#if defined(_WIN32)
    #define GODNET_WINDOWS
#elif defined(__linux__)
    #define GODNET_LINUX
#endif

#if defined(GODNET_STATIC_LIB)
    #define GODNET_EXPORT
#elif defined(_MSC_VER)
    #if defined(GODNET_DYNAMIC_LIB)
        #define GODNET_EXPORT __declspec(dllexport)
    #else
        #define GODNET_EXPORT __declspec(dllimport)
    #endif
#elif defined(__GNUC__)
    #define GODNET_EXPORT __attribute__((visibility("default")))
#endif

#endif
