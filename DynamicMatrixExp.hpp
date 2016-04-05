#ifndef AX_DYNAMIC_MATRIX_EXPRESSION
#define AX_DYNAMIC_MATRIX_EXPRESSION
#include "Expression.hpp"
#include <stdexcept>

namespace ax
{

template<class L, class R>
class DynamicMatrixAdd
{
  public:

    using value_trait = DynamicMatrixExp;

    DynamicMatrixAdd(const L& lhs, const R& rhs)
        : l_(lhs), r_(rhs)
    {}

    const double operator()(const std::size_t i, const std::size_t j) const
    {
        return l_(i, j) + r_(i, j);
    }

  private:

    const L& l_;
    const R& r_;

};

template<class L, class R>
class DynamicMatrixSub
{
  public:

    using value_trait = DynamicMatrixExp;

    DynamicMatrixSub(const L& lhs, const R& rhs)
        : l_(lhs), r_(rhs)
    {}

    const double operator()(const std::size_t i, const std::size_t j) const
    {
        return l_(i, j) + r_(i, j);
    }

  private:

    const L& l_;
    const R& r_;

};

template<class L, class R>
class DynamicMatrixMul
{
  public:

    using value_trait = DynamicMatrixExp;

    DynamicMatrixMul(const L& lhs, const R& rhs)
        : l_(lhs), r_(rhs)
    {}

    double operator()(const std::size_t i, const std::size_t j) const
    {
        double retval(0e0);
        for(std::size_t k(0); k < r_.size(); ++k)
            retval += l_(i,k) * r_(k,j);

        return retval;
    }

  private:

    const L& l_;
    const R& r_;
};

template<class R>
class DynamicMatrixSclMul
{
  public:

    using value_trait = DynamicMatrixExp;

    DynamicMatrixSclMul(const double lhs, const R& rhs)
        : l(lhs), r(rhs)
    {}

    double operator()(const std::size_t i, const std::size_t j) const
    {
        return l * r(i,j);
    }

  private:

    const double l;
    const R& r;
};

template<class L>
class DynamicMatrixSclDiv
{
  public:

    using value_trait = DynamicMatrixExp;

    DynamicMatrixSclDiv(const L& lhs, const double rhs)
        : l(lhs), r(rhs)
    {}

    const double operator()(const std::size_t i, const std::size_t j) const
    {
        return l(i,j) / r;
    }

  private:

    const L& l;
    const double r;
};

template<class L>
class DynamicMatrixTranspose
{
  public:

    using value_trait = DynamicMatrixExp;

    DynamicMatrixTranspose(const L& lhs)
        : l(lhs)
    {}

    const double operator()(const std::size_t i, const std::size_t j) const
    {
        return l(j, i);
    }

  private:

