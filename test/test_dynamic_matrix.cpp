#define BOOST_TEST_MODULE "test_dynamic_matrix"

#ifdef UNITTEST_FRAMEWORK_LIBRARY_EXIST
#include <boost/test/unit_test.hpp>
#else
#define BOOST_TEST_NO_LIB
#include <boost/test/included/unit_test.hpp>
#endif

#include "../src/DynamicMatrix.hpp"
using MatrixNMd = ax::RealDynamicMatrix;

#include "test_Defs.hpp"
using ax::test::tolerance;
using ax::test::seed;
using ax::test::Dim_N;
using ax::test::Dim_M;

#include <random>

BOOST_AUTO_TEST_CASE(DynamicMatrix_Ctor)
{
    const MatrixNMd mat(Dim_N, Dim_M);

    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            BOOST_CHECK_EQUAL(mat.at(i,j), 0e0);

    MatrixNMd mat1(Dim_N, Dim_M);

    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            if(i == j)
                mat1.at(i,j) = 1e0;
            else
                mat1.at(i,j) = 0e0;

    const MatrixNMd mat2(mat1);

    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            if(i == j)
                BOOST_CHECK_EQUAL(mat2.at(i,j), 1e0);
            else
                BOOST_CHECK_EQUAL(mat2.at(i,j), 0e0);

    const MatrixNMd mat3 = mat1;

    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            if(i == j)
                BOOST_CHECK_EQUAL(mat3.at(i,j), 1e0);
            else
                BOOST_CHECK_EQUAL(mat3.at(i,j), 0e0);
}

BOOST_AUTO_TEST_CASE(DynamicMatrix_Add)
{
    std::mt19937 mt(seed);
    std::uniform_real_distribution<double> randreal(0e0, 1e0);

    std::vector<std::vector<double>> rand1(Dim_N, std::vector<double>(Dim_M));
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            rand1.at(i).at(j) = randreal(mt);

    std::vector<std::vector<double>> rand2(Dim_N, std::vector<double>(Dim_M));
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            rand2.at(i).at(j) = randreal(mt);

    const MatrixNMd mat1(rand1);
    const MatrixNMd mat2(rand2);

    const MatrixNMd mat3(mat1 + mat2);
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            BOOST_CHECK_EQUAL(mat3.at(i,j), rand1.at(i).at(j) + rand2.at(i).at(j));

    const MatrixNMd mat4 = mat1 + mat2;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            BOOST_CHECK_EQUAL(mat4.at(i,j), rand1.at(i).at(j) + rand2.at(i).at(j));

    const MatrixNMd mat5 = mat1 + mat1 + mat1 + mat1 + mat1;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            BOOST_CHECK_CLOSE(mat5.at(i,j), rand1.at(i).at(j) * 5, tolerance);
}

BOOST_AUTO_TEST_CASE(DynamicMatrix_Sub)
{
    std::mt19937 mt(seed);
    std::uniform_real_distribution<double> randreal(0e0, 1e0);

    std::vector<std::vector<double>> rand1(Dim_N, std::vector<double>(Dim_M));
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            rand1.at(i).at(j) = randreal(mt);

    std::vector<std::vector<double>> rand2(Dim_N, std::vector<double>(Dim_M));
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            rand2.at(i).at(j) = randreal(mt);

    const MatrixNMd mat1(rand1);
    const MatrixNMd mat2(rand2);

    const MatrixNMd mat3 = mat1 - mat2;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            BOOST_CHECK_EQUAL(mat3.at(i,j), rand1.at(i).at(j) - rand2.at(i).at(j));

    const MatrixNMd mat4(mat1 - mat2);
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            BOOST_CHECK_EQUAL(mat4.at(i,j), rand1.at(i).at(j) - rand2.at(i).at(j));


    const MatrixNMd zero(Dim_N, Dim_M);
    const MatrixNMd mat5 =
        zero - mat1 - mat1 - mat1 - mat1 - mat1;

    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            BOOST_CHECK_CLOSE(mat5.at(i,j), rand1.at(i).at(j) * (-5e0), tolerance);
}

