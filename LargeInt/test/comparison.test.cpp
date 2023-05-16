//
// Created by alexs on 2023-05-14.
//

#include "gtest/gtest.h"
#include "LargeIntImplementation.h"

TEST(large_int, comparison) {
    LargeNumbers::LargeIntImplementation<uint8_t> integer("0");
    EXPECT_EQ(integer.compare(LargeNumbers::LargeIntImplementation<uint8_t>("0")), 0);
    EXPECT_EQ(integer.compare(LargeNumbers::LargeIntImplementation<uint8_t>("-1")), 1);
    EXPECT_EQ(integer.compare(LargeNumbers::LargeIntImplementation<uint8_t>("1")), -1);
    EXPECT_EQ(integer.compare(LargeNumbers::LargeIntImplementation<uint8_t>("256")), -1);
    EXPECT_EQ(integer.compare(LargeNumbers::LargeIntImplementation<uint8_t>("-256")), 1);
}
