#ifndef AX_VECTOR_ROTATION
#define AX_VECTOR_ROTATION
#include "Vector3.hpp"
#include <boost/math/quaternion.hpp>

namespace ax
{
    using Realquat = boost::math::quaternion<double>;

    template<class A, class T,
             typename std::enable_if<
                 is_VectorExpression<typename A::value_trait>::value&&
                 is_VectorExpression<typename T::value_trait>::value&&
                 is_SameSize<A::size, 3>::value&&
                 is_SameSize<T::size, 3>::value
                 >::type*& = enabler
             >
    Realvec rotation(const double angle, const A& axis, const T& target)
    {
        const double sin_normalize(sin(angle * 0.5) / length(axis));

        const Realquat Q(cos(angle * 0.5), axis[0] * sin_normalize, 
                                           axis[1] * sin_normalize,
                                           axis[2] * sin_normalize);
        const Realquat P(0e0, target[0], target[1], target[2]);
        const Realquat S(Q * P * conj(Q));

        return RealVector<3>(S.R_component_2(), S.R_component_3(), S.R_component_4());
    }

}
#endif//AX_VECTOR_ROTATION
