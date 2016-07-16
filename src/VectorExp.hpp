#ifndef AX_VECTOR_EXPRESSION_H
#define AX_VECTOR_EXPRESSION_H
#include <cmath>
#include "Expression.hpp"
#include "util.hpp"

namespace ax
{

namespace detail
{

template <typename T_lhs, typename T_oper, typename T_rhs>
class VectorExpression
{
  public:

    static_assert(is_operator_struct<typename T_oper::tag>::value,
                  "invalid Expression Operator");

    using tag = vector_expression_tag;
    constexpr static std::size_t dim = T_lhs::dim;

    VectorExpression(const T_lhs& lhs, const T_rhs& rhs)
        : l_(lhs), r_(rhs)
    {}

    double operator[](const std::size_t i) const
    {
        return T_oper::apply(l_[i], r_[i]);
    }

  private:
    T_lhs const& l_;
    T_rhs const& r_;
};

template <typename T_vec /* = Vector */, typename T_oper,
          typename T_scl /* = Scalar */,
          typename std::enable_if<
              is_vector_expression<typename T_vec::tag>::value&&
              is_scalar_type<T_scl, T_vec>::value
              >::type*& = enabler>
class VectorScalarExpression
{
  public:
    static_assert(is_operator_struct<typename T_oper::tag>::value,
                  "invalid Expression Operator");
    using tag = vector_expression_tag;
    constexpr static std::size_t dim = T_vec::dim;

    VectorScalarExpression(const T_vec& lhs, const T_scl& rhs)
        : l_(lhs), r_(rhs)
    {}

    double operator[](const std::size_t i) const
    {
        return T_oper::apply(l_[i], r_);
    }

  private:
    T_vec const& l_;
    T_scl const& r_;
};

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

template<template<typename T_l, typename T_r> class T_oper,
         typename T_lhs, typename T_rhs>
using vector_operator_type = T_oper<typename T_lhs::elem_t, typename T_rhs::elem_t>;

template<typename T_lhs,
    template<typename T_l, typename T_r> class T_oper, typename T_rhs>
using vector_expr_type =
    VectorExpression<T_lhs, vector_operator_type<T_oper, T_lhs, T_rhs>, T_rhs>;

template <typename T_lhs, typename T_rhs>
class Vector3DCrossProduct
{
  public:
    using tag = vector_expression_tag;
    constexpr static std::size_t dim = T_lhs::dim;

    Vector3DCrossProduct(const T_lhs& lhs, const T_rhs& rhs)
        : l_(lhs), r_(rhs)
    {}

    double operator[](const std::size_t i) const
    {
        using circ = circular_iteration<3>;
        return l_[circ::advance(i)] * r_[circ::advance_times(i, 2)] -
               l_[circ::advance_times(i, 2)] * r_[circ::advance(i)];
    }

  private:

    T_lhs const& l_;
    T_rhs const& r_;
};

} // detail

template <class L, class R,
          typename std::enable_if<is_same_vector<L,R>::value>::type*& = enabler>
inline typename detail::vector_expr_type<L, detail::Add_Operator, R>
operator+(const L& lhs, const R& rhs)
{
    return detail::VectorExpression<L,
               detail::Add_Operator<typename L::elem_t, typename R::elem_t>,
               R>(lhs, rhs);
}

template <class L, class R,
          typename std::enable_if<is_same_vector<L,R>::value>::type*& = enabler>
inline typename detail::vector_expr_type<L, detail::Subtract_Operator, R>
operator-(const L& lhs, const R& rhs)
{
    return detail::VectorExpression<L,
               detail::Subtract_Operator<typename L::elem_t, typename R::elem_t>,
               R>(lhs, rhs);
}

// vector * scalar
template <class L /* = Vector */, class R /* = Scalar */,
          typename std::enable_if<
              is_vector_expression<typename L::tag>::value&&
              is_scalar_type<R, L>::value
              >::type*& = enabler>
inline detail::VectorScalarExpression<L,
    detail::Multiply_Operator<typename L::elem_t, R>, R>
operator*(const L& lhs, const R& rhs)
{
    return detail::VectorScalarExpression<L,
               detail::Multiply_Operator<typename L::elem_t, R>, R>(lhs, rhs);
}

// scalar * vector
template <class L /* = Scalar */, class R /* = Vector */,
          typename std::enable_if<
              is_vector_expression<typename R::tag>::value&&
              is_scalar_type<L, R>::value
              >::type*& = enabler>
inline detail::VectorScalarExpression<R,
    detail::Multiply_Operator<typename R::elem_t, L>, L>
operator*(const L& lhs, const R& rhs)
{
    return detail::VectorScalarExpression<R,
               detail::Multiply_Operator<typename R::elem_t, L>, L>(rhs, lhs);
}

// vector / scalar
template <class L /* = Vector */, class R /* = Scalar */,
          typename std::enable_if<
              is_vector_expression<typename L::tag>::value&&
              is_scalar_type<R, L>::value
              >::type*& = enabler>
inline detail::VectorScalarExpression<L,
    detail::Divide_Operator<typename L::elem_t, R>, R>
operator/(const L& lhs, const R& rhs)
{
    return detail::VectorScalarExpression<L,
               detail::Divide_Operator<typename L::elem_t, R>, R>(lhs, rhs);
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
    return (i_dim == 0) ? sum + val[i_dim] * val[i_dim] :
        length_square_impl<T_vec>(val, i_dim - 1, sum + val[i_dim] * val[i_dim]);
}

}//detail

template <class T_vec,
          typename std::enable_if<
              is_vector_expression<typename T_vec::tag>::value
              >::type*& = enabler>
constexpr inline typename T_vec::elem_t
len_square(const T_vec& vec)
{
    return detail::length_square_impl<T_vec>(vec, T_vec::dim - 1, 0.0);
}

template <class T_vec,
          typename std::enable_if<
              is_vector_expression<typename T_vec::tag>::value
              >::type*& = enabler>
inline double length(const T_vec& l)
{
    return std::sqrt(len_square(l));
}

namespace detail
{

template <class T_lhs, class T_rhs,
          typename std::enable_if<
              is_same_vector<T_lhs, T_rhs>::value>::type*& = enabler>
constexpr inline typename T_lhs::elem_t
dot_prod_impl(const T_lhs& lhs, const T_rhs& rhs, const std::size_t i_dim,
              const typename T_lhs::elem_t sum)
{
    return (i_dim == 0) ? sum + lhs[i_dim] * rhs[i_dim] :
        dot_prod_impl<T_lhs, T_rhs>(lhs, rhs, i_dim - 1, sum + lhs[i_dim] * rhs[i_dim]);
}

}//detail

template <class T_lhs, class T_rhs,
          typename std::enable_if<
              is_same_vector<T_lhs, T_rhs>::value>::type*& = enabler>
constexpr inline typename T_lhs::elem_t
dot_prod(const T_lhs& lhs, const T_rhs& rhs)
{
    return detail::dot_prod_impl<T_lhs, T_rhs>(lhs, rhs, T_lhs::dim - 1, 0.0);
}

template <class T_lhs, class T_rhs,
          typename std::enable_if<
              is_same_vector<T_lhs, T_rhs>::value&&
              is_same_dimention<T_lhs::dim, 3>::value&&
              is_same_dimention<T_rhs::dim, 3>::value
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
inline detail::VectorScalarExpression<T_vec,
    detail::Divide_Operator<typename T_vec::elem_t, typename T_vec::elem_t>,
    typename T_vec::elem_t>
normalize(const T_vec& lhs)
{
    return lhs / length(lhs);
}

}
#endif //AX_VECTOR3_EXPRESSION_H
