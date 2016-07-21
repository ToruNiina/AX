#ifndef AX_INVERSE_MATRIX_H
#define AX_INVERSE_MATRIX_H
#include "Matrix.hpp"

namespace ax
{

// for 2x2 dimentional
template<class T_mat, typename std::enable_if<
    is_matrix_expression<typename T_mat::tag>::value&&
    is_same_dimension<T_mat::dim_col, T_mat::dim_row>::value&&
    is_same_dimension<T_mat::dim_col, 2>::value>::type*& = enabler>
inline typename T_mat::elem_t
determinant(const T_mat& mat)
{
    return mat(0,0) * mat(1,1) - mat(1,0) * mat(0,1);
}

// for 3x3 dimentional
template<class T_mat, typename std::enable_if<
    is_matrix_expression<typename T_mat::tag>::value&&
    is_same_dimension<T_mat::dim_col, T_mat::dim_row>::value&&
    is_same_dimension<T_mat::dim_col, 3>::value>::type*& = enabler>
inline typename T_mat::elem_t
determinant(const T_mat& mat)
{
    return mat(0,0) * mat(1,1) * mat(2,2) +
           mat(1,0) * mat(2,1) * mat(0,2) +
           mat(2,0) * mat(0,1) * mat(1,2) - 
           mat(0,0) * mat(2,1) * mat(1,2) - 
           mat(2,0) * mat(1,1) * mat(0,2) - 
           mat(1,0) * mat(0,1) * mat(2,2);
}

template<class T_mat, typename std::enable_if<
    is_matrix_expression<typename T_mat::tag>::value&&
    is_same_dimension<T_mat::dim_col, T_mat::dim_row>::value&&
    is_same_dimension<T_mat::dim_col, 2>::value>::type*& = enabler>
Matrix<typename T_mat::elem_t, T_mat::dim_row, T_mat::dim_col>
inverse(const T_mat& mat)
{
    const auto det_inv = 1e0 / determinant(mat);
    Matrix<typename T_mat::elem_t, T_mat::dim_row, T_mat::dim_col> inv;
    inv(0,0) =  det_inv * mat(1,1);
    inv(1,1) =  det_inv * mat(0,0);
    inv(0,1) = -det_inv * mat(0,1);
    inv(1,0) = -det_inv * mat(1,0);
    return inv;
}

template<class T_mat, typename std::enable_if<
    is_matrix_expression<typename T_mat::tag>::value&&
    is_same_dimension<T_mat::dim_col, T_mat::dim_row>::value&&
    is_same_dimension<T_mat::dim_col, 3>::value>::type*& = enabler>
Matrix<typename T_mat::elem_t, T_mat::dim_row, T_mat::dim_col>
inverse(const T_mat& mat)
{
    const auto det_inv = 1e0 / determinant(mat);

    Matrix<typename T_mat::elem_t, T_mat::dim_row, T_mat::dim_col> inv;
    inv(0,0) = det_inv * (mat(1,1) * mat(2,2) - mat(1,2) * mat(2,1));
    inv(1,1) = det_inv * (mat(0,0) * mat(2,2) - mat(0,2) * mat(2,0));
    inv(2,2) = det_inv * (mat(0,0) * mat(1,1) - mat(0,1) * mat(1,0));

    inv(0,1) = det_inv * (mat(0,2) * mat(2,1) - mat(0,1) * mat(2,2));
    inv(0,2) = det_inv * (mat(0,1) * mat(1,2) - mat(0,2) * mat(1,1));
    inv(1,2) = det_inv * (mat(0,2) * mat(1,0) - mat(0,0) * mat(1,2));

    inv(1,0) = det_inv * (mat(1,2) * mat(2,0) - mat(1,0) * mat(2,2));
    inv(2,0) = det_inv * (mat(1,0) * mat(2,1) - mat(2,0) * mat(1,1));
    inv(2,1) = det_inv * (mat(2,0) * mat(0,1) - mat(0,0) * mat(2,1));
    return inv;
}

}
#endif /* AX_INVERSE_MATRIX_H */
