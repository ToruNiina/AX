#ifndef AX_3_DIMENTIONAL_VECTOR_H
#define AX_3_DIMENTIONAL_VECTOR_H
#include "Vector.hpp"

namespace ax
{
    template <>
    class RealVector<3>
    {
        public:
            using value_trait = Vector;
            constexpr static std::size_t size = 3;

        public:

            RealVector()
                : values({{0e0, 0e0, 0e0}})
            {}

            RealVector(double d)
                : values({{d, d, d}})
            {} 

            RealVector(double x, double y, double z)
                : values({{x, y, z}})
            {} 

            RealVector(const std::array<double, 3>& array)
                : values(array)
            {} 

            RealVector(const RealVector<3>& v)
                : values(v.values)
            {} 

            template<class E, 
                     typename std::enable_if<
                         is_VectorExpression<typename E::value_trait>::value&&
                         is_SameSize<E::size, 3>::value
                         >::type*& = enabler>
            RealVector(const E& exp)
            {
                (*this)[0] = exp[0];
                (*this)[1] = exp[1];
                (*this)[2] = exp[2];
            } 

            template<class E, 
                     typename std::enable_if<
                         is_VectorExpression<typename E::value_trait>::value&&
                         is_SameSize<E::size, 3>::value
                         >::type*& = enabler>
            RealVector& operator=(const E& exp)
            {
                (*this)[0] = exp[0];
                (*this)[1] = exp[1];
                (*this)[2] = exp[2];
                return *this;
            } 

            template<class E, 
                     typename std::enable_if<
                         is_VectorExpression<typename E::value_trait>::value&&
                         is_SameSize<E::size, 3>::value
                         >::type*& = enabler>
            RealVector& operator+=(const E& exp)
            {
                *this = VectorAdd<RealVector, E>(*this, exp);
                return *this;
            } 

            template<class E, 
                     typename std::enable_if<
                         is_VectorExpression<typename E::value_trait>::value&&
                         is_SameSize<E::size, 3>::value
                         >::type*& = enabler>
            RealVector& operator-=(const E& exp)
            {
                *this = VectorSub<RealVector, E>(*this, exp);
                return *this;
            } 

            template<class E, typename std::enable_if<
                         is_ScalarType<E>::value>::type*& = enabler>
            RealVector& operator*=(const E& exp)
            {
                *this = VectorSclMul<RealVector>(exp, *this);
                return *this;
            } 

            template<class E, typename std::enable_if<
                         is_ScalarType<E>::value>::type*& = enabler>
            RealVector& operator/=(const E& exp)
            {
                *this = VectorSclDiv<RealVector>(*this, exp);
                return *this;
            } 

            double operator[](const std::size_t i) const
            {
                return values[i];
            }

            double& operator[](const std::size_t i)
            {
                return values[i];
            }

            double at(const std::size_t i) const
            {
                return values.at(i);
            }

            double& at(const std::size_t i)
            {
                return values.at(i);
            }

        private:
            std::array<double, 3> values;
    };
    using Realvec = RealVector<3>;
}
#endif//AX_VECTOR_H
