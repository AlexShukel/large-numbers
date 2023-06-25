//
// Created by alexs on 2023-06-22.
//

#include "gtest/gtest.h"
#include "LargeIntImplementation.h"
#include <limits>

TEST(large_int, int_constructor) {
    LargeNumbers::LargeIntImplementation<uint8_t> n1(0);
    EXPECT_EQ(n1.toString(), "0");

    LargeNumbers::LargeIntImplementation<uint8_t> n2(1);
    EXPECT_EQ(n2.toString(), "1");

    LargeNumbers::LargeIntImplementation<uint8_t> n3(-1);
    EXPECT_EQ(n3.toString(), "-1");

    LargeNumbers::LargeIntImplementation<uint8_t> n4(256);
    EXPECT_EQ(n4.toString(), "256");

    LargeNumbers::LargeIntImplementation<uint8_t> n5(-256);
    EXPECT_EQ(n5.toString(), "-256");

    LargeNumbers::LargeIntImplementation<uint8_t> n6(16777216);
    EXPECT_EQ(n6.toString(), "16777216");

    LargeNumbers::LargeIntImplementation<uint8_t> n7(-16777216);
    EXPECT_EQ(n7.toString(), "-16777216");

    LargeNumbers::LargeIntImplementation<uint8_t> n8(std::numeric_limits<int>::max());
    EXPECT_EQ(n8.toString(), "2147483647");

    LargeNumbers::LargeIntImplementation<uint8_t> n9(7877);
    EXPECT_EQ(n9.toString(), "7877");

    LargeNumbers::LargeIntImplementation<uint8_t> n10(2);
    EXPECT_EQ(n10.toString(), "2");
}

TEST(large_int, int_constructor_32_t) {
    LargeNumbers::LargeIntImplementation<uint32_t> n1(0);
    EXPECT_EQ(n1.toString(), "0");

    LargeNumbers::LargeIntImplementation<uint32_t> n2(1);
    EXPECT_EQ(n2.toString(), "1");

    LargeNumbers::LargeIntImplementation<uint32_t> n3(-1);
    EXPECT_EQ(n3.toString(), "-1");

    LargeNumbers::LargeIntImplementation<uint32_t> n4(256);
    EXPECT_EQ(n4.toString(), "256");

    LargeNumbers::LargeIntImplementation<uint32_t> n5(-256);
    EXPECT_EQ(n5.toString(), "-256");

    LargeNumbers::LargeIntImplementation<uint32_t> n6(16777216);
    EXPECT_EQ(n6.toString(), "16777216");

    LargeNumbers::LargeIntImplementation<uint32_t> n7(-16777216);
    EXPECT_EQ(n7.toString(), "-16777216");

    LargeNumbers::LargeIntImplementation<uint32_t> n8(std::numeric_limits<int>::max());
    EXPECT_EQ(n8.toString(), "2147483647");

    LargeNumbers::LargeIntImplementation<uint32_t> n9(7877);
    EXPECT_EQ(n9.toString(), "7877");

    LargeNumbers::LargeIntImplementation<uint32_t> n10(2);
    EXPECT_EQ(n10.toString(), "2");
}
