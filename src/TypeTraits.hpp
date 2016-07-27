#ifndef AX_EXPRESSION_H
#define AX_EXPRESSION_H
#include <type_traits>
#include <cstddef>

namespace ax
{
    extern void* enabler; //never defined

    using dimension_type = std::size_t;
    constexpr static dimension_type DYNAMIC = 0;

    struct operator_tag{};
    struct matrix_tag{};
    struct matrix_expression_tag{};
    struct matrix_product_tag{};
    struct matrix_transpose_tag{};
    struct vector_tag{};
    struct vector_expression_tag{};
    struct avx_operation_tag{};

    template <dimension_type I_dim>
    struct is_static_dimension{constexpr static bool value = (I_dim > 0);};
    template <dimension_type I_dim>
    struct is_dynamic_dimension{constexpr static bool value = (I_dim == 0);};

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

    template<typename T>
    struct is_exactly_matrix_prod : public std::false_type {};
    template<>
    struct is_exactly_matrix_prod<matrix_product_tag>: public std::true_type{};

    template<typename T>
    struct is_exactly_matrix_trans : public std::false_type {};
    template<>
    struct is_exactly_matrix_trans<matrix_transpose_tag>: public std::true_type{};

    template <typename T>
    struct is_matrix_expression: public std::false_type{};
    template <>
    struct is_matrix_expression<matrix_tag>: public std::true_type{};
    template <>
    struct is_matrix_expression<matrix_expression_tag>: public std::true_type{};
    template <>
    struct is_matrix_expression<matrix_product_tag>: public std::true_type{};
    template <>
    struct is_matrix_expression<matrix_transpose_tag>: public std::true_type{};

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

    template<typename T_target, typename Front, typename ... T_args>
    struct is_all
    {
        constexpr static bool value =
            std::is_same<T_target, Front>::value &&
            is_all<T_target, T_args...>::value;
    };

    template<typename T_target, typename Last>
    struct is_all<T_target, Last>
    {
        constexpr static bool value = std::is_same<T_target, Last>::value;
    };

}
#endif //AX_MATRIX_EXPRESSION_H