    const L& l;
};

// =============== Dynamic * Dynamic ===============

template<class L, class R,
         typename std::enable_if<
             is_DynamicMatrixExpression<typename L::value_trait>::value&&
             is_DynamicMatrixExpression<typename R::value_trait>::value
             >::type*& = enabler>
DynamicMatrixAdd<L, R> operator+(const L& lhs, const R& rhs)
{
    if(lhs.size_col() != rhs.size_col() || lhs.size_row() != rhs.size_row())
        throw std::invalid_argument("add different size matricise");

    return DynamicMatrixAdd<L, R>(lhs, rhs);
}

template<class L, class R,
         typename std::enable_if<
             is_DynamicMatrixExpression<typename L::value_trait>::value&&
             is_DynamicMatrixExpression<typename R::value_trait>::value
             >::type*& = enabler>
DynamicMatrixSub<L, R> operator-(const L& lhs, const R& rhs)
{
    if(lhs.size_col() != rhs.size_col() || lhs.size_row() != rhs.size_row())
        throw std::invalid_argument("subtract different size matricise");

    return DynamicMatrixSub<L, R>(lhs, rhs);
}

template<class L, class R,
         typename std::enable_if<
             is_DynamicMatrixExpression<typename L::value_trait>::value&&
             is_DynamicMatrixExpression<typename R::value_trait>::value
             >::type*& = enabler>
DynamicMatrixMul<L, R> operator*(const L& lhs, const R& rhs)
{
    if(lhs.size_col() != rhs.size_row())
        throw std::invalid_argument("multiple different size matricise");

    return DynamicMatrixMul<L, R>(lhs, rhs);
}

template<class R,
         typename std::enable_if<
             is_DynamicMatrixExpression<typename R::value_trait>::value
             >::type*& = enabler>
DynamicMatrixSclMul<R> operator*(const double lhs, const R& rhs)
{
    return DynamicMatrixSclMul<R>(lhs, rhs);
}

template<class L,
         typename std::enable_if<
             is_DynamicMatrixExpression<typename L::value_trait>::value
             >::type*& = enabler>
DynamicMatrixSclMul<L> operator*(const L& lhs, const double rhs)
{
    return DynamicMatrixSclMul<L>(rhs, lhs);
}

template<class L,
         typename std::enable_if<
             is_DynamicMatrixExpression<typename L::value_trait>::value
             >::type*& = enabler>
DynamicMatrixSclDiv<L> operator/(const L& lhs, const double rhs)
{
    return DynamicMatrixSclDiv<L>(lhs, rhs);
}

template<class L,
         typename std::enable_if<
             is_DynamicMatrixExpression<typename L::value_trait>::value
             >::type*& = enabler>
DynamicMatrixTranspose<L> transpose(const L& lhs)
{
    return DynamicMatrixTranspose<L>(lhs);
}

// =============== Static * Dynamic ===============

template<class L, class R,
         typename std::enable_if<
             is_MatrixExpression<typename L::value_trait>::value&&
             is_DynamicMatrixExpression<typename R::value_trait>::value
             >::type*& = enabler>
DynamicMatrixAdd<L, R> operator+(const L& lhs, const R& rhs)
{
    if(L::col != rhs.size_col() || L::row != rhs.size_row())
        throw std::invalid_argument("add different size matricise");

    return DynamicMatrixAdd<L, R>(lhs, rhs);
}

template<class L, class R,
         typename std::enable_if<
             is_MatrixExpression<typename L::value_trait>::value&&
             is_DynamicMatrixExpression<typename R::value_trait>::value
             >::type*& = enabler>
DynamicMatrixSub<L, R> operator-(const L& lhs, const R& rhs)
{
    if(L::col != rhs.size_col() || L::row() != rhs.size_row())
        throw std::invalid_argument("subtract different size matricise");

    return DynamicMatrixSub<L, R>(lhs, rhs);
}

template<class L, class R,
         typename std::enable_if<
             is_MatrixExpression<typename L::value_trait>::value&&
             is_DynamicMatrixExpression<typename R::value_trait>::value
             >::type*& = enabler>
DynamicMatrixMul<L, R> operator*(const L& lhs, const R& rhs)
{
    if(L::col() != rhs.size_row())
        throw std::invalid_argument("multiple different size matricise");

    return DynamicMatrixMul<L, R>(lhs, rhs);
}

// =============== Dynamic * Static ===============

template<class L, class R,
         typename std::enable_if<
             is_DynamicMatrixExpression<typename L::value_trait>::value&&
             is_MatrixExpression<typename R::value_trait>::value
             >::type*& = enabler>
DynamicMatrixAdd<L, R> operator+(const L& lhs, const R& rhs)
{
    if(R::col != lhs.size_col() || R::row != lhs.size_row())
        throw std::invalid_argument("add different size matricise");

    return DynamicMatrixAdd<L, R>(lhs, rhs);
}

template<class L, class R,
         typename std::enable_if<
             is_DynamicMatrixExpression<typename L::value_trait>::value&&
             is_MatrixExpression<typename R::value_trait>::value
             >::type*& = enabler>
DynamicMatrixSub<L, R> operator-(const L& lhs, const R& rhs)
{
    if(R::col != lhs.size_col() || R::row() != lhs.size_row())
        throw std::invalid_argument("subtract different size matricise");

    return DynamicMatrixSub<L, R>(lhs, rhs);
}

template<class L, class R,
         typename std::enable_if<
             is_DynamicMatrixExpression<typename L::value_trait>::value&&
             is_MatrixExpression<typename R::value_trait>::value
             >::type*& = enabler>
DynamicMatrixMul<L, R> operator*(const L& lhs, const R& rhs)
{
    if(R::col() != lhs.size_row())
        throw std::invalid_argument("multiple different size matricise");

    return DynamicMatrixMul<L, R>(lhs, rhs);
}



}

#endif /* AX_DYNAMIC_MATRIX_EXPRESSION */
