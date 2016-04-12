#define BOOST_TEST_MODULE "test_static_matrix"

#ifdef UNITTEST_FRAMEWORK_LIBRARY_EXIST
#include <boost/test/unit_test.hpp>
#else
#define BOOST_TEST_NO_LIB
#include <boost/test/included/unit_test.hpp>
#endif

#include "Matrix.hpp"
template<std::size_t N, std::size_t M>
using MatrixNMd = ax::RealMatrix<N, M>;

#include "test_Defs.hpp"
using ax::test::tolerance;
using ax::test::seed;
using ax::test::Dim_N;
using ax::test::Dim_M;

#include <random>

BOOST_AUTO_TEST_CASE(MatrixNd_Ctor)
{
    const MatrixNMd<Dim_N, Dim_M> mat;

    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            BOOST_CHECK_EQUAL(mat(i,j), 0e0);

    const MatrixNMd<Dim_N, Dim_M> mat1(1e0);

    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            if(i == j)
                BOOST_CHECK_EQUAL(mat1(i,j), 1e0);
            else
                BOOST_CHECK_EQUAL(mat1(i,j), 0e0);


    const MatrixNMd<Dim_N, Dim_M> mat2(mat1);

    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            if(i == j)
                BOOST_CHECK_EQUAL(mat2(i,j), 1e0);
            else
                BOOST_CHECK_EQUAL(mat2(i,j), 0e0);

    const MatrixNMd<Dim_N, Dim_M> mat3 = mat1;

    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            if(i == j)
                BOOST_CHECK_EQUAL(mat3(i,j), 1e0);
            else
                BOOST_CHECK_EQUAL(mat3(i,j), 0e0);
}

BOOST_AUTO_TEST_CASE(MatrixNd_Add)
{
    const MatrixNMd<Dim_N, Dim_M> mat1(1e0);
    const MatrixNMd<Dim_N, Dim_M> mat2(2e0);
    const MatrixNMd<Dim_N, Dim_M> mat3(mat1 + mat2);

    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            if(i == j)
                BOOST_CHECK_EQUAL(mat3(i,j), 3e0);
            else
                BOOST_CHECK_EQUAL(mat3(i,j), 0e0);

    const MatrixNMd<Dim_N, Dim_M> mat4 = mat1 + mat2;

    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            if(i == j)
                BOOST_CHECK_EQUAL(mat4(i,j), 3e0);
            else
                BOOST_CHECK_EQUAL(mat4(i,j), 0e0);

    MatrixNMd<Dim_N, Dim_M> mat5;
    mat5 = mat1 + mat2;

    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            if(i == j)
                BOOST_CHECK_EQUAL(mat5(i,j), 3e0);
            else
                BOOST_CHECK_EQUAL(mat5(i,j), 0e0);

    MatrixNMd<Dim_N, Dim_M> mat6;
    mat6 += mat1;
    mat6 += mat2;

    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            if(i == j)
                BOOST_CHECK_EQUAL(mat6(i,j), 3e0);
            else
                BOOST_CHECK_EQUAL(mat6(i,j), 0e0);


    // ~~~~~~~~~~~~~~~~ random ~~~~~~~~~~~~~~~~

    std::mt19937 mt(seed);
    std::uniform_real_distribution<double> randreal(0e0, 1e0);

    std::array<std::array<double, Dim_M>, Dim_N> rand1;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            rand1[i][j] = randreal(mt);

    std::array<std::array<double, Dim_M>, Dim_N> rand2;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            rand2[i][j] = randreal(mt);

    MatrixNMd<Dim_N, Dim_M> mat7;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            mat7(i, j) = rand1[i][j];

    MatrixNMd<Dim_N, Dim_M> mat8;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            mat8(i, j) = rand2[i][j];


    const MatrixNMd<Dim_N, Dim_M> mat9 = mat7 + mat8;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            BOOST_CHECK_EQUAL(mat9(i,j), rand1[i][j] + rand2[i][j]);

    const MatrixNMd<Dim_N, Dim_M> mat10 = mat7 + mat7 + mat7 + mat7 + mat7;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            BOOST_CHECK_CLOSE(mat10(i,j), rand1[i][j] * 5, tolerance);
}

