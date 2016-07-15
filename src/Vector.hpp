#ifndef AX_VECTOR_H
#define AX_VECTOR_H
#include <array>
#include <vector>
#include <iostream>
#include "VectorExp.hpp"

namespace ax
{

// static dimention case
template<typename T_elem, int I_dim,
         typename std::enable_if<is_static_dimention<I_dim>::value
             >::type*& = enabler>
class Vector
{
  public:
    // traits
    using tag    = vector_tag;
    using elem_t = T_elem;
    constexpr static std::size_t dim = I_dim;

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
        if(vec.size() < dim) vec.resize(dim);
        for(std::size_t i(0); i<dim; ++i) values_[i] = vec[i];
    }

    template<typename ... T_args,
             typename std::enable_if<sizeof...(T_args) == dim>::type*& = enabler>
    Vector(T_args ... args) : values_{{args...}}
    {
        ;
    }

    template<class T_expr,
             typename std::enable_if<
                 is_vector_expression<typename T_expr::tag>::value&&
                 is_same_dimention<dim, T_expr::dim>::value
                 >::type*& = enabler>
    Vector(const T_expr& expr)
    {
        for(std::size_t i(0); i<dim; ++i) (*this)[i] = expr[i];
    }

    template<class T_expr,
             typename std::enable_if<
                 is_vector_expression<typename T_expr::tag>::value&&
                 is_same_dimention<dim, T_expr::dim>::value
                 >::type*& = enabler>
    Vector& operator=(const T_expr& expr)
    {
        for(auto i(0); i<dim; ++i) (*this)[i] = expr[i];
        return *this;
    }

    template<class T_expr,
             typename std::enable_if<
                 is_vector_expression<typename T_expr::tag>::value&&
                 is_same_dimention<dim, T_expr::dim>::value
                 >::type*& = enabler>
    Vector& operator+=(const T_expr& expr)
    {
        return *this = (*this + expr);
    }

    template<class T_expr,
             typename std::enable_if<
                 is_vector_expression<typename T_expr::tag>::value&&
                 is_same_dimention<dim, T_expr::dim>::value
                 >::type*& = enabler>
    Vector& operator-=(const T_expr& expr)
    {
        return *this = (*this - expr);
    }

    Vector& operator*=(const elem_t& expr)
    {
        return *this = (*this * expr);
    }

    Vector& operator/=(const elem_t& expr)
    {
        return *this = (*this / expr);
    }

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

  private:
    container_t values_;
};

}

#endif//AX_VECTOR_H
