#ifndef AX_VECTOR_EXPRESSION_H
#define AX_VECTOR_EXPRESSION_H
#include "Expression.hpp"
#include "util.hpp"
#include <stdexcept>
#include <cmath>

namespace ax
{

// constexpr std::size_t dimension(T_vex vex){return dimension of vex} {{{

// for static vector
template <class T_vec, typename std::enable_if<
              is_vector_type<typename T_vec::tag>::value&&
              is_static_dimension<T_vec::dim>::value>::type*& = enabler>
constexpr inline std::size_t dimension(const T_vec& v){return T_vec::dim;}

// for dynamic vector
template <class T_vec, typename std::enable_if<
              is_vector_type<typename T_vec::tag>::value&&
              is_dynamic_dimension<T_vec::dim>::value>::type*& = enabler>
constexpr inline std::size_t dimension(const T_vec& v){return v.size();}

// for static vector expression
template <class T_vexpr, typename std::enable_if<
              is_exactly_vector_expr<typename T_vexpr::tag>::value&&
              is_static_dimension<T_vexpr::dim>::value>::type*& = enabler>
constexpr inline std::size_t dimension(const T_vexpr& vexpr)
{
    return T_vexpr::dim;
}

// for dynamic vector expression
template <class T_vexpr, typename std::enable_if<
              is_exactly_vector_expr<typename T_vexpr::tag>::value&&
              is_dynamic_dimension<T_vexpr::dim>::value>::type*& = enabler>
constexpr inline std::size_t dimension(const T_vexpr& vexpr)
{
    return dimension(vexpr.l_); //XXX: in vector_scalar_operation, l is vector
}
// }}}

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
        return T_oper::apply(l_[i], r_[i]);
    }

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
    using elem_t = typename T_vec::elem_t;
    constexpr static dimension_type dim = T_vec::dim;

    VectorScalarExpression(const T_vec& lhs, const T_scl& rhs)
        : l_(lhs), r_(rhs)
    {}

    elem_t operator[](const std::size_t i) const
    {
        return T_oper::apply(l_[i], r_);
    }

    T_vec const& l_;
    T_scl const  r_;
};

// operator definitions Some_Operator::apply(lhs, rhs) return lhs (op) rhs {{{
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
// }}}

// alias to use VectorExpression more easily {{{
template<template<typename T_l, typename T_r> class T_oper,
         typename T_lhs, typename T_rhs>
using vector_operator_type = T_oper<typename T_lhs::elem_t, typename T_rhs::elem_t>;

template<typename T_lhs,
    template<typename T_l, typename T_r> class T_oper,
    typename T_rhs, dimension_type I_dim>
using vector_expr_type =
    VectorExpression<T_lhs, vector_operator_type<T_oper, T_lhs, T_rhs>, T_rhs, I_dim>;
// }}}

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
        return l_[circ::advance(i)] * r_[circ::retreat(i)] -
               l_[circ::retreat(i)] * r_[circ::advance(i)];
    }

    T_lhs const& l_;
    T_rhs const& r_;
};

} // detail

// for static + static or dynamic + dynamic
template <class L, class R,
          typename std::enable_if<is_same_vector<L,R>::value>::type*& = enabler>
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
          is_static_dynamic_pair<L,R>::value&&
          std::is_same<typename L::elem_t, typename R::elem_t>::value
          >::type*& = enabler>
typename detail::vector_expr_type<L, detail::Add_Operator, R,
    vector_expression_dimension<L, R>::value>
operator+(const L& lhs, const R& rhs)
{
    if(dimension(lhs) != dimension(rhs))
        throw std::invalid_argument("in operator+, vector dimension different");
    return detail::VectorExpression<L,
               detail::Add_Operator<typename L::elem_t, typename R::elem_t>,
               R, vector_expression_dimension<L, R>::value>(lhs, rhs);
}

// for static + static or dynamic + dynamic
template <class L, class R,
          typename std::enable_if<is_same_vector<L,R>::value>::type*& = enabler>
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
          is_static_dynamic_pair<L,R>::value&&
          std::is_same<typename L::elem_t, typename R::elem_t>::value
          >::type*& = enabler>
typename detail::vector_expr_type<L, detail::Subtract_Operator, R,
    vector_expression_dimension<L, R>::value>
operator-(const L& lhs, const R& rhs)
{
    if(dimension(lhs) != dimension(rhs))
        throw std::invalid_argument("in operator-, vector dimension different");
    return detail::VectorExpression<L,
               detail::Subtract_Operator<typename L::elem_t, typename R::elem_t>,
               R, vector_expression_dimension<L, R>::value>(lhs, rhs);
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

// static * static
template <class T_lhs, class T_rhs, typename std::enable_if<
              is_same_vector<T_lhs, T_rhs>::value&&
              is_static_dimension<T_lhs::dim>::value&&
              is_static_dimension<T_rhs::dim>::value&&
              is_same_dimension<T_lhs::dim, T_rhs::dim>::value
              >::type*& = enabler>
constexpr inline typename T_lhs::elem_t
dot_prod(const T_lhs& lhs, const T_rhs& rhs)
{
    return detail::dot_prod_impl<T_lhs, T_rhs>(lhs, rhs, T_lhs::dim - 1, 0.0);
}

// static * dynamic
template <class T_lhs, class T_rhs, typename std::enable_if<
              is_same_vector<T_lhs, T_rhs>::value&&
              is_static_dimension<T_lhs::dim>::value&&
              is_dynamic_dimension<T_rhs::dim>::value
              >::type*& = enabler>
typename T_lhs::elem_t
dot_prod(const T_lhs& lhs, const T_rhs& rhs)
{
    if(T_lhs::dim != dimension(rhs)) 
        throw std::invalid_argument(
                std::string("in dot_prod, vector size different: lhs = ")
                + std::to_string(dimension(lhs)) + std::string(", rhs = ")
                + std::to_string(dimension(rhs)));
    return detail::dot_prod_impl<T_lhs, T_rhs>(lhs, rhs, T_lhs::dim - 1, 0.0);
}

// dynamic * static
template <class T_lhs, class T_rhs, typename std::enable_if<
              is_same_vector<T_lhs, T_rhs>::value&&
              is_dynamic_dimension<T_lhs::dim>::value&&
              is_static_dimension<T_rhs::dim>::value
              >::type*& = enabler>
typename T_lhs::elem_t
dot_prod(const T_lhs& lhs, const T_rhs& rhs)
{
    if(dimension(lhs) != T_rhs::dim) 
        throw std::invalid_argument("in dot_prod, vector size different");
    return detail::dot_prod_impl<T_lhs, T_rhs>(lhs, rhs, T_rhs::dim - 1, 0.0);
}

// dynamic * dynamic
template <class T_lhs, class T_rhs, typename std::enable_if<
              is_same_vector<T_lhs, T_rhs>::value&&
              is_dynamic_dimension<T_lhs::dim>::value&&
              is_dynamic_dimension<T_rhs::dim>::value
              >::type*& = enabler>
typename T_lhs::elem_t
dot_prod(const T_lhs& lhs, const T_rhs& rhs)
{
    if(dimension(lhs) != dimension(rhs))
        throw std::invalid_argument("in dot_prod, vector size different");
    return detail::dot_prod_impl<T_lhs, T_rhs>(lhs, rhs, dimension(lhs) - 1, 0.0);
}

template <class T_lhs, class T_rhs,
          typename std::enable_if<
              is_static_dimension<T_lhs::dim>::value&&
              is_same_dimension<T_lhs::dim, 3>::value&&
              is_same_vector<T_lhs, T_rhs>::value
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
