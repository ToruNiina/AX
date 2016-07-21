#define BOOST_TEST_MODULE "test_JacobiMethod"

#ifdef UNITTEST_FRAMEWORK_LIBRARY_EXIST
#include <boost/test/unit_test.hpp>
#else
#define BOOST_TEST_NO_LIB
#include <boost/test/included/unit_test.hpp>
#endif

#include "../src/JacobiMethod.hpp"
#include "../src/InverseMatrix.hpp"
#include "../src/io.hpp"

#include "test_Defs.hpp"
using ax::test::seed;

#include <random>

BOOST_AUTO_TEST_CASE(matrix_2x2)
{
    constexpr std::size_t msize = 2;

    std::mt19937 mt(seed);
    std::uniform_real_distribution<double> randreal(0e0, 1e0);

    ax::Matrix<double, msize,msize> mat;
    double det(0e0);

    while(det == 0e0)
    {
        for(std::size_t i=0; i<msize; ++i)
            for(std::size_t j=i; j<msize; ++j)
                if(i==j)
                    mat(i,j) = randreal(mt);
                else
                    mat(i,j) = mat(j,i) = randreal(mt);
        det = ax::determinant(mat);
   }

    const ax::Matrix<double, msize,msize> values = mat;
    const ax::Matrix<double, msize,msize> E(1e0);

    ax::JacobiMethod<ax::Matrix<double, msize,msize>> jacobi(mat);

    auto eigenpair = jacobi.solve();

    for(std::size_t i=0; i<msize; ++i)
    {
        const double eigenvalue = eigenpair.at(i).first;
        const ax::Vector<double, msize> eigenvector = eigenpair.at(i).second; 

        std::cout << "eval " << eigenvalue << std::endl;
        std::cout << "evec " << eigenvector << std::endl;

        const ax::Vector<double, msize> zeros = (values - eigenvalue * E) * eigenvector; 
        for(std::size_t j=0; j<msize; ++j)
            BOOST_CHECK_SMALL(zeros[j], 1e-7);
    }
}


BOOST_AUTO_TEST_CASE(matrix_3x3)
{
    constexpr std::size_t msize = 3;

    std::mt19937 mt(seed);
    std::uniform_real_distribution<double> randreal(0e0, 1e0);

    ax::Matrix<double, msize,msize> mat;
    double det(0e0);

    while(det == 0e0)
    {
        for(std::size_t i=0; i<msize; ++i)
            for(std::size_t j=i; j<msize; ++j)
                if(i==j)
                    mat(i,j) = randreal(mt);
                else
                    mat(i,j) = mat(j,i) = randreal(mt);
        det = ax::determinant(mat);
    }

    const ax::Matrix<double, msize,msize> values = mat;
    const ax::Matrix<double, msize,msize> E(1e0);

    ax::JacobiMethod<ax::Matrix<double, msize,msize>> jacobi(mat);
    const auto eigenpair = jacobi.solve();

    for(std::size_t i=0; i<msize; ++i)
    {
        const double eigenvalue = eigenpair.at(i).first;
        const ax::Vector<double, msize> eigenvector = eigenpair.at(i).second; 

        std::cout << "eval " << eigenvalue << std::endl;
        std::cout << "evec " << eigenvector << std::endl;

        const ax::Vector<double, msize> zeros = (values - eigenvalue * E) * eigenvector;
        for(std::size_t j=0; j<msize; ++j)
            BOOST_CHECK_SMALL(zeros[j], 1e-7);
    }
}


BOOST_AUTO_TEST_CASE(matrix_4x4)
{
    constexpr std::size_t msize = 4;

    std::mt19937 mt(seed);
    std::uniform_real_distribution<double> randreal(1e0, 2e0);

    ax::Matrix<double, msize,msize> mat;

    for(std::size_t i=0; i<msize; ++i)
        for(std::size_t j=i; j<msize; ++j)
            if(i==j)
                mat(i,j) = randreal(mt);
            else
                mat(i,j) = mat(j,i) = randreal(mt);

    const ax::Matrix<double, msize,msize> values = mat;
    const ax::Matrix<double, msize,msize> E(1e0);

    ax::JacobiMethod<ax::Matrix<double, msize,msize>> jacobi(mat);
    auto eigenpair = jacobi.solve();

    for(std::size_t i=0; i<msize; ++i)
    {
        const double eigenvalue = eigenpair.at(i).first;
        const ax::Vector<double, msize> eigenvector = eigenpair.at(i).second; 

        std::cout << "eval " << eigenvalue << std::endl;
        std::cout << "evec " << eigenvector << std::endl;

        const ax::Vector<double, msize> zeros = (values - eigenvalue * E) * eigenvector; 
        for(std::size_t j=0; j<msize; ++j)
            BOOST_CHECK_SMALL(zeros[j], 1e-7);
    }
}
