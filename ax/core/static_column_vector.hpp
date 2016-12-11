#ifndef AX_STATIC_COLUMN_VECTOR
#define AX_STATIC_COLUMN_VECTOR
#include "matrix.hpp"
#include "vector_traits.hpp"
#include <ax/util/is_all.hpp>

namespace ax
{

template<typename scalarT, dimension_type colN>
class Matrix<scalarT, 1, colN>
{
  public:
    typedef matrix_tag tag;
    typedef scalarT scalar_type;
    constexpr static dimension_type row = 1;
    constexpr static dimension_type col = colN;
    constexpr static dimension_type num = col;
    typedef std::array<scalar_type, num> container_type;

    template<typename T>
    using convertible = std::is_convertible<T, scalar_type>;

  public:
    Matrix() = default;
    ~Matrix() = default;
    Matrix(const Matrix&) = default;
    Matrix(Matrix&&) = default;
    template<typename expT, class = typename std::enable_if<
        is_vector<expT>::value && vector_traits<expT>::size == num>::type>
    Matrix(const expT&);
    template<typename ... Ts, class = typename std::enable_if<
        sizeof...(Ts) == num && is_all<convertible, Ts...>::value>::type>
    Matrix(Ts&&...);
    template<typename ... Ts, class = typename std::enable_if<
        sizeof...(Ts) == num && is_all<convertible, Ts...>::value>::type>
    Matrix(const Ts&...);

    Matrix& operator=(const Matrix&) = default;
    Matrix& operator=(Matrix&&) = default;
    template<typename expT, class = typename std::enable_if<
        is_vector<expT>::value && vector_traits<expT>::size == num>::type>
    Matrix& operator=(const expT&);

    template<typename expT, class = typename std::enable_if<
        is_vector<expT>::value && vector_traits<expT>::size == num>::type>
    Matrix& operator+=(const expT&);
    template<typename expT, class = typename std::enable_if<
        is_vector<expT>::value && vector_traits<expT>::size == num>::type>
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

    scalar_type&       operator[](const std::size_t i);
    scalar_type const& operator[](const std::size_t i) const;
    scalar_type&       at(const std::size_t i);
    scalar_type const& at(const std::size_t i) const;

  private:
    container_type values_;
};

template<typename scalarT, dimension_type colN>
template<typename expT, class>
inline Matrix<scalarT, 1, colN>::Matrix(const expT& exp)
{
    for(dimension_type j=0; j<col; ++j)
        values_[j] = exp(0, j);
}

template<typename scalarT, dimension_type colN>
template<typename ... Ts, class>
inline Matrix<scalarT, 1, colN>::Matrix(Ts&&... args)
    : values_{{std::forward<scalar_type>(args)...}}
{}

template<typename scalarT, dimension_type colN>
template<typename ... Ts, class>
inline Matrix<scalarT, 1, colN>::Matrix(const Ts&... args)
    : values_{{args...}}
{}

template<typename scalarT, dimension_type colN>
template<typename expT, class>
inline Matrix<scalarT, 1, colN>&
Matrix<scalarT, 1, colN>::operator=(const expT& exp)
{
    for(dimension_type j=0; j<col; ++j)
        values_[j] = exp(0, j);
    return *this;
}

template<typename scalarT, dimension_type colN>
template<typename expT, class>
inline Matrix<scalarT, 1, colN>&
Matrix<scalarT, 1, colN>::operator+=(const expT& exp)
{
    for(dimension_type j=0; j<col; ++j)
        values_[j] += exp(0, j);
    return *this;
}

template<typename scalarT, dimension_type colN>
template<typename expT, class>
inline Matrix<scalarT, 1, colN>&
Matrix<scalarT, 1, colN>::operator-=(const expT& exp)
{
    for(dimension_type j=0; j<col; ++j)
        values_[j] -= exp(0, j);
    return *this;
}
 
template<typename scalarT, dimension_type colN>
template<typename sclT, class>
inline Matrix<scalarT, 1, colN>&
Matrix<scalarT, 1, colN>::operator*=(const sclT& s)
{
    for(dimension_type j=0; j<col; ++j)
        values_[j] *= s;
    return *this;
}

template<typename scalarT, dimension_type colN>
template<typename sclT, class>
inline Matrix<scalarT, 1, colN>&
Matrix<scalarT, 1, colN>::operator/=(const sclT& s)
{
    for(dimension_type j=0; j<col; ++j)
        values_[j] /= s;
    return *this;
}

template<typename scalarT, dimension_type colN>
inline typename Matrix<scalarT, 1, colN>::scalar_type&
Matrix<scalarT, 1, colN>::operator()(const std::size_t i, const std::size_t j)
{
    return values_[j];
}

template<typename scalarT, dimension_type colN>
inline typename Matrix<scalarT, 1, colN>::scalar_type const&
Matrix<scalarT, 1, colN>::operator()(const std::size_t i, const std::size_t j) const
{
    return values_[j];
}

template<typename scalarT, dimension_type colN>
inline typename Matrix<scalarT, 1, colN>::scalar_type&
Matrix<scalarT, 1, colN>::at(const std::size_t i, const std::size_t j)
{
    if(i != 0) throw std::out_of_range("matrix::at out of range");
    return values_.at(j);
}

template<typename scalarT, dimension_type colN>
inline typename Matrix<scalarT, 1, colN>::scalar_type const&
Matrix<scalarT, 1, colN>::at(const std::size_t i, const std::size_t j) const
{
    if(i != 0) throw std::out_of_range("matrix::at out of range");
    return values_.at(j);
}

template<typename scalarT, dimension_type colN>
inline typename Matrix<scalarT, 1, colN>::scalar_type&
Matrix<scalarT, 1, colN>::operator[](const std::size_t i)
{
    return values_[i];
}

template<typename scalarT, dimension_type colN>
inline typename Matrix<scalarT, 1, colN>::scalar_type const&
Matrix<scalarT, 1, colN>::operator[](const std::size_t i) const
{
    return values_[i];
}

template<typename scalarT, dimension_type colN>
inline typename Matrix<scalarT, 1, colN>::scalar_type&
Matrix<scalarT, 1, colN>::at(const std::size_t i)
{
    return values_.at(i);
}

template<typename scalarT, dimension_type colN>
inline typename Matrix<scalarT, 1, colN>::scalar_type const&
Matrix<scalarT, 1, colN>::at(const std::size_t i) const
{
    return values_.at(i);
}

} // ax
#endif /* AX_STATIC_COLUMN_VECTOR */
