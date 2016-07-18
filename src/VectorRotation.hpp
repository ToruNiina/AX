#ifndef AX_VECTOR_ROTATION
#define AX_VECTOR_ROTATION
#include "Vector.hpp"
#include <boost/math/quaternion.hpp>

namespace ax
{

template <class T_lhs, class T_rhs,
          typename std::enable_if<
              is_static_dimension<T_lhs::dim>::value&&
              is_same_dimension<T_lhs::dim, 3>::value&&
              is_same_vector<T_lhs, T_rhs>::value
              >::type*& = enabler>
Vector<typename T_lhs::elem_t, 3>
rotation(const double angle, const T_lhs& axis, const T_rhs& target)
{
    using Quat = boost::math::quaternion<double>;
    using namespace boost::math;

    const double sin_normalize(sin(angle * 0.5) / length(axis));

    const Quat Q(cos(angle * 0.5), axis[0] * sin_normalize, 
                                   axis[1] * sin_normalize,
                                   axis[2] * sin_normalize);
    const Quat P(0e0, target[0], target[1], target[2]);
    const Quat S(Q * P * conj(Q));

    return Vector<typename T_lhs::elem_t, 3>(
            S.R_component_2(), S.R_component_3(), S.R_component_4());
}

}
#endif//AX_VECTOR_ROTATION
