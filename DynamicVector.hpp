#ifndef AX_DYNAMIC_VECTOR_H
#define AX_DYNAMIC_VECTOR_H
#include "DynamicVectorExp.hpp"
#include <iostream>
#include <vector>
#include <array>

namespace ax
{

class RealDynamicVector
{
  public:
    using value_trait = DynamicVector;

  public:
    RealDynamicVector(){}
    ~RealDynamicVector() = default;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ctor ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    RealDynamicVector(const std::size_t size)
        : values_(size, 0e0)
    {}

    RealDynamicVector(const std::size_t size, const double v)
        : values_(size, v)
    {}

    RealDynamicVector(const std::vector<double>& v)
        : values_(v)
    {}

    RealDynamicVector(std::vector<double>&& v)
        : values_(std::move(v))
    {}

    template<std::size_t N>
    RealDynamicVector(const std::array<double, N>& v)
        : values_(N, 0e0)
    {
        for(std::size_t i=0; i<N; ++i)
            values_[i] = v[i];
    }

    RealDynamicVector(const RealDynamicVector& vec)
        : values_(vec.values_)
    {}

    RealDynamicVector(RealDynamicVector&& vec)
        : values_(std::move(vec.values_))
    {}

    template<class E,
            typename std::enable_if<
                is_VectorExpression<typename E::value_trait>::value
                >::type*& = enabler>
    RealDynamicVector(const E& vec)
    {
//         this->values_.clear();
        this->values_.resize(E::size, 0e0);
        for(std::size_t i=0; i<E::size; ++i)
            this->values_.at(i) = vec[i];
    }

    template<class E,
            typename std::enable_if<
                is_DynamicVectorExpression<typename E::value_trait>::value
                >::type*& = enabler>
    RealDynamicVector(const E& vec)
    {
//         this->values_.clear();
        this->values_.resize(vec.size(), 0e0);
        for(std::size_t i=0; i<vec.size(); ++i)
            this->values_.at(i) = vec[i];
    }

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ operator = ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    RealDynamicVector& operator=(const std::vector<double>& v)
    {
        this->values_ = v;
        return *this;
    }

    RealDynamicVector& operator=(std::vector<double>&& v)
    {
        this->values_ = std::move(v);
        return *this;
    }

    RealDynamicVector& operator=(const RealDynamicVector& vec)
    {
        this->values_ = vec.values_;
        return *this;
    }


    RealDynamicVector& operator=(RealDynamicVector&& vec)
    {
        this->values_ = std::move(vec.values_);
        return *this;
    }

    template<class E,
            typename std::enable_if<
                is_VectorExpression<typename E::value_trait>::value
                >::type*& = enabler>
    RealDynamicVector& operator=(const E& vec)
    {
//         this->values_.clear();
        this->values_.resize(E::size, 0e0);
        for(std::size_t i=0; i<E::size; ++i)
            this->values_.at(i) = vec[i];
        return *this;
    }

    template<class E,
            typename std::enable_if<
                is_DynamicVectorExpression<typename E::value_trait>::value
                >::type*& = enabler>
    RealDynamicVector& operator=(const E& vec)
    {
//         this->values_.clear();
        this->values_.resize(vec.size(), 0e0);
        for(std::size_t i=0; i<vec.size(); ++i)
            this->values_.at(i) = vec[i];
        return *this;
    }

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ operator += ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // for dynamic += dynamic
    template<class E, 
             typename std::enable_if<
                     is_DynamicVectorExpression<typename E::value_trait>::value
                 >::type*& = enabler>
    RealDynamicVector& operator+=(const E& exp)
    {
        if(this->size() != exp.size())
            throw std::invalid_argument("add different size vector");

        *this = DynamicVectorAdd<RealDynamicVector, E>(*this, exp);
        return *this;
    } 

    // for dynamic += static
    template<class E, 
             typename std::enable_if<
                     is_VectorExpression<typename E::value_trait>::value
                 >::type*& = enabler>
    RealDynamicVector& operator+=(const E& exp)
    {
        if(this->size() != E::size)
            throw std::invalid_argument("add different size vector");

        *this = DynamicVectorAdd<RealDynamicVector, E>(*this, exp);
        return *this;
    } 

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ operator -= ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // for dynamic -= dynamic
    template<class E, 
             typename std::enable_if<
                     is_DynamicVectorExpression<typename E::value_trait>::value
                 >::type*& = enabler>
    RealDynamicVector& operator-=(const E& exp)
    {
        if(this->size() != exp.size())
            throw std::invalid_argument("add different size vector");

        *this = DynamicVectorSub<RealDynamicVector, E>(*this, exp);
        return *this;
    }

    // for dynamic -= static
    template<class E, 
             typename std::enable_if<
                     is_VectorExpression<typename E::value_trait>::value
                 >::type*& = enabler>
    RealDynamicVector& operator-=(const E& exp)
    {
        if(this->size() != E::size)
            throw std::invalid_argument("subtract different size vector");

        *this = DynamicVectorSub<RealDynamicVector, E>(*this, exp);
        return *this;
    } 

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ operator *= ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    template<class E, 
             typename std::enable_if<is_ScalarType<E>::value>::type*& =
                 enabler>
    RealDynamicVector& operator*=(const E& exp)
    {
        *this = DynamicVectorSclMul<RealDynamicVector>(exp, *this);
        return *this;
    } 

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ operator /= ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    template<class E, 
             typename std::enable_if<is_ScalarType<E>::value>::type*& =
                 enabler>
    RealDynamicVector& operator/=(const E& exp)
    {
        *this = DynamicVectorSclDiv<RealDynamicVector>(*this, exp);
        return *this;
    } 

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ member access ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    const double& operator[](const std::size_t i) const
    {
        return values_[i];
    }

    double& operator[](const std::size_t i)
    {
        return values_[i];
    }

    const double& at(const std::size_t i) const
    {
        return values_.at(i);
    }

    double& at(const std::size_t i)
    {
        return values_.at(i);
    }

    const std::size_t size() const
    {
        return values_.size();
    }

  private:

    std::vector<double> values_;
};

std::ostream& operator<<(std::ostream& os, const RealDynamicVector& vec)
{
    for(std::size_t i(0); i<vec.size(); ++i)
        os << vec[i] << " ";
    return os;
}

}
#endif /* AX_DYNAMIC_VECTOR */
