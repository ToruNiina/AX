#ifndef AX_TEST_DEFINITIONS
#define AX_TEST_DEFINITIONS
#include <cstddef>

namespace ax
{
    namespace test
    {
        constexpr static double      tolerance = 1e-12;
        constexpr static unsigned    seed      = 10;
        constexpr static std::size_t Dim_N     = 10;
        constexpr static std::size_t Dim_M     = 12;
    }
}

#endif /* AX_TEST_DEFINITIONS */
