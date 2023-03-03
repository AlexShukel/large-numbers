#include <gtest/gtest.h>
#include "LargeInt/LargeInt.h"

typedef uint8_t byte;

TEST(LargeInt, multiply) {
    EXPECT_EQ((LargeInt<byte>("2") * LargeInt<byte>("3")).toString(), "6");
    EXPECT_EQ((LargeInt<byte>("1") * LargeInt<byte>("5")).toString(), "5");
    EXPECT_EQ((LargeInt<byte>("-2") * LargeInt<byte>("-3")).toString(), "6");
    EXPECT_EQ((LargeInt<byte>("-2") * LargeInt<byte>("3")).toString(), "-6");
    EXPECT_EQ((LargeInt<byte>("45678974851315645646541351") * LargeInt<byte>("0")).toString(), "0");
    EXPECT_EQ((LargeInt<byte>("0") * LargeInt<byte>("784131457564551321325")).toString(), "0");
}

TEST(LargeInt, multiplyAssignment) {
    LargeInt<byte> n1("2");
    n1 *= LargeInt<byte>("3");
    EXPECT_EQ(n1.toString(), "6");

    LargeInt<byte> n2("-2");
    n2 *= LargeInt<byte>("3");
    EXPECT_EQ(n2.toString(), "-6");

    LargeInt<byte> n3("45612313");
    n3 *= LargeInt<byte>("0");
    EXPECT_EQ(n3.toString(), "0");

    LargeInt<byte> n4("45645121");
    n4 *= LargeInt<byte>("-0");
    EXPECT_EQ(n4.toString(), "0");
}
