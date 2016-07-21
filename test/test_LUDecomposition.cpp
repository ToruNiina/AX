#define BOOST_TEST_MODULE "test_LUDecomposition"

#ifdef UNITTEST_FRAMEWORK_LIBRARY_EXIST
#include <boost/test/unit_test.hpp>
#else
#define BOOST_TEST_NO_LIB
#include <boost/test/included/unit_test.hpp>
#endif

#include "test_Defs.hpp"
using ax::test::tolerance;
using ax::test::seed;

#include <random>

#include "../src/LUDecomposition.hpp"

BOOST_AUTO_TEST_CASE(LUDecomposition)
{
    ax::Matrix<double, 4,4> mat;

    std::mt19937 mt(seed);
    std::uniform_real_distribution<double> randreal(0e0, 1e0);

    std::array<std::array<double, 4>, 4> rand1;
    for(std::size_t i=0; i<4; ++i)
        for(std::size_t j=0; j<4; ++j)
            mat(i,j) = rand1[i][j] = randreal(mt);

    const auto LUpair = ax::LUdecompose<ax::Doolittle>(mat);

    const ax::Matrix<double, 4,4> L = LUpair.first;
    const ax::Matrix<double, 4,4> U = LUpair.second;
    const ax::Matrix<double, 4,4> A = L * U;

    // ============= test for L ============= 
    for(std::size_t i = 0; i<4; ++i)
        BOOST_CHECK_EQUAL(L(i,i), 1e0);

    for(std::size_t i = 0; i<4; ++i)
        for(std::size_t j = i+1; j<4; ++j)
        {
            BOOST_CHECK_EQUAL(L(i,j), 0e0);
        }

    // ============= test for U ============= 
    for(std::size_t i = 0; i<4; ++i)
        for(std::size_t j = 0; j<i; ++j)
        {
            BOOST_CHECK_EQUAL(U(i,j), 0e0);
        }

    for(std::size_t i=0; i<4; ++i)
        for(std::size_t j=0; j<4; ++j)
            BOOST_CHECK_CLOSE(A(i,j), mat(i,j), tolerance);
}
