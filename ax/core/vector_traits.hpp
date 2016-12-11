#ifndef AX_VECTOR_TRAITS
#define AX_VECTOR_TRAITS
#include "matrix_traits.hpp"

namespace ax
{

template<typename T>
struct is_vector : public std::integral_constant<bool, is_matrix<T>::value &&
    (matrix_traits<T>::row == 1 || matrix_traits<T>::col == 1)>{};

template<typename vectorT>
struct vector_traits
{
    typedef vectorT vector_type;
    typedef typename vector_type::tag tag;
    typedef typename scalar_type_of<vector_type>::type scalar_type;
    typedef scalar_type value_type;

    constexpr static dimension_type row  = row_dimension_of<vectorT>::value;
    constexpr static dimension_type col  = column_dimension_of<vectorT>::value;
    constexpr static dimension_type size = (row == 1) ? col : row;
    constexpr static bool is_static      = size != DYNAMIC;
    constexpr static bool is_dynamic     = size == DYNAMIC;
};

template<typename vectorT, typename std::enable_if<
    is_vector<vectorT>::value && vector_traits<vectorT>::is_static,
    std::nullptr_t>::type = nullptr>
constexpr inline dimension_type size(const vectorT& vec)
{
    return vector_traits<vectorT>::size;
}

template<typename vectorT, typename std::enable_if<
    is_vector<vectorT>::value && vector_traits<vectorT>::is_dynamic,
    std::nullptr_t>::type = nullptr>
constexpr inline dimension_type size(const vectorT& vec)
{
    return vec.size();
}

} // ax
#endif /* AX_VECTOR_TRAITS */
