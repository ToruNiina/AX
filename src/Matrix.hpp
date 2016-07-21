#ifndef AX_MATRIX_H
#define AX_MATRIX_H
#include <array>
#include <iostream>
#include "MatrixExpression.hpp"

namespace ax
{

/* static C x R matrix M
     C O L U M N s
  R ( M_00 M_01 ... M_0C )
  O ( M_10  .        .   )
  W (  ...       .   .   )
  s ( M_R0 ...      M_RC ) */
template<typename T_elem, dimension_type I_row, dimension_type I_col>
class Matrix
{
  public:

    using tag = matrix_tag;
    using elem_t = T_elem;
    constexpr static dimension_type dim_row = I_row;//number of row
    constexpr static dimension_type dim_col = I_col;//number of column

    using container_type = std::array<std::array<elem_t, dim_col>, dim_row>;
    using self_type = Matrix<elem_t, dim_row, dim_col>;
    // {{col_vec}, {col_vec}, ... }

  public:

    Matrix() : values_{{{}}}{}
    ~Matrix() = default;

    Matrix(const self_type& mat) : values_(mat.values_){};
    Matrix(self_type&& mat): values_(std::move(mat.values_)){}
    Matrix(const container_type& val) : values_(val){}

    // to make Identity matrix
    Matrix(const elem_t d) : values_{{{}}}
    {
        for(std::size_t i(0); i<dim_row; ++i) values_[i][i] = d;
    }

    template<class T_expr, typename std::enable_if<
        is_matrix_expression<typename T_expr::tag>::value&&
        is_same_dimension<T_expr::dim_col, dim_col>::value&&
        is_same_dimension<T_expr::dim_row, dim_row>::value>::type*& = enabler>
    Matrix(const T_expr& mat)
    {
         for(std::size_t i(0); i<dim_row; ++i)
            for(std::size_t j(0); j<dim_col; ++j)
                values_[i][j] = mat(i, j);
    }

    template<class T_expr, typename std::enable_if<
        is_matrix_expression<typename T_expr::tag>::value&&
        is_dynamic_dimension<T_expr::dim_col>::value&&
        is_same_dimension<T_expr::dim_row, dim_row>::value>::type*& = enabler>
    Matrix(const T_expr& mat)
    {
        if(dimension_col(mat) != dim_col)
            throw std::invalid_argument("matrix size different");

        for(std::size_t i(0); i<dim_row; ++i)
            for(std::size_t j(0); j<dim_col; ++j)
                values_[i][j] = mat(i, j);
    }

    template<class T_expr, typename std::enable_if<
        is_matrix_expression<typename T_expr::tag>::value&&
        is_same_dimension<T_expr::dim_col, dim_col>::value&&
        is_dynamic_dimension<T_expr::dim_row>::value>::type*& = enabler>
    Matrix(const T_expr& mat)
    {
        if(dimension_row(mat) != dim_row)
            throw std::invalid_argument("matrix size different");

        for(std::size_t i(0); i<dim_row; ++i)
            for(std::size_t j(0); j<dim_col; ++j)
                values_[i][j] = mat(i, j);
    }

    template<class T_expr, typename std::enable_if<
        is_matrix_expression<typename T_expr::tag>::value&&
        is_dynamic_dimension<T_expr::dim_col>::value&&
        is_dynamic_dimension<T_expr::dim_row>::value>::type*& = enabler>
    Matrix(const T_expr& mat)
    {
        if(dimension_row(mat) != dim_row || dimension_col(mat) != dim_col)
            throw std::invalid_argument("matrix size different");

        for(std::size_t i(0); i<dim_row; ++i)
            for(std::size_t j(0); j<dim_col; ++j)
                values_[i][j] = mat(i, j);
    }

    // ~~~~~~~~~~~~~~~~~~~~~ operator ~~~~~~~~~~~~~~~~~~~~~~~~~
    self_type& operator=(const self_type& mat)
    {
        this->values_ = mat.values_;
        return *this;
    }

    template<class T_expr, typename std::enable_if<
        is_matrix_expression<typename T_expr::tag>::value&&
        is_same_dimension<T_expr::dim_col, dim_col>::value&&
        is_same_dimension<T_expr::dim_row, dim_row>::value>::type*& = enabler>
    self_type& operator=(const T_expr& expr)
    {
        for(std::size_t i(0); i<dim_row; ++i)
            for(std::size_t j(0); j<dim_col; ++j)
               (*this)(i,j) = expr(i,j);
        return *this;
    }

    template<class T_expr, typename std::enable_if<
        is_matrix_expression<typename T_expr::tag>::value&&
        is_same_dimension<T_expr::dim_col, dim_col>::value&&
        is_same_dimension<T_expr::dim_row, dim_row>::value>::type*& = enabler>
    self_type& operator+=(const T_expr& mat)
    {
        return *this = (*this + mat);
    }

    template<class T_expr, typename std::enable_if<
        is_matrix_expression<typename T_expr::tag>::value&&
        is_same_dimension<T_expr::dim_col, dim_col>::value&&
        is_same_dimension<T_expr::dim_row, dim_row>::value>::type*& = enabler>
    self_type& operator-=(const T_expr& mat)
    {
        return *this = (*this - mat);
    }

    //operator*= can be used in the case of same size matrix
    template<class T_expr, typename std::enable_if<
        is_matrix_expression<typename T_expr::tag>::value&&
        is_same_dimension<dim_col, dim_row>::value&&
        is_same_dimension<T_expr::dim_col, dim_col>::value&&
        is_same_dimension<T_expr::dim_row, dim_row>::value>::type*& = enabler>
    self_type& operator*=(const T_expr& mat)
    {
        return *this = (*this * mat);
    }

    self_type& operator*=(const elem_t rhs)
    {
        return *this = (*this * rhs);
    }

    self_type& operator/=(const elem_t rhs)
    {
        return *this = (*this / rhs);
    }

    elem_t const& operator()(const std::size_t i, const std::size_t j) const
    {
#ifdef AX_PARANOIAC
        return this->values_.at(i).at(j);
#else
        return this->values_[i][j];
#endif
    }
    elem_t&       operator()(const std::size_t i, const std::size_t j)
    {
#ifdef AX_PARANOIAC
        return this->values_.at(i).at(j);
#else
        return this->values_[i][j];
#endif
    }
    elem_t const& at(const std::size_t i, const std::size_t j) const
    {
        return this->values_.at(i).at(j);
    }
    elem_t&       at(const std::size_t i, const std::size_t j)
    {
        return this->values_.at(i).at(j);
    }

  private:

    container_type values_;
};


}//ax

#endif//AX_MATRIX_NxN
