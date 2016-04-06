#ifndef AX_MATRIX_H
#define AX_MATRIX_H
#include <array>
#include <iostream>
#include "MatrixExp.hpp"

namespace ax
{
    template<std::size_t R, std::size_t C>
    class RealMatrix
    {
        public:

            using value_trait = Matrix;
            constexpr static std::size_t row = R;//number of row
            constexpr static std::size_t col = C;//number of column
            /*   C x R matrix
             C O L U M N s
          R ( M_00 M_01 ... M_0C )
          O ( M_10  .        .   )
          W (  ...       .   .   )
          s ( M_R0 ...      M_RC )
            */

        public:

            RealMatrix()
            {
                for(std::size_t i(0); i<R; ++i)
                    values[i].fill(0e0);
            }

            // to make Identity matrix or something
            RealMatrix(const double d)
            {
                for(std::size_t i(0); i<R; ++i)
                    for(std::size_t j(0); j<C; ++j)
                        if(i == j)
                            values[i][i] = d;
                        else
                            values[i][j] = 0e0;
            }

            template<class E,
                     typename std::enable_if<
                         is_MatrixExpression<typename E::value_trait>::value&&
                         is_SameSize<E::col, col>::value&&
                         is_SameSize<E::row, row>::value
                         >::type*& = enabler>
            RealMatrix(const E& mat)
            {
                for(std::size_t i(0); i<R; ++i)
                    for(std::size_t j(0); j<C; ++j)
                       (*this)(i,j) = mat(i,j);
            }

            template<class E,
                     typename std::enable_if<
                         is_MatrixExpression<typename E::value_trait>::value&&
                         is_SameSize<E::col, col>::value&&
                         is_SameSize<E::row, row>::value
                         >::type*& = enabler>
            RealMatrix& operator=(const E& mat)
            {
                for(std::size_t i(0); i<R; ++i)
                    for(std::size_t j(0); j<C; ++j)
                       (*this)(i,j) = mat(i,j);
                return *this;
            }

            template<class E,
                     typename std::enable_if<
                         is_MatrixExpression<typename E::value_trait>::value&&
                         is_SameSize<E::col, col>::value&&
                         is_SameSize<E::row, row>::value
                         >::type*& = enabler>
            RealMatrix& operator+=(const E& mat)
            {
                *this = MatrixAdd<RealMatrix, E>(*this, mat);
                return *this;
            }

            template<class E,
                     typename std::enable_if<
                         is_MatrixExpression<typename E::value_trait>::value&&
                         is_SameSize<E::col, col>::value&&
                         is_SameSize<E::row, row>::value
                         >::type*& = enabler>
            RealMatrix& operator-=(const E& mat)
            {
                *this = MatrixSub<RealMatrix, E>(*this, mat);
                return *this;
            }

            //operator*= can be used in the case of same size matrix
            template<class E,
                     typename std::enable_if<
                         is_MatrixExpression<typename E::value_trait>::value&&
                         is_SameSize<E::col, col>::value&&
                         is_SameSize<E::row, row>::value
                         >::type*& = enabler>
            RealMatrix& operator*=(const E& mat)
            {
                *this = MatrixMul<RealMatrix, E>(*this, mat);
                return *this;
            }

            template<class E,
                     typename std::enable_if<
                         is_ScalarType<typename E::value_trait>::value
                         >::type*& = enabler>
            RealMatrix& operator*=(const double rhs)
            {
                *this = MatrixSclMul<RealMatrix>(rhs, *this);
                return *this;
            }

            template<class E,
                     typename std::enable_if<
                         is_ScalarType<typename E::value_trait>::value
                         >::type*& = enabler>
            RealMatrix& operator/=(const double rhs)
            {
                *this = MatrixSclDiv<RealMatrix>(*this, rhs);
                return *this;
            }

            double operator()(const std::size_t i, const std::size_t j) const
            {
                return values[i][j];
            }

            double& operator()(const std::size_t i, const std::size_t j)
            {
                return values[i][j];
            }


        private:

            std::array<std::array<double, C>, R> values;
    };

    template<std::size_t R, std::size_t C>
    std::ostream& operator<<(std::ostream& os, const RealMatrix<R,C>& mat)
    {
        for(std::size_t i(0); i<R; ++i)
        {
            for(std::size_t j(0); j<C; ++j)
                os << mat(i,j) << " ";
            std::cout << std::endl;
        }
        return os;
    }
}

#endif//AX_MATRIX_NxN