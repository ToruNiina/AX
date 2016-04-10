#ifndef AX_MATRIX_EXPRESSION_H
#define AX_MATRIX_EXPRESSION_H
#include "Expression.hpp"

namespace ax
{
    template<class L, class R>
    class MatrixAdd
    {
        public:

            using value_trait = MatrixExp;
            constexpr static std::size_t row = L::row;
            constexpr static std::size_t col = L::col;

            MatrixAdd(const L& lhs, const R& rhs)
                : l(lhs), r(rhs)
            {}

            double operator()(const std::size_t i, const std::size_t j) const
            {
                return l(i,j) + r(i,j);
            }

        private:

            const L& l;
            const R& r;
    };

    template<class L, class R>
    class MatrixSub
    {
        public:

            using value_trait = MatrixExp;
            constexpr static std::size_t row = L::row;
            constexpr static std::size_t col = L::col;

            MatrixSub(const L& lhs, const R& rhs)
                : l(lhs), r(rhs)
            {}

            double operator()(const std::size_t i, const std::size_t j) const
            {
                return l(i,j) - r(i,j);
            }

        private:

            const L& l;
            const R& r;
    };

    template<class L, class R>
    class MatrixMul
    {
        public:

            using value_trait = MatrixExp;
            constexpr static std::size_t row = L::row;
            constexpr static std::size_t col = R::col;

            MatrixMul(const L& lhs, const R& rhs)
                : l(lhs), r(rhs)
            {}

            double operator()(const std::size_t i, const std::size_t j) const
            {
                double retval(0e0);
                for(std::size_t k(0); k<R::row; ++k)
                    retval += l(i,k) * r(k,j);

                return retval;
            }

        private:

            const L& l;
            const R& r;
    };

    template<class R>
    class MatrixSclMul
    {
        public:

            using value_trait = MatrixExp;
            constexpr static std::size_t row = R::row;
            constexpr static std::size_t col = R::col;

            MatrixSclMul(const double& lhs, const R& rhs)
                : l(lhs), r(rhs)
            {}

            double operator()(const std::size_t i, const std::size_t j) const
            {
                return l * r(i,j);
            }

        private:

            const double& l;
            const R& r;
    };

    template<class L>
    class MatrixSclDiv
    {
        public:

            using value_trait = MatrixExp;
            constexpr static std::size_t row = L::row;
            constexpr static std::size_t col = L::col;

            MatrixSclDiv(const L& lhs, const double& rhs)
                : l(lhs), r(rhs)
            {}

            double operator()(const std::size_t i, const std::size_t j) const
            {
                return l(i,j) / r;
            }

        private:

            const L& l;
            const double& r;
    };

    template<class L>
    class MatrixTranspose
    {
        public:

            using value_trait = MatrixExp;
            constexpr static std::size_t row = L::col;
            constexpr static std::size_t col = L::row;

            MatrixTranspose(const L& lhs)
                : l(lhs)
            {}

            double operator()(const std::size_t i, const std::size_t j) const
            {
                return l(j,i);
            }

        private:

            const L& l;
    };

    template<class L, class R,
             typename std::enable_if<
                 is_MatrixExpression<typename L::value_trait>::value&&
                 is_MatrixExpression<typename R::value_trait>::value&&
                 is_SameSize<L::row, R::row>::value&&
                 is_SameSize<L::col, R::col>::value
                 >::type*& = enabler>
    MatrixAdd<L, R> operator+(const L& lhs, const R& rhs)
    {
        return MatrixAdd<L, R>(lhs, rhs);
    }

    template<class L, class R,
             typename std::enable_if<
                 is_MatrixExpression<typename L::value_trait>::value&&
                 is_MatrixExpression<typename R::value_trait>::value&&
                 is_SameSize<L::row, R::row>::value&&
                 is_SameSize<L::col, R::col>::value
                 >::type*& = enabler>
    MatrixSub<L, R> operator-(const L& lhs, const R& rhs)
    {
        return MatrixSub<L, R>(lhs, rhs);
    }

    template<class L, class R,
             typename std::enable_if<
                 is_MatrixExpression<typename L::value_trait>::value&&
                 is_MatrixExpression<typename R::value_trait>::value&&
                 is_SameSize<L::col, R::row>::value
                 >::type*& = enabler>
    MatrixMul<L, R> operator*(const L& lhs, const R& rhs)
    {
        return MatrixMul<L, R>(lhs, rhs);
    }

//L is matrix
    template<class L, class R,
             typename std::enable_if<
                 is_MatrixExpression<typename L::value_trait>::value&&
                 is_ScalarType<R>::value>::type*& = enabler>
    MatrixSclMul<L> operator*(const L& lhs, const R& rhs)
    {
        return MatrixSclMul<L>(rhs, lhs);
    }

//R is matrix
    template<class L, class R,
             typename std::enable_if<
                 is_ScalarType<L>::value&&
                 is_MatrixExpression<typename R::value_trait>::value
                 >::type*& = enabler>
    MatrixSclMul<R> operator*(const L& lhs, const R& rhs)
    {
        return MatrixSclMul<R>(lhs, rhs);
    }

    template<class L, class R,
             typename std::enable_if<
                 is_MatrixExpression<typename L::value_trait>::value&&
                 is_ScalarType<R>::value>::type*& = enabler>
    MatrixSclDiv<L> operator/(const L& lhs, const R& rhs)
    {
        return MatrixSclDiv<L>(lhs, rhs);
    }

    template<class L, typename std::enable_if<
                 is_MatrixExpression<typename L::value_trait>::value
                 >::type*& = enabler>
    MatrixTranspose<L> transpose(const L& lhs)
    {
        return MatrixTranspose<L>(lhs);
    }
}
#endif//AX_EXPRESSION_H