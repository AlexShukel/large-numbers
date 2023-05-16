FILE(GLOB TEST_FILES *.test.cpp)

add_executable(large_float_tests ${TEST_FILES})

target_link_libraries(large_float_tests GTest::gtest_main large_float)
target_include_directories(large_float_tests PUBLIC ../src)

include(GoogleTest)
gtest_discover_tests(large_float_tests)
