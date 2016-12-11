#ifndef AX_STATIC_ROW_VECTOR
#define AX_STATIC_ROW_VECTOR
#include "matrix.hpp"
#include "vector_traits.hpp"
#include <ax/util/is_all.hpp>
#include <vector>

namespace ax
{

template<typename scalarT>
class Matrix<scalarT, DYNAMIC, 1>
{
  public:
    typedef matrix_tag tag;
    typedef scalarT scalar_type;
    constexpr static dimension_type row = DYNAMIC;
    constexpr static dimension_type col = 1;
    constexpr static dimension_type num = DYNAMIC;
    typedef std::vector<scalar_type> container_type;

    template<typename T>
    using convertible = std::is_convertible<T, scalar_type>;

  public:
    Matrix() = default;
    ~Matrix() = default;
    Matrix(const Matrix&) = default;
    Matrix(Matrix&&) = default;
    template<typename expT, class = typename std::enable_if<
        is_vector<expT>::value>::type>
    Matrix(const expT&);
    template<typename ... Ts, class = typename std::enable_if<
        is_all<convertible, Ts...>::value>::type>
    Matrix(Ts&&...);
    template<typename ... Ts, class = typename std::enable_if<
        is_all<convertible, Ts...>::value>::type>
    Matrix(const Ts&...);

    Matrix& operator=(const Matrix&) = default;
    Matrix& operator=(Matrix&&) = default;
    template<typename expT, class = typename std::enable_if<
        is_vector<expT>::value>::type>
    Matrix& operator=(const expT&);

    template<typename expT, class = typename std::enable_if<
        is_vector<expT>::value>::type>
    Matrix& operator+=(const expT&);
    template<typename expT, class = typename std::enable_if<
        is_vector<expT>::value>::type>
    Matrix& operator-=(const expT&);
    template<typename sclT, class = typename std::enable_if<
        convertible<sclT>::value>::type>
    Matrix& operator*=(const sclT&);
    template<typename sclT, class = typename std::enable_if<
        convertible<sclT>::value>::type>
    Matrix& operator/=(const sclT&);

    dimension_type size() const {return values_.size();}
    void resize(const dimension_type d){return values_.resize(d);}
    void resize(const dimension_type d, const scalar_type s){return values_.resize(d, s);}
    void clear() {return values_.clear();}
    template<typename sclT, class = typename std::enable_if<
        convertible<sclT>::value>::type>
    void append(const sclT s){values_.push_back(s);}
    template<typename sclT, class = typename std::enable_if<
        convertible<sclT>::value>::type>
    void append(sclT&& s){values_.emplace_back(std::forward<scalar_type>(s));}

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

template<typename scalarT>
template<typename expT, class>
inline Matrix<scalarT, DYNAMIC, 1>::Matrix(const expT& exp)
    : values_(size(exp))
{
    for(dimension_type i=0; i<size(exp); ++i)
        values_[i] = exp(i, 0);
}

template<typename scalarT>
template<typename ... Ts, class>
inline Matrix<scalarT, DYNAMIC, 1>::Matrix(Ts&&... args)
    : values_{std::forward<scalar_type>(args)...}
{}

template<typename scalarT>
template<typename ... Ts, class>
inline Matrix<scalarT, DYNAMIC, 1>::Matrix(const Ts&... args)
    : values_{args...}
{}

template<typename scalarT>
template<typename expT, class>
inline Matrix<scalarT, DYNAMIC, 1>&
Matrix<scalarT, DYNAMIC, 1>::operator=(const expT& exp)
{
    if(this->size() != size(exp))
        throw std::out_of_range("vector dimension different");
    for(dimension_type i=0; i<this->size(); ++i)
        values_[i] = exp(i, 0);
    return *this;
}

template<typename scalarT>
template<typename expT, class>
inline Matrix<scalarT, DYNAMIC, 1>&
Matrix<scalarT, DYNAMIC, 1>::operator+=(const expT& exp)
{
    if(this->size() != size(exp))
        throw std::out_of_range("vector dimension different");
    for(dimension_type i=0; i<this->size(); ++i)
        values_[i] += exp(i, 0);
    return *this;
}

template<typename scalarT>
template<typename expT, class>
inline Matrix<scalarT, DYNAMIC, 1>&
Matrix<scalarT, DYNAMIC, 1>::operator-=(const expT& exp)
{
    if(this->size() != size(exp))
        throw std::out_of_range("vector dimension different");
    for(dimension_type i=0; i<this->size(); ++i)
        values_[i] -= exp(i, 0);
    return *this;
}
 
template<typename scalarT>
template<typename sclT, class>
inline Matrix<scalarT, DYNAMIC, 1>&
Matrix<scalarT, DYNAMIC, 1>::operator*=(const sclT& s)
{
    for(dimension_type i=0; i<this->size(); ++i)
        values_[i] *= s;
    return *this;
}

template<typename scalarT>
template<typename sclT, class>
inline Matrix<scalarT, DYNAMIC, 1>&
Matrix<scalarT, DYNAMIC, 1>::operator/=(const sclT& s)
{
    for(dimension_type i=0; i<this->size(); ++i)
        values_[i] /= s;
    return *this;
}

template<typename scalarT>
inline typename Matrix<scalarT, DYNAMIC, 1>::scalar_type&
Matrix<scalarT, DYNAMIC, 1>::operator()(const std::size_t i, const std::size_t j)
{
    return values_[i];
}

template<typename scalarT>
inline typename Matrix<scalarT, DYNAMIC, 1>::scalar_type const&
Matrix<scalarT, DYNAMIC, 1>::operator()(const std::size_t i, const std::size_t j) const
{
    return values_[i];
}

template<typename scalarT>
inline typename Matrix<scalarT, DYNAMIC, 1>::scalar_type&
Matrix<scalarT, DYNAMIC, 1>::at(const std::size_t i, const std::size_t j)
{
    if(j != 0) throw std::out_of_range("matrix::at out of range");
    return values_.at(i);
}

template<typename scalarT>
inline typename Matrix<scalarT, DYNAMIC, 1>::scalar_type const&
Matrix<scalarT, DYNAMIC, 1>::at(const std::size_t i, const std::size_t j) const
{
    if(j != 0) throw std::out_of_range("matrix::at out of range");
    return values_.at(i);
}

template<typename scalarT>
inline typename Matrix<scalarT, DYNAMIC, 1>::scalar_type&
Matrix<scalarT, DYNAMIC, 1>::operator[](const std::size_t i)
{
    return values_[i];
}

template<typename scalarT>
inline typename Matrix<scalarT, DYNAMIC, 1>::scalar_type const&
Matrix<scalarT, DYNAMIC, 1>::operator[](const std::size_t i) const
{
    return values_[i];
}

template<typename scalarT>
inline typename Matrix<scalarT, DYNAMIC, 1>::scalar_type&
Matrix<scalarT, DYNAMIC, 1>::at(const std::size_t i)
{
    return values_.at(i);
}

template<typename scalarT>
inline typename Matrix<scalarT, DYNAMIC, 1>::scalar_type const&
Matrix<scalarT, DYNAMIC, 1>::at(const std::size_t i) const
{
    return values_.at(i);
}

} // ax
#endif /* AX_STATIC_ROW_VECTOR */
