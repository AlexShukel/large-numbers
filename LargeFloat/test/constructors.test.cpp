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
