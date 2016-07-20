#ifndef AX_INPUT_OUTPUT_H
#define AX_INPUT_OUTPUT_H
#include <iostream>
#include <array>
#include "TypeTraits.hpp"

namespace ax
{

template<class T_vec,
         typename std::enable_if<
                 is_vector_expression<typename T_vec::tag>::value
             >::type*& = enabler>
std::ostream& operator<<(std::ostream& os, const T_vec& vec)
{
    for(std::size_t i = 0; i<dimension(vec); ++i)
        os << vec[i] << " ";
    return os;
}

// template<class V,
//          typename std::enable_if<
//                  is_AVXVectorExpression<typename V::value_trait>::value
//              >::type*& = enabler>
// std::ostream& operator<<(std::ostream& os, const V& vec)
// {
//     std::array<double, V::size> val = vec.get();
//     for(auto i(0); i<V::size; ++i)
//         os << val[i] << " ";
//     return os;
// }

// template<class M,
//          typename std::enable_if<
//                  is_MatrixExpression<typename M::value_trait>::value
//              >::type*& = enabler>
// std::ostream& operator<<(std::ostream& os, const M& mat)
// {
//     for(std::size_t i(0); i<M::row; ++i)
//     {
//         for(std::size_t j(0); j<M::col; ++j)
//             os << mat(i,j) << " ";
//         std::cout << std::endl;
//     }
//     return os;
// }
//
// template<class M,
//          typename std::enable_if<
//                  is_DynamicMatrixExpression<typename M::value_trait>::value
//              >::type*& = enabler>
// std::ostream& operator<<(std::ostream& os, const M& mat)
// {
//     for(std::size_t i(0); i<mat.size_row(); ++i)
//     {
//         for(std::size_t j(0); j<mat.size_col(); ++j)
//             os << mat(i,j) << " ";
//         std::cout << std::endl;
//     }
//     return os;
// }

}
#endif /*AX_INPUT_OUTPUT_H*/
