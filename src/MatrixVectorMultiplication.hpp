#ifndef AX_MATRIX_VECTOR_MULTIPLICATION
#define AX_MATRIX_VECTOR_MULTIPLICATION
#include "Vector3.hpp"
#include "Matrix.hpp"

namespace ax
{
    template<class M, class V>
    class MatVecMul
    {
        public:

            using value_trait = VectorExp;
            constexpr static std::size_t size = V::size;

            MatVecMul(const M& lhs, const V& rhs)
                :mat(lhs), vec(rhs)
            {}

            double operator[](const std::size_t i) const
            {
                double retval(0e0);
                for(std::size_t j(0); j<size; ++j)
                    retval += mat(i, j) * vec[j];
                return retval;
                // mat(i,0) * vec[0] + mat(i,1) * vec[1] + mat(i,2) * vec[2]
            }

        private:

            const M& mat;//matrix
            const V& vec;//vector
    };

    template<class M, class V, typename std::enable_if<
             is_MatrixExpression<typename M::value_trait>::value&&
             is_VectorExpression<typename V::value_trait>::value&&
             is_SameSize<V::size, M::col>::value
             >::type*& = enabler>
    MatVecMul<M,V> operator*(const M& mat, const V& vec)
    {
        return MatVecMul<M,V>(mat, vec);
    }

    template<class V, class M>
    class VecMatMul
    {
        public:

            using value_trait = VectorExp;
            constexpr static std::size_t size = V::size;

            VecMatMul(const V& lhs, const M& rhs)
                :vec(lhs), mat(rhs) 
            {}

            double operator[](const std::size_t i) const
            {
                double retval(0e0);
                for(std::size_t j(0); j<size; ++j)
                    retval += vec[j] * mat(j,i);
                return retval;
                // vec[0] * mat(0, i) + vec[1] * mat(1, i) + vec[2] * mat(2, i)
            }

        private:

            const V& vec;//vector
            const M& mat;//matrix
    };

    template<class V, class M, typename std::enable_if<
             is_MatrixExpression<typename M::value_trait>::value&&
             is_VectorExpression<typename V::value_trait>::value&&
             is_SameSize<V::size, M::row>::value
             >::type*& = enabler>
    VecMatMul<V,M> operator*(const V& vec, const M& mat)
    {
        return VecMatMul<V,M>(vec, mat);
    }
}
#endif//AX_MATRIX_VECTOR_MULTIPLICATION
