#ifndef AX_MATRIX_TRAITS
#define AX_MATRIX_TRAITS
#include "scalar_type_of.hpp"
#include "dimension.hpp"
#include "tags.hpp"

namespace ax
{
// forward decl
template<typename T, dimension_type R, dimension_type C>
class Matrix;
template<typename lT, typename Op, typename rT, dimension_type R, dimension_type C>
struct matrix_expression;
template<typename lT, typename rT, dimension_type R, dimension_type C>
struct matrix_product;
template<typename lT, typename Op, dimension_type R, dimension_type C>
struct scalar_expression;
template<typename lT, dimension_type R, dimension_type C>
struct matrix_transpose;

template<typename T>
struct is_matrix_tag : public std::false_type{};
template<>
struct is_matrix_tag<matrix_tag> : public std::true_type{};
template<>
struct is_matrix_tag<vector_tag> : public std::true_type{};
template<>
struct is_matrix_tag<expression_tag> : public std::true_type{};

template<typename T>
struct is_matrix : public std::false_type{};
template<typename T, dimension_type R, dimension_type C>
struct is_matrix<Matrix<T, R, C>> : public std::true_type{};
template<typename lT, typename Op, typename rT, dimension_type R, dimension_type C>
struct is_matrix<matrix_expression<lT, Op, rT, R, C>> : public std::true_type{};
template<typename lT, typename rT, dimension_type R, dimension_type C>
struct is_matrix<matrix_product<lT, rT, R, C>> : public std::true_type{};
template<typename lT, typename Op, dimension_type R, dimension_type C>
struct is_matrix<scalar_expression<lT, Op, R, C>> : public std::true_type{};
template<typename lT, dimension_type R, dimension_type C>
struct is_matrix<matrix_transpose<lT, R, C>> : public std::true_type{};

template<typename matrixT>
struct matrix_traits
{
    typedef matrixT matrix_type;
    typedef typename matrix_type::tag tag;
    typedef typename scalar_type_of<matrix_type>::type scalar_type;
    typedef scalar_type value_type;

    constexpr static dimension_type row  = row_dimension_of<matrixT>::value;
    constexpr static dimension_type col  = column_dimension_of<matrixT>::value;
    constexpr static bool is_dynamic_row = (row == DYNAMIC);
    constexpr static bool is_dynamic_col = (col == DYNAMIC);
    constexpr static bool is_static_row  = !is_dynamic_row;
    constexpr static bool is_static_col  = !is_dynamic_row;
    constexpr static bool is_static      = is_static_row  && is_static_col;
    constexpr static bool is_dynamic     = is_dynamic_row || is_dynamic_col;
    constexpr static bool is_square      = row == col;
};

template<typename matrixT, typename std::enable_if<
    is_matrix<matrixT>::value && matrix_traits<matrixT>::is_static_col,
    std::nullptr_t>::type = nullptr>
constexpr inline dimension_type column_size(const matrixT& mat)
{
    return matrix_traits<matrixT>::col;
}

template<typename matrixT, typename std::enable_if<
    is_matrix<matrixT>::value && matrix_traits<matrixT>::is_dynamic_col,
    std::nullptr_t>::type = nullptr>
constexpr inline dimension_type column_size(const matrixT& mat)
{
    return mat.column_size();
}


template<typename matrixT, typename std::enable_if<
    is_matrix<matrixT>::value && matrix_traits<matrixT>::is_static_row,
    std::nullptr_t>::type = nullptr>
constexpr inline dimension_type row_size(const matrixT& mat)
{
    return matrix_traits<matrixT>::row;
}

template<typename matrixT, typename std::enable_if<
    is_matrix<matrixT>::value && matrix_traits<matrixT>::is_dynamic_row,
    std::nullptr_t>::type = nullptr>
constexpr inline dimension_type row_size(const matrixT& mat)
{
    return mat.row_size();
}

} // ax

#endif /* AX_MATRIX_TRAITS */
