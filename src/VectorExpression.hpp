#ifndef AX_VECTOR_EXPRESSION_H
#define AX_VECTOR_EXPRESSION_H
#include "TypeTraits.hpp"
#include "OperatorStructs.hpp"
#include "Dimension.hpp"
#include "util.hpp"
#include <stdexcept>
#include <cmath>

namespace ax
{


namespace detail
{

template <typename T_lhs, typename T_oper, typename T_rhs, dimension_type I_dim>
class VectorExpression
{
  public:

    static_assert(is_operator_struct<typename T_oper::tag>::value,
                  "invalid Expression Operator");

    using tag = vector_expression_tag;
    using elem_t = typename T_lhs::elem_t;
    constexpr static dimension_type dim = I_dim;

    VectorExpression(const T_lhs& lhs, const T_rhs& rhs)
        : l_(lhs), r_(rhs)
    {}

    elem_t operator[](const std::size_t i) const
    {
#ifdef AX_PARANOIAC
        return T_oper::apply(l_.at(i), r_.at(i));
#else
        return T_oper::apply(l_[i], r_[i]);
#endif
    }

    T_lhs const& l_;
    T_rhs const& r_;
};

template <typename T_vec /* = Vector */, typename T_oper,
          typename T_scl /* = Scalar */,
          typename std::enable_if<
              is_vector_expression<typename T_vec::tag>::value&&
              std::is_same<T_scl, typename T_vec::elem_t>::value
              >::type*& = enabler>
class VectorScalarExpression
{
  public:
    static_assert(is_operator_struct<typename T_oper::tag>::value,
                  "invalid Expression Operator");

    using tag = vector_expression_tag;
    using elem_t = typename T_vec::elem_t;
    constexpr static dimension_type dim = T_vec::dim;

    VectorScalarExpression(const T_vec& lhs, const T_scl& rhs)
        : l_(lhs), r_(rhs)
    {}

    elem_t operator[](const std::size_t i) const
    {
#ifdef AX_PARANOIAC
        return T_oper::apply(l_.at(i), r_);
#else
        return T_oper::apply(l_[i], r_);
#endif

    }

    T_vec const& l_;
    T_scl const  r_;
};

template <typename T_lhs, typename T_rhs>
class Vector3DCrossProduct
{
  public:
    using tag = vector_expression_tag;
    using elem_t = typename T_lhs::elem_t;
    constexpr static dimension_type dim = T_lhs::dim;

    Vector3DCrossProduct(const T_lhs& lhs, const T_rhs& rhs)
        : l_(lhs), r_(rhs)
    {}

    elem_t operator[](const std::size_t i) const
    {
        using circ = circular_iteration<3>;
        return l_[circ::advance(i)] * r_[circ::retrace(i)] -
               l_[circ::retrace(i)] * r_[circ::advance(i)];
    }

