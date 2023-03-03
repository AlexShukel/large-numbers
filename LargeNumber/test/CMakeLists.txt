FILE(GLOB TEST_FILES *.test.cpp)

add_executable(largeNumbersTest ${TEST_FILES})

target_link_libraries(largeNumbersTest GTest::gtest_main largeNumbers)
target_include_directories(largeNumbersTest PUBLIC ../src)

include(GoogleTest)
gtest_discover_tests(largeNumbersTest)
