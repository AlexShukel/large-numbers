//
// Created by alexs on 2023-05-16.
//

#include "gtest/gtest.h"
#include "LargeInt.h"

TEST(large_int_api, modulo) {
    LargeNumbers::LargeInt integer("5");
    EXPECT_EQ((integer % LargeNumbers::LargeInt("6")).toString(), "5");
    EXPECT_EQ((integer % LargeNumbers::LargeInt("5")).toString(), "0");
    EXPECT_EQ((integer % LargeNumbers::LargeInt("3")).toString(), "2");
    EXPECT_EQ((integer % LargeNumbers::LargeInt("-3")).toString(), "2");
    EXPECT_EQ((integer % LargeNumbers::LargeInt("2")).toString(), "1");
    EXPECT_EQ((integer % LargeNumbers::LargeInt("-2")).toString(), "1");

    integer = LargeNumbers::LargeInt("-5");
    EXPECT_EQ((integer % LargeNumbers::LargeInt("6")).toString(), "-5");
    EXPECT_EQ((integer % LargeNumbers::LargeInt("-6")).toString(), "-5");
    EXPECT_EQ((integer % LargeNumbers::LargeInt("4")).toString(), "-1");
    EXPECT_EQ((integer % LargeNumbers::LargeInt("-4")).toString(), "-1");
    EXPECT_EQ((integer % LargeNumbers::LargeInt("1")).toString(), "0");
    EXPECT_EQ((integer % LargeNumbers::LargeInt("-1")).toString(), "0");
}
