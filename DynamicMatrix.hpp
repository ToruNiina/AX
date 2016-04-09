#ifndef AX_DYNAMIC_MATRIX
#define AX_DYNAMIC_MATRIX
#include "DynamicMatrixExp.hpp"
#include <iostream>
#include <utility>
#include <vector>

namespace ax
{

class RealDynamicMatrix
{
  public:

    using value_trait = DynamicMatrix;
    /*   C x R matrix
     C O L U M N s
  R ( M_00 M_01 ... M_0C )
  O ( M_10  .        .   )
  W (  ...       .   .   )
  s ( M_R0 ...      M_RC )
    */

  public:
    RealDynamicMatrix(){};
    ~RealDynamicMatrix() = default;

    RealDynamicMatrix(const std::size_t Col, const std::size_t Row)
        : values_(Row, std::vector<double>(Col, 0e0))
    {}

    RealDynamicMatrix(const RealDynamicMatrix& mat)
        : values_(mat.values_)
    {}

    RealDynamicMatrix(RealDynamicMatrix&& mat)
        : values_(std::move(mat.values_))
    {}

    template<class E, typename std::enable_if<
            is_DynamicMatrixExpression<typename E::value_trait>::type
        >::type*& = enabler>
    RealDynamicMatrix(const E& exp)
    {
        for(auto i=0; i<exp.values_.size(); ++i)
            for(auto j=0; j<exp.values_.size(); ++j)
                this->values_.at(i).at(j) = exp.values_.at(i).at(j);
    }

    template<class E, typename std::enable_if<
            is_MatrixExpression<typename E::value_trait>::type
        >::type*& = enabler>
    RealDynamicMatrix(const E& exp)
    {
        for(auto i=0; i<E::row; ++i)
            for(auto j=0; j<E::col; ++j)
                this->values_.at(i).at(j) = exp.values_(i, j);
    }

    // operator= 
    RealDynamicMatrix& operator=(const RealDynamicMatrix& mat)
    {
        values_ = mat.values_;
        return *this;
    }

    template<class E, typename std::enable_if<
            is_DynamicMatrixExpression<typename E::value_trait>::type
        >::type*& = enabler>
    RealDynamicMatrix& operator=(const E& exp)
    {
        for(auto i=0; i<exp.values_.size(); ++i)
            for(auto j=0; j<exp.values_.size(); ++j)
                this->values_.at(i).at(j) = exp.values_.at(i).at(j);
        return *this;
    }

    template<class E, typename std::enable_if<
            is_MatrixExpression<typename E::value_trait>::type
        >::type*& = enabler>
    RealDynamicMatrix& operator=(const E& exp)
    {
        for(auto i=0; i<E::row; ++i)
            for(auto j=0; j<E::col; ++j)
                this->values_.at(i).at(j) = exp(i,j);
        return *this;
    }

    const double operator()(const std::size_t i, const std::size_t j) const
    {
        return values_[i][j];
    }

    double& operator()(const std::size_t i, const std::size_t j)
    {
        return values_[i][j];
    }

    const double at(const std::size_t i, const std::size_t j) const
    {
        return values_.at(i).at(j);
    }

    double& at(const std::size_t i, const std::size_t j)
    {
        return values_.at(i).at(j);
    }

    const std::size_t size_row() const
    {
        return values_.size();
    }

    const std::size_t size_col() const
    {
        return values_.at(0).size();
    }

  private:

    std::vector<std::vector<double>> values_;
};

}

#endif /* AX_DYNAMIC_MATRIX */
