#define BOOST_TEST_MODULE "test_vector_matrix"

#ifdef UNITTEST_FRAMEWORK_LIBRARY_EXIST
#include <boost/test/unit_test.hpp>
#else
#define BOOST_TEST_NO_LIB
#include <boost/test/included/unit_test.hpp>
#endif

#include "../LinearAlgebra.hpp"
using Vector3d = ax::Vector<double, 3>;
using Vector4d = ax::Vector<double, 4>;
using Matrix3  = ax::Matrix3d;
using Matrix4  = ax::Matrix4d;

#include "test_Defs.hpp"
using ax::test::tolerance;
using ax::test::seed;

#include <random>

BOOST_AUTO_TEST_CASE(vector3d_matrix3x3_multiplication)
{
    const Vector3d vec1(1e0, 2e0, 3e0);
    const Matrix3  mat1(1e0);
    const Vector3d vec2 = mat1 * vec1;

    BOOST_CHECK_EQUAL(vec2[0], vec1[0]);
    BOOST_CHECK_EQUAL(vec2[1], vec1[1]);
    BOOST_CHECK_EQUAL(vec2[2], vec1[2]);

    const Matrix3  mat2(2e0);
    const Vector3d vec3 = mat2 * vec1;

    BOOST_CHECK_EQUAL(vec3[0], 2e0 * vec1[0]);
    BOOST_CHECK_EQUAL(vec3[1], 2e0 * vec1[1]);
    BOOST_CHECK_EQUAL(vec3[2], 2e0 * vec1[2]);

    std::mt19937 mt(seed);
    std::uniform_real_distribution<double> randreal(0e0, 1e0);

    Matrix3  mat3;
    std::array<std::array<double, 3>, 3> random1;
    for(std::size_t i = 0; i < 3; ++i)
        for(std::size_t j = 0; j < 3; ++j)
            random1[i][j] = randreal(mt);

    for(std::size_t i = 0; i < 3; ++i)
        for(std::size_t j = 0; j < 3; ++j)
            mat3(i, j) = random1[i][j];

    const Vector3d ones(1e0, 1e0, 1e0);
    const Vector3d vec4 = mat3 * ones;
    for(std::size_t i = 0; i < 3; ++i)
    {
        double value = 0e0;
        for(std::size_t j = 0; j < 3; ++j)
            value += random1[i][j];
        BOOST_CHECK_EQUAL(vec4[i], value);
    }
}

BOOST_AUTO_TEST_CASE(matrix3x3_vector3d_multiplication)
{
    const Vector3d vec1(1e0, 2e0, 3e0);
    const Matrix3  mat1(1e0);
    const Vector3d vec2 = vec1 * mat1;

    BOOST_CHECK_EQUAL(vec2[0], vec1[0]);
    BOOST_CHECK_EQUAL(vec2[1], vec1[1]);
    BOOST_CHECK_EQUAL(vec2[2], vec1[2]);

    const Matrix3  mat2(2e0);
    const Vector3d vec3 = vec1 * mat2;

    BOOST_CHECK_EQUAL(vec3[0], 2e0 * vec1[0]);
    BOOST_CHECK_EQUAL(vec3[1], 2e0 * vec1[1]);
    BOOST_CHECK_EQUAL(vec3[2], 2e0 * vec1[2]);

    std::mt19937 mt(seed);
    std::uniform_real_distribution<double> randreal(0e0, 1e0);

    Matrix3  mat3;
    std::array<std::array<double, 3>, 3> random1;
    for(std::size_t i = 0; i < 3; ++i)
        for(std::size_t j = 0; j < 3; ++j)
            random1[i][j] = randreal(mt);

    for(std::size_t i = 0; i < 3; ++i)
        for(std::size_t j = 0; j < 3; ++j)
            mat3(i, j) = random1[i][j];

    const Vector3d ones(1e0, 1e0, 1e0);
    const Vector3d vec4 = ones * mat3;
    for(std::size_t i = 0; i < 3; ++i)
    {
        double value = 0e0;
        for(std::size_t j = 0; j < 3; ++j)
            value += random1[j][i];
        BOOST_CHECK_EQUAL(vec4[i], value);
    }
}

BOOST_AUTO_TEST_CASE(vector4d_matrix4x4_multiplication)
{
    const Vector4d vec1(2e0);
    const Matrix4  mat1(1e0);
    const Vector4d vec2 = mat1 * vec1;

    for(std::size_t i = 0; i<4; ++i)
        BOOST_CHECK_EQUAL(vec2[i], vec1[i]);

    const Matrix4 mat2(2e0);
    const Vector4d vec3 = mat2 * vec1;

    for(std::size_t i = 0; i<4; ++i)
        BOOST_CHECK_EQUAL(vec3[i], 2e0 * vec1[i]);

    std::mt19937 mt(seed);
    std::uniform_real_distribution<double> randreal(0e0, 1e0);

    Matrix4  mat3;
    std::array<std::array<double, 4>, 4> random1;
    for(std::size_t i = 0; i < 4; ++i)
        for(std::size_t j = 0; j < 4; ++j)
            random1[i][j] = randreal(mt);

    for(std::size_t i = 0; i < 4; ++i)
        for(std::size_t j = 0; j < 4; ++j)
            mat3(i, j) = random1[i][j];

    const Vector4d ones(1e0);
    const Vector4d vec4 = mat3 * ones;
    for(std::size_t i = 0; i < 4; ++i)
    {
        double value = 0e0;
        for(std::size_t j = 0; j < 4; ++j)
            value += random1[i][j];
        BOOST_CHECK_EQUAL(vec4[i], value);
    }
}

