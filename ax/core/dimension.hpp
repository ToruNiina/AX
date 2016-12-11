#ifndef AX_DIMENSION
#define AX_DIMENSION
#include <type_traits>

namespace ax
{

typedef std::size_t dimension_type;
constexpr static dimension_type DYNAMIC = 0;

template<typename matrixT>
struct row_dimension_of
    : public std::integral_constant<dimension_type, matrixT::row>{};

template<typename matrixT>
struct column_dimension_of
    : public std::integral_constant<dimension_type, matrixT::col>{};

} // ax

#endif /* AX_DIMENSION */
