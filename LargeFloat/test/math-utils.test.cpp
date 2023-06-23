//
// Created by Aleksandras on 2023-06-22.
//

#include "gtest/gtest.h"
#include "LargeFloatImplementation.h"

TEST(large_float, floor) {
    LargeNumbers::LargeFloatImplementation<uint8_t> n("0.0");

    n.floor();
    EXPECT_EQ(n.toString(), "0.0");

    n = LargeNumbers::LargeFloatImplementation<uint8_t>("1.1");
    n.floor();
    EXPECT_EQ(n.toString(), "1.0");

    n = LargeNumbers::LargeFloatImplementation<uint8_t>("-1.1");
    n.floor();
    EXPECT_EQ(n.toString(), "-2.0");

    n = LargeNumbers::LargeFloatImplementation<uint8_t>("256.0");
    n.floor();
    EXPECT_EQ(n.toString(), "256.0");

    n = LargeNumbers::LargeFloatImplementation<uint8_t>("0.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");
    n.floor();
    EXPECT_EQ(n.toString(), "0.0");

    n = LargeNumbers::LargeFloatImplementation<uint8_t>("1.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");
    n.floor();
    EXPECT_EQ(n.toString(), "1.0");
}
