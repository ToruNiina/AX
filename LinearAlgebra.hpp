#ifndef AX_LINEAR_ALGEBRA_H
#define AX_LINEAR_ALGEBRA_H
#include "src/Vector.hpp"
#include "src/DynamicVector.hpp"
#include "src/Matrix.hpp"
#include "src/io.hpp"

// reuquire Boost.math
#include "src/VectorRotation.hpp"

namespace ax
{
    using Vector3d = Vector<double, 3>;
    using Matrix3d = Matrix<double, 3,3>;
    using Matrix4d = Matrix<double, 4,4>;
}


#endif //AX_LINEAR_ALGEBRA_H
