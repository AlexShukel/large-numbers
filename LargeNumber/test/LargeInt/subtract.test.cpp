#include <gtest/gtest.h>
#include "LargeInt/LargeInt.h"

typedef uint8_t byte;

TEST(LargeInt, subtract) {
    LargeInt<byte> a("1");
    LargeInt<byte> b("1");
    LargeInt<byte> sum = a - b;
    EXPECT_EQ(sum.toString(), "0");

    sum = LargeInt<byte>("0") - LargeInt<byte>("0");
    EXPECT_EQ(sum.toString(), "0");

    sum = LargeInt<byte>("13") - LargeInt<byte>("-5");
    EXPECT_EQ(sum.toString(), "18");

    sum = LargeInt<byte>("4") - LargeInt<byte>("13");
    EXPECT_EQ(sum.toString(), "-9");

    sum = LargeInt<byte>("-4") - LargeInt<byte>("3");
    EXPECT_EQ(sum.toString(), "-7");
}

TEST(LargeInt, subtractAssignment) {
    LargeInt<byte> a("1");
    a -= LargeInt<byte>("1");
    EXPECT_EQ(a.toString(), "0");

    a -= LargeInt<byte>("2");
    EXPECT_EQ(a.toString(), "-2");

    a -= LargeInt<byte>("-13");
    EXPECT_EQ(a.toString(), "11");
}

TEST(LargeInt, preDecrement) {
    LargeInt<byte> a("0");
    EXPECT_EQ((--a).toString(), "-1");

    LargeInt<byte> b("-1");
    EXPECT_EQ((--b).toString(), "-2");
}

TEST(LargeInt, postDecrement) {
    LargeInt<byte> a("0");
    EXPECT_EQ((a--).toString(), "0");
    EXPECT_EQ(a.toString(), "-1");

    LargeInt<byte> b("-1");
    EXPECT_EQ((b--).toString(), "-1");
    EXPECT_EQ(b.toString(), "-2");
}

TEST(LargeInt, unaryMinus) {
    LargeInt<byte> a("5");
    EXPECT_EQ((-a).toString(), "-5");

    LargeInt<byte> b("-5");
    EXPECT_EQ((-b).toString(), "5");
}
