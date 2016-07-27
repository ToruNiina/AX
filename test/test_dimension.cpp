#define BOOST_TEST_MODULE "test_dimension"

#ifdef UNITTEST_FRAMEWORK_LIBRARY_EXIST
#include <boost/test/unit_test.hpp>
#else
#define BOOST_TEST_NO_LIB
#include <boost/test/included/unit_test.hpp>
#endif

#include "../LinearAlgebra.hpp"
constexpr static std::size_t N = 3;
constexpr static std::size_t M = 6;

BOOST_AUTO_TEST_CASE(dimension_static_vector)
{
    const ax::Vector<double, N> vec1;
    const ax::Vector<double, M> vec2(1e0);

    BOOST_CHECK_EQUAL(dimension(vec1), N);
    BOOST_CHECK_EQUAL(dimension(vec2), M);
}

BOOST_AUTO_TEST_CASE(dimension_dynamic_vector)
{
    const ax::Vector<double, ax::DYNAMIC> vec1(N);
          ax::Vector<double, ax::DYNAMIC> vec2(M);

    BOOST_CHECK_EQUAL(dimension(vec1), N);
    BOOST_CHECK_EQUAL(dimension(vec2), M);

    vec2.append(1.0);
    BOOST_CHECK_EQUAL(dimension(vec2), M+1);
}

BOOST_AUTO_TEST_CASE(dimension_expression)
{
    const ax::Vector<double, N> vec1(1.0);
    const ax::Vector<double, N> vec2(2.0);

    // static + static
    const auto expr1 = vec1 + vec2;
    BOOST_CHECK_EQUAL(dimension(expr1), N);

    const auto expr2 = vec1 * 2.0;
    BOOST_CHECK_EQUAL(dimension(expr2), N);

    // dynamic + dynamic
    const ax::Vector<double, ax::DYNAMIC> vec3(N);
    const ax::Vector<double, ax::DYNAMIC> vec4(N);

    const auto expr3 = vec3 + vec4;
    BOOST_CHECK_EQUAL(dimension(expr3), N);

    const auto expr4 = vec3 * 2.0;
    BOOST_CHECK_EQUAL(dimension(expr4), N);

    // mixture
    const auto expr5 = vec1 + vec3;
    BOOST_CHECK_EQUAL(dimension(expr5), N);

    const auto expr6 = vec3 + vec1;
    BOOST_CHECK_EQUAL(dimension(expr6), N);
}

BOOST_AUTO_TEST_CASE(dimension_static_matrix_column)
{
    const ax::Matrix<double, N, M> mat1(1e0);
    const ax::Matrix<double, M, N> mat2(1e0);

    BOOST_CHECK_EQUAL(dimension_col(mat1), M);
    BOOST_CHECK_EQUAL(dimension_col(mat2), N);
}

BOOST_AUTO_TEST_CASE(dimension_static_matrix_row)
{
    const ax::Matrix<double, N, M> mat1(1e0);
    const ax::Matrix<double, M, N> mat2(1e0);

    BOOST_CHECK_EQUAL(dimension_row(mat1), N);
    BOOST_CHECK_EQUAL(dimension_row(mat2), M);
}

BOOST_AUTO_TEST_CASE(dimension_dynamic_matrix_column)
{
    const ax::Matrix<double, ax::DYNAMIC, ax::DYNAMIC> mat1(N, M);
    const ax::Matrix<double, ax::DYNAMIC, ax::DYNAMIC> mat2(M, N);

    BOOST_CHECK_EQUAL(dimension_col(mat1), M);
    BOOST_CHECK_EQUAL(dimension_col(mat2), N);
}

BOOST_AUTO_TEST_CASE(dimension_dynamic_matrix_row)
{
    const ax::Matrix<double, ax::DYNAMIC, ax::DYNAMIC> mat1(N, M);
    const ax::Matrix<double, ax::DYNAMIC, ax::DYNAMIC> mat2(M, N);

    BOOST_CHECK_EQUAL(dimension_row(mat1), N);
    BOOST_CHECK_EQUAL(dimension_row(mat2), M);
}

