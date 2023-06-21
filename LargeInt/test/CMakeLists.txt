FILE(GLOB TEST_FILES *.test.cpp)

add_executable(large_int_tests ${TEST_FILES})

target_link_libraries(large_int_tests GTest::gtest_main large_int)
target_include_directories(large_int_tests PUBLIC "../src" "${CMAKE_SOURCE_DIR}/test-utils")

include(GoogleTest)
gtest_discover_tests(large_int_tests)
