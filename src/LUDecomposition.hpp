#ifndef AX_LU_DECOMPOSE_H
#define AX_LU_DECOMPOSE_H
#include "Matrix.hpp"
#include "DynamicMatrix.hpp"
#include <stdexcept>

namespace ax
{


template<class T_mat>
class Doolittle;

// template<class M>
// class Crout;

// template<class M>
// class Cholesky;

template<class T_mat, class T_solver>
class LUDecomposer;

template<typename T_elem, dimension_type I_dim, class T_solver>
class LUDecomposer<Matrix<T_elem, I_dim, I_dim>, T_solver>
{
  public:
    using matrix_type = Matrix<T_elem, I_dim, I_dim>;
    using solver_type = T_solver;

    // return pairof(L, U)
    static std::pair<matrix_type, matrix_type>
    solve(const matrix_type& mat){return solver_type::solve(mat);}
};

template<typename T_elem, dimension_type I_dim, class T_solver>
class LUDecomposer<Matrix<T_elem, DYNAMIC, I_dim>, T_solver>
{
  public:
    using matrix_type = Matrix<T_elem, DYNAMIC, I_dim>;
    using solver_type = T_solver;

    // return pairof(L, U)
    static std::pair<matrix_type, matrix_type>
    solve(const matrix_type& mat){return solver_type::solve(mat);}
};

template<typename T_elem, dimension_type I_dim, class T_solver>
class LUDecomposer<Matrix<T_elem, I_dim, DYNAMIC>, T_solver>
{
  public:
    using matrix_type = Matrix<T_elem, I_dim, DYNAMIC>;
    using solver_type = T_solver;

    // return pairof(L, U)
    static std::pair<matrix_type, matrix_type>
    solve(const matrix_type& mat){return solver_type::solve(mat);}
};

template<typename T_elem, class T_solver>
class LUDecomposer<Matrix<T_elem, DYNAMIC, DYNAMIC>, T_solver>
{
  public:
    using matrix_type = Matrix<T_elem, DYNAMIC, DYNAMIC>;
    using solver_type = T_solver;

    // return pairof(L, U)
    static std::pair<matrix_type, matrix_type>
    solve(const matrix_type& mat){return solver_type::solve(mat);}
};

template<typename T_elem, dimension_type I_dim>
class Doolittle<Matrix<T_elem, I_dim, I_dim>>
{
  public:

    using elem_t = T_elem;
    constexpr static dimension_type dim = I_dim;
    using matrix_type = Matrix<T_elem, I_dim, I_dim>;
    using self_type = Doolittle<Matrix<T_elem, I_dim, I_dim>>;

    static std::pair<matrix_type, matrix_type> solve(const matrix_type& mat)
    {
        matrix_type L;
        matrix_type U;
        matrix_type LU = mat;
        // TODO: exchange if 0 devide occurs

        self_type::rec_solve(0, LU);

        // ~~~~~~~ store values in L and U ~~~~~~~
        for(std::size_t i=0; i < dim; ++i)
        {
            L(i, i) = 1e0;
            for(std::size_t j = 0; j < i; ++j)
                L(i, j) = LU(i, j);

            for(std::size_t j = i+1; j < dim; ++j)
                L(i, j) = 0e0;
        }
        for(std::size_t i=0; i < dim; ++i)
        {
            for(std::size_t j = 0; j < i; ++j)
                U(i, j) = 0e0;

            for(std::size_t j = i; j < dim; ++j)
                U(i, j) = LU(i, j);
        }
        return std::make_pair(L, U);
    }

  private:
    static void rec_solve(const std::size_t step, matrix_type& LU)
    {
        if(step >= dim - 1)
            return;
        else
        {
            const elem_t inv_nn = 1e0 / LU(step,step);
            for(std::size_t i = step+1; i<dim; ++i)
                LU(i,step) = LU(i,step) * inv_nn;

            for(std::size_t i = step+1; i<dim; ++i)
                for(std::size_t j = step+1; j<dim; ++j)
                {
                    LU(i,j) = LU(i,j) - (LU(step,j) * LU(i,step));
                }
            return rec_solve(step + 1, LU);
        }
    }
};

// partial template specialization of Doolittle class for dynamic matrix{{{
template<typename T_elem, dimension_type I_dim>
class Doolittle<Matrix<T_elem, I_dim, DYNAMIC>>
{
  public:

