#ifndef AX_STATIC_ROW_VECTOR
#define AX_STATIC_ROW_VECTOR
#include "matrix.hpp"
#include "vector_traits.hpp"
#include <ax/util/is_all.hpp>

namespace ax
{

template<typename scalarT, dimension_type rowN>
class Matrix<scalarT, rowN, 1>
{
  public:
    typedef matrix_tag tag;
    typedef scalarT scalar_type;
    constexpr static dimension_type row = rowN;
    constexpr static dimension_type col = 1;
    constexpr static dimension_type num = row;
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

template<typename scalarT, dimension_type rowN>
template<typename expT, class>
inline Matrix<scalarT, rowN, 1>::Matrix(const expT& exp)
{
    for(dimension_type i=0; i<row; ++i)
        values_[i] = exp(i, 0);
}

template<typename scalarT, dimension_type rowN>
template<typename ... Ts, class>
inline Matrix<scalarT, rowN, 1>::Matrix(Ts&&... args)
    : values_{{std::forward<scalar_type>(args)...}}
{}

template<typename scalarT, dimension_type rowN>
template<typename ... Ts, class>
inline Matrix<scalarT, rowN, 1>::Matrix(const Ts&... args)
    : values_{{args...}}
{}

template<typename scalarT, dimension_type rowN>
template<typename expT, class>
inline Matrix<scalarT, rowN, 1>&
Matrix<scalarT, rowN, 1>::operator=(const expT& exp)
{
    for(dimension_type i=0; i<row; ++i)
        values_[i] = exp(i, 0);
    return *this;
}

template<typename scalarT, dimension_type rowN>
template<typename expT, class>
inline Matrix<scalarT, rowN, 1>&
Matrix<scalarT, rowN, 1>::operator+=(const expT& exp)
{
    for(dimension_type i=0; i<row; ++i)
        values_[i] += exp(i, 0);
    return *this;
}

template<typename scalarT, dimension_type rowN>
template<typename expT, class>
inline Matrix<scalarT, rowN, 1>&
Matrix<scalarT, rowN, 1>::operator-=(const expT& exp)
{
    for(dimension_type i=0; i<row; ++i)
        values_[i] -= exp(i, 0);
    return *this;
}
 
template<typename scalarT, dimension_type rowN>
template<typename sclT, class>
inline Matrix<scalarT, rowN, 1>&
Matrix<scalarT, rowN, 1>::operator*=(const sclT& s)
{
    for(dimension_type i=0; i<row; ++i)
        values_[i] *= s;
    return *this;
}

template<typename scalarT, dimension_type rowN>
template<typename sclT, class>
inline Matrix<scalarT, rowN, 1>&
Matrix<scalarT, rowN, 1>::operator/=(const sclT& s)
{
    for(dimension_type i=0; i<row; ++i)
        values_[i] /= s;
    return *this;
}

template<typename scalarT, dimension_type rowN>
inline typename Matrix<scalarT, rowN, 1>::scalar_type&
Matrix<scalarT, rowN, 1>::operator()(const std::size_t i, const std::size_t j)
{
    return values_[i];
}

template<typename scalarT, dimension_type rowN>
inline typename Matrix<scalarT, rowN, 1>::scalar_type const&
Matrix<scalarT, rowN, 1>::operator()(const std::size_t i, const std::size_t j) const
{
    return values_[i];
}

template<typename scalarT, dimension_type rowN>
inline typename Matrix<scalarT, rowN, 1>::scalar_type&
Matrix<scalarT, rowN, 1>::at(const std::size_t i, const std::size_t j)
{
    if(j != 0) throw std::out_of_range("matrix::at out of range");
    return values_.at(i);
}

template<typename scalarT, dimension_type rowN>
inline typename Matrix<scalarT, rowN, 1>::scalar_type const&
Matrix<scalarT, rowN, 1>::at(const std::size_t i, const std::size_t j) const
{
    if(j != 0) throw std::out_of_range("matrix::at out of range");
    return values_.at(i);
}

template<typename scalarT, dimension_type rowN>
inline typename Matrix<scalarT, rowN, 1>::scalar_type&
Matrix<scalarT, rowN, 1>::operator[](const std::size_t i)
{
    return values_[i];
}

template<typename scalarT, dimension_type rowN>
inline typename Matrix<scalarT, rowN, 1>::scalar_type const&
Matrix<scalarT, rowN, 1>::operator[](const std::size_t i) const
{
    return values_[i];
}

template<typename scalarT, dimension_type rowN>
inline typename Matrix<scalarT, rowN, 1>::scalar_type&
Matrix<scalarT, rowN, 1>::at(const std::size_t i)
{
    return values_.at(i);
}

template<typename scalarT, dimension_type rowN>
inline typename Matrix<scalarT, rowN, 1>::scalar_type const&
Matrix<scalarT, rowN, 1>::at(const std::size_t i) const
{
    return values_.at(i);
}

} // ax
#endif /* AX_STATIC_ROW_VECTOR */