BOOST_AUTO_TEST_CASE(MatrixNd_Sub)
{
    const MatrixNMd<Dim_N, Dim_M> mat1(3e0);
    const MatrixNMd<Dim_N, Dim_M> mat2(1e0);
    const MatrixNMd<Dim_N, Dim_M> mat3(mat1 - mat2);

    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            if(i == j)
                BOOST_CHECK_EQUAL(mat3(i,j), 2e0);
            else
                BOOST_CHECK_EQUAL(mat3(i,j), 0e0);

    const MatrixNMd<Dim_N, Dim_M> mat4 = mat1 - mat2;

    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            if(i == j)
                BOOST_CHECK_EQUAL(mat4(i,j), 2e0);
            else
                BOOST_CHECK_EQUAL(mat4(i,j), 0e0);

    MatrixNMd<Dim_N, Dim_M> mat5;
    mat5 = mat1 - mat2;

    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            if(i == j)
                BOOST_CHECK_EQUAL(mat5(i,j), 2e0);
            else
                BOOST_CHECK_EQUAL(mat5(i,j), 0e0);

    MatrixNMd<Dim_N, Dim_M> mat6(mat1);
    mat6 -= mat2;

    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            if(i == j)
                BOOST_CHECK_EQUAL(mat6(i,j), 2e0);
            else
                BOOST_CHECK_EQUAL(mat6(i,j), 0e0);

    // ~~~~~~~~~~~~~~~~ random ~~~~~~~~~~~~~~~~

    std::mt19937 mt(seed);
    std::uniform_real_distribution<double> randreal(0e0, 1e0);

    std::array<std::array<double, Dim_M>, Dim_N> rand1;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            rand1[i][j] = randreal(mt);

    std::array<std::array<double, Dim_M>, Dim_N> rand2;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            rand2[i][j] = randreal(mt);

    MatrixNMd<Dim_N, Dim_M> mat7;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            mat7(i, j) = rand1[i][j];

    MatrixNMd<Dim_N, Dim_M> mat8;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            mat8(i, j) = rand2[i][j];


    const MatrixNMd<Dim_N, Dim_M> mat9 = mat7 - mat8;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            BOOST_CHECK_EQUAL(mat9(i,j), rand1[i][j] - rand2[i][j]);

    const MatrixNMd<Dim_N, Dim_M> zero;
    const MatrixNMd<Dim_N, Dim_M> mat10 =
        zero - mat7 - mat7 - mat7 - mat7 - mat7;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            BOOST_CHECK_CLOSE(mat10(i,j), rand1[i][j] * (-5e0), tolerance);
}

BOOST_AUTO_TEST_CASE(MatrixNd_Scalar_Maltiple)
{
    std::mt19937 mt(seed);
    std::uniform_real_distribution<double> randreal(0e0, 1e0);

    std::array<std::array<double, Dim_M>, Dim_N> rand1;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            rand1[i][j] = randreal(mt);

    MatrixNMd<Dim_N, Dim_M> mat1;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            mat1(i, j) = rand1[i][j];

    const MatrixNMd<Dim_N, Dim_M> mat2(mat1 * 2e0);
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            BOOST_CHECK_EQUAL(mat2(i,j), rand1[i][j] * 2e0);

    const MatrixNMd<Dim_N, Dim_M> mat3 = mat1 * 2e0;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            BOOST_CHECK_EQUAL(mat3(i,j), rand1[i][j] * 2e0);

    const MatrixNMd<Dim_N, Dim_M> mat4(2e0 * mat1);
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            BOOST_CHECK_EQUAL(mat4(i,j), rand1[i][j] * 2e0);

    const MatrixNMd<Dim_N, Dim_M> mat5 = 2e0 * mat1;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            BOOST_CHECK_EQUAL(mat5(i,j), rand1[i][j] * 2e0);

    MatrixNMd<Dim_N, Dim_M> mat6;
    mat6 = mat1 * 2e0;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            BOOST_CHECK_EQUAL(mat6(i,j), rand1[i][j] * 2e0);

    mat6 = 2e0 * mat1;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            BOOST_CHECK_EQUAL(mat6(i,j), rand1[i][j] * 2e0);

    MatrixNMd<Dim_N, Dim_M> mat7(mat1);
    mat7 *= 2e0;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            BOOST_CHECK_EQUAL(mat7(i,j), rand1[i][j] * 2e0);
}

