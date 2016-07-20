#define BOOST_TEST_MODULE "test_type_traits"

#ifdef UNITTEST_FRAMEWORK_LIBRARY_EXIST
#include <boost/test/unit_test.hpp>
#else
#define BOOST_TEST_NO_LIB
#include <boost/test/included/unit_test.hpp>
#endif

#include "../src/TypeTraits.hpp"

BOOST_AUTO_TEST_CASE(test_is_all)
{
    const bool is_all = ax::is_all<double, double, double, double>::value;
    BOOST_CHECK(is_all);
    const bool is_not_all = ax::is_all<double, double, int, double>::value;
    BOOST_CHECK(!is_not_all);
}
