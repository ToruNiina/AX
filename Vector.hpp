#ifndef AX_VECTOR_H
#define AX_VECTOR_H
#include <array>
#include <iostream>
#include "VectorExp.hpp"

namespace ax
{
    template<std::size_t N>
    class RealVector
    {
        public:
            using value_trait = Vector;
            constexpr static std::size_t size = N;

        public:

            RealVector()
            {
                values.fill(0e0);
            }

            RealVector(const double d)
            {
                values.fill(d);
            } 

            RealVector(const std::array<double, N>& v)
                : values(v)
            {} 

            template<class E,
                     typename std::enable_if<is_VectorExpression<
                         typename E::value_trait>::value>::type*& = enabler>
            RealVector(const E& exp)
            {
                for(auto i(0); i<size; ++i)
                    (*this)[i] = exp[i];
            } 

            template<class E, 
                     typename std::enable_if<is_VectorExpression<
                         typename E::value_trait>::value>::type*& = enabler>
            RealVector& operator=(const E& exp)
            {
                for(auto i(0); i<size; ++i)
                    (*this)[i] = exp[i];
                return *this;
            } 

            template<class E, 
                     typename std::enable_if<is_VectorExpression<
                         typename E::value_trait>::value>::type*& = enabler>
            RealVector& operator+=(const E& exp)
            {
                *this = VectorAdd<RealVector, E>(*this, exp);
                return *this;
            } 


            template<class E, 
                     typename std::enable_if<is_VectorExpression<
                         typename E::value_trait>::value>::type*& = enabler>
            RealVector& operator-=(const E& exp)
            {
                *this = VectorSub<RealVector, E>(*this, exp);
                return *this;
            } 

            template<class E, 
                     typename std::enable_if<is_ScalarType<E>::value>::type*& =
                         enabler>
            RealVector& operator*=(const E& exp)
            {
                *this = VectorSclMul<RealVector>(exp, *this);
                return *this;
            } 

            template<class E, 
                     typename std::enable_if<is_ScalarType<E>::value>::type*& =
                         enabler>
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

        private:
            std::array<double, N> values;
    };

    template<std::size_t N>
    std::ostream& operator<<(std::ostream& os, const RealVector<N>& vec)
    {
        for(auto i(0); i<N; ++i)
            os << vec[i] << " ";
        return os;
    }
}

#endif//AX_VECTOR_H
