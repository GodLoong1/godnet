#include "godnet/network/endpoint.hpp"
#include <iostream>
#include <type_traits>
#include <vector>

template <typename T, typename = void>
struct has_type : std::false_type
{
};

template <typename T>
struct has_type<T, std::void_t<typename T::value_type>> : std::true_type
{
};

template <typename T>
constexpr bool has_type_t = has_type<T>::value;

int main()
{
    std::cout << has_type_t<std::vector<int>> << std::endl;
    std::cout << has_type<std::vector<int>>::value << std::endl;
}