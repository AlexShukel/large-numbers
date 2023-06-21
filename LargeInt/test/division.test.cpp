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

// TODO: fix large_int division
TEST(large_int, large_numbers_division) {
    LargeNumbers::LargeIntImplementation<uint8_t> integer("163456132345312");
    integer.divide(LargeNumbers::LargeIntImplementation<uint8_t>("4561321"));
    EXPECT_EQ(integer.toString(), "35835261");

    integer = LargeNumbers::LargeIntImplementation<uint8_t>(
            "100000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    integer.divide(LargeNumbers::LargeIntImplementation<uint8_t>("100000000000"));
    EXPECT_EQ(integer.toString(), "1000000000000000000000000000000000000000000000000000000000000000000000000");
}

TEST(large_int, division_remainder) {
    LargeNumbers::LargeIntImplementation<uint8_t> integer("5");
    EXPECT_EQ(integer.divide(LargeNumbers::LargeIntImplementation<uint8_t>("6")).toString(), "5");
    EXPECT_EQ(integer.toString(), "0");

    integer = LargeNumbers::LargeIntImplementation<uint8_t>("5");
    EXPECT_EQ(integer.divide(LargeNumbers::LargeIntImplementation<uint8_t>("5")).toString(), "0");
    EXPECT_EQ(integer.toString(), "1");

    integer = LargeNumbers::LargeIntImplementation<uint8_t>("11");
    EXPECT_EQ(integer.divide(LargeNumbers::LargeIntImplementation<uint8_t>("3")).toString(), "2");
    EXPECT_EQ(integer.toString(), "3");
}
