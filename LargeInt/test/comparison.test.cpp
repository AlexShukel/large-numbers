//
// Created by alexs on 2023-05-14.
//

#include "gtest/gtest.h"
#include "LargeIntImplementation.h"

TEST(large_int, comparison) {
    LargeNumbers::LargeIntImplementation<uint32_t> integer("0");
    EXPECT_EQ(integer.compare(LargeNumbers::LargeIntImplementation<uint32_t>("0")), 0);
    EXPECT_EQ(integer.compare(LargeNumbers::LargeIntImplementation<uint32_t>("-1")), 1);
    EXPECT_EQ(integer.compare(LargeNumbers::LargeIntImplementation<uint32_t>("1")), -1);
    EXPECT_EQ(integer.compare(LargeNumbers::LargeIntImplementation<uint32_t>("256")), -1);
    EXPECT_EQ(integer.compare(LargeNumbers::LargeIntImplementation<uint32_t>("-256")), 1);
}
