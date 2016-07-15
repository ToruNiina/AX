#ifndef AX_EXPRESSION_H
#define AX_EXPRESSION_H
#include <type_traits>
#include <cstddef>

namespace ax
{
    extern void* enabler; //never defined

    using dimention_type = int;

    struct operator_tag{};
    struct matrix_tag{};
    struct matrix_expression_tag{};
    struct vector_tag{};
    struct vector_expression_tag{};
    struct avx_operation_tag{};

    template <dimention_type I_dim>
    struct is_static_dimention{constexpr static bool value = I_dim >= 0;};
    template <dimention_type I_dim>
    struct is_dynamic_dimention{constexpr static bool value = I_dim < 0;};

    template <typename T>
    struct is_operator_struct : public std::false_type{};
    template <>
    struct is_operator_struct<operator_tag> : public std::true_type{};

    template <typename T>
    struct is_matrix_expression: public std::false_type{};
    template <>
    struct is_matrix_expression<matrix_tag>: public std::true_type{};
    template <>
    struct is_matrix_expression<matrix_expression_tag>: public std::true_type{};

    template <typename T>
    struct is_vector_expression: public std::false_type{};
    template <>
    struct is_vector_expression<vector_tag>: public std::true_type{};
    template <>
    struct is_vector_expression<vector_expression_tag>: public std::true_type{};

    template <dimention_type I_ldim, dimention_type I_rdim>
    struct is_same_dimention: public std::false_type{};
    template <dimention_type I_dim>
    struct is_same_dimention<I_dim, I_dim>: public std::true_type{};

    template <dimention_type I_dim>
    struct is_scalar{constexpr static bool value = (I_dim == 0);};

    template <typename T, typename T_vec>
    struct is_scalar_type
    {
        constexpr static bool value =
            std::is_same<T, typename T_vec::elem_t>::value;
    };

    template <typename T_lhs, typename T_rhs>
    struct is_same_vector
    {
        constexpr static bool value =
            is_vector_expression<typename T_lhs::tag>::value&&
            is_vector_expression<typename T_rhs::tag>::value&&
            is_same_dimention<T_lhs::dim, T_rhs::dim>::value&&
            std::is_same<typename T_lhs::elem_t, typename T_rhs::elem_t>::value;
    };

}
#endif //AX_MATRIX_EXPRESSION_H
