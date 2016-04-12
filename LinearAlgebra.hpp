#ifndef AX_LINEAR_ALGEBRA_H
#define AX_LINEAR_ALGEBRA_H
#include "src/MatrixVectorMultiplication.hpp"
#include "src/InverseMatrix.hpp"
#include "src/LUDecomposition.hpp"
#include "src/JacobiMethod.hpp"
#include "src/io.hpp"

// reuquire Boost.math
#include "src/VectorRotation.hpp"

namespace ax
{
    using Vector3d = RealVector<3>;
    using Matrix3  = RealMatrix<3,3>;
    using Matrix4  = RealMatrix<4,4>;
}


#endif //AX_LINEAR_ALGEBRA_H
