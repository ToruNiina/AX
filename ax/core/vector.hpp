#ifndef AX_VECTOR
#define AX_VECTOR
#include "matrix.hpp"
#include "vector_traits.hpp"
#include "static_row_vector.hpp"
#include "static_column_vector.hpp"
#include "dynamic_row_vector.hpp"
#include "dynamic_column_vector.hpp"
#include <cmath>

namespace ax
{

template<typename T, dimension_type N>
using Vector = Matrix<T, N, 1>;

template<typename vecT, typename std::enable_if<
    is_vector<vecT>::value && vector_traits<vecT>::is_static,
    std::nullptr_t>::type = nullptr>
inline typename vector_traits<vecT>::scalar_type
length_sq(const vecT& vec)
{
    typename vector_traits<vecT>::scalar_type retval = 0;
    for(dimension_type i=0; i<vector_traits<vecT>::size; ++i)
        retval += vec[i] * vec[i];
    return retval;
}

template<typename vecT, typename std::enable_if<
    is_vector<vecT>::value && vector_traits<vecT>::is_dynamic,
    std::nullptr_t>::type = nullptr>
inline typename vector_traits<vecT>::scalar_type
length_sq(const vecT& vec)
{
    typename vector_traits<vecT>::scalar_type retval = 0;
    for(dimension_type i=0; i<size(vec); ++i)
        retval += vec[i] * vec[i];
    return retval;
}

template<typename vecT, class = typename std::enable_if<
    is_vector<vecT>::value>::type>
inline typename vector_traits<vecT>::scalar_type
length(const vecT& vec)
{
    return std::sqrt(length_sq(vec));
}

template<typename lhsT, typename rhsT, typename std::enable_if<
    is_vector<lhsT>::value && is_vector<rhsT>::value &&
    vector_traits<lhsT>::is_static && vector_traits<rhsT>::is_static &&
    vector_traits<lhsT>::size == vector_traits<rhsT>::size &&
    std::is_convertible<typename vector_traits<lhsT>::scalar_type,
        typename vector_traits<rhsT>::scalar_type>::value,
    std::nullptr_t>::type = nullptr>
inline typename vector_traits<lhsT>::scalar_type
dot_product(const lhsT& lhs, const rhsT& rhs)
{
    typename vector_traits<lhsT>::scalar_type retval = 0;
    for(dimension_type i=0; i<vector_traits<lhsT>::size; ++i)
        retval += lhs[i] * rhs[i];
    return retval;
}

template<typename lhsT, typename rhsT, typename std::enable_if<
    is_vector<lhsT>::value && is_vector<rhsT>::value &&
    (vector_traits<lhsT>::is_dynamic || vector_traits<rhsT>::is_dynamic) &&
    std::is_convertible<typename vector_traits<lhsT>::scalar_type,
        typename vector_traits<rhsT>::scalar_type>::value,
    std::nullptr_t>::type = nullptr>
inline typename vector_traits<lhsT>::scalar_type
dot_product(const lhsT& lhs, const rhsT& rhs)
{
    if(size(lhs) != size(rhs))
        throw std::out_of_range("dot_product: dimensions are not same");
    typename vector_traits<lhsT>::scalar_type retval = 0;
    for(dimension_type i=0; i<size(lhs); ++i)
        retval += lhs[i] * rhs[i];
    return retval;
}

template<typename lhsT, typename rhsT, typename std::enable_if<
    is_vector<lhsT>::value && is_vector<rhsT>::value &&
    vector_traits<lhsT>::is_static && vector_traits<rhsT>::is_static &&
    vector_traits<lhsT>::size == 3 && vector_traits<rhsT>::size == 3 &&
    std::is_convertible<typename vector_traits<lhsT>::scalar_type,
                        typename vector_traits<rhsT>::scalar_type>::value,
    std::nullptr_t>::type = nullptr>
inline Vector<typename vector_traits<lhsT>::scalar_type, 3>
cross_product(const lhsT& lhs, const rhsT& rhs)
{
    Vector<typename vector_traits<lhsT>::scalar_type, 3> retval;
    retval[0] = lhs[1] * rhs[2] - lhs[2] * rhs[1];
    retval[1] = lhs[2] * rhs[0] - lhs[0] * rhs[2];
    retval[2] = lhs[0] * rhs[1] - lhs[1] * rhs[0];
    return retval;
}

template<typename lhsT, typename rhsT, typename std::enable_if<
    is_vector<lhsT>::value && is_vector<rhsT>::value &&
    (vector_traits<lhsT>::is_dynamic || vector_traits<rhsT>::is_dynamic) &&
    std::is_convertible<typename vector_traits<lhsT>::scalar_type,
        typename vector_traits<rhsT>::scalar_type>::value,
    std::nullptr_t>::type = nullptr>
inline Vector<typename vector_traits<lhsT>::scalar_type, 3>
cross_product(const lhsT& lhs, const rhsT& rhs)
{
    if(size(lhs) != 3 || size(rhs) != 3)
        throw std::out_of_range("cross_product: 3d only");
    Vector<typename vector_traits<lhsT>::scalar_type, 3> retval;
    retval[0] = lhs[1] * rhs[2] - lhs[2] * rhs[1];
    retval[1] = lhs[2] * rhs[0] - lhs[0] * rhs[2];
    retval[2] = lhs[0] * rhs[1] - lhs[1] * rhs[0];
    return retval;
}

template<typename vecT, class = typename std::enable_if<
    is_vector<vecT>::value>::type>
inline scalar_expression<vecT, multiply<typename vector_traits<vecT>::scalar_type,
        typename vector_traits<vecT>::scalar_type>, matrix_traits<vecT>::row,
    matrix_traits<vecT>::col>
regularize(const vecT& vec)
{
    return scalar_expression<vecT, multiply<typename vector_traits<vecT>::scalar_type,
        typename vector_traits<vecT>::scalar_type>, matrix_traits<vecT>::row,
        matrix_traits<vecT>::col>(vec, 1. / std::sqrt(length_sq(vec)));
}

} // ax
#endif /* AX_VECTOR */