BOOST_AUTO_TEST_CASE(DynamicMatrix_Scalar_Multiple)
{
    std::mt19937 mt(seed);
    std::uniform_real_distribution<double> randreal(0e0, 1e0);

    std::vector<std::vector<double>> rand1(Dim_N, std::vector<double>(Dim_M));
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            rand1.at(i).at(j) = randreal(mt);

    MatrixNMd mat1(rand1);

    const MatrixNMd mat2(mat1 * 2e0);
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            BOOST_CHECK_EQUAL(mat2.at(i,j), rand1.at(i).at(j) * 2e0);

    const MatrixNMd mat3 = mat1 * 2e0;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            BOOST_CHECK_EQUAL(mat3.at(i,j), rand1.at(i).at(j) * 2e0);

    const MatrixNMd mat4(2e0 * mat1);
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            BOOST_CHECK_EQUAL(mat4.at(i,j), rand1.at(i).at(j) * 2e0);

    const MatrixNMd mat5 = 2e0 * mat1;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            BOOST_CHECK_EQUAL(mat5.at(i,j), rand1.at(i).at(j) * 2e0);

    MatrixNMd mat6(Dim_N, Dim_M);
    mat6 = mat1 * 2e0;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            BOOST_CHECK_EQUAL(mat6.at(i,j), rand1.at(i).at(j) * 2e0);

    mat6 = 2e0 * mat1;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            BOOST_CHECK_EQUAL(mat6.at(i,j), rand1.at(i).at(j) * 2e0);
}

BOOST_AUTO_TEST_CASE(MatrixNd_Scalar_Division)
{
    std::mt19937 mt(seed);
    std::uniform_real_distribution<double> randreal(0e0, 1e0);

    std::vector<std::vector<double>> rand1(Dim_N, std::vector<double>(Dim_M));
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            rand1.at(i).at(j) = randreal(mt);

    const MatrixNMd mat1(rand1);

    const MatrixNMd mat2(mat1 / 2e0);
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            BOOST_CHECK_EQUAL(mat2.at(i,j), rand1.at(i).at(j) / 2e0);

    const MatrixNMd mat3 = mat1 / 2e0;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            BOOST_CHECK_EQUAL(mat3.at(i,j), rand1.at(i).at(j) / 2e0);

    MatrixNMd mat6(Dim_N, Dim_M);
    mat6 = mat1 / 2e0;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            BOOST_CHECK_EQUAL(mat6.at(i,j), rand1.at(i).at(j) / 2e0);
}

BOOST_AUTO_TEST_CASE(MatrixNd_Multiple)
{
    std::mt19937 mt(seed);
    std::uniform_real_distribution<double> randreal(0e0, 1e0);

    std::vector<std::vector<double>> rand1(Dim_N, std::vector<double>(Dim_M));
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            rand1.at(i).at(j) = randreal(mt);

    std::vector<std::vector<double>> rand2(Dim_M, std::vector<double>(Dim_N));
    for(std::size_t i=0; i<Dim_M; ++i)
        for(std::size_t j=0; j<Dim_N; ++j)
            rand2.at(i).at(j) = randreal(mt);

    const MatrixNMd mat1(rand1);
    const MatrixNMd mat2(rand2);

    const MatrixNMd mat3 = mat1 * mat2;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_N; ++j)
        {
            double value = 0e0;
            for(std::size_t k=0; k<Dim_M; ++k)
                value += rand1.at(i).at(k) * rand2.at(k).at(j);

            BOOST_CHECK_EQUAL(mat3.at(i,j), value);
        }

    const MatrixNMd mat4 = mat2 * mat1;
    for(std::size_t i=0; i<Dim_M; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
        {
            double value = 0e0;
            for(std::size_t k=0; k<Dim_N; ++k)
                value += rand2.at(i).at(k) * rand1.at(k).at(j);

            BOOST_CHECK_EQUAL(mat4.at(i,j), value);
        }
}

BOOST_AUTO_TEST_CASE(MatrixNd_transpose)
{
    std::mt19937 mt(seed);
    std::uniform_real_distribution<double> randreal(0e0, 1e0);

    std::vector<std::vector<double>> rand1(Dim_N, std::vector<double>(Dim_M));
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            rand1[i][j] = randreal(mt);

    const MatrixNMd mat1(rand1);

    const MatrixNMd mat2 = transpose(mat1);
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=0; j<Dim_M; ++j)
            BOOST_CHECK_EQUAL(mat2.at(j, i), rand1.at(i).at(j));

    const MatrixNMd mat3 = transpose(mat1) * mat1;
    for(std::size_t i=0; i<Dim_N; ++i)
        for(std::size_t j=i+1; j<Dim_N; ++j)
            BOOST_CHECK_EQUAL(mat3.at(j, i), mat3.at(i, j));
}
