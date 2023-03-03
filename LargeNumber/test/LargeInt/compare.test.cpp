#include <gtest/gtest.h>
#include "LargeInt/LargeInt.h"

typedef uint8_t byte;

TEST(LargeInt, compareIsEqual) {
    LargeInt<byte> a("1");
    EXPECT_EQ(a == LargeInt<byte>("0"), false);
    EXPECT_EQ(a == LargeInt<byte>("1"), true);
}

TEST(LargeInt, compareIsNotEqual) {
    LargeInt<byte> a("1");
    EXPECT_EQ(a != LargeInt<byte>("0"), true);
    EXPECT_EQ(a != LargeInt<byte>("1"), false);
}

TEST(LargeInt, compareIsGreater) {
    LargeInt<byte> a("1");
    EXPECT_EQ(a > LargeInt<byte>("0"), true);
    EXPECT_EQ(a > LargeInt<byte>("1"), false);
}

TEST(LargeInt, compareIsLower) {
    LargeInt<byte> a("1");
    EXPECT_EQ(a < LargeInt<byte>("2"), true);
    EXPECT_EQ(a < LargeInt<byte>("1"), false);
}

TEST(LargeInt, compareIsGreaterOrEqual) {
    LargeInt<byte> a("1");
    EXPECT_EQ(a >= LargeInt<byte>("0"), true);
    EXPECT_EQ(a >= LargeInt<byte>("1"), true);
    EXPECT_EQ(a >= LargeInt<byte>("2"), false);
}

TEST(LargeInt, compareIsLowerOrEqual) {
    LargeInt<byte> a("1");
    EXPECT_EQ(a <= LargeInt<byte>("0"), false);
    EXPECT_EQ(a <= LargeInt<byte>("1"), true);
    EXPECT_EQ(a <= LargeInt<byte>("2"), true);
}
