#ifndef AX_DYNAMIC_VECTOR_EXPRESSION_H
#define AX_DYNAMIC_VECTOR_EXPRESSION_H
#include "Expression.hpp"
#include <stdexcept>
#include <cmath>

namespace ax
{

template<class L, class R>
class DynamicVectorAdd
{
  public:

    using value_trait = DynamicVectorExp;

    DynamicVectorAdd(const L& lhs, const R& rhs)
        : l(lhs), r(rhs)
    {}

    const double operator[](const std::size_t i) const
    {
        return l[i] + r[i];
    }

    const std::size_t size() const
    {
        return l.size();
    }

  private:

    const L& l;
    const R& r;
};

template<class L, class R>
class DynamicVectorSub
{
  public:

    using value_trait = DynamicVectorExp;

    DynamicVectorSub(const L& lhs, const R& rhs)
        : l(lhs), r(rhs)
    {}

    const double operator[](const std::size_t i) const
    {
        return l[i] - r[i];
    }

    const std::size_t size() const
    {
        return l.size();
    }

  private:

    const L& l;
    const R& r;
};

template <class R>
class DynamicVectorSclMul
{
  public:

    using value_trait = DynamicVectorExp;

    DynamicVectorSclMul(const double lhs, const R& rhs)
        : l(lhs), r(rhs)
    {}

    const double operator[](const std::size_t i) const
    {
        return l * r[i];
    }

    const std::size_t size() const
    {
        return r.size();
    }

  private:
    const double l;
    const R& r;
};

template <class L>
class DynamicVectorSclDiv
{
  public:

    using value_trait = DynamicVectorExp;

    DynamicVectorSclDiv(const L& lhs, const double rhs)
        : l(lhs), r(rhs)
    {}

    const double operator[](const std::size_t i) const
    {
        return l[i] / r;
    }

    const std::size_t size() const
    {
        return l.size();
    }

  private:

    const L& l;
    const double r;
};

template <class L, class R,
          typename std::enable_if<
              is_DynamicVectorExpression<typename L::value_trait>::value&&
              is_DynamicVectorExpression<typename R::value_trait>::value
              >::type*& = enabler>
DynamicVectorAdd<L,R> operator+(const L& lhs, const R& rhs)
{
    if(lhs.size() != rhs.size())
        throw std::invalid_argument("add different size vector");
    return DynamicVectorAdd<L,R>(lhs, rhs);
}

template <class L, class R,
          typename std::enable_if<
              is_DynamicVectorExpression<typename L::value_trait>::value&&
              is_DynamicVectorExpression<typename R::value_trait>::value
              >::type*& = enabler>
DynamicVectorSub<L,R> operator-(const L& lhs, const R& rhs)
{
    if(lhs.size() != rhs.size())
        throw std::invalid_argument("add different size vector");
    return DynamicVectorSub<L,R>(lhs, rhs);
}

template <class L,
          typename std::enable_if<
              is_DynamicVectorExpression<typename L::value_trait>::value
              >::type*& = enabler>
DynamicVectorSclMul<L> operator*(const L& lhs, const double rhs)
{
    return DynamicVectorSclMul<L>(lhs, rhs);
}

template <class R,
          typename std::enable_if<
              is_DynamicVectorExpression<typename R::value_trait>::value
              >::type*& = enabler>
DynamicVectorSclMul<R> operator*(const double lhs, const R& rhs)
{
    return DynamicVectorSclMul<R>(rhs, lhs);
}

template <class L,
          typename std::enable_if<
              is_DynamicVectorExpression<typename L::value_trait>::value
              >::type*& = enabler>
DynamicVectorSclDiv<L> operator/(const L& lhs, const double rhs)
{
    return DynamicVectorSclDiv<L>(rhs, lhs);
}

template <class L,
          typename std::enable_if<
              is_DynamicVectorExpression<typename L::value_trait>::value
              >::type*& = enabler>
const double len_square(const L& l)
{
    double len(0e0);
    for(std::size_t i(0); i<l.size(); ++i)
        len += l[i] * l[i];
    return len;
}

template <class L,
          typename std::enable_if<
              is_VectorExpression<typename L::value_trait>::value
              >::type*& = enabler>
const double length(const L& l)
{
    return std::sqrt(len_square(l));
}

template <class L, class R,
          typename std::enable_if<
              is_VectorExpression<typename L::value_trait>::value&&
              is_VectorExpression<typename R::value_trait>::value&&
              is_SameSize<L::size, R::size>::value
              >::type*& = enabler>
const double dot_prod(const L& lhs, const R& rhs)
{
    if(lhs.size() != rhs.size())
        throw std::invalid_argument("dot prod different size vector");

    double dot(0e0);
    for(std::size_t i(0); i<lhs.size(); ++i)
        dot += lhs[i] * rhs[i];
    return dot;
}


}
#endif /* AX_DYNAMIC_VECTOR_EXPRESSION_H */
