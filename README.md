AX
====

Library for using Vector and Matrix.

## usage

AX is C++11 header only library.
To use AX, the only thing you have to do is including these files in your codes.

types

    ax::Vector<typename T_element, dimension_type(a.k.a size_t) dimension>;
    ax::Matrix<typename T_element, dimension_type raw, dimension_type column>;

methods

    // Jacobi Method to obtain eigenvalue and eigenvector
    ax::Matrix<double, 4, 4> matrix;
    // do some works
    auto eigenpair = Jacobimethod(matrix);
    double                 eigenvalue  = eigenpair.at(0).first;
    ax::Vector<double, 4>> eigenvector = eigenpair.at(0).second;

    // LU decomposition
    ax::Matrix<double, 4, 4> matrix;
    auto LUpair = LUdecompose(matrix);
    ax::Matrix<double, 4, 4> L = LUpair.first;
    ax::Matrix<double, 4, 4> U = LUpair.second;

sample code:

    ax::Vector<double, 3> vec1(1.0, 2.0, 3.0);
    ax::Vector<double, 3> vec2 = vec1;
    ax::Vector<double, 6> vec3(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    
    auto vec4 = vec1 + vec2; // will be (2.0, 4.0, 6.0)
    // auto vec5 = vec1 + vec3; will cause compilation error
    
    ax::Vector<char, 3> vec_char('a','b','c');// you can do this but not so useful

    ax::Vector<double, ax::DYNAMIC> vec_d(5) // will be 5-dimensitonal vector
    std::cout << vec_d << std::endl; // will be "0 0 0 0 0"
    vec_d.append(2, 1.0);
    std::cout << vec_d << std::endl; // will be "0 0 0 0 0 2 2"

    ax::Matrix<double, 2, 3> matrix; // will be {{0,0,0}, {0,0,0}}
    auto vec_m = matrix * vec1;      // will be {0,0,0}
    // auto vec_m = vec1 * matrix;   // will cause compilation error

## testing

using Boost.Test framework and CTest.

to test AX, run following commands.

    cd build
    cmake ..
    make test

## history

This library is picked out from Coffee-mill.
 The original version of these codes were developed as a part of PDBtool
 repository and then the repository was integrated into Coffee-mill.

## Licensing Terms
This project is licensed under the terms of the MIT License.
See LICENSE for the project license.

- Copyright (c) 2016 Toru Niina

All rights reserved.