    using elem_t = T_elem;
    constexpr static dimension_type dim = I_dim;
    using matrix_type = Matrix<T_elem, I_dim, DYNAMIC>;
    using self_type = Doolittle<Matrix<T_elem, I_dim, DYNAMIC>>;

    static std::pair<matrix_type, matrix_type> solve(const matrix_type& mat)
    {
        if(dimension_col(mat) != dimension_row(mat))
            throw std::invalid_argument("Doolittle method: not square matrix");

        matrix_type L;
        matrix_type U;
        matrix_type LU = mat;
        // TODO: exchange if 0 devide occurs

        self_type::rec_solve(0, LU);

        // ~~~~~~~ store values in L and U ~~~~~~~
        for(std::size_t i=0; i < dim; ++i)
        {
            L(i, i) = 1e0;
            for(std::size_t j = 0; j < i; ++j)
                L(i, j) = LU(i, j);

            for(std::size_t j = i+1; j < dim; ++j)
                L(i, j) = 0e0;
        }
        for(std::size_t i=0; i < dim; ++i)
        {
            for(std::size_t j = 0; j < i; ++j)
                U(i, j) = 0e0;

            for(std::size_t j = i; j < dim; ++j)
                U(i, j) = LU(i, j);
        }
        return std::make_pair(L, U);
    }

  private:
    static void rec_solve(const std::size_t step, matrix_type& LU)
    {
        if(step >= dim - 1)
            return;
        else
        {
            const elem_t inv_nn = 1e0 / LU(step,step);
            for(std::size_t i = step+1; i<dim; ++i)
                LU(i,step) = LU(i,step) * inv_nn;

            for(std::size_t i = step+1; i<dim; ++i)
                for(std::size_t j = step+1; j<dim; ++j)
                {
                    LU(i,j) = LU(i,j) - (LU(step,j) * LU(i,step));
                }
            return rec_solve(step + 1, LU);
        }
    }
};

template<typename T_elem, dimension_type I_dim>
class Doolittle<Matrix<T_elem, DYNAMIC, I_dim>>
{
  public:

    using elem_t = T_elem;
    constexpr static dimension_type dim = I_dim;
    using matrix_type = Matrix<T_elem, DYNAMIC, I_dim>;
    using self_type = Doolittle<Matrix<T_elem, DYNAMIC, I_dim>>;

    static std::pair<matrix_type, matrix_type> solve(const matrix_type& mat)
    {
        if(dimension_col(mat) != dimension_row(mat))
            throw std::invalid_argument("Doolittle method: not square matrix");

        matrix_type L;
        matrix_type U;
        matrix_type LU = mat;
        // TODO: exchange if 0 devide occurs

        self_type::rec_solve(0, LU);

        // ~~~~~~~ store values in L and U ~~~~~~~
        for(std::size_t i=0; i < dim; ++i)
        {
            L(i, i) = 1e0;
            for(std::size_t j = 0; j < i; ++j)
                L(i, j) = LU(i, j);

            for(std::size_t j = i+1; j < dim; ++j)
                L(i, j) = 0e0;
        }
        for(std::size_t i=0; i < dim; ++i)
        {
            for(std::size_t j = 0; j < i; ++j)
                U(i, j) = 0e0;

            for(std::size_t j = i; j < dim; ++j)
                U(i, j) = LU(i, j);
        }
        return std::make_pair(L, U);
    }

  private:
    static void rec_solve(const std::size_t step, matrix_type& LU)
    {
        if(step >= dim - 1)
            return;
        else
        {
            const elem_t inv_nn = 1e0 / LU(step,step);
            for(std::size_t i = step+1; i<dim; ++i)
                LU(i,step) = LU(i,step) * inv_nn;

            for(std::size_t i = step+1; i<dim; ++i)
                for(std::size_t j = step+1; j<dim; ++j)
                {
                    LU(i,j) = LU(i,j) - (LU(step,j) * LU(i,step));
                }
            return rec_solve(step + 1, LU);
        }
    }
};

template<typename T_elem>
class Doolittle<Matrix<T_elem, DYNAMIC, DYNAMIC>>
{
  public:

    using elem_t = T_elem;
    constexpr static dimension_type dim = DYNAMIC;
    using matrix_type = Matrix<T_elem, DYNAMIC, DYNAMIC>;
    using self_type = Doolittle<Matrix<T_elem, DYNAMIC, DYNAMIC>>;

