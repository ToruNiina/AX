#ifndef AX_LINEAR_ALGEBRA_H
#define AX_LINEAR_ALGEBRA_H
#include "MatrixVectorMultiplication.hpp"
#include "io.hpp"

// reuquire Boost.math
#include "VectorRotation.hpp"

namespace ax
{
    using Vector3d = RealVector<3>;
    using Matrix3  = RealMatrix<3,3>;
    using Matrix4  = RealMatrix<4,4>;
}

#include "JacobiMethod.hpp"

#endif //AX_LINEAR_ALGEBRA_H
