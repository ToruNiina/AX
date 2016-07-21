#define BOOST_TEST_MODULE "test_small_inverse_matrix"

#ifdef UNITTEST_FRAMEWORK_LIBRARY_EXIST
#include <boost/test/unit_test.hpp>
#else
#define BOOST_TEST_NO_LIB
#include <boost/test/included/unit_test.hpp>
#endif

#include "../src/InverseMatrix.hpp"

#include "test_Defs.hpp"
using ax::test::tolerance;
using ax::test::seed;

#include <random>


BOOST_AUTO_TEST_CASE(matrix_2x2)
{
    constexpr std::size_t msize = 2;

    std::mt19937 mt(seed);
    std::uniform_real_distribution<double> randreal(0e0, 1e0);

    ax::Matrix<double, msize,msize> mat;
    double det = 0e0;

    while(det == 0e0)
    {
        std::array<std::array<double, msize>, msize> rand1;
        for(std::size_t i=0; i<msize; ++i)
            for(std::size_t j=0; j<msize; ++j)
                mat(i,j) = rand1[i][j] = randreal(mt);

        det = ax::determinant(mat);
    }

    const ax::Matrix<double, msize,msize> inv = inverse(mat);
    const ax::Matrix<double, msize,msize> E   = inv * mat;

    for(std::size_t i=0; i<msize; ++i)
        for(std::size_t j=0; j<msize; ++j)
            if(i==j)
                BOOST_CHECK_CLOSE(E(i,j), 1e0, tolerance);
            else
                BOOST_CHECK_SMALL(E(i,j), tolerance);
}

BOOST_AUTO_TEST_CASE(matrix_3x3)
{
    constexpr std::size_t msize = 3;

    std::mt19937 mt(seed);
    std::uniform_real_distribution<double> randreal(0e0, 1e0);

    ax::Matrix<double, msize,msize> mat;
    double det = 0e0;

    while(det == 0e0)
    {
        std::array<std::array<double, msize>, msize> rand1;
        for(std::size_t i=0; i<msize; ++i)
            for(std::size_t j=0; j<msize; ++j)
                mat(i,j) = rand1[i][j] = randreal(mt);

        det = ax::determinant(mat);
    }

    const ax::Matrix<double, msize,msize> inv = inverse(mat);
    const ax::Matrix<double, msize,msize> E   = inv * mat;

    for(std::size_t i=0; i<msize; ++i)
        for(std::size_t j=0; j<msize; ++j)
            if(i==j)
                BOOST_CHECK_CLOSE(E(i,j), 1e0, tolerance);
            else
                BOOST_CHECK_SMALL(E(i,j), tolerance);
}