    static std::pair<matrix_type, matrix_type> solve(const matrix_type& mat)
    {
        if(dimension_col(mat) != dimension_row(mat))
            throw std::invalid_argument("Doolittle method: not square matrix");

        const dimension_type dim_ = dimension_col(mat);
        matrix_type L;
        matrix_type U;
        matrix_type LU = mat;
        // TODO: exchange if 0 devide occurs

        self_type::rec_solve(0, LU);

        // ~~~~~~~ store values in L and U ~~~~~~~
        for(std::size_t i=0; i < dim_; ++i)
        {
            L(i, i) = 1e0;
            for(std::size_t j = 0; j < i; ++j)
                L(i, j) = LU(i, j);

            for(std::size_t j = i+1; j < dim_; ++j)
                L(i, j) = 0e0;
        }
        for(std::size_t i=0; i < dim_; ++i)
        {
            for(std::size_t j = 0; j < i; ++j)
                U(i, j) = 0e0;

            for(std::size_t j = i; j < dim_; ++j)
                U(i, j) = LU(i, j);
        }
        return std::make_pair(L, U);
    }

  private:
    static void rec_solve(const std::size_t step, matrix_type& LU)
    {
        const dimension_type dim_ = dimension_col(LU);
        if(step >= dim_ - 1)
            return;
        else
        {
            const elem_t inv_nn = 1e0 / LU(step,step);
            for(std::size_t i = step+1; i<dim_; ++i)
                LU(i,step) = LU(i,step) * inv_nn;

            for(std::size_t i = step+1; i<dim_; ++i)
                for(std::size_t j = step+1; j<dim_; ++j)
                {
                    LU(i,j) = LU(i,j) - (LU(step,j) * LU(i,step));
                }
            return rec_solve(step + 1, LU);
        }
    }
};

// }}}

// helper function

template<template<typename T>class T_solver, typename T_mat,
    typename std::enable_if<
    is_matrix_expression<typename T_mat::tag>::value&&
    is_same_dimension<T_mat::dim_col, T_mat::dim_row>::value>::type*& = enabler>
std::pair<Matrix<typename T_mat::elem_t, T_mat::dim_row, T_mat::dim_col>,
          Matrix<typename T_mat::elem_t, T_mat::dim_row, T_mat::dim_col>>
LUdecompose(const T_mat& mat)
{
    return LUDecomposer<
        Matrix<typename T_mat::elem_t, T_mat::dim_row, T_mat::dim_col>,
        T_solver<Matrix<typename T_mat::elem_t, T_mat::dim_row, T_mat::dim_col>>
            >::solve(mat);
}

// for (static, dynamic)
template<template<typename T>class T_solver, typename T_mat,
    typename std::enable_if<
    is_matrix_expression<typename T_mat::tag>::value&&
    is_static_dimension<T_mat::dim_row>::value&&
    is_dynamic_dimension<T_mat::dim_col>::value
    >::type*& = enabler>
std::pair<Matrix<typename T_mat::elem_t, T_mat::dim_row, T_mat::dim_row>,
          Matrix<typename T_mat::elem_t, T_mat::dim_row, T_mat::dim_row>>
LUdecompose(const T_mat& mat)
{
    return LUDecomposer<
        Matrix<typename T_mat::elem_t, T_mat::dim_row, T_mat::dim_col>,
        T_solver<Matrix<typename T_mat::elem_t, T_mat::dim_row, T_mat::dim_col>>
            >::solve(mat);
}

// for (dynamic, static)
template<template<typename T>class T_solver, typename T_mat,
    typename std::enable_if<
    is_matrix_expression<typename T_mat::tag>::value&&
    is_dynamic_dimension<T_mat::dim_row>::value&&
    is_static_dimension<T_mat::dim_col>::value
    >::type*& = enabler>
std::pair<Matrix<typename T_mat::elem_t, T_mat::dim_col, T_mat::dim_col>,
          Matrix<typename T_mat::elem_t, T_mat::dim_col, T_mat::dim_col>>
LUdecompose(const T_mat& mat)
{
    return LUDecomposer<
        Matrix<typename T_mat::elem_t, T_mat::dim_row, T_mat::dim_col>,
        T_solver<Matrix<typename T_mat::elem_t, T_mat::dim_row, T_mat::dim_col>>
            >::solve(mat);
}

}
#endif /* AX_LU_DECOMPOSE_H */
