#define BOOST_TEST_MODULE "test_3DVector"

#ifdef UNITTEST_FRAMEWORK_LIBRARY_EXIST
#include <boost/test/unit_test.hpp>
#else
#define BOOST_TEST_NO_LIB
#include <boost/test/included/unit_test.hpp>
#endif

#include "Vector3.hpp"
using Vector3d = ax::RealVector<3>;

#include <random>

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

BOOST_AUTO_TEST_CASE(Vector3d_dot_product)
{
    const Vector3d vec1(1e0, 0e0, 0e0);
    const Vector3d vec2(0e0, 1e0, 0e0);

    BOOST_CHECK_EQUAL(dot_prod(vec1, vec2), 0e0);
    BOOST_CHECK_EQUAL(dot_prod(vec2, vec1), 0e0);

    unsigned seed(10);
    std::mt19937 mt(seed);
    std::uniform_real_distribution<double> randreal(0e0, 1e0);

    for(auto i=0; i<100; ++i)
    {
        const double x1 = randreal(mt);
        const double y1 = randreal(mt);
        const double z1 = randreal(mt);

        const double x2 = randreal(mt);
        const double y2 = randreal(mt);
        const double z2 = randreal(mt);
       
        const Vector3d vec3(x1, y1, z1);
        const Vector3d vec4(x2, y2, z2);

        const double dot_product = x1 * x2 + y1 * y2 + z1 * z2;

        BOOST_CHECK_EQUAL(dot_prod(vec3, vec4), dot_product);
    }
}

BOOST_AUTO_TEST_CASE(Vector3d_length)
{
    const Vector3d vec1(1e0, 0e0, 0e0);
    BOOST_CHECK_EQUAL(length(vec1), 1e0);

    unsigned seed(10);
    std::mt19937 mt(seed);
    std::uniform_real_distribution<double> randreal(0e0, 1e0);
    for(auto i=0; i<100; ++i)
    {
        const double x1 = randreal(mt);
        const double y1 = randreal(mt);
        const double z1 = randreal(mt);

        const Vector3d vec3(x1, y1, z1);

        const double lensq_vec3 = x1 * x1 + y1 * y1 + z1 * z1;

        BOOST_CHECK_EQUAL(len_square(vec3), lensq_vec3);
        BOOST_CHECK_EQUAL(length(vec3), std::sqrt(lensq_vec3));

        BOOST_CHECK_EQUAL(len_square(vec3), dot_prod(vec3, vec3));
    }
}

BOOST_AUTO_TEST_CASE(Vector3d_cross_product)
{
    const Vector3d vec1(1e0, 0e0, 0e0);
    const Vector3d vec2(0e0, 1e0, 0e0);
    const Vector3d vec3 = cross_prod(vec1, vec2);

    BOOST_CHECK_EQUAL(vec3[0], 0e0);
    BOOST_CHECK_EQUAL(vec3[1], 0e0);
    BOOST_CHECK_EQUAL(vec3[2], 1e0);

    unsigned seed(10);
    std::mt19937 mt(seed);
    std::uniform_real_distribution<double> randreal(0e0, 1e0);
    for(auto i = 0; i<100; ++i)
    {
        const double x1 = randreal(mt);
        const double y1 = randreal(mt);
        const double z1 = randreal(mt);

        const double x2 = randreal(mt);
        const double y2 = randreal(mt);
        const double z2 = randreal(mt);

        const Vector3d vec4(x1, y1, z1);
        const Vector3d vec5(x2, y2, z2);
        const Vector3d vec6 = cross_prod(vec4, vec5);

        const double cos_theta = dot_prod(vec4, vec5) / length(vec4) / length(vec5);
        const double area = length(vec4) * length(vec5) * sin(acos(cos_theta));

        BOOST_CHECK_SMALL(dot_prod(vec4, vec6), 1e-12);
        BOOST_CHECK_SMALL(dot_prod(vec5, vec6), 1e-12);
        BOOST_CHECK_CLOSE_FRACTION(length(vec6), area, 1e-12);
    }
}
