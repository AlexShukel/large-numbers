#include <gtest/gtest.h>
#include "LargeInt.h"

typedef uint8_t byte;

TEST(LargeInt, plus) {
    LargeInt<byte> a("1");
    LargeInt<byte> b("1");
    LargeInt<byte> sum = a + b;
    EXPECT_EQ(sum.toString(), "2");

    sum = LargeInt<byte>("0") + LargeInt<byte>("0");
    EXPECT_EQ(sum.toString(), "0");

    sum = LargeInt<byte>("13") + LargeInt<byte>("-5");
    EXPECT_EQ(sum.toString(), "8");

    sum = LargeInt<byte>("4") + LargeInt<byte>("-13");
    EXPECT_EQ(sum.toString(), "-9");

    sum = LargeInt<byte>("-4") + LargeInt<byte>("3");
    EXPECT_EQ(sum.toString(), "-1");
}

TEST(LargeInt, plusAssignment) {
    LargeInt<byte> a("1");
    a += LargeInt<byte>("1");
    EXPECT_EQ(a.toString(), "2");

    a += LargeInt<byte>("-2");
    EXPECT_EQ(a.toString(), "0");

    a += LargeInt<byte>("-13");
    EXPECT_EQ(a.toString(), "-13");
}