BOOST_AUTO_TEST_CASE(MatrixNd_Scalar_Division)
{
    std::mt19937 mt(seed);
    std::uniform_real_distribution<double> randreal(0e0, 1e0);

    std::array<std::array<double, Dim_M>, Dim_N> rand1;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            rand1[i][j] = randreal(mt);

    MatrixNMd<Dim_N, Dim_M> mat1;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            mat1(i, j) = rand1[i][j];

    const MatrixNMd<Dim_N, Dim_M> mat2(mat1 / 2e0);
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            BOOST_CHECK_EQUAL(mat2(i,j), rand1[i][j] / 2e0);

    const MatrixNMd<Dim_N, Dim_M> mat3 = mat1 / 2e0;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            BOOST_CHECK_EQUAL(mat3(i,j), rand1[i][j] / 2e0);

    MatrixNMd<Dim_N, Dim_M> mat4;
    mat4 = mat1 / 2e0;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            BOOST_CHECK_EQUAL(mat4(i,j), rand1[i][j] / 2e0);

    MatrixNMd<Dim_N, Dim_M> mat5(mat1);
    mat5 /= 2e0;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            BOOST_CHECK_EQUAL(mat5(i,j), rand1[i][j] / 2e0);
}

BOOST_AUTO_TEST_CASE(MatrixNd_Multiple)
{
    std::mt19937 mt(seed);
    std::uniform_real_distribution<double> randreal(0e0, 1e0);

    std::array<std::array<double, Dim_M>, Dim_N> rand1;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            rand1[i][j] = randreal(mt);

    std::array<std::array<double, Dim_N>, Dim_M> rand2;
    for(std::size_t i=0; i<Dim_M; ++i)
        for(std::size_t j=0; j<Dim_N; ++j)
            rand2[i][j] = randreal(mt);

    MatrixNMd<Dim_N, Dim_M> mat1;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            mat1(i, j) = rand1[i][j];

    MatrixNMd<Dim_M, Dim_N> mat2;
    for(std::size_t i=0; i<Dim_M; ++i)
        for(std::size_t j=0; j<Dim_N; ++j)
            mat2(i, j) = rand2[i][j];

    const MatrixNMd<Dim_N, Dim_N> mat3 = mat1 * mat2;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_N; ++j)
        {
            double value = 0e0;
            for(std::size_t k=0; k<Dim_M; ++k)
                value += rand1[i][k] * rand2[k][j];

            BOOST_CHECK_EQUAL(mat3(i,j), value);
        }

    const MatrixNMd<Dim_M, Dim_M> mat4 = mat2 * mat1;
    for(std::size_t i=0; i<Dim_M; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
        {
            double value = 0e0;
            for(std::size_t k=0; k<Dim_N; ++k)
                value += rand2[i][k] * rand1[k][j];

            BOOST_CHECK_EQUAL(mat4(i,j), value);
        }
}

BOOST_AUTO_TEST_CASE(MatrixNd_transpose)
{
    std::mt19937 mt(seed);
    std::uniform_real_distribution<double> randreal(0e0, 1e0);

    std::array<std::array<double, Dim_M>, Dim_N> rand1;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            rand1[i][j] = randreal(mt);

    MatrixNMd<Dim_N, Dim_M> mat1;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            mat1(i, j) = rand1[i][j];

    const MatrixNMd<Dim_M, Dim_N> mat2 = transpose(mat1);
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            BOOST_CHECK_EQUAL(mat2(j, i), rand1[i][j]);
}
