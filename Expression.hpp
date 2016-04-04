#ifndef AX_EXPRESSION_H
#define AX_EXPRESSION_H
#include <type_traits>
#include <cstddef>

namespace ax
{
    extern void* enabler;

    class Matrix{};
    class MatrixExp{};
    class Vector{};
    class VectorExp{};

    class DynamicMatrix{};
    class DynamicMatrixExp{};
    class DynamicVector{};
    class DynamicVectorExp{};

    template <typename T>
    class is_MatrixExpression:public std::false_type{};
    template <>
    class is_MatrixExpression<Matrix>:public std::true_type{};
    template <>
    class is_MatrixExpression<MatrixExp>: public std::true_type{};

    template <typename T>
    class is_VectorExpression:public std::false_type{};
    template <>
    class is_VectorExpression<Vector>:public std::true_type{};
    template <>
    class is_VectorExpression<VectorExp>:public std::true_type{};

    template <std::size_t LN, std::size_t RN>
    class is_SameSize: public std::false_type{};
    template <std::size_t LN>
    class is_SameSize<LN, LN>: public std::true_type{};

    template <typename T>
    class is_ScalarType: public std::false_type{};
    template <>
    class is_ScalarType<double>: public std::true_type{};

    // =============================== dynamic =================================
    template <typename T>
    class is_DynamicVectorExpression:public std::false_type{};
    template <>
    class is_DynamicVectorExpression<Vector>:public std::true_type{};
    template <>
    class is_DynamicVectorExpression<VectorExp>:public std::true_type{};

    template <typename T>
    class is_DynamicMatrixExpression:public std::false_type{};
    template <>
    class is_DynamicMatrixExpression<DynamicMatrix>:public std::true_type{};
    template <>
    class is_DynamicMatrixExpression<DynamicMatrixExp>: public std::true_type{};

}
#endif //AX_MATRIX_EXPRESSION_H
