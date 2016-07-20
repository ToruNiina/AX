#ifndef AX_DYNAMIC_VECTOR_H
#define AX_DYNAMIC_VECTOR_H
#include "Vector.hpp"
#include <iostream>
#include <vector>
#include <array>

namespace ax
{

template<typename T_elem>
class Vector<T_elem, DYNAMIC>
{
  public:

    using tag = vector_tag;
    using elem_t = T_elem;
    constexpr static dimension_type dim = DYNAMIC;

  public:
    Vector(){}
    ~Vector() = default;

    Vector(const std::size_t size) : values_(size, 0e0){}
    Vector(const std::size_t size, const elem_t v) : values_(size, v){}
    Vector(const std::vector<elem_t>& v) : values_(v){}
    Vector(std::vector<elem_t>&& v): values_(std::move(v)){}

    template<std::size_t N>
    Vector(const std::array<elem_t, N>& v): values_(N)
    {
        for(std::size_t i=0; i<N; ++i) values_[i] = v[i];
    }

    // from dynamic Vector
    Vector(const Vector<elem_t, dim>& vec) : values_(vec.values_){}
    Vector(Vector<elem_t, dim>&& vec) : values_(std::move(vec.values_)){}

    // from static Vector
    template<dimension_type D, typename std::enable_if<
        is_static_dimension<D>::value>::type*& = enabler>
    Vector(const Vector<elem_t, D>& vec) : values_(D)
    {
        for(std::size_t i=0; i<D; ++i) this->values_[i] = vec[i];
    }

    // from dynamic Vector expression
    template<class T_expr, typename std::enable_if<
                is_vector_expression<typename T_expr::tag>::value&&
                is_dynamic_dimension<T_expr::dim>::value>::type*& = enabler>
    Vector(const T_expr& expr) : values_(dimension(expr))
    {
        for(std::size_t i=0; i<dimension(expr); ++i) this->values_[i] = expr[i];
    }

    // from static Vector
    template<class T_expr, typename std::enable_if<
                is_vector_expression<typename T_expr::tag>::value&&
                is_static_dimension<T_expr::dim>::value>::type*& = enabler>
    Vector(const T_expr& expr) : values_(T_expr::dim)
    {
        for(std::size_t i=0; i<T_expr::dim; ++i) this->values_[i] = expr[i];
    }

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ operator = ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Vector<elem_t, dim>& operator=(const std::vector<elem_t>& v)
    {
        this->values_ = v; return *this;
    }

    Vector<elem_t, dim>& operator=(std::vector<elem_t>&& v)
    {
        this->values_ = std::move(v); return *this;
    }

    Vector<elem_t, dim>& operator=(const Vector<elem_t, dim>& vec)
    {
        this->values_ = vec.values_; return *this;
    }

    Vector<elem_t, dim>& operator=(Vector<elem_t, dim>&& vec)
    {
        this->values_ = std::move(vec.values_);return *this;
    }

    template<class T_expr,
            typename std::enable_if<
                is_vector_expression<typename T_expr::tag>::value&&
                is_dynamic_dimension<T_expr::dim>::value>::type*& = enabler>
    Vector<elem_t, dim>& operator=(const T_expr& expr)
    {
        this->values_.resize(dimension(expr), 0e0);
        for(std::size_t i=0; i<dimension(expr); ++i) this->values_[i] = expr[i];
        return *this;
    }

    template<class T_expr,
            typename std::enable_if<
                is_vector_expression<typename T_expr::tag>::value&&
                is_static_dimension<T_expr::dim>::value>::type*& = enabler>
    Vector<elem_t, dim>& operator=(const T_expr& expr)
    {
        this->values_.resize(T_expr::dim, 0e0);
        for(std::size_t i=0; i<T_expr::dim; ++i) this->values_[i] = expr[i];
        return *this;
    }

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ operator += ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // for dynamic += dynamic
    template<class T_expr,
            typename std::enable_if<
                is_vector_expression<typename T_expr::tag>::value&&
                is_dynamic_dimension<T_expr::dim>::value>::type*& = enabler>
    Vector<elem_t, dim>& operator+=(const T_expr& expr)
    {
        if(this->size() != dimension(expr))
            throw std::invalid_argument("add different size vector");
        return *this = (*this + expr);
    } 

    // for dynamic += static
    template<class T_expr,
            typename std::enable_if<
                is_vector_expression<typename T_expr::tag>::value&&
                is_static_dimension<T_expr::dim>::value>::type*& = enabler>
    Vector<elem_t, dim>& operator+=(const T_expr& expr)
    {
        if(this->size() != T_expr::dim)
            throw std::invalid_argument("add different size vector");
        return *this = (*this + expr);
    }

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ operator -= ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // for dynamic -= dynamic
    template<class T_expr,
            typename std::enable_if<
                is_vector_expression<typename T_expr::tag>::value&&
                is_dynamic_dimension<T_expr::dim>::value>::type*& = enabler>
    Vector<elem_t, dim>& operator-=(const T_expr& expr)
    {
        if(this->size() != dimension(expr))
            throw std::invalid_argument("add different size vector");
        return *this = (*this - expr);
    }

    // for dynamic -= static
    template<class T_expr,
            typename std::enable_if<
                is_vector_expression<typename T_expr::tag>::value&&
                is_static_dimension<T_expr::dim>::value>::type*& = enabler>
    Vector<elem_t, dim>& operator-=(const T_expr& expr)
    {
        if(this->size() != T_expr::dim)
            throw std::invalid_argument("add different size vector");
        return *this = (*this - expr);
    }

    Vector<elem_t, dim>& operator*=(const elem_t& scl)
    {
        return *this = (*this * scl);
    }
    Vector<elem_t, dim>& operator/=(const elem_t& scl)
    {
        return *this = (*this / scl);
    } 

    elem_t const& operator[](const std::size_t i) const {return values_[i];}
    elem_t&       operator[](const std::size_t i)       {return values_[i];}
    elem_t const& at(const std::size_t i) const {return values_.at(i);}
    elem_t&       at(const std::size_t i)       {return values_.at(i);}

    std::size_t size() const {return values_.size();}

  private:

    std::vector<elem_t> values_;
};

}
#endif /* AX_DYNAMIC_VECTOR */
