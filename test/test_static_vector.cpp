#define BOOST_TEST_MODULE "test_static_vector"

#ifdef UNITTEST_FRAMEWORK_LIBRARY_EXIST
#include <boost/test/unit_test.hpp>
#else
#define BOOST_TEST_NO_LIB
#include <boost/test/included/unit_test.hpp>
#endif

#include "Vector3.hpp"
template<std::size_t N>
using VectorNd = ax::RealVector<N>;

#include "test_Defs.hpp"
using ax::test::seed;

#include <random>

BOOST_AUTO_TEST_CASE(VectorNd_Constructable)
{
    const VectorNd<10> vec;

    for(std::size_t i=0; i<10; ++i)
        BOOST_CHECK_EQUAL(vec[i], 0e0);

    const VectorNd<10> vec_1(1e0);

    for(std::size_t i=0; i<10; ++i)
        BOOST_CHECK_EQUAL(vec_1[i], 1e0);

    const VectorNd<10> vec_cp_0(vec_1);

    for(std::size_t i=0; i<10; ++i)
        BOOST_CHECK_EQUAL(vec_cp_0[i], 1e0);

    const VectorNd<10> vec_cp_1 = vec_1;

    for(std::size_t i=0; i<10; ++i)
        BOOST_CHECK_EQUAL(vec_cp_1[i], 1e0);
}

BOOST_AUTO_TEST_CASE(VectorNd_Add)
{
    const VectorNd<10> vec1(1e0);
    const VectorNd<10> vec2(2e0);
    const VectorNd<10> vec3(vec1 + vec2);

    for(std::size_t i=0; i<10; ++i)
        BOOST_CHECK_EQUAL(vec3[i], 3e0);

    VectorNd<10> vec4;
    vec4 = vec1 + vec2;

    for(std::size_t i=0; i<10; ++i)
        BOOST_CHECK_EQUAL(vec4[i], 3e0);

    VectorNd<10> vec5;
    vec5 += vec1;
    vec5 += vec2;

    for(std::size_t i=0; i<10; ++i)
        BOOST_CHECK_EQUAL(vec5[i], 3e0);
}

BOOST_AUTO_TEST_CASE(VectorNd_Sub)
{
    const VectorNd<10> vec1(3e0);
    const VectorNd<10> vec2(2e0);
    const VectorNd<10> vec3(vec1 - vec2);

    for(std::size_t i=0; i<10; ++i)
        BOOST_CHECK_EQUAL(vec3[i], 1e0);

    VectorNd<10> vec4;
    vec4 = vec1 - vec2;

    for(std::size_t i=0; i<10; ++i)
        BOOST_CHECK_EQUAL(vec4[i], 1e0);

    VectorNd<10> vec5(vec1);
    vec5 -= vec2;

    for(std::size_t i=0; i<10; ++i)
        BOOST_CHECK_EQUAL(vec5[i], 1e0);
}

BOOST_AUTO_TEST_CASE(VectorNd_Scalar_multiple)
{
    const VectorNd<10> vec1(1e0);
    const VectorNd<10> vec2(2e0 * vec1);

    for(std::size_t i=0; i<10; ++i)
        BOOST_CHECK_EQUAL(vec2[i], 2e0);

    const VectorNd<10> vec3(vec1 * 2e0);

    for(std::size_t i=0; i<10; ++i)
        BOOST_CHECK_EQUAL(vec3[i], 2e0);

    VectorNd<10> vec4;
    vec4 = vec1 * 2e0;

    for(std::size_t i=0; i<10; ++i)
        BOOST_CHECK_EQUAL(vec4[i], 2e0);

    vec4 = 2e0 * vec1;

    for(std::size_t i=0; i<10; ++i)
        BOOST_CHECK_EQUAL(vec4[i], 2e0);

    VectorNd<10> vec5(vec1);
    vec5 *= 2e0;

    for(std::size_t i=0; i<10; ++i)
        BOOST_CHECK_EQUAL(vec5[i], 2e0);
}

BOOST_AUTO_TEST_CASE(VectorNd_Scalar_division)
{
    const VectorNd<10> vec1(2e0);
    const VectorNd<10> vec2(vec1 / 2e0);

    for(std::size_t i=0; i<10; ++i)
        BOOST_CHECK_EQUAL(vec2[i], 1e0);

    VectorNd<10> vec3;
    vec3 = vec1 / 2e0;

    for(std::size_t i=0; i<10; ++i)
        BOOST_CHECK_EQUAL(vec3[i], 1e0);

    VectorNd<10> vec4(vec1);
    vec4 /= 2e0;

    for(std::size_t i=0; i<10; ++i)
        BOOST_CHECK_EQUAL(vec4[i], 1e0);
}

BOOST_AUTO_TEST_CASE(VectorNd_dot_product)
{
    std::mt19937 mt(seed);
    std::uniform_real_distribution<double> randreal(0e0, 1e0);

    for(auto i=0; i<100; ++i)
    {
        std::array<double, 10> v1;
        for(std::size_t i=0; i<10; ++i)
            v1.at(i) = randreal(mt);

        std::array<double, 10> v2;
        for(std::size_t i=0; i<10; ++i)
            v2.at(i) = randreal(mt);

        const VectorNd<10> vec1(v1);
        const VectorNd<10> vec2(v2);

        double dot_product = 0e0;
        for(std::size_t i=0; i<10; ++i)
            dot_product += v1.at(i) * v2.at(i);

        BOOST_CHECK_EQUAL(dot_prod(vec1, vec2), dot_product);
    }
}

BOOST_AUTO_TEST_CASE(VectorNd_length)
{
    std::mt19937 mt(seed);
    std::uniform_real_distribution<double> randreal(0e0, 1e0);

    for(auto i=0; i<100; ++i)
    {
        std::array<double, 10> v1;
        for(std::size_t i=0; i<10; ++i)
            v1.at(i) = randreal(mt);

        const VectorNd<10> vec1(v1);

        double lensq = 0e0;
        for(std::size_t i=0; i<10; ++i)
            lensq += v1.at(i) * v1.at(i);

        BOOST_CHECK_EQUAL(len_square(vec1), lensq);
        BOOST_CHECK_EQUAL(length(vec1), std::sqrt(lensq));

        BOOST_CHECK_EQUAL(len_square(vec1), dot_prod(vec1, vec1));
    }
}
