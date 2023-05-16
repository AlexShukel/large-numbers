//
// Created by alexs on 2023-05-14.
//

#include "gtest/gtest.h"
#include "LargeIntImplementation.h"

TEST(large_int, simple_division) {
    LargeNumbers::LargeIntImplementation<uint8_t> integer("0");
    integer.divide(LargeNumbers::LargeIntImplementation<uint8_t>("1"));
    integer.divide(LargeNumbers::LargeIntImplementation<uint8_t>("-256"));
    EXPECT_EQ(integer.toString(), "0");

    integer = LargeNumbers::LargeIntImplementation<uint8_t>("1");
    integer.divide(LargeNumbers::LargeIntImplementation<uint8_t>("1"));
    EXPECT_EQ(integer.toString(), "1");
    integer.divide(LargeNumbers::LargeIntImplementation<uint8_t>("2"));
    EXPECT_EQ(integer.toString(), "0");

    integer = LargeNumbers::LargeIntImplementation<uint8_t>("24");
    integer.divide(LargeNumbers::LargeIntImplementation<uint8_t>("4"));
    EXPECT_EQ(integer.toString(), "6");
    integer.divide(LargeNumbers::LargeIntImplementation<uint8_t>("-6"));
    EXPECT_EQ(integer.toString(), "-1");
    integer.divide(LargeNumbers::LargeIntImplementation<uint8_t>("-1000"));
    EXPECT_EQ(integer.toString(), "0");
}

TEST(large_int, large_numbers_division) {
    LargeNumbers::LargeIntImplementation<uint8_t> integer("163456132345312");
    integer.divide(LargeNumbers::LargeIntImplementation<uint8_t>("4561321"));
    EXPECT_EQ(integer.toString(), "35835261");
}
