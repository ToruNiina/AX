#ifndef AX_OPERATOR
#define AX_OPERATOR
#include "calculator.hpp"
#include "expression.hpp"
#include "matrix_traits.hpp"
#include <stdexcept>

namespace ax
{
// operator+

template<typename lhsT, typename rhsT, typename std::enable_if<
    matrix_traits<lhsT>::is_static && matrix_traits<lhsT>::is_static &&
    matrix_traits<lhsT>::row == matrix_traits<rhsT>::row &&
    matrix_traits<lhsT>::col == matrix_traits<rhsT>::col,
    std::nullptr_t>::type = nullptr>
inline matrix_expression<lhsT, add<typename matrix_traits<lhsT>::scalar_type,
    typename matrix_traits<rhsT>::scalar_type>, rhsT, matrix_traits<lhsT>::row,
    matrix_traits<lhsT>::col>
operator+(const lhsT& lhs, const rhsT& rhs)
{
    return matrix_expression<lhsT, add<typename matrix_traits<lhsT>::scalar_type,
        typename matrix_traits<rhsT>::scalar_type>, rhsT, matrix_traits<lhsT>::row,
        matrix_traits<lhsT>::col>(lhs, rhs);
}

template<typename lhsT, typename rhsT, typename std::enable_if<
    matrix_traits<lhsT>::is_static_row && matrix_traits<lhsT>::is_static_row &&
    (matrix_traits<lhsT>::is_dynamic_col || matrix_traits<rhsT>::is_dynamic_col) &&
    matrix_traits<lhsT>::row == matrix_traits<rhsT>::row,
    std::nullptr_t>::type = nullptr>
inline matrix_expression<lhsT, add<typename matrix_traits<lhsT>::scalar_type,
    typename matrix_traits<rhsT>::scalar_type>, rhsT,
    row_dimension_of<lhsT>::value, DYNAMIC>
operator+(const lhsT& lhs, const rhsT& rhs)
{
    if(column_size(lhs) != column_size(rhs))
        throw std::out_of_range("operator+: dimensions are not same");
    return matrix_expression<lhsT, add<typename matrix_traits<lhsT>::scalar_type,
        typename matrix_traits<rhsT>::scalar_type>, rhsT,
        row_dimension_of<lhsT>::value, DYNAMIC>(lhs, rhs);
}

template<typename lhsT, typename rhsT, typename std::enable_if<
    matrix_traits<lhsT>::is_static_col && matrix_traits<lhsT>::is_static_col &&
    (matrix_traits<lhsT>::is_dynamic_row || matrix_traits<rhsT>::is_dynamic_row) &&
    matrix_traits<lhsT>::col == matrix_traits<rhsT>::col, std::nullptr_t
    >::type = nullptr>
inline matrix_expression<lhsT, add<typename matrix_traits<lhsT>::scalar_type,
    typename matrix_traits<rhsT>::scalar_type>, rhsT, DYNAMIC,
    column_dimension_of<lhsT>::value>
operator+(const lhsT& lhs, const rhsT& rhs)
{
    if(row_size(lhs) != row_size(rhs))
        throw std::out_of_range("operator+: dimensions are not same");
    return matrix_expression<lhsT, add<typename matrix_traits<lhsT>::scalar_type,
        typename matrix_traits<rhsT>::scalar_type>, rhsT, DYNAMIC,
        column_dimension_of<lhsT>::value>(lhs, rhs);
}

template<typename lhsT, typename rhsT, typename std::enable_if<
    (matrix_traits<lhsT>::is_dynamic_row || matrix_traits<rhsT>::is_dynamic_row) &&
    (matrix_traits<lhsT>::is_dynamic_col || matrix_traits<rhsT>::is_dynamic_col),
    std::nullptr_t
    >::type = nullptr>
inline matrix_expression<lhsT, add<typename matrix_traits<lhsT>::scalar_type,
    typename matrix_traits<rhsT>::scalar_type>, rhsT, DYNAMIC, DYNAMIC>
operator+(const lhsT& lhs, const rhsT& rhs)
{
    if((row_size(lhs) != row_size(rhs)) || (column_size(lhs) != column_size(rhs)))
        throw std::out_of_range("operator+: dimensions are not same");
    return matrix_expression<lhsT, add<typename matrix_traits<lhsT>::scalar_type,
        typename matrix_traits<rhsT>::scalar_type>, rhsT, DYNAMIC, DYNAMIC>(lhs, rhs);
}

// operator-

template<typename lhsT, typename rhsT, typename std::enable_if<
    matrix_traits<lhsT>::is_static && matrix_traits<lhsT>::is_static &&
    matrix_traits<lhsT>::row == matrix_traits<rhsT>::row &&
    matrix_traits<lhsT>::col == matrix_traits<rhsT>::col, std::nullptr_t
    >::type = nullptr>
inline matrix_expression<lhsT, subtract<typename matrix_traits<lhsT>::scalar_type,
    typename matrix_traits<rhsT>::scalar_type>, rhsT,
    row_dimension_of<lhsT>::value, column_dimension_of<lhsT>::value>
operator-(const lhsT& lhs, const rhsT& rhs)
{
    return matrix_expression<lhsT, subtract<typename matrix_traits<lhsT>::scalar_type,
        typename matrix_traits<rhsT>::scalar_type>, rhsT, row_dimension_of<lhsT>::value,
        column_dimension_of<lhsT>::value>(lhs, rhs);
}

template<typename lhsT, typename rhsT, typename std::enable_if<
    matrix_traits<lhsT>::is_static_row && matrix_traits<lhsT>::is_static_row &&
    (matrix_traits<lhsT>::is_dynamic_col || matrix_traits<rhsT>::is_dynamic_col) &&
    matrix_traits<lhsT>::row == matrix_traits<rhsT>::row, std::nullptr_t
    >::type = nullptr>
inline matrix_expression<lhsT, subtract<typename matrix_traits<lhsT>::scalar_type,
    typename matrix_traits<rhsT>::scalar_type>, rhsT,
    row_dimension_of<lhsT>::value, DYNAMIC>
operator-(const lhsT& lhs, const rhsT& rhs)
{
    if(column_size(lhs) != column_size(rhs))
        throw std::out_of_range("operator-: dimensions are not same");
    return matrix_expression<lhsT, subtract<typename matrix_traits<lhsT>::scalar_type,
        typename matrix_traits<rhsT>::scalar_type>, rhsT, row_dimension_of<lhsT>::value,
        DYNAMIC>(lhs, rhs);
}

template<typename lhsT, typename rhsT, typename std::enable_if<
    matrix_traits<lhsT>::is_static_col && matrix_traits<lhsT>::is_static_col &&
    (matrix_traits<lhsT>::is_dynamic_row || matrix_traits<rhsT>::is_dynamic_row) &&
    matrix_traits<lhsT>::col == matrix_traits<rhsT>::col, std::nullptr_t
    >::type = nullptr>
inline matrix_expression<lhsT, subtract<typename matrix_traits<lhsT>::scalar_type,
    typename matrix_traits<rhsT>::scalar_type>, rhsT, DYNAMIC,
    column_dimension_of<lhsT>::value>
operator-(const lhsT& lhs, const rhsT& rhs)
{
    if(row_size(lhs) != row_size(rhs))
        throw std::out_of_range("operator-: dimensions are not same");
    return matrix_expression<lhsT, subtract<typename matrix_traits<lhsT>::scalar_type,
        typename matrix_traits<rhsT>::scalar_type>, rhsT, DYNAMIC,
        column_dimension_of<rhsT>::value>(lhs, rhs);
}

template<typename lhsT, typename rhsT, typename std::enable_if<
    (matrix_traits<lhsT>::is_dynamic_row || matrix_traits<rhsT>::is_dynamic_row) &&
    (matrix_traits<lhsT>::is_dynamic_col || matrix_traits<rhsT>::is_dynamic_col),
    std::nullptr_t
    >::type = nullptr>
inline matrix_expression<lhsT, subtract<typename matrix_traits<lhsT>::scalar_type,
    typename matrix_traits<rhsT>::scalar_type>, rhsT, DYNAMIC, DYNAMIC>
operator-(const lhsT& lhs, const rhsT& rhs)
{
    if((row_size(lhs) != row_size(rhs)) || (column_size(lhs) != column_size(rhs)))
        throw std::out_of_range("operator-: dimensions are not same");
    return matrix_expression<lhsT, subtract<typename matrix_traits<lhsT>::scalar_type,
        typename matrix_traits<rhsT>::scalar_type>, rhsT, DYNAMIC, DYNAMIC>(lhs, rhs);
}

// operator*

template<typename lhsT, typename rhsT, typename std::enable_if<
    matrix_traits<lhsT>::is_static_col && matrix_traits<rhsT>::is_static_row &&
    matrix_traits<lhsT>::col == matrix_traits<rhsT>::row, std::nullptr_t
    >::type = nullptr>
inline matrix_product<lhsT, rhsT,
    row_dimension_of<lhsT>::value, column_dimension_of<rhsT>::value>
operator*(const lhsT& lhs, const rhsT& rhs)
{
    return matrix_product<lhsT, rhsT, row_dimension_of<lhsT>::value,
               column_dimension_of<rhsT>::value>(lhs, rhs);
}

template<typename lhsT, typename rhsT, typename std::enable_if<
    (matrix_traits<lhsT>::is_dynamic_col || matrix_traits<rhsT>::is_dynamic_row),
    std::nullptr_t>::type = nullptr>
inline matrix_product<lhsT, rhsT,
    row_dimension_of<lhsT>::value, column_dimension_of<rhsT>::value>
operator*(const lhsT& lhs, const rhsT& rhs)
{
    if(column_size(lhs) != row_size(rhs))
        throw std::out_of_range("operator*: column size and row size");
    return matrix_product<lhsT, rhsT, row_dimension_of<lhsT>::value,
               column_dimension_of<rhsT>::value>(lhs, rhs);
}

// scalar product 

template<typename matT, typename sclT, typename std::enable_if<
    is_matrix<matT>::value &&
    std::is_convertible<typename matrix_traits<matT>::scalar_type, sclT>::value,
    std::nullptr_t>::type = nullptr>
inline scalar_expression<matT, multiply<typename matrix_traits<matT>::scalar_type,
    sclT>, matrix_traits<matT>::row, matrix_traits<matT>::col>
operator*(const matT& mat, const sclT scl)
{
    return scalar_expression<matT, multiply<typename matrix_traits<matT>::scalar_type,
       sclT>, matrix_traits<matT>::row, matrix_traits<matT>::col>(mat, scl);
}

template<typename matT, typename sclT, typename std::enable_if<
    is_matrix<matT>::value &&
    std::is_convertible<typename matrix_traits<matT>::scalar_type, sclT>::value,
    std::nullptr_t>::type = nullptr>
inline scalar_expression<matT, multiply<typename matrix_traits<matT>::scalar_type,
    sclT>, matrix_traits<matT>::row, matrix_traits<matT>::col>
operator*(const sclT scl, const matT& mat)
{
    return scalar_expression<matT, multiply<typename matrix_traits<matT>::scalar_type,
       sclT>, matrix_traits<matT>::row, matrix_traits<matT>::col>(mat, scl);
}

template<typename matT, typename sclT, typename std::enable_if<
    is_matrix<matT>::value &&
    std::is_convertible<typename matrix_traits<matT>::scalar_type, sclT>::value,
    std::nullptr_t>::type = nullptr>
inline scalar_expression<matT, divide<typename matrix_traits<matT>::scalar_type,
    sclT>, matrix_traits<matT>::row, matrix_traits<matT>::col>
operator/(const matT& mat, const sclT scl)
{
    return scalar_expression<matT, divide<typename matrix_traits<matT>::scalar_type,
       sclT>, matrix_traits<matT>::row, matrix_traits<matT>::col>(mat, scl);
}

} // ax

#endif /*AX_OPERATOR*/
