#ifndef AX_JACOBI_METHOD_H
#define AX_JACOBI_METHOD_H
#include <utility>
#include <algorithm>
#include <cmath>
#include "Matrix.hpp"
#include "Vector.hpp"

namespace ax
{

template <typename T_mat>
class JacobiMethod;


template <typename T_elem, dimension_type I_dim>
class JacobiMethod<Matrix<T_elem, I_dim, I_dim>>
{
  public:
    // traits
    using elem_t = T_elem;
    constexpr static dimension_type dim = I_dim;

    using matrix_type = Matrix<elem_t, dim, dim>;
    using vector_type = Vector<elem_t, dim>;
    using eigenvalue_type = elem_t;
    using eigenvector_type = vector_type;
    using eigenpair_type = std::pair<elem_t, vector_type>;

    constexpr static elem_t ABS_TOLERANCE = 1e-10;
    constexpr static elem_t REL_TOLERANCE = 1e-12;
    constexpr static std::size_t MAX_LOOP = 10000;

  public:
    JacobiMethod(){}
    ~JacobiMethod() = default;

    template<class T_mat, typename std::enable_if<
        is_matrix_expression<typename T_mat::tag>::value&&
        is_same_dimension<T_mat::dim_row, dim>::value&&
        is_same_dimension<T_mat::dim_col, dim>::value
        >::type*& = enabler>
    JacobiMethod(const T_mat& mat) : matrix_(mat){}

    std::array<eigenpair_type, dim> solve() const;

    matrix_type const& matrix() const {return this->matrix_;}
    matrix_type&       matrix()       {return this->matrix_;}

  private:

    bool is_symmetric(const matrix_type& m) const;
    std::pair<std::size_t, std::size_t> get_maxindex(const matrix_type& m) const;
    elem_t max_relative_tolerance(const matrix_type& ta, const matrix_type& tm) const;

  private:

    matrix_type matrix_;
};


template <typename T_elem, dimension_type I_dim>
std::array<typename JacobiMethod<Matrix<T_elem, I_dim, I_dim>>::eigenpair_type,
           JacobiMethod<Matrix<T_elem, I_dim, I_dim>>::dim>
JacobiMethod<Matrix<T_elem, I_dim, I_dim>>::solve() const
{
    if(!is_symmetric(matrix_))
        throw std::invalid_argument("JacobiMethod: asymmetric matrix");

    matrix_type target(matrix_);
    matrix_type Ps(1e0);

    unsigned int num_Jacobi_loop(0);
    for(; num_Jacobi_loop < MAX_LOOP; ++num_Jacobi_loop)
    {
        if(!is_symmetric(target))
            throw std::invalid_argument("JacobiMethod: asymmetric matrix");

        std::pair<std::size_t, std::size_t> index(get_maxindex(target));

        if(std::abs(target(index.first, index.second)) < ABS_TOLERANCE) break;

        const elem_t alpha = (target(index.first,  index.first) -
                              target(index.second, index.second)) * 0.5;
        const elem_t beta  = -1e0 * target(index.first, index.second);
        const elem_t gamma = std::abs(alpha) / sqrt(alpha * alpha + beta * beta);

        const elem_t cos_ = sqrt((1e0 + gamma) * 0.5);
        const elem_t sin_ = (alpha * beta < 0e0) ?
                             -1.0 * sqrt(0.5 * (1e0 - gamma)) :
                             sqrt(0.5 * (1e0 - gamma));
        matrix_type Ppri(1e0);
        Ppri(index.first, index.first)   =  cos_;
        Ppri(index.first, index.second)  =  sin_;
        Ppri(index.second, index.first)  = -sin_;
        Ppri(index.second, index.second) =  cos_;

        matrix_type temp(transpose(Ppri) * target * Ppri);
        temp(index.first, index.second) = 0e0; // should be zero
        temp(index.second, index.first) = 0e0;

        if(max_relative_tolerance(target, temp) < REL_TOLERANCE) break;

        target = temp;
        temp = Ps * Ppri;
        Ps = temp;
    }

    if(num_Jacobi_loop == MAX_LOOP)
        std::cerr << "Warning: Cannot solve with the tolerance" << std::endl;

    std::array<eigenpair_type, dim> retval;
    for(std::size_t i(0); i<dim; ++i)
    {
        vector_type evec;
        for(std::size_t j(0); j<dim; ++j) evec[j] = Ps(j,i);
        retval[i] = std::make_pair(target(i,i), evec);
    }

    return retval;
}

template <typename T_elem, dimension_type I_dim>
inline std::pair<std::size_t, std::size_t>
JacobiMethod<Matrix<T_elem, I_dim, I_dim>>::get_maxindex(const matrix_type& m) const
{
    elem_t max = std::abs(m(0,1));
    auto index = std::make_pair(0,1);

    for(std::size_t i(0); i<dim-1; ++i)
        for(std::size_t j(i+1); j<dim; ++j)
            if(max < std::abs(m(i,j)))
            {
                max = std::abs(m(i,j));
                index = std::make_pair(i,j);
            }
    return index;
}

template <typename T_elem, dimension_type I_dim>
inline typename JacobiMethod<Matrix<T_elem, I_dim, I_dim>>::elem_t
JacobiMethod<Matrix<T_elem, I_dim, I_dim>>::max_relative_tolerance
    (const matrix_type& ta,  const matrix_type& tm) const
{
    elem_t max_reltol(0e0);
    for(auto i(0); i<dim; ++i)
    {
        const elem_t temp = std::abs(ta(i,i) - tm(i,i));
        if(temp > max_reltol) max_reltol = temp;
    }
    return max_reltol;
}

template <typename T_elem, dimension_type I_dim>
inline bool
JacobiMethod<Matrix<T_elem, I_dim, I_dim>>::is_symmetric(const matrix_type& m) const
{
    for(auto i(0); i<dim-1; ++i)
        for(auto j(i+1); j<dim; ++j)
            if(fabs(m(i,j) - m(j,i)) > ABS_TOLERANCE) return false;
    return true;
}

// helper function
template<typename T_mat, typename std::enable_if<
    is_matrix_expression<typename T_mat::tag>::value&&
    is_same_dimension<T_mat::dim_col, T_mat::dim_row>::value&&
    is_static_dimension<T_mat::dim_col>::value>::type*& = enabler>
std::array<typename JacobiMethod<
               Matrix<typename T_mat::elem_t, T_mat::dim_row, T_mat::dim_col>
           >::eigenpair_type, T_mat::dim_col>
Jacobimethod(const T_mat& mat)
{
    return (JacobiMethod<
               Matrix<typename T_mat::elem_t, T_mat::dim_row, T_mat::dim_col>
            >(mat)).solve();
}


}//ax

#endif //AX_JACOBI_METHOD_H
