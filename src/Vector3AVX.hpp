#ifndef AX_AVX_3_DIMENTIONAL_VECTOR_H
#define AX_AVX_3_DIMENTIONAL_VECTOR_H
#include "Vector.hpp"

#include <cassert>
#include <xmmintrin.h>
#include <immintrin.h>

namespace ax
{

class AVXVector3d
{
  public:

    using value_trait = AVXVector;
    constexpr static std::size_t size = 3;

  public:

    AVXVector3d()
        : values_(_mm256_setzero_pd())
    {}

    AVXVector3d(double d)
        : values_(_mm256_broadcast_sd(&d))
    {} 

    AVXVector3d(double x, double y, double z)
        : values_(_mm256_set_pd(0e0, z, y, x))
    {} 

    AVXVector3d(const std::array<double, 3>& array)
        : values_(_mm256_set_pd(0e0, array[2], array[1], array[0]))
    {}

    AVXVector3d(const __m256d& val)
        : values_(val)
    {}

    AVXVector3d(const AVXVector3d& v)
        : values_(v.values_)
    {} 

    template<class E, 
             typename std::enable_if<
                 is_VectorExpression<typename E::value_trait>::value&&
                 is_SameSize<E::size, 3>::value
                 >::type*& = enabler>
    AVXVector3d(const E& exp)
        : values_(_mm256_set_pd(0e0, exp[2], exp[1], exp[0]))
    {}

    template<class E, 
             typename std::enable_if<
                 is_VectorExpression<typename E::value_trait>::value&&
                 is_SameSize<E::size, 3>::value
                 >::type*& = enabler>
    AVXVector3d& operator=(const E& exp)
    {
        values_ = _mm256_set_pd(0e0, exp[2], exp[1], exp[0]);
        return *this;
    }

    template<class E, 
             typename std::enable_if<
                 is_VectorExpression<typename E::value_trait>::value&&
                 is_SameSize<E::size, 3>::value
                 >::type*& = enabler>
    AVXVector3d& operator+=(const E& exp)
    {
        const __m256d ex = _mm256_set_pd(0e0, exp[2], exp[1], exp[0]);
        values_ = _mm256_add_pd(values_, ex);
        return *this;
    }

    AVXVector3d& operator+=(const AVXVector3d& rhs)
    {
        values_ = _mm256_add_pd(values_, rhs.values_);
        return *this;
    }

    template<class E, 
             typename std::enable_if<
                 is_VectorExpression<typename E::value_trait>::value&&
                 is_SameSize<E::size, 3>::value
                 >::type*& = enabler>
    AVXVector3d& operator-=(const E& exp)
    {
        const __m256d ex = _mm256_set_pd(0e0, exp[2], exp[1], exp[0]);
        values_ = _mm256_sub_pd(ex, values_);
        return *this;
    } 

    AVXVector3d& operator-=(const AVXVector3d& rhs)
    {
        values_ = _mm256_sub_pd(values_, rhs.values_);
        return *this;
    }

    AVXVector3d& operator*=(const double scl)
    {
        const __m256d ex = _mm256_broadcast_sd(&scl);
        values_ = _mm256_mul_pd(ex, values_);
        return *this;
    } 

    AVXVector3d& operator/=(const double scl)
    {
        const __m256d ex = _mm256_broadcast_sd(&scl);
        values_ = _mm256_div_pd(values_, ex);
        return *this;
    }

    std::array<double, 3> get() const
    {
        double val[4];
        _mm256_storeu_pd(val, values_);
        return std::array<double, 3>{{val[0], val[1], val[2]}};
    }

    double operator[](const std::size_t i) const
    {
        double val[4]; _mm256_storeu_pd(val, values_);
        return val[i];
    }

    double at(const std::size_t i) const
    {
        assert(0 <= i && i < 4);
        double val[4]; _mm256_storeu_pd(val, values_);
        return val[i];
    }

    const __m256d& value() const {return values_;}
          __m256d& value()       {return values_;}

  private:

