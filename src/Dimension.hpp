#ifndef AX_DIMENSION_FUNC_H
#define AX_DIMENSION_FUNC_H
#include "TypeTraits.hpp"
#include <utility>

namespace ax
{

// for static vector
template <class T_vec, typename std::enable_if<
              is_vector_type<typename T_vec::tag>::value&&
              is_static_dimension<T_vec::dim>::value>::type*& = enabler>
constexpr inline std::size_t dimension(const T_vec& v)
{
    return T_vec::dim;
}

// for dynamic vector
template <class T_vec, typename std::enable_if<
              is_vector_type<typename T_vec::tag>::value&&
              is_dynamic_dimension<T_vec::dim>::value>::type*& = enabler>
constexpr inline std::size_t dimension(const T_vec& v)
{
    return v.size();
}

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
    //XXX: in vector_scalar_operation, l must be vector
    return dimension(vexpr.l_);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Matrix ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template <class T_mat, typename std::enable_if<
              is_matrix_type<typename T_mat::tag>::value&&
              is_static_dimension<T_mat::dim_col>::value>::type*& = enabler>
constexpr inline std::size_t dimension_col(const T_mat&)
{
    return T_mat::dim_col;
}

template <class T_mat, typename std::enable_if<
              is_matrix_type<typename T_mat::tag>::value&&
              is_dynamic_dimension<T_mat::dim_col>::value>::type*& = enabler>
constexpr inline std::size_t dimension_col(const T_mat& m)
{
    return m.size_col();
}

template <class T_mexpr, typename std::enable_if<
              is_exactly_matrix_expr<typename T_mexpr::tag>::value&&
              is_static_dimension<T_mexpr::dim_col>::value>::type*& = enabler>
constexpr inline std::size_t dimension_col(const T_mexpr&)
{
    return T_mexpr::dim_col;
}

template <class T_mexpr, typename std::enable_if<
              is_exactly_matrix_expr<typename T_mexpr::tag>::value&&
              is_dynamic_dimension<T_mexpr::dim>::value>::type*& = enabler>
constexpr inline std::size_t dimension_col(const T_mexpr& mexpr)
{
    return dimension_col(mexpr.l_);
}

template <class T_mat, typename std::enable_if<
              is_matrix_type<typename T_mat::tag>::value&&
              is_static_dimension<T_mat::dim_row>::value>::type*& = enabler>
constexpr inline std::size_t dimension_row(const T_mat&)
{
    return T_mat::dim_row;
}

template <class T_mat, typename std::enable_if<
              is_matrix_type<typename T_mat::tag>::value&&
              is_dynamic_dimension<T_mat::dim_row>::value>::type*& = enabler>
constexpr inline std::size_t dimension_row(const T_mat& m)
{
    return m.size_row();
}

template <class T_mexpr, typename std::enable_if<
              is_exactly_matrix_expr<typename T_mexpr::tag>::value&&
              is_static_dimension<T_mexpr::dim_row>::value>::type*& = enabler>
constexpr inline std::size_t dimension_row(const T_mexpr&){return T_mexpr::dim_row;}

template <class T_mexpr, typename std::enable_if<
              is_exactly_matrix_expr<typename T_mexpr::tag>::value&&
              is_dynamic_dimension<T_mexpr::dim>::value>::type*& = enabler>
constexpr inline std::size_t dimension_row(const T_mexpr& mexpr)
{
    return dimension_row(mexpr.l_);
}

template <class T_mat, typename std::enable_if<
              is_matrix_type<typename T_mat::tag>::value&&
              is_static_dimension<T_mat::dim_row>::value>::type*& = enabler>
constexpr inline std::pair<std::size_t, std::size_t> dimension(const T_mat& m)
{
    return std::make_pair(dimension_row(m), dimension_col(m));
}

}// ax
#endif /* AX_DIMENSION_FUNC_H */
