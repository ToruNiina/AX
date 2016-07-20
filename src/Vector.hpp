#ifndef AX_VECTOR_H
#define AX_VECTOR_H
#include <array>
#include <vector>
#include <iostream>
#include "VectorExpression.hpp"

namespace ax
{

// static dimension case
template<typename T_elem, dimension_type I_dim, typename std::enable_if<
    is_static_dimension<I_dim>::value>::type*& = enabler>
class Vector
{
  public:
    // traits
    using tag    = vector_tag;
    using elem_t = T_elem;
    constexpr static dimension_type dim = I_dim;

    using container_t = std::array<elem_t, dim>;
    using self_type   = Vector<elem_t, dim>;

  public:

    Vector() : values_{{}}{}
    ~Vector() = default;
    Vector(const elem_t d){values_.fill(d);} 
    Vector(const container_t& v) : values_(v){} 
    Vector(const self_type& v): values_(v.values_){} 
    Vector(const std::vector<elem_t>& vec)
    {
        if(vec.size() < dim) vec.resize(dim, 0e0);
        for(std::size_t i(0); i<dim; ++i) values_[i] = vec[i];
    }

    template<typename ... T_args, typename std::enable_if<
        (sizeof...(T_args) == dim) && is_all<elem_t, T_args...>::value
        >::type*& = enabler>
    Vector(T_args ... args) : values_{{args...}}{}

    template<class T_expr, typename std::enable_if<
        is_vector_expression<typename T_expr::tag>::value&&
        is_same_dimension<dim, T_expr::dim>::value>::type*& = enabler>
    Vector(const T_expr& expr)
    {
        for(std::size_t i(0); i<dim; ++i) (*this)[i] = expr[i];
    }

    // from dynamic
    template<class T_expr, typename std::enable_if<
        is_vector_expression<typename T_expr::tag>::value&&
        is_dynamic_dimension<T_expr::dim>::value>::type*& = enabler>
    Vector(const T_expr& expr)
    {
        if(expr.size() != dim)
            throw std::invalid_argument("vector size different");
        for(std::size_t i(0); i<dim; ++i) (*this)[i] = expr[i];
    }

    // from static
    template<class T_expr, typename std::enable_if<
        is_vector_expression<typename T_expr::tag>::value&&
        is_same_dimension<dim, T_expr::dim>::value>::type*& = enabler>
    Vector<elem_t, dim>& operator=(const T_expr& expr)
    {
        for(auto i(0); i<dim; ++i) (*this)[i] = expr[i];
        return *this;
    }

    // from dynamic
    template<class T_expr, typename std::enable_if<
        is_vector_expression<typename T_expr::tag>::value&&
        is_dynamic_dimension<T_expr::dim>::value>::type*& = enabler>
    Vector<elem_t, dim>& operator=(const T_expr& expr)
    {
        if(expr.size() != dim)
            throw std::invalid_argument("vector size different");
        for(auto i(0); i<dim; ++i) (*this)[i] = expr[i];
        return *this;
    }

    template<class T_expr, typename std::enable_if<
        is_vector_expression<typename T_expr::tag>::value&&
        is_same_dimension<dim, T_expr::dim>::value>::type*& = enabler>
    Vector<elem_t, dim>& operator+=(const T_expr& expr)
    {
        return *this = (*this + expr);
    }

    template<class T_expr, typename std::enable_if<
        is_vector_expression<typename T_expr::tag>::value&&
        is_dynamic_dimension<T_expr::dim>::value>::type*& = enabler>
    Vector<elem_t, dim>& operator+=(const T_expr& expr)
    {
        if(expr.size() != dim)
            throw std::invalid_argument("vector size different");
        return *this = (*this + expr);
    }

    template<class T_expr, typename std::enable_if<
        is_vector_expression<typename T_expr::tag>::value&&
        is_same_dimension<dim, T_expr::dim>::value>::type*& = enabler>
    Vector<elem_t, dim>& operator-=(const T_expr& expr)
    {
        return *this = (*this - expr);
    }

    template<class T_expr, typename std::enable_if<
        is_vector_expression<typename T_expr::tag>::value&&
        is_dynamic_dimension<T_expr::dim>::value>::type*& = enabler>
    Vector<elem_t, dim>& operator-=(const T_expr& expr)
    {
        if(expr.size() != dim)
            throw std::invalid_argument("vector size different");
        return *this = (*this - expr);
    }

    Vector<elem_t, dim>& operator*=(const elem_t& expr)
    {
        return *this = (*this * expr);
    }

    Vector<elem_t, dim>& operator/=(const elem_t& expr)
    {
        return *this = (*this / expr);
    }

    elem_t const& operator[](const std::size_t i) const {return values_[i];}
    elem_t&       operator[](const std::size_t i)       {return values_[i];}

    elem_t const& at(const std::size_t i) const {return values_.at(i);}
    elem_t&       at(const std::size_t i)       {return values_.at(i);}

  private:
    container_t values_;
};

}

#endif//AX_VECTOR_H
