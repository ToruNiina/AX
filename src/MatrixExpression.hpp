#ifndef AX_MATRIX_EXPRESSION_H
#define AX_MATRIX_EXPRESSION_H
#include "TypeTraits.hpp"
#include "OperatorStructs.hpp"
#include "Dimension.hpp"
#include <utility>

namespace ax
{


namespace detail
{

template <typename T_lhs, typename T_oper, typename T_rhs,
          dimension_type I_dim_row, dimension_type I_dim_col>
class MatrixExpression
{
  public:

    static_assert(is_operator_struct<typename T_oper::tag>::value,
                  "invalid Expression Operator");

    using tag = matrix_expression_tag;
    using elem_t = typename T_lhs::elem_t;
    constexpr static dimension_type dim_row = I_dim_row;
    constexpr static dimension_type dim_col = I_dim_col;

    MatrixExpression(const T_lhs& lhs, const T_rhs& rhs)
        : l_(lhs), r_(rhs)
    {}

    elem_t operator()(const std::size_t i, const std::size_t j) const
    {
        return T_oper::apply(l_(i,j), r_(i,j));
    }

    T_lhs const& l_;
    T_rhs const& r_;
};

template <typename T_lhs, typename T_rhs,
          dimension_type I_dim_row, dimension_type I_dim_col>
class MatrixProduct
{
  public:

    using tag = matrix_product_tag;
    using elem_t = typename T_lhs::elem_t;
    constexpr static dimension_type dim_row = I_dim_row;
    constexpr static dimension_type dim_col = I_dim_col;

    MatrixProduct(const T_lhs& lhs, const T_rhs& rhs)
        : l_(lhs), r_(rhs)
    {}

    elem_t operator()(const std::size_t i, const std::size_t j) const
    {
        elem_t retval(0);
        for(std::size_t k(0); k<dimension_row(r_); ++k)
            retval += l_(i,k) * r_(k,j);

        return retval;
    }

    T_lhs const& l_;
    T_rhs const& r_;
};

template<typename T_mat, typename T_vec, dimension_type I_dim>
class MatrixVectorProduct
{
  public:

    static_assert(is_matrix_expression<typename T_mat::tag>::value&&
                  is_vector_expression<typename T_vec::tag>::value,
                  "in matrix_vector_product, invalid type");

    using tag = vector_expression_tag;
    using elem_t = typename T_vec::elem_t;
    constexpr static dimension_type dim = I_dim;

    MatrixVectorProduct(const T_mat& mat, const T_vec& vec)
        : l_(vec), r_(mat)
    {}

    elem_t operator[](const std::size_t i) const
    {
        elem_t retval(0);
        for(std::size_t j=0; j<dim; ++j)
            retval += r_(i, j) * l_[j];
        return retval;
    }

    T_vec const& l_; //XXX: for dimension() function!;
    T_mat const& r_;
};

template<typename T_mat, typename T_vec, dimension_type I_dim>
class VectorMatrixProduct
{
  public:

    static_assert(is_matrix_expression<typename T_mat::tag>::value&&
                  is_vector_expression<typename T_vec::tag>::value,
                  "in vector_matrix_product, invalid type");

    using tag = vector_expression_tag;
    using elem_t = typename T_vec::elem_t;
    constexpr static dimension_type dim = I_dim;

    VectorMatrixProduct(const T_vec& vec, const T_mat& mat)
        : l_(vec), r_(mat)
    {}

    elem_t operator[](const std::size_t i) const
    {
        elem_t retval(0);
        for(std::size_t j=0; j<dim; ++j)
            retval += l_[j] * r_(j, i);
        return retval;
    }

    T_vec const& l_;
    T_mat const& r_;
};

template<typename T_mat, typename T_oper, typename T_scl>
class MatrixScalarExpression
{
  public:

