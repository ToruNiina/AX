#ifndef AX_INPUT_OUTPUT_H
#define AX_INPUT_OUTPUT_H
#include <iostream>
#include "Dimension.hpp"

namespace ax
{

template<class T_vec, typename std::enable_if<
    is_vector_expression<typename T_vec::tag>::value>::type*& = enabler>
std::ostream& operator<<(std::ostream& os, const T_vec& vec)
{
    for(std::size_t i = 0; i<dimension(vec); ++i)
        os << vec[i] << " ";
    return os;
}

template<class T_vec, typename std::enable_if<
    is_vector_expression<typename T_vec::tag>::value>::type*& = enabler>
std::istream& operator>>(std::istream& is, T_vec& vec)
{
    for(std::size_t i = 0; i<dimension(vec); ++i)
        is >> vec[i];
    return is;
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

template<class T_mat, typename std::enable_if<
    is_matrix_expression<typename T_mat::tag>::value>::type*& = enabler>
std::ostream& operator<<(std::ostream& os, const T_mat& mat)
{
    for(std::size_t i = 0; i<dimension_row(mat); ++i)
    {
        for(std::size_t j = 0; j<dimension_col(mat); ++j)
            os << mat(i,j) << " ";
        std::cout << std::endl;
    }
    return os;
}

template<class T_mat, typename std::enable_if<
    is_matrix_expression<typename T_mat::tag>::value>::type*& = enabler>
std::istream& operator>>(std::istream& is, T_mat& mat)
{
    for(std::size_t i = 0; i<dimension_row(mat); ++i)
        for(std::size_t j = 0; j<dimension_col(mat); ++j)
            is >> mat(i,j);
    return is;
}

}
#endif /*AX_INPUT_OUTPUT_H*/