    T_lhs const& l_;
    T_rhs const& r_;
};

template<template<typename T_l, typename T_r> class T_oper,
         typename T_lhs, typename T_rhs>
using vector_operator_type = T_oper<typename T_lhs::elem_t, typename T_rhs::elem_t>;

template<typename T_lhs,
    template<typename T_l, typename T_r> class T_oper,
    typename T_rhs, dimension_type I_dim>
using vector_expr_type =
    VectorExpression<T_lhs, vector_operator_type<T_oper, T_lhs, T_rhs>, T_rhs, I_dim>;

} // detail

// for static + static or dynamic + dynamic
template <class L, class R, typename std::enable_if<
    is_vector_expression<typename L::tag>::value&&
    is_vector_expression<typename R::tag>::value&&
    is_same_dimension<L::dim, R::dim>::value&&
    std::is_same<typename L::elem_t, typename R::elem_t>::value
    >::type*& = enabler>
inline typename detail::vector_expr_type<L, detail::Add_Operator, R, L::dim>
operator+(const L& lhs, const R& rhs)
{
    return detail::VectorExpression<L,
               detail::Add_Operator<typename L::elem_t, typename R::elem_t>,
               R, L::dim>(lhs, rhs);
}

// for static + dynamic or dynamic + static
template <class L, class R, typename std::enable_if<
    is_vector_expression<typename L::tag>::value&&
    is_vector_expression<typename R::tag>::value&&
    ((is_static_dimension<L::dim>::value&&is_dynamic_dimension<R::dim>::value)||
     (is_static_dimension<R::dim>::value&&is_dynamic_dimension<L::dim>::value))&&
    std::is_same<typename L::elem_t, typename R::elem_t>::value
    >::type*& = enabler>
inline typename detail::vector_expr_type<L, detail::Add_Operator, R,
    vector_expression_dimension<L, R>::value>
operator+(const L& lhs, const R& rhs)
{
    return detail::VectorExpression<L,
               detail::Add_Operator<typename L::elem_t, typename R::elem_t>,
               R, vector_expression_dimension<L, R>::value>(lhs, rhs);
}

// for static + static or dynamic + dynamic
template <class L, class R, typename std::enable_if<
    is_vector_expression<typename L::tag>::value&&
    is_vector_expression<typename R::tag>::value&&
    is_same_dimension<L::dim, R::dim>::value&&
    std::is_same<typename L::elem_t, typename R::elem_t>::value
    >::type*& = enabler>
inline typename detail::vector_expr_type<L, detail::Subtract_Operator, R, L::dim>
operator-(const L& lhs, const R& rhs)
{
    return detail::VectorExpression<L,
               detail::Subtract_Operator<typename L::elem_t, typename R::elem_t>,
               R, L::dim>(lhs, rhs);
}

// for static + dynamic or dynamic + static
template <class L, class R, typename std::enable_if<
    is_vector_expression<typename L::tag>::value&&
    is_vector_expression<typename R::tag>::value&&
    ((is_static_dimension<L::dim>::value&&is_dynamic_dimension<R::dim>::value)||
     (is_static_dimension<R::dim>::value&&is_dynamic_dimension<L::dim>::value))&&
    std::is_same<typename L::elem_t, typename R::elem_t>::value
    >::type*& = enabler>
inline typename detail::vector_expr_type<L, detail::Subtract_Operator, R,
    vector_expression_dimension<L, R>::value>
operator-(const L& lhs, const R& rhs)
{
    return detail::VectorExpression<L,
               detail::Subtract_Operator<typename L::elem_t, typename R::elem_t>,
               R, vector_expression_dimension<L, R>::value>(lhs, rhs);
}

// vector * scalar
template <class T_vec, class T_scl, typename std::enable_if<
    is_vector_expression<typename T_vec::tag>::value&&
    std::is_same<typename T_vec::elem_t, T_scl>::value>::type*& = enabler>
inline detail::VectorScalarExpression<T_vec,
    detail::Multiply_Operator<typename T_vec::elem_t, T_scl>, T_scl>
operator*(const T_vec& lhs, const T_scl& rhs)
{
    return detail::VectorScalarExpression<T_vec,
               detail::Multiply_Operator<typename T_vec::elem_t, T_scl>,
               T_scl>(lhs, rhs);
}

// scalar * vector
template <class T_scl, class T_vec, typename std::enable_if<
    is_vector_expression<typename T_vec::tag>::value&&
    std::is_same<T_scl, typename T_vec::elem_t>::value
    >::type*& = enabler>
inline detail::VectorScalarExpression<T_vec,
    detail::Multiply_Operator<typename T_vec::elem_t, T_scl>, T_scl>
operator*(const T_scl& lhs, const T_vec& rhs)
{
    return detail::VectorScalarExpression<T_vec,
               detail::Multiply_Operator<typename T_vec::elem_t,
               T_scl>, T_scl>(rhs, lhs);
}

// vector / scalar
template <class T_vec, class T_scl, typename std::enable_if<
    is_vector_expression<typename T_vec::tag>::value&&
    std::is_same<T_scl, typename T_vec::elem_t>::value
    >::type*& = enabler>
inline detail::VectorScalarExpression<T_vec,
    detail::Divide_Operator<typename T_vec::elem_t, T_scl>, T_scl>
operator/(const T_vec& lhs, const T_scl& rhs)
{
    return detail::VectorScalarExpression<T_vec,
               detail::Divide_Operator<typename T_vec::elem_t, T_scl>,
               T_scl>(lhs, rhs);
}

namespace detail
{

template <class T_vec,
          typename std::enable_if<
              is_vector_expression<typename T_vec::tag>::value
              >::type*& = enabler>
constexpr inline typename T_vec::elem_t
length_square_impl(const T_vec& val, const std::size_t i_dim, const typename T_vec::elem_t sum)
{
#ifdef AX_PARANOIAC
    return (i_dim == 0) ? sum + val.at(i_dim) * val.at(i_dim) :
        length_square_impl<T_vec>(val, i_dim - 1, sum + val.at(i_dim) * val.at(i_dim));
#else
    return (i_dim == 0) ? sum + val[i_dim] * val[i_dim] :
        length_square_impl<T_vec>(val, i_dim - 1, sum + val[i_dim] * val[i_dim]);
#endif
}

}//detail

template <class T_vec,
          typename std::enable_if<
              is_vector_expression<typename T_vec::tag>::value&&
              is_static_dimension<T_vec::dim>::value>::type*& = enabler>
constexpr inline typename T_vec::elem_t
len_square(const T_vec& vec)
{
    return detail::length_square_impl<T_vec>(vec, T_vec::dim - 1, 0.0);
}

template <class T_vec,
          typename std::enable_if<
              is_vector_expression<typename T_vec::tag>::value&&
              is_dynamic_dimension<T_vec::dim>::value>::type*& = enabler>
constexpr inline typename T_vec::elem_t
len_square(const T_vec& vec)
{
    return detail::length_square_impl<T_vec>(vec, dimension(vec) - 1, 0.0);
}

template <class T_vec,
          typename std::enable_if<
              is_vector_expression<typename T_vec::tag>::value
              >::type*& = enabler>
inline typename T_vec::elem_t length(const T_vec& l)
{
    return std::sqrt(len_square(l));
}

namespace detail
{

template <class T_lhs, class T_rhs, typename std::enable_if<
    is_vector_expression<typename T_lhs::tag>::value&&
    is_vector_expression<typename T_rhs::tag>::value>::type*& = enabler>
constexpr inline typename T_lhs::elem_t
dot_prod_impl(const T_lhs& lhs, const T_rhs& rhs, const std::size_t i_dim,
              const typename T_lhs::elem_t sum)
{
#ifdef AX_PARANOIAC
    return (i_dim == 0) ? sum + lhs.at(i_dim) * rhs.at(i_dim) :
        dot_prod_impl<T_lhs, T_rhs>(
                lhs, rhs, i_dim - 1, sum + lhs.at(i_dim) * rhs.at(i_dim));
#else
    return (i_dim == 0) ? sum + lhs[i_dim] * rhs[i_dim] :
        dot_prod_impl<T_lhs, T_rhs>(
                lhs, rhs, i_dim - 1, sum + lhs[i_dim] * rhs[i_dim]);
#endif
}

}//detail

// static * static
template <class T_lhs, class T_rhs, typename std::enable_if<
    is_vector_expression<typename T_lhs::tag>::value&&
    is_vector_expression<typename T_rhs::tag>::value&&
    std::is_same<typename T_lhs::elem_t, typename T_rhs::elem_t>::value&&
    is_static_dimension<T_lhs::dim>::value&&
    is_same_dimension<T_lhs::dim, T_rhs::dim>::value
    >::type*& = enabler>
constexpr inline typename T_lhs::elem_t
dot_prod(const T_lhs& lhs, const T_rhs& rhs)
{
    return detail::dot_prod_impl<T_lhs, T_rhs>(lhs, rhs, dimension(lhs) - 1, 0.0);
}

// static * dynamic
template <class T_lhs, class T_rhs, typename std::enable_if<
    is_vector_expression<typename T_lhs::tag>::value&&
    is_vector_expression<typename T_rhs::tag>::value&&
    std::is_same<typename T_lhs::elem_t, typename T_rhs::elem_t>::value&&
    is_static_dimension<T_lhs::dim>::value&&
    is_dynamic_dimension<T_rhs::dim>::value
    >::type*& = enabler>
inline typename T_lhs::elem_t
dot_prod(const T_lhs& lhs, const T_rhs& rhs)
{
    return detail::dot_prod_impl<T_lhs, T_rhs>(lhs, rhs, dimension(lhs) - 1, 0.0);
}

// dynamic * static
template <class T_lhs, class T_rhs, typename std::enable_if<
    is_vector_expression<typename T_lhs::tag>::value&&
    is_vector_expression<typename T_rhs::tag>::value&&
    std::is_same<typename T_lhs::elem_t, typename T_rhs::elem_t>::value&&
    is_dynamic_dimension<T_lhs::dim>::value&&
    is_static_dimension<T_rhs::dim>::value
    >::type*& = enabler>
inline typename T_lhs::elem_t
dot_prod(const T_lhs& lhs, const T_rhs& rhs)
{
    return detail::dot_prod_impl<T_lhs, T_rhs>(lhs, rhs, dimension(lhs) - 1, 0.0);
}

// dynamic * dynamic
template <class T_lhs, class T_rhs, typename std::enable_if<
    is_vector_expression<typename T_lhs::tag>::value&&
    is_vector_expression<typename T_rhs::tag>::value&&
    std::is_same<typename T_lhs::elem_t, typename T_rhs::elem_t>::value&&
    is_dynamic_dimension<T_lhs::dim>::value&&
    is_dynamic_dimension<T_rhs::dim>::value
    >::type*& = enabler>
inline typename T_lhs::elem_t
dot_prod(const T_lhs& lhs, const T_rhs& rhs)
{
    return detail::dot_prod_impl<T_lhs, T_rhs>(lhs, rhs, dimension(lhs) - 1, 0.0);
}

template <class T_lhs, class T_rhs, typename std::enable_if<
    is_vector_expression<typename T_lhs::tag>::value&&
    is_vector_expression<typename T_rhs::tag>::value&&
    std::is_same<typename T_lhs::elem_t, typename T_rhs::elem_t>::value&&
    is_same_dimension<T_lhs::dim, 3>::value&&
    is_same_dimension<T_rhs::dim, 3>::value
    >::type*& = enabler>
inline detail::Vector3DCrossProduct<T_lhs, T_rhs>
cross_prod(const T_lhs& lhs, const T_rhs& rhs)
{
    return detail::Vector3DCrossProduct<T_lhs, T_rhs>(lhs, rhs);
}

template <class T_vec,
          typename std::enable_if<
              is_vector_expression<typename T_vec::tag>::value
              >::type*& = enabler>
detail::VectorScalarExpression<T_vec,
    detail::Divide_Operator<typename T_vec::elem_t, typename T_vec::elem_t>,
    typename T_vec::elem_t>
normalize(const T_vec& lhs)
{
    const typename T_vec::elem_t len = length(lhs);
    if(len == 0 || len != len)
        throw std::invalid_argument("length is 0 or nan");
    return detail::VectorScalarExpression<T_vec,
        detail::Divide_Operator<typename T_vec::elem_t, typename T_vec::elem_t>,
        typename T_vec::elem_t>(lhs, len);
}


}
#endif //AX_VECTOR3_EXPRESSION_H
