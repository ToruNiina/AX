set(TEST_NAMES
    test_3Dvector
#     test_static_vector
#     test_dynamic_vector
#     test_static_matrix
#     test_dynamic_matrix
    )

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/test/)

set(test_library_dependencies)
find_library(BOOST_UNITTEST_FRAMEWORK_LIBRARY boost_unit_test_framework)
if (BOOST_UNITTEST_FRAMEWORK_LIBRARY)
    add_definitions(-DBOOST_TEST_DYN_LINK)
    add_definitions(-DUNITTEST_FRAMEWORK_LIBRARY_EXIST)
    set(test_library_dependencies boost_unit_test_framework)
endif()

foreach(TEST_NAME ${TEST_NAMES})
    add_executable(${TEST_NAME} ${TEST_NAME}.cpp)
    target_link_libraries(${TEST_NAME} ${test_library_dependencies})
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach(TEST_NAME)