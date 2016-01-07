AX
====

Library for using Vector and Matrix.

This library is picked out from Coffee-mill.
 The original version of these codes were developed as a part of PDBtool
 repository and then the repository was integrated into Coffee-mill.

This uses Expression Template technique.

This requires c++11.

This library is headder only. To use this, the only thing you have to do is
 include "LinearAlgebra.hpp".

In VectorRotation, ax uses Boost::math::quaternion. If you don't have boost
 library or don't need to use Rotation method, you can comment out the line
 includes "VectorRotation.hpp" in file "LinearAlgebra.hpp".
