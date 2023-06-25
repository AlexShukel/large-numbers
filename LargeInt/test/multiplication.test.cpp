//
// Created by alexs on 2023-05-14.
//

#include "gtest/gtest.h"
#include "LargeIntImplementation.h"

TEST(large_int, simple_multiplication) {
    LargeNumbers::LargeIntImplementation<uint32_t> integer("0");
    integer.multiply(LargeNumbers::LargeIntImplementation<uint32_t>("0"));
    EXPECT_EQ(integer.toString(), "0");

    integer = LargeNumbers::LargeIntImplementation<uint32_t>("1");
    integer.multiply(LargeNumbers::LargeIntImplementation<uint32_t>("1"));
    EXPECT_EQ(integer.toString(), "1");

    integer.multiply(LargeNumbers::LargeIntImplementation<uint32_t>("-1"));
    EXPECT_EQ(integer.toString(), "-1");

    integer.multiply(LargeNumbers::LargeIntImplementation<uint32_t>("2"));
    EXPECT_EQ(integer.toString(), "-2");

    integer.multiply(LargeNumbers::LargeIntImplementation<uint32_t>("-2"));
    EXPECT_EQ(integer.toString(), "4");
}

TEST(large_int, large_numbers_multiplication) {
    LargeNumbers::LargeIntImplementation<uint32_t> integer("456415131564531");
    integer.multiply(LargeNumbers::LargeIntImplementation<uint32_t>("1531212313456"));
    EXPECT_EQ(integer.toString(), "698868469499250121263629136");

    integer.multiply(LargeNumbers::LargeIntImplementation<uint32_t>("-2"));
    EXPECT_EQ(integer.toString(), "-1397736938998500242527258272");

    integer.multiply(LargeNumbers::LargeIntImplementation<uint32_t>("-1"));
    EXPECT_EQ(integer.toString(), "1397736938998500242527258272");
}

TEST(large_int, base_256_multiplication) {
    LargeNumbers::LargeIntImplementation<uint32_t> integer("2");

    integer.multiply(LargeNumbers::LargeIntImplementation<uint32_t>("-128"));
    EXPECT_EQ(integer.toString(), "-256");

    integer.multiply(LargeNumbers::LargeIntImplementation<uint32_t>("256"));
    EXPECT_EQ(integer.toString(), "-65536");
}
