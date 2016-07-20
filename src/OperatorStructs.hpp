#ifndef AX_OPERATOR_STRUCT_H
#define AX_OPERATOR_STRUCT_H
#include "TypeTraits.hpp"

namespace ax
{

namespace detail
{

template<typename T_lhs, typename T_rhs>
struct Add_Operator
{
    using tag = operator_tag;
    static auto apply(const T_lhs lhs, const T_rhs rhs) -> decltype(lhs + rhs)
    {return lhs + rhs;}
};

template<typename T_lhs, typename T_rhs>
struct Subtract_Operator
{
    using tag = operator_tag;
    static auto apply(const T_lhs lhs, const T_rhs rhs) -> decltype(lhs - rhs)
    {return lhs - rhs;}
};

template<typename T_lhs, typename T_rhs>
struct Multiply_Operator
{
    using tag = operator_tag;
    static auto apply(const T_lhs lhs, const T_rhs rhs) -> decltype(lhs * rhs)
    {return lhs * rhs;}
};

template<typename T_lhs, typename T_rhs>
struct Divide_Operator
{
    using tag = operator_tag;
    static auto apply(const T_lhs lhs, const T_rhs rhs) -> decltype(lhs / rhs)
    {return lhs / rhs;}
};

}// detail

}// ax

#endif /* AX_OPERATOR_STRUCT_H */
