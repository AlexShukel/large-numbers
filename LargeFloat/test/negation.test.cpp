//
// Created by alexs on 2023-06-22.
//

#include "gtest/gtest.h"
#include "LargeFloatImplementation.h"

TEST(large_float, negation_basic) {
    LargeNumbers::LargeFloatImplementation<uint32_t> n1(0);
    n1.negate();
    EXPECT_EQ(n1.toString(), "0.0");

    LargeNumbers::LargeFloatImplementation<uint32_t> n2(1);
    n2.negate();
    EXPECT_EQ(n2.toString(), "-1.0");

    LargeNumbers::LargeFloatImplementation<uint32_t> n3(-1);
    n3.negate();
    EXPECT_EQ(n3.toString(), "1.0");

    LargeNumbers::LargeFloatImplementation<uint32_t> n4(256);
    n4.negate();
    EXPECT_EQ(n4.toString(), "-256.0");

    LargeNumbers::LargeFloatImplementation<uint32_t> n5(-256);
    n5.negate();
    EXPECT_EQ(n5.toString(), "256.0");

    LargeNumbers::LargeFloatImplementation<uint32_t> n6("0.1");
    n6.negate();
    EXPECT_EQ(n6.toString(), "-0.1");
}
