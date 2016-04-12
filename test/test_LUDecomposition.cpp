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

template<std::size_t N, std::size_t M>
using RealMatrix = ax::RealMatrix<N,M>;

BOOST_AUTO_TEST_CASE(LUDecomposition)
{
    RealMatrix<4,4> mat;

    std::mt19937 mt(seed);
    std::uniform_real_distribution<double> randreal(0e0, 1e0);

    std::array<std::array<double, 4>, 4> rand1;
    for(std::size_t i=0; i<4; ++i)
        for(std::size_t j=0; j<4; ++j)
            mat(i,j) = rand1[i][j] = randreal(mt);

    ax::StaticLUDecomposer<RealMatrix<4,4>> solver(mat);
    solver.solve();

    const RealMatrix<4,4> L = solver.get_L();
    const RealMatrix<4,4> U = solver.get_U();
    const RealMatrix<4,4> A = L * U;

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
