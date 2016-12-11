#ifndef AX_MATRIX
#define AX_MATRIX

#include "static_matrix.hpp"
#include "operator.hpp"

namespace ax
{

template<typename matT, class = typename std::enable_if<
    is_matrix<matT>::value>::type>
inline matrix_transpose<matT, matrix_traits<matT>::row, matrix_traits<matT>::col>
transpose(const matT& mat)
{
    return matrix_transpose<matT, matrix_traits<matT>::row,
               matrix_traits<matT>::col>(mat);
}

template<typename matT, class = typename std::enable_if<
    is_matrix<matT>::value && matrix_traits<matT>::row == matrix_traits<matT>::col
    >::type>
inline typename matrix_traits<matT>::scalar_type
trace(const matT& mat)
{
    typename matrix_traits<matT>::scalar_type retval = 0;
    for(dimension_type i=0; i<matrix_traits<matT>::row; ++i)
        retval += mat(i, i);
    return retval;
}

template<typename scalarT, dimension_type rowN, dimension_type colN>
inline Matrix<scalarT, rowN, colN> zero_matrix()
{
    Matrix<scalarT, rowN, colN> retval;
    for(dimension_type i=0; i<rowN; ++i)
    for(dimension_type j=0; j<colN; ++j)
        retval(i, j) = 0;
    return retval;
}

template<typename scalarT, dimension_type rowN, dimension_type colN>
inline Matrix<scalarT, rowN, colN> filled_matrix(const scalarT s)
{
    Matrix<scalarT, rowN, colN> retval;
    for(dimension_type i=0; i<rowN; ++i)
    for(dimension_type j=0; j<colN; ++j)
        retval(i, j) = s;
    return retval;
}

template<typename scalarT, dimension_type N>
inline Matrix<scalarT, N, N> identity_matrix(const scalarT s = 1)
{
    Matrix<scalarT, N, N> retval = zero_matrix<scalarT, N, N>();
    for(dimension_type i=0; i<N; ++i)
        retval(i, i) = s;
    return retval;
}

} // ax
#endif/* AX_MATRIX */
