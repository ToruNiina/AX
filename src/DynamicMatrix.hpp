#ifndef AX_DYNAMIC_MATRIX
#define AX_DYNAMIC_MATRIX
#include "MatrixExpression.hpp"
#include <vector>
#include <stdexcept>

namespace ax
{

/*   C x R matrix
     C O L U M N s
  R ( M_00 M_01 ... M_0C )
  O ( M_10  .        .   )
  W (  ...       .   .   )
  s ( M_R0 ...      M_RC ) */
   
template <typename T_elem, dimension_type I_row, dimension_type I_col,
    typename std::enable_if<is_dynamic_dimension<I_row>::value&&
    is_dynamic_dimension<I_col>::value>::type*& = enabler>
class Matrix
{
  public:

    using tag = matrix_tag;
    using elem_t = T_elem;
    constexpr static dimension_type dim_row = I_row;//number of row
    constexpr static dimension_type dim_col = I_col;//number of column
    using nest_container_type = std::vector<elem_t>;
    using container_type = std::vector<nest_container_type>;
    using self_type = Matrix<elem_t, dim_row, dim_col>;

  public:
    Matrix(){}
    ~Matrix() = default;

    Matrix(const std::size_t Row, const std::size_t Col)
        : values_(Row, std::vector<double>(Col, 0e0))
    {}

    Matrix(const std::vector<std::vector<double>>& val): values_(val)
    {}

    Matrix(const Matrix<elem_t, dim_row, dim_col>& mat)
        : values_(mat.values_)
    {}

    Matrix(Matrix<elem_t, dim_row, dim_col>&& mat)
        : values_(std::move(mat.values_))
    {}

    template<class T_expr, typename std::enable_if<
        is_matrix_expression<typename T_expr::tag>::value&&
        std::is_same<elem_t, typename T_expr::elem_t>::value
        >::type*& = enabler>
    Matrix(const T_expr& expr)
        : values_(dimension_row(expr), nest_container_type(dimension_col(expr), 0e0))
    {
        for(auto i=0; i<dimension_row(expr); ++i)
            for(auto j=0; j<dimension_col(expr); ++j)
                (*this)(i, j) = expr(i, j);
    }

    // operator = 
    self_type& operator=(const self_type& mat)
    {
        this->values_ = mat.values_;
        return *this;
    }

    template<class T_expr, typename std::enable_if<
        is_matrix_expression<typename T_expr::tag>::value&&
        std::is_same<elem_t, typename T_expr::elem_t>::value
        >::type*& = enabler>
    self_type& operator=(const T_expr& expr)
    {
        if(dimension_row(expr) != this->size_row() ||
           dimension_col(expr) != this->size_col())
            throw std::invalid_argument("different size matrix");

        for(std::size_t i = 0; i<dimension_row(expr); ++i)
            for(auto j=0; j<dimension_col(expr); ++j)
                this->values_.at(i).at(j) = expr(i, j);
        return *this;
    }

    template<class T_expr, typename std::enable_if<
        is_matrix_expression<typename T_expr::tag>::value&&
        std::is_same<elem_t, typename T_expr::elem_t>::value
        >::type*& = enabler>
    self_type& operator+=(const T_expr& expr)
    {
        return *this = (*this + expr);
    }

    template<class T_expr, typename std::enable_if<
        is_matrix_expression<typename T_expr::tag>::value&&
        std::is_same<elem_t, typename T_expr::elem_t>::value
        >::type*& = enabler>
    self_type& operator-=(const T_expr& expr)
    {
        return *this = (*this - expr);
    }

    self_type& operator*=(const elem_t& scl)
    {
        return *this = (*this * scl);
    }

    self_type& operator/=(const elem_t& scl)
    {
        return *this = (*this / scl);
    }

    elem_t const& operator()(const std::size_t i, const std::size_t j) const
    {
        return values_[i][j];
    }

    elem_t& operator()(const std::size_t i, const std::size_t j)
    {
        return values_[i][j];
    }

    elem_t const& at(const std::size_t i, const std::size_t j) const
    {
        return values_.at(i).at(j);
    }

    elem_t& at(const std::size_t i, const std::size_t j)
    {
        return values_.at(i).at(j);
    }

    std::size_t size_row() const {return values_.size();}
    std::size_t size_col() const {return values_.front().size();}

  private:

    container_type values_;
};

}

#endif /* AX_DYNAMIC_MATRIX */
