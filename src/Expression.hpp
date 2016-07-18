#ifndef AX_EXPRESSION_H
#define AX_EXPRESSION_H
#include <type_traits>
#include <cstddef>

namespace ax
{
    extern void* enabler; //never defined

    using dimension_type = int;
    constexpr static dimension_type DYNAMIC = -1;

    struct operator_tag{};
    struct matrix_tag{};
    struct matrix_expression_tag{};
    struct vector_tag{};
    struct vector_expression_tag{};
    struct avx_operation_tag{};

    template <dimension_type I_dim>
    struct is_static_dimension{constexpr static bool value = I_dim > 0;};
    template <dimension_type I_dim>
    struct is_dynamic_dimension{constexpr static bool value = I_dim < 0;};
    template <dimension_type I_dim>
    struct is_void_dimension{constexpr static bool value = I_dim == 0;};

    template <typename T>
    struct is_operator_struct : public std::false_type{};
    template <>
    struct is_operator_struct<operator_tag> : public std::true_type{};

    template<typename T>
    struct is_matrix_type : public std::false_type {};
    template<>
    struct is_matrix_type<matrix_tag> : public std::true_type {};

    template<typename T>
    struct is_exactly_matrix_expr : public std::false_type {};
    template<>
    struct is_exactly_matrix_expr<matrix_expression_tag>: public std::true_type{};

    template <typename T>
    struct is_matrix_expression: public std::false_type{};
    template <>
    struct is_matrix_expression<matrix_tag>: public std::true_type{};
    template <>
    struct is_matrix_expression<matrix_expression_tag>: public std::true_type{};

    template<typename T>
    struct is_vector_type : public std::false_type {};
    template<>
    struct is_vector_type<vector_tag> : public std::true_type {};

    template<typename T>
    struct is_exactly_vector_expr : public std::false_type {};
    template<>
    struct is_exactly_vector_expr<vector_expression_tag> : public std::true_type {};

    template <typename T>
    struct is_vector_expression: public std::false_type{};
    template <>
    struct is_vector_expression<vector_tag>: public std::true_type{};
    template <>
    struct is_vector_expression<vector_expression_tag>: public std::true_type{};

    template <dimension_type I_ldim, dimension_type I_rdim>
    struct is_same_dimension: public std::false_type{};
    template <dimension_type I_dim>
    struct is_same_dimension<I_dim, I_dim>: public std::true_type{};

    template <dimension_type I_dim>
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
            is_same_dimension<T_lhs::dim, T_rhs::dim>::value&&
            std::is_same<typename T_lhs::elem_t, typename T_rhs::elem_t>::value;
    };

    template<typename T_lhs, typename T_rhs>
    struct is_static_dynamic_pair
    {
        constexpr static bool value = 
            (is_static_dimension<T_lhs::dim>::value &&
             is_dynamic_dimension<T_rhs::dim>::value) || 
            (is_dynamic_dimension<T_lhs::dim>::value &&
             is_static_dimension<T_rhs::dim>::value);
    };

    template<typename T_lhs, typename T_rhs>
    struct vector_expression_dimension
    {
        // case static  * static  -> lhs::dim (static  = N)
        // case static  * dynamic -> lhs::dim (static  = N)
        // case dynamic * static  -> rhs::dim (static  = N)
        // case dynamic * dynamic -> lhs::dim (DYNAMIC = -1)
        constexpr static dimension_type value =
            (is_dynamic_dimension<T_lhs::dim>::value &&
             is_static_dimension<T_rhs::dim>::value)
            ? T_rhs::dim : T_lhs::dim;
    };

}
#endif //AX_MATRIX_EXPRESSION_H
