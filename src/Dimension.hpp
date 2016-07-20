#ifndef AX_DIMENSION_FUNC_H
#define AX_DIMENSION_FUNC_H
#include "TypeTraits.hpp"

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

}// ax
#endif /* AX_DIMENSION_FUNC_H */
