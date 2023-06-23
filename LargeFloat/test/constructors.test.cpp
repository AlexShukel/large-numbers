//
// Created by alexs on 2023-06-22.
//

#include "gtest/gtest.h"
#include "LargeFloatImplementation.h"
#include <limits>

TEST(large_float, int_constructor) {
    LargeNumbers::LargeFloatImplementation<uint8_t> n1(0);
    EXPECT_EQ(n1.toString(), "0.0");

    LargeNumbers::LargeFloatImplementation<uint8_t> n2(1);
    EXPECT_EQ(n2.toString(), "1.0");

    LargeNumbers::LargeFloatImplementation<uint8_t> n3(-1);
    EXPECT_EQ(n3.toString(), "-1.0");

    LargeNumbers::LargeFloatImplementation<uint8_t> n4(256);
    EXPECT_EQ(n4.toString(), "256.0");

    LargeNumbers::LargeFloatImplementation<uint8_t> n5(-256);
    EXPECT_EQ(n5.toString(), "-256.0");

    LargeNumbers::LargeFloatImplementation<uint8_t> n6(16777216);
    EXPECT_EQ(n6.toString(), "16777216.0");

    LargeNumbers::LargeFloatImplementation<uint8_t> n7(-16777216);
    EXPECT_EQ(n7.toString(), "-16777216.0");

    LargeNumbers::LargeFloatImplementation<uint8_t> n8(std::numeric_limits<int>::max());
    EXPECT_EQ(n8.toString(), "2147483647.0");

    LargeNumbers::LargeFloatImplementation<uint8_t> n9(7877);
    EXPECT_EQ(n9.toString(), "7877.0");
}

TEST(large_float, double_constructor) {
    double d1 = 0.0;
    LargeNumbers::LargeFloatImplementation<uint8_t> n1(d1);
    EXPECT_EQ(n1.toString(), "0.0");

    double d2 = 1.5;
    LargeNumbers::LargeFloatImplementation<uint8_t> n2(d2);
    EXPECT_EQ(n2.toString(), "1.5");

    double d3 = -1.5;
    LargeNumbers::LargeFloatImplementation<uint8_t> n3(d3);
    EXPECT_EQ(n3.toString(), "-1.5");

    double d4 = 0.1;
    LargeNumbers::LargeFloatImplementation<uint8_t> n4(d4);
    EXPECT_EQ(n4.toString(), "0.1");

    double d5 = 0.111111111111111;
    LargeNumbers::LargeFloatImplementation<uint8_t> n5(d5);
    EXPECT_EQ(n5.toString(), "0.111111111111111");
}