    __m256d values_;
};

template <class L, class R,
          typename std::enable_if<
              is_AVXVectorExpression<typename L::value_trait>::value&&
              is_AVXVectorExpression<typename R::value_trait>::value&&
              is_SameSize<L::size, R::size>::value
              >::type*& = enabler>
inline AVXVector3d operator+(const L& lhs, const R& rhs)
{
    return AVXVector3d(_mm256_add_pd(lhs.value(), rhs.value()));
}

template <class L, class R,
          typename std::enable_if<
              is_AVXVectorExpression<typename L::value_trait>::value&&
              is_AVXVectorExpression<typename R::value_trait>::value&&
              is_SameSize<L::size, R::size>::value
              >::type*& = enabler>
inline AVXVector3d operator-(const L& lhs, const R& rhs)
{
    return AVXVector3d(_mm256_sub_pd(lhs.value(), rhs.value()));
}

template <class L, class R,
          typename std::enable_if<
              is_AVXVectorExpression<typename L::value_trait>::value&&
              is_ScalarType<R>::value>::type*& = enabler>
inline AVXVector3d operator*(const L& lhs, const R& rhs)
{
    return AVXVector3d(_mm256_mul_pd(lhs.value(), _mm256_broadcast_sd(&rhs)));
}

template <class L, class R,
          typename std::enable_if<
              is_AVXVectorExpression<typename R::value_trait>::value&&
              is_ScalarType<L>::value>::type*& = enabler>
inline AVXVector3d operator*(const L& lhs, const R& rhs)
{
    return AVXVector3d(_mm256_mul_pd(rhs.value(), _mm256_broadcast_sd(&lhs)));
}

template <class L, class R,
          typename std::enable_if<
              is_AVXVectorExpression<typename L::value_trait>::value&&
              is_ScalarType<R>::value>::type*& = enabler>
inline AVXVector3d operator/(const L& lhs, const R& rhs)
{
    return AVXVector3d(_mm256_div_pd(lhs.value(), _mm256_broadcast_sd(&rhs)));
}

template <class L,
          typename std::enable_if<
              is_AVXVectorExpression<typename L::value_trait>::value
              >::type*& = enabler>
inline double len_square(const L& l)
{
    double lensq[4];/* = */ _mm256_storeu_pd(lensq, _mm256_mul_pd(l.value(), l.value()));
    return lensq[0] + lensq[1] + lensq[2];
}

template <class L,
          typename std::enable_if<
              is_AVXVectorExpression<typename L::value_trait>::value
              >::type*& = enabler>
inline double length(const L& l)
{
    return std::sqrt(len_square(l));
}

template <class L, class R,
          typename std::enable_if<
              is_AVXVectorExpression<typename L::value_trait>::value&&
              is_AVXVectorExpression<typename R::value_trait>::value&&
              is_SameSize<L::size, R::size>::value
              >::type*& = enabler>
inline double dot_prod(const L& lhs, const R& rhs)
{
    double dotp[4];/* = */ _mm256_storeu_pd(dotp, _mm256_mul_pd(lhs.value(), rhs.value()));
    return dotp[0] + dotp[1] + dotp[2];
}

template <class L, class R,
          typename std::enable_if<
              is_AVXVectorExpression<typename L::value_trait>::value&&
              is_AVXVectorExpression<typename R::value_trait>::value&&
              is_SameSize<L::size, 3>::value&&
              is_SameSize<R::size, 3>::value
              >::type*& = enabler>
AVXVector3d cross_prod(const L& lhs, const R& rhs)
{
    double l[4]; _mm256_storeu_pd(l, lhs.value());
    double r[4]; _mm256_storeu_pd(r, rhs.value());
    return AVXVector3d(l[1] * r[2] - l[2] * r[1], 
                       l[2] * r[0] - l[0] * r[2],
                       l[0] * r[1] - l[1] * r[0]);
}

template <class L,
          typename std::enable_if<
              is_AVXVectorExpression<typename L::value_trait>::value
              >::type*& = enabler>
AVXVector3d normalize(const L& lhs)
{
    const double len = length(lhs);
    return AVXVector3d(_mm256_div_pd(lhs, _mm256_broadcast_sd(&len)));
}

}
#endif//AX_VECTOR_H
