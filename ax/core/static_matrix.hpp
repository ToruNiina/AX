#ifndef AX_STATIC_MATRIX
#define AX_STATIC_MATRIX
#include "matrix_traits.hpp"
#include <array>

namespace ax
{

template<typename scalarT, dimension_type rowN, dimension_type colN>
class Matrix
{
  public:
    typedef matrix_tag tag;
    typedef scalarT scalar_type;
    constexpr static dimension_type row = rowN;
    constexpr static dimension_type col = colN;
    constexpr static dimension_type num = row * col;
    typedef std::array<scalar_type, num> container_type;

    template<typename T>
    using convertible = std::is_convertible<scalar_type, T>;

  public:
    Matrix() = default;
    ~Matrix() = default;
    Matrix(const Matrix&) = default;
    Matrix(Matrix&&) = default;
    template<typename expT, class = typename std::enable_if<
        is_matrix<expT>::value && matrix_traits<expT>::row == row &&
        matrix_traits<expT>::col == col>::type>
    Matrix(const expT&);

    Matrix& operator=(const Matrix&) = default;
    Matrix& operator=(Matrix&&) = default;
    template<typename expT, class = typename std::enable_if<
        is_matrix<expT>::value && matrix_traits<expT>::row == row &&
        matrix_traits<expT>::col == col>::type>
    Matrix& operator=(const expT&);

    template<typename expT, class = typename std::enable_if<
        is_matrix<expT>::value && matrix_traits<expT>::row == row &&
        matrix_traits<expT>::col == col>::type>
    Matrix& operator+=(const expT&);
    template<typename expT, class = typename std::enable_if<
        is_matrix<expT>::value && matrix_traits<expT>::row == row &&
        matrix_traits<expT>::col == col>::type>
    Matrix& operator-=(const expT&);
    template<typename sclT, class = typename std::enable_if<
        convertible<sclT>::value>::type>
    Matrix& operator*=(const sclT&);
    template<typename sclT, class = typename std::enable_if<
        convertible<sclT>::value>::type>
    Matrix& operator/=(const sclT&);

    scalar_type&       operator()(const std::size_t i, const std::size_t j);
    scalar_type const& operator()(const std::size_t i, const std::size_t j) const;
    scalar_type&       at(const std::size_t i, const std::size_t j);
    scalar_type const& at(const std::size_t i, const std::size_t j) const;

  private:
    container_type values_;
};

template<typename scalarT, dimension_type rowN, dimension_type colN>
template<typename expT, class>
inline Matrix<scalarT, rowN, colN>::Matrix(const expT& exp)
{
    for(dimension_type i=0; i<row; ++i)
    for(dimension_type j=0; j<col; ++j)
        values_[i * col + j] = exp(i, j);
}

template<typename scalarT, dimension_type rowN, dimension_type colN>
template<typename expT, class>
inline Matrix<scalarT, rowN, colN>&
Matrix<scalarT, rowN, colN>::operator=(const expT& exp)
{
    for(dimension_type i=0; i<row; ++i)
    for(dimension_type j=0; j<col; ++j)
        values_[i * col + j] = exp(i, j);
    return *this;
}

template<typename scalarT, dimension_type rowN, dimension_type colN>
template<typename expT, class>
inline Matrix<scalarT, rowN, colN>&
Matrix<scalarT, rowN, colN>::operator+=(const expT& exp)
{
    for(dimension_type i=0; i<row; ++i)
    for(dimension_type j=0; j<col; ++j)
        values_[i * col + j] += exp(i, j);
    return *this;
}

template<typename scalarT, dimension_type rowN, dimension_type colN>
template<typename expT, class>
inline Matrix<scalarT, rowN, colN>&
Matrix<scalarT, rowN, colN>::operator-=(const expT& exp)
{
    for(dimension_type i=0; i<row; ++i)
    for(dimension_type j=0; j<col; ++j)
        values_[i * col + j] -= exp(i, j);
    return *this;
}
 
template<typename scalarT, dimension_type rowN, dimension_type colN>
template<typename sclT, class>
inline Matrix<scalarT, rowN, colN>&
Matrix<scalarT, rowN, colN>::operator*=(const sclT& s)
{
    for(dimension_type i=0; i<num; ++i)
        values_[i] *= s;
    return *this;
}

template<typename scalarT, dimension_type rowN, dimension_type colN>
template<typename sclT, class>
inline Matrix<scalarT, rowN, colN>&
Matrix<scalarT, rowN, colN>::operator/=(const sclT& s)
{
    for(dimension_type i=0; i<num; ++i)
        values_[i] /= s;
    return *this;
}

template<typename scalarT, dimension_type rowN, dimension_type colN>
inline typename Matrix<scalarT, rowN, colN>::scalar_type&
Matrix<scalarT, rowN, colN>::operator()(
        const std::size_t i, const std::size_t j)
{
    return values_[i * col + j];
}

template<typename scalarT, dimension_type rowN, dimension_type colN>
inline typename Matrix<scalarT, rowN, colN>::scalar_type const&
Matrix<scalarT, rowN, colN>::operator()(
        const std::size_t i, const std::size_t j) const
{
    return values_[i * col + j];
}

template<typename scalarT, dimension_type rowN, dimension_type colN>
inline typename Matrix<scalarT, rowN, colN>::scalar_type&
Matrix<scalarT, rowN, colN>::at(const std::size_t i, const std::size_t j)
{
    return values_.at(i * col + j);
}

template<typename scalarT, dimension_type rowN, dimension_type colN>
inline typename Matrix<scalarT, rowN, colN>::scalar_type const&
Matrix<scalarT, rowN, colN>::at(const std::size_t i, const std::size_t j) const
{
    return values_.at(i * col + j);
}

} // ax
#endif/* AX_MATRIX */
