//
// Created by alexs on 2023-05-14.
//

#include "gtest/gtest.h"
#include "LargeIntImplementation.h"

TEST(large_int, simple_addition) {
    LargeNumbers::LargeIntImplementation<uint8_t> integer("0");
    EXPECT_EQ(integer.toString(), "0");
    integer.add(LargeNumbers::LargeIntImplementation<uint8_t>("0"));
    EXPECT_EQ(integer.toString(), "0");

    integer.add(LargeNumbers::LargeIntImplementation<uint8_t>("1"));
    EXPECT_EQ(integer.toString(), "1");
    integer.add(LargeNumbers::LargeIntImplementation<uint8_t>("-1"));
    EXPECT_EQ(integer.toString(), "0");
    integer.add(LargeNumbers::LargeIntImplementation<uint8_t>("-1"));
    EXPECT_EQ(integer.toString(), "-1");

    integer.add(LargeNumbers::LargeIntImplementation<uint8_t>("3"));
    EXPECT_EQ(integer.toString(), "2");

    integer.add(LargeNumbers::LargeIntImplementation<uint8_t>("254"));
    EXPECT_EQ(integer.toString(), "256");

    integer.add(LargeNumbers::LargeIntImplementation<uint8_t>("-16"));
    EXPECT_EQ(integer.toString(), "240");
}

TEST(large_int, large_numbers_addition) {
    LargeNumbers::LargeIntImplementation<uint8_t> integer("18446744073709551615");
    integer.add(LargeNumbers::LargeIntImplementation<uint8_t>("5412332563215361225241123"));
    EXPECT_EQ(integer.toString(), "5412351009959434934792738");
    integer.add(LargeNumbers::LargeIntImplementation<uint8_t>("-5412351009959434934792739"));
    EXPECT_EQ(integer.toString(), "-1");
    integer.add(LargeNumbers::LargeIntImplementation<uint8_t>("-564589415613548547687945261"));
    EXPECT_EQ(integer.toString(), "-564589415613548547687945262");
}
