#ifndef AX_CALCULATOR
#define AX_CALCULATOR
#include "tags.hpp"

namespace ax
{

template<typename lhsT, typename rhsT>
struct add
{
    typedef operator_tag tag;

    constexpr static auto
    invoke(const lhsT lhs, const rhsT rhs) -> decltype(lhs + rhs)
    {
        return lhs + rhs;
    }
};

template<typename lhsT, typename rhsT>
struct subtract
{
    typedef operator_tag tag;

    constexpr static auto
    invoke(const lhsT lhs, const rhsT rhs) -> decltype(lhs - rhs)
    {
        return lhs - rhs;
    }
};

template<typename lhsT, typename rhsT>
struct multiply
{
    typedef operator_tag tag;

    constexpr static auto
    invoke(const lhsT lhs, const rhsT rhs) -> decltype(lhs * rhs)
    {
        return lhs * rhs;
    }
};

template<typename lhsT, typename rhsT>
struct divide
{
    typedef operator_tag tag;

    constexpr static auto
    invoke(const lhsT lhs, const rhsT rhs) -> decltype(lhs / rhs)
    {
        return lhs / rhs;
    }
};

} // ax

#endif /* AX_CALCULATOR */