    using tag = matrix_expression_tag;
    using elem_t = typename T_mat::elem_t;
    constexpr static dimension_type dim_row = T_mat::dim_row;
    constexpr static dimension_type dim_col = T_mat::dim_col;

    static_assert(std::is_same<typename T_mat::elem_t, T_scl>::value,
            "type of matrix element and scalar different");
    static_assert(is_operator_struct<typename T_oper::tag>::value,
                  "invalid Expression Operator");

    MatrixScalarExpression(const T_mat& lhs, const T_scl& rhs)
        : l_(lhs), r_(rhs)
    {}

    elem_t operator()(const std::size_t i, const std::size_t j) const
    {
        return T_oper::apply(l_(i,j), r_);
    }

    const T_mat& l_;
    const elem_t r_;
};


template<typename T_mat>
class MatrixTranspose
{
  public:

    using tag = matrix_transpose_tag;
    using elem_t = typename T_mat::elem_t;
    constexpr static std::size_t dim_row = T_mat::dim_col;
    constexpr static std::size_t dim_col = T_mat::dim_row;

    MatrixTranspose(const T_mat& mat): l_(mat){}

    elem_t operator()(const std::size_t i, const std::size_t j) const
    {
        return l_(j, i);
    }

    T_mat const& l_;
};

template<template<typename T_l, typename T_r> class T_oper,
         typename T_lhs, typename T_rhs>
using matrix_operator_type =
    T_oper<typename T_lhs::elem_t, typename T_rhs::elem_t>;

template<template<typename T_l, typename T_r> class T_oper,
         typename T_mat, typename T_scl>
using matrix_scalar_operator_type = T_oper<typename T_mat::elem_t, T_scl>;

}//detail

// for static + static, dyn + dyn
template<class T_lhs, class T_rhs, typename std::enable_if<
    is_matrix_expression<typename T_lhs::tag>::value&&
    is_matrix_expression<typename T_rhs::tag>::value&&
    is_same_dimension<T_lhs::dim_col, T_rhs::dim_col>::value&&
    is_same_dimension<T_lhs::dim_row, T_rhs::dim_row>::value>::type*& = enabler>
inline detail::MatrixExpression<T_lhs,
    detail::Add_Operator<typename T_lhs::elem_t, typename T_rhs::elem_t>,
    T_rhs, T_lhs::dim_row, T_lhs::dim_col>
operator+(const T_lhs& lhs, const T_rhs& rhs)
{
    return detail::MatrixExpression<T_lhs, detail::Add_Operator<
               typename T_lhs::elem_t, typename T_rhs::elem_t>,
               T_rhs, T_lhs::dim_row, T_lhs::dim_col>(lhs, rhs);
}

// for static + static, dyn + dyn
template<class T_lhs, class T_rhs, typename std::enable_if<
    is_matrix_expression<typename T_lhs::tag>::value&&
    is_matrix_expression<typename T_rhs::tag>::value&&
    is_same_dimension<T_lhs::dim_col, T_rhs::dim_col>::value&&
    is_same_dimension<T_lhs::dim_row, T_rhs::dim_row>::value
    >::type*& = enabler>
inline detail::MatrixExpression<T_lhs,
    detail::Subtract_Operator<typename T_lhs::elem_t, typename T_rhs::elem_t>,
    T_rhs, T_lhs::dim_row, T_lhs::dim_col>
operator-(const T_lhs& lhs, const T_rhs& rhs)
{
    return detail::MatrixExpression<T_lhs, detail::Subtract_Operator<
               typename T_lhs::elem_t, typename T_rhs::elem_t>,
               T_rhs, T_lhs::dim_row, T_lhs::dim_col>(lhs, rhs);
}

// for (static, static) * (static, static)
template<class T_lhs, class T_rhs, typename std::enable_if<
    is_matrix_expression<typename T_lhs::tag>::value&&
    is_matrix_expression<typename T_rhs::tag>::value&&
    is_same_dimension<T_lhs::dim_col, T_rhs::dim_row>::value&&
    is_static_dimension<T_lhs::dim_col>::value&&
    is_static_dimension<T_lhs::dim_row>::value&&
    is_static_dimension<T_rhs::dim_col>::value&&
    is_static_dimension<T_rhs::dim_row>::value
    >::type*& = enabler>
inline detail::MatrixProduct<T_lhs, T_rhs, T_lhs::dim_row, T_rhs::dim_col>
operator*(const T_lhs& lhs, const T_rhs& rhs)
{
    return detail::MatrixProduct<T_lhs, T_rhs,
               T_lhs::dim_row, T_rhs::dim_col>(lhs, rhs);
}
// for (static, static) * (static, static)
template<class T_lhs, class T_rhs, typename std::enable_if<
    is_matrix_expression<typename T_lhs::tag>::value&&
    is_matrix_expression<typename T_rhs::tag>::value&&
    is_dynamic_dimension<T_lhs::dim_col>::value&&
    is_dynamic_dimension<T_lhs::dim_row>::value&&
    is_dynamic_dimension<T_rhs::dim_col>::value&&
    is_dynamic_dimension<T_rhs::dim_row>::value
    >::type*& = enabler>
inline detail::MatrixProduct<T_lhs, T_rhs, T_lhs::dim_row, T_rhs::dim_col>
operator*(const T_lhs& lhs, const T_rhs& rhs)
{
    return detail::MatrixProduct<T_lhs, T_rhs,
               T_lhs::dim_row, T_rhs::dim_col>(lhs, rhs);
}


//left hand side is matrix
template<class T_mat, class T_scl,
         typename std::enable_if<
             is_matrix_expression<typename T_mat::tag>::value&&
             std::is_same<typename T_mat::elem_t, T_scl>::value
             >::type*& = enabler>
inline detail::MatrixScalarExpression<T_mat,
    detail::Multiply_Operator<typename T_mat::elem_t, T_scl>, T_scl>
operator*(const T_mat& lhs, const T_scl& rhs)
{
    return detail::MatrixScalarExpression<T_mat,
        detail::Multiply_Operator<typename T_mat::elem_t, T_scl>,
        T_scl>(lhs /* = matrix*/, rhs /* = scalar*/);
}

//right hand side is matrix
template<class T_scl, class T_mat,
         typename std::enable_if<
             is_matrix_expression<typename T_mat::tag>::value&&
             std::is_same<typename T_mat::elem_t, T_scl>::value
             >::type*& = enabler>
inline detail::MatrixScalarExpression<T_mat,
    detail::Multiply_Operator<typename T_mat::elem_t, T_scl>, T_scl>
operator*(const T_scl& lhs, const T_mat& rhs)
{
    return detail::MatrixScalarExpression<T_mat,
        detail::Multiply_Operator<typename T_mat::elem_t, T_scl>,
        T_scl>(rhs /* = matrix*/, lhs /* = scalar*/);
}

template<class T_mat, class T_scl,
         typename std::enable_if<
             is_matrix_expression<typename T_mat::tag>::value&&
             std::is_same<typename T_mat::elem_t, T_scl>::value
             >::type*& = enabler>
inline detail::MatrixScalarExpression<T_mat,
    detail::Divide_Operator<typename T_mat::elem_t, T_scl>, T_scl>
operator/(const T_mat& mat, const T_scl& scl)
{
    return detail::MatrixScalarExpression<T_mat,
               detail::Divide_Operator<typename T_mat::elem_t, T_scl>,
               T_scl>(mat, scl);
}

template<class T_mat, typename std::enable_if<
         is_matrix_expression<typename T_mat::tag>::value>::type*& = enabler>
inline detail::MatrixTranspose<T_mat> transpose(const T_mat& mat)
{
    return detail::MatrixTranspose<T_mat>(mat);
}

}//ax
#endif//AX_EXPRESSION_H
