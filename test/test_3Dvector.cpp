#define BOOST_TEST_MODULE "test_3DVector"

#ifdef UNITTEST_FRAMEWORK_LIBRARY_EXIST
#include <boost/test/unit_test.hpp>
#else
#define BOOST_TEST_NO_LIB
#include <boost/test/included/unit_test.hpp>
#endif

#include "Vector3.hpp"
using Vector3d = ax::RealVector<3>;

BOOST_AUTO_TEST_CASE(Vector3d_Constructable)
{
    const Vector3d vec;

    BOOST_CHECK_EQUAL(vec[0], 0e0);
    BOOST_CHECK_EQUAL(vec[1], 0e0);
    BOOST_CHECK_EQUAL(vec[2], 0e0);

    const Vector3d vec_1(1e0);

    BOOST_CHECK_EQUAL(vec_1[0], 1e0);
    BOOST_CHECK_EQUAL(vec_1[1], 1e0);
    BOOST_CHECK_EQUAL(vec_1[2], 1e0);

    const Vector3d vec_123(1e0, 2e0, 3e0);

    BOOST_CHECK_EQUAL(vec_123[0], 1e0);
    BOOST_CHECK_EQUAL(vec_123[1], 2e0);
    BOOST_CHECK_EQUAL(vec_123[2], 3e0);

    const Vector3d vec_cp_0(vec);

    BOOST_CHECK_EQUAL(vec_cp_0[0], 0e0);
    BOOST_CHECK_EQUAL(vec_cp_0[1], 0e0);
    BOOST_CHECK_EQUAL(vec_cp_0[2], 0e0);

    const Vector3d vec_cp_1 = vec_1;

    BOOST_CHECK_EQUAL(vec_cp_1[0], 1e0);
    BOOST_CHECK_EQUAL(vec_cp_1[1], 1e0);
    BOOST_CHECK_EQUAL(vec_cp_1[2], 1e0);
}

BOOST_AUTO_TEST_CASE(Vector3d_Add)
{
    const Vector3d vec1(1e0, 2e0, 3e0);
    const Vector3d vec2(1e0, 2e0, 3e0);
    const Vector3d vec3(vec1 + vec2);

    BOOST_CHECK_EQUAL(vec3[0], 2e0);
    BOOST_CHECK_EQUAL(vec3[1], 4e0);
    BOOST_CHECK_EQUAL(vec3[2], 6e0);

    Vector3d vec4;
    vec4 = vec1 + vec2;

    BOOST_CHECK_EQUAL(vec4[0], 2e0);
    BOOST_CHECK_EQUAL(vec4[1], 4e0);
    BOOST_CHECK_EQUAL(vec4[2], 6e0);

    Vector3d vec5;
    vec5 += vec1;
    vec5 += vec2;

    BOOST_CHECK_EQUAL(vec5[0], 2e0);
    BOOST_CHECK_EQUAL(vec5[1], 4e0);
    BOOST_CHECK_EQUAL(vec5[2], 6e0);
}

BOOST_AUTO_TEST_CASE(Vector3d_Sub)
{
    const Vector3d vec1(2e0, 3e0, 4e0);
    const Vector3d vec2(1e0, 2e0, 3e0);
    const Vector3d vec3(vec1 - vec2);

    BOOST_CHECK_EQUAL(vec3[0], 1e0);
    BOOST_CHECK_EQUAL(vec3[1], 1e0);
    BOOST_CHECK_EQUAL(vec3[2], 1e0);

    Vector3d vec4;
    vec4 = vec1 - vec2;

    BOOST_CHECK_EQUAL(vec4[0], 1e0);
    BOOST_CHECK_EQUAL(vec4[1], 1e0);
    BOOST_CHECK_EQUAL(vec4[2], 1e0);

    Vector3d vec5(vec1);
    vec5 -= vec2;

    BOOST_CHECK_EQUAL(vec5[0], 1e0);
    BOOST_CHECK_EQUAL(vec5[1], 1e0);
    BOOST_CHECK_EQUAL(vec5[2], 1e0);
}

BOOST_AUTO_TEST_CASE(Vector3d_Scalar_multiple)
{
    const Vector3d vec1(1e0, 2e0, 3e0);
    const Vector3d vec2(2e0 * vec1);

    BOOST_CHECK_EQUAL(vec2[0], 2e0);
    BOOST_CHECK_EQUAL(vec2[1], 4e0);
    BOOST_CHECK_EQUAL(vec2[2], 6e0);

    const Vector3d vec3(vec1 * 2e0);

    BOOST_CHECK_EQUAL(vec3[0], 2e0);
    BOOST_CHECK_EQUAL(vec3[1], 4e0);
    BOOST_CHECK_EQUAL(vec3[2], 6e0);

    Vector3d vec4;
    vec4 = vec1 * 2e0;

    BOOST_CHECK_EQUAL(vec4[0], 2e0);
    BOOST_CHECK_EQUAL(vec4[1], 4e0);
    BOOST_CHECK_EQUAL(vec4[2], 6e0);

    vec4 = 2e0 * vec1;

    BOOST_CHECK_EQUAL(vec4[0], 2e0);
    BOOST_CHECK_EQUAL(vec4[1], 4e0);
    BOOST_CHECK_EQUAL(vec4[2], 6e0);

    Vector3d vec5(vec1);
    vec5 *= 2e0;

    BOOST_CHECK_EQUAL(vec5[0], 2e0);
    BOOST_CHECK_EQUAL(vec5[1], 4e0);
    BOOST_CHECK_EQUAL(vec5[2], 6e0);
}

BOOST_AUTO_TEST_CASE(Vector3d_Scalar_division)
{
    const Vector3d vec1(2e0, 4e0, 6e0);
    const Vector3d vec2(vec1 / 2e0);

    BOOST_CHECK_EQUAL(vec2[0], 1e0);
    BOOST_CHECK_EQUAL(vec2[1], 2e0);
    BOOST_CHECK_EQUAL(vec2[2], 3e0);

    Vector3d vec3;
    vec3 = vec1 / 2e0;

    BOOST_CHECK_EQUAL(vec3[0], 1e0);
    BOOST_CHECK_EQUAL(vec3[1], 2e0);
    BOOST_CHECK_EQUAL(vec3[2], 3e0);

    Vector3d vec4(vec1);
    vec4 /= 2e0;

    BOOST_CHECK_EQUAL(vec4[0], 1e0);
    BOOST_CHECK_EQUAL(vec4[1], 2e0);
    BOOST_CHECK_EQUAL(vec4[2], 3e0);
}


