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

TEST(large_float, mantissa_exponent_constructor) {
    LargeNumbers::LargeFloatImplementation<uint8_t> pi(LargeNumbers::LargeIntImplementation<uint8_t>(
            {141, 72, 86, 253, 82, 1, 121, 177, 12, 57, 203, 15, 222, 146, 191, 13, 183, 170, 153, 141, 112, 153, 104,
             218, 216, 37, 2, 217, 215, 48, 247, 92, 10, 145, 101, 79, 142, 107, 43, 166, 86, 96, 104, 84, 190, 119, 19,
             208, 56, 230, 33, 40, 69, 137, 108, 78, 236, 152, 250, 46, 8, 208, 49, 159, 41, 34, 56, 9, 164, 68, 115,
             112, 3, 46, 138, 25, 19, 211, 8, 163, 133, 136, 106, 63, 36, 3}, false), 0);

    EXPECT_EQ(pi.toString(), "3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117068");
}
