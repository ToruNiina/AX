#ifndef AX_INVERSE_MATRIX_H
#define AX_INVERSE_MATRIX_H
#include "Matrix.hpp"

namespace ax
{

// for 2x2 dimentional
template<class L, typename std::enable_if<
             is_MatrixExpression<typename L::value_trait>::value&&
             is_SameSize<L::col, L::row>::value&&
             is_SameSize<L::col, 2>::value
             >::type*& = enabler>
const double determinant(const L& lhs)
{
    return lhs(0,0) * lhs(1,1) - lhs(1,0) * lhs(0,1);
}

// for 3x3 dimentional
template<class L, typename std::enable_if<
             is_MatrixExpression<typename L::value_trait>::value&&
             is_SameSize<L::col, L::row>::value&&
             is_SameSize<L::col, 3>::value
             >::type*& = enabler>
const double determinant(const L& lhs)
{
    return lhs(0,0) * lhs(1,1) * lhs(2,2) +
           lhs(1,0) * lhs(2,1) * lhs(0,2) +
           lhs(2,0) * lhs(0,1) * lhs(1,2) - 
           lhs(0,0) * lhs(2,1) * lhs(1,2) - 
           lhs(2,0) * lhs(1,1) * lhs(0,2) - 
           lhs(1,0) * lhs(0,1) * lhs(2,2);
}

template<class L, typename std::enable_if<
             is_MatrixExpression<typename L::value_trait>::value&&
             is_SameSize<L::col, L::row>::value&&
             is_SameSize<L::col, 2>::value
             >::type*& = enabler>
RealMatrix<L::row, L::col> inverse(const L& lhs)
{
    const double det_inv = 1e0 / determinant(lhs);
    RealMatrix<L::row, L::col> inv;
    inv(0,0) =  det_inv * lhs(1,1);
    inv(1,1) =  det_inv * lhs(0,0);
    inv(0,1) = -det_inv * lhs(0,1);
    inv(1,0) = -det_inv * lhs(1,0);
    return inv;
}

template<class L, typename std::enable_if<
             is_MatrixExpression<typename L::value_trait>::value&&
             is_SameSize<L::col, L::row>::value&&
             is_SameSize<L::col, 3>::value
             >::type*& = enabler>
RealMatrix<L::row, L::col> inverse(const L& lhs_)
{
    const L lhs = lhs_;
    const double det_inv = 1e0 / determinant(lhs);

    RealMatrix<L::row, L::col> inv;
    inv(0,0) = det_inv * (lhs(1,1) * lhs(2,2) - lhs(1,2) * lhs(2,1));
    inv(1,1) = det_inv * (lhs(0,0) * lhs(2,2) - lhs(0,2) * lhs(2,0));
    inv(2,2) = det_inv * (lhs(0,0) * lhs(1,1) - lhs(0,1) * lhs(1,0));

    inv(0,1) = det_inv * (lhs(0,2) * lhs(2,1) - lhs(0,1) * lhs(2,2));
    inv(0,2) = det_inv * (lhs(0,1) * lhs(1,2) - lhs(0,2) * lhs(1,1));
    inv(1,2) = det_inv * (lhs(0,2) * lhs(1,0) - lhs(0,0) * lhs(1,2));

    inv(1,0) = det_inv * (lhs(1,2) * lhs(2,0) - lhs(1,0) * lhs(2,2));
    inv(2,0) = det_inv * (lhs(1,0) * lhs(2,1) - lhs(2,0) * lhs(1,1));
    inv(2,1) = det_inv * (lhs(2,0) * lhs(0,1) - lhs(0,0) * lhs(2,1));
    return inv;
}

}
#endif /* AX_INVERSE_MATRIX_H */
