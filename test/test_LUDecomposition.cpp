#include "LUDecomposition.hpp"
// #include "io.hpp"
using namespace ax;

int main()
{
    RealMatrix<4,4> mat;
    mat(0,0) =  8e0;
    mat(0,1) = 16e0;
    mat(0,2) = 24e0;
    mat(0,3) = 32e0;

    mat(1,0) =  2e0;
    mat(1,1) =  7e0;
    mat(1,2) = 12e0;
    mat(1,3) = 17e0;

    mat(2,0) =  6e0;
    mat(2,1) = 17e0;
    mat(2,2) = 32e0;
    mat(2,3) = 59e0;

    mat(3,0) =  7e0;
    mat(3,1) = 22e0;
    mat(3,2) = 46e0;
    mat(3,3) =105e0;

    StaticLUDecomposer<RealMatrix<4,4>> solver(mat);
    solver.solve();

    const RealMatrix<4,4> L = solver.get_L();
    const RealMatrix<4,4> U = solver.get_U();
    const RealMatrix<4,4> A = L * U;

    for(std::size_t i = 0; i<4; ++i)
        BOOST_CHECK_EQUAL(L(i,i), 1e0);

    for(std::size_t i = 0; i<4; ++i)
        for(std::size_t j = i+1; j<4; ++j)
        {
            BOOST_CHECK_EQUAL(L(i,j), 0e0);
        }

    for(std::size_t i = 0; i<4; ++i)
        for(std::size_t j = 0; j<=i; ++j)
        {
            BOOST_CHECK_EQUAL(U(i,j), 0e0);
        }

//     std::cout << "M: " << std::endl;
//     std::cout << mat << std::endl;
//
//     std::cout << "L: " << std::endl;
//     std::cout << L << std::endl;
//
//     std::cout << "U: " << std::endl;
//     std::cout << U << std::endl;
//
//     std::cout << "A: " << std::endl;
//     std::cout << A << std::endl;

    return 0;
}
