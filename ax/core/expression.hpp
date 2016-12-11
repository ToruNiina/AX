#ifndef AX_EXPRESSION
#define AX_EXPRESSION
#include "scalar_type_of.hpp"
#include <type_traits>

namespace ax
{

template<typename lhsT, typename operatorT, typename rhsT,
         dimension_type rowN, dimension_type colN>
struct matrix_expression
{
  public:
    typedef expression_tag tag;
    typedef typename scalar_type_of<lhsT>::type scalar_type;
    constexpr static dimension_type row = rowN;
    constexpr static dimension_type col = colN;

  public:
    matrix_expression(const lhsT& lhs, const rhsT& rhs): l_(lhs), r_(rhs){}

    scalar_type operator()(const std::size_t i, const std::size_t j) const
    {
        return operatorT::invoke(l_(i, j), r_(i, j));
    }

    lhsT const& l_;
    rhsT const& r_;
};

template<typename lhsT, typename rhsT, dimension_type rowN, dimension_type colN>
struct matrix_product
{
  public:
    typedef expression_tag tag;
    typedef typename scalar_type_of<lhsT>::type scalar_type;
    constexpr static dimension_type row = rowN;
    constexpr static dimension_type col = colN;

  public:
    matrix_product(const lhsT& lhs, const rhsT& rhs): l_(lhs), r_(rhs){}

    scalar_type operator()(const std::size_t i, const std::size_t j) const
    {
        scalar_type retval = 0;
        for(std::size_t k = 0; k < row_size(r_); ++k)
            retval += l_(i,k) * r_(k,j);
        return retval;
    }

    lhsT const& l_;
    rhsT const& r_;
};

template<typename matrixT, typename operatorT,
         dimension_type rowN, dimension_type colN>
struct scalar_expression
{
  public:
    typedef expression_tag tag;
    typedef typename scalar_type_of<matrixT>::type scalar_type;
    constexpr static dimension_type row = rowN;
    constexpr static dimension_type col = colN;

  public:
    template<typename sclT, class = typename std::enable_if<
        std::is_convertible<sclT, scalar_type>::value>::type>
    scalar_expression(const matrixT& mat, const sclT& scl): m_(mat), s_(scl){}

    scalar_type operator()(const std::size_t i, const std::size_t j) const
    {
        return m_(i, j) * s_;
    }

    matrixT     const& m_;
    scalar_type const  s_; // is not reference
};

template<typename matrixT, dimension_type rowN, dimension_type colN>
struct matrix_transpose
{
  public:

    typedef expression_tag tag;
    typedef typename scalar_type_of<matrixT>::type scalar_type;
    constexpr static dimension_type row = rowN;
    constexpr static dimension_type col = colN;

    matrix_transpose(const matrixT& mat): m_(mat){}

    scalar_type operator()(const std::size_t i, const std::size_t j) const
    {
        return m_(j, i);
    }

    matrixT const& m_;
};

} // ax
#endif /* AX_EXPRESSION */