BOOST_AUTO_TEST_CASE(matrix4x4_vector4d_multiplication)
{
    const Vector4d vec1(1e0);
    const Matrix4  mat1(1e0);
    const Vector4d vec2 = vec1 * mat1;

    for(std::size_t i=0; i<4; ++i)
        BOOST_CHECK_EQUAL(vec2[i], vec1[i]);

    const Matrix4  mat2(2e0);
    const Vector4d vec3 = vec1 * mat2;

    for(std::size_t i=0; i<4; ++i)
        BOOST_CHECK_EQUAL(vec3[i], 2e0 * vec1[i]);

    std::mt19937 mt(seed);
    std::uniform_real_distribution<double> randreal(0e0, 1e0);

    Matrix4 mat3;
    std::array<std::array<double, 4>, 4> random1;
    for(std::size_t i = 0; i < 4; ++i)
        for(std::size_t j = 0; j < 4; ++j)
            random1.at(i).at(j) = randreal(mt);

    for(std::size_t i = 0; i < 4; ++i)
        for(std::size_t j = 0; j < 4; ++j)
            mat3(i, j) = random1.at(i).at(j);

    const Vector4d ones(1e0);
    const Vector4d vec4 = ones * mat3;
    for(std::size_t i = 0; i < 4; ++i)
    {
        double value = 0e0;
        for(std::size_t j = 0; j < 4; ++j)
            value += random1[j][i];
        BOOST_CHECK_EQUAL(vec4[i], value);
    }
}


BOOST_AUTO_TEST_CASE(matrix4x3_vector3d_multiplication)
{
    const Vector3d        vec1(1e0, 1e0, 1e0);
    ax::Matrix<double, 4, 3>  mat1;

    std::mt19937 mt(seed);
    std::uniform_real_distribution<double> randreal(0e0, 1e0);

    std::array<std::array<double, 3>, 4> random1;
    for(std::size_t i = 0; i < 4; ++i)
        for(std::size_t j = 0; j < 3; ++j)
            random1[i][j] = randreal(mt);

    for(std::size_t i = 0; i < 4; ++i)
        for(std::size_t j = 0; j < 3; ++j)
            mat1(i, j) = random1[i][j];

    const Vector4d   vec2 = mat1 * vec1;
    for(std::size_t i = 0; i < 4; ++i)
    {
        double value = 0e0;
        for(std::size_t j = 0; j < 3; ++j)
            value += random1[i][j];
        BOOST_CHECK_EQUAL(vec2[i], value);
    }
}

BOOST_AUTO_TEST_CASE(matrix3x4_vector4d_multiplication)
{
    const Vector4d vec1(1e0);
    for(std::size_t i=0; i<4;++i)
        assert(vec1[i] == 1e0);
    ax::Matrix<double, 3, 4>    mat1;

    std::mt19937 mt(seed);
    std::uniform_real_distribution<double> randreal(0e0, 1e0);

    std::array<std::array<double, 4>, 3> random1;
    for(std::size_t i = 0; i < 3; ++i)
        for(std::size_t j = 0; j < 4; ++j)
            random1.at(i).at(j) = randreal(mt);

    for(std::size_t i = 0; i < 3; ++i)
        for(std::size_t j = 0; j < 4; ++j)
            mat1(i, j) = random1.at(i).at(j);

    const Vector3d vec2 = mat1 * vec1;
    for(std::size_t i = 0; i < 3; ++i)
    {
        double value = 0e0;
        for(std::size_t j = 0; j < 4; ++j)
            value += random1[i][j];
        BOOST_CHECK_EQUAL(vec2[i], value);
    }
}

BOOST_AUTO_TEST_CASE(vector4d_matrix4x3_multiplication)
{
    const Vector4d vec1(1e0);
    for(std::size_t i = 0; i<4; ++i)
        assert(vec1[i] == 1e0);

    ax::Matrix<double, 4, 3>    mat1;

    std::mt19937 mt(seed);
    std::uniform_real_distribution<double> randreal(0e0, 1e0);

    std::array<std::array<double, 3>, 4> random1;
    for(std::size_t i = 0; i < 4; ++i)
        for(std::size_t j = 0; j < 3; ++j)
            random1[i][j] = randreal(mt);

    for(std::size_t i = 0; i < 4; ++i)
        for(std::size_t j = 0; j < 3; ++j)
            mat1(i, j) = random1[i][j];

    const Vector3d vec2 = vec1 * mat1;
    for(std::size_t i = 0; i < 3; ++i)
    {
        double value = 0e0;
        for(std::size_t j = 0; j < 4; ++j)
            value += random1[j][i];
        BOOST_CHECK_EQUAL(vec2[i], value);
    }
}

BOOST_AUTO_TEST_CASE(vector3d_matrix3x4_multiplication)
{
    const Vector3d vec1(1e0, 1e0, 1e0);
    for(std::size_t i = 0; i<3; ++i)
        assert(vec1[i] == 1e0);

    ax::Matrix<double, 3, 4> mat1;

    std::mt19937 mt(seed);
    std::uniform_real_distribution<double> randreal(0e0, 1e0);

    std::array<std::array<double, 4>, 3> random1;
    for(std::size_t i = 0; i < 3; ++i)
        for(std::size_t j = 0; j < 4; ++j)
            random1.at(i).at(j) = randreal(mt);

    for(std::size_t i = 0; i < 3; ++i)
        for(std::size_t j = 0; j < 4; ++j)
            mat1(i, j) = random1.at(i).at(j);

    const Vector4d vec2 = vec1 * mat1;
    for(std::size_t i = 0; i < 4; ++i)
    {
        double value = 0e0;
        for(std::size_t j = 0; j < 3; ++j)
            value += random1[j][i];
        BOOST_CHECK_EQUAL(vec2[i], value);
    }
}
