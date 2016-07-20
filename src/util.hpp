#ifndef AX_UTILITY_H
#define AX_UTILITY_H
#include <cstddef>

namespace ax
{

template<std::size_t I_inter>
struct circular_iteration
{
    constexpr static std::size_t advance(const std::size_t i);
    constexpr static std::size_t retrace(const std::size_t i);
    constexpr static std::size_t advance_times(const std::size_t i, const std::size_t times);
    constexpr static std::size_t retrace_times(const std::size_t i, const std::size_t times);
};


template<std::size_t I_inter>
constexpr inline std::size_t circular_iteration<I_inter>::advance(const std::size_t i)
{
    return (i + 1 < I_inter) ? (i + 1) : (i + 1 - I_inter);
}

template<std::size_t I_inter>
constexpr inline std::size_t circular_iteration<I_inter>::retrace(const std::size_t i)
{
    return (0 < i) ? (i - 1) : (i - 1 + I_inter);
}

template<std::size_t I_inter>
constexpr inline std::size_t
circular_iteration<I_inter>::advance_times(
        const std::size_t i, const std::size_t times)
{
    return (times == 0) ? i : advance_times(advance(i), times - 1);
}

template<std::size_t I_inter>
constexpr inline std::size_t
circular_iteration<I_inter>::retrace_times(
        const std::size_t i, const std::size_t times)
{
    return (times == 0) ? i : retrace_times(retrace(i), times - 1);
}


} // ax

#endif //AX_UTILITY_H

