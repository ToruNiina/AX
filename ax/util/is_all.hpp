#ifndef AX_IS_ALL
#define AX_IS_ALL
#include <type_traits>

namespace ax
{

template<template<typename> class T_cond, typename ... T_args>
struct is_all;

template<template<typename> class T_cond, typename T_front, typename ... T_args>
struct is_all<T_cond, T_front, T_args...>
    : public std::integral_constant<bool, T_cond<T_front>::value &&
        is_all<T_cond, T_args...>::value>{};

template<template<typename> class T_cond, typename T_last>
struct is_all<T_cond,T_last>
    : public std::integral_constant<bool, T_cond<T_last>::value>{};

} // ax

#endif /* AX_IS_ALL */
