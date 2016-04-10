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

    RealDynamicMatrix(const std::size_t Row, const std::size_t Col)
        : values_(Row, std::vector<double>(Col, 0e0))
    {}

    RealDynamicMatrix(const std::vector<std::vector<double>>& val)
        : values_(val)
    {
        if(val.empty())       throw std::invalid_argument("empty data");
        if(val.at(0).empty()) throw std::invalid_argument("empty data");

        const std::size_t col_size = val.at(0).size();
        for(auto iter = val.cbegin(); iter != val.cend(); ++iter)
            if(iter->size() != col_size)
                throw std::invalid_argument("invalid size");
    }

    RealDynamicMatrix(const RealDynamicMatrix& mat)
        : values_(mat.values_)
    {}

    RealDynamicMatrix(RealDynamicMatrix&& mat)
        : values_(std::move(mat.values_))
    {}

    template<class E,
             typename std::enable_if<
                 is_DynamicMatrixExpression<typename E::value_trait>::value
                 >::type*& = enabler>
    RealDynamicMatrix(const E& exp)
        : values_(exp.size_row(), std::vector<double>(exp.size_col(), 0e0))
    {
        for(auto i=0; i<exp.size_row(); ++i)
            for(auto j=0; j<exp.size_col(); ++j)
                (*this)(i, j) = exp(i, j);
    }

    template<class E,
             typename std::enable_if<
                 is_MatrixExpression<typename E::value_trait>::value
                 >::type*& = enabler>
    RealDynamicMatrix(const E& exp)
        : values_(E::row, std::vector<double>(E::col, 0e0))
    {
        for(auto i=0; i<E::row; ++i)
            for(auto j=0; j<E::col; ++j)
                 (*this)(i, j) = exp(i, j);
    }

    // operator = 
    RealDynamicMatrix& operator=(const RealDynamicMatrix& mat)
    {
        values_ = mat.values_;
        return *this;
    }

    template<class E, typename std::enable_if<
            is_DynamicMatrixExpression<typename E::value_trait>::value
        >::type*& = enabler>
    RealDynamicMatrix& operator=(const E& exp)
    {
        if(exp.size_row() != this->size_row() ||
           exp.size_col() != this->size_col())
        {
            throw std::invalid_argument("different size matrix");
        }

        for(auto i=0; i<exp.size_row(); ++i)
            for(auto j=0; j<exp.size_col(); ++j)
                this->values_.at(i).at(j) = exp(i, j);
        return *this;
    }

    template<class E, typename std::enable_if<
            is_MatrixExpression<typename E::value_trait>::value
        >::type*& = enabler>
    RealDynamicMatrix& operator=(const E& exp)
    {
        if(E::row != this->size_row() || E::col != this->size_col())
        {
            throw std::invalid_argument("different size matrix");
        }

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
