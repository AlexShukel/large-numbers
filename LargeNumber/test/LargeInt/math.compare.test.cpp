#include <gtest/gtest.h>
#include "LargeInt/LargeIntMath.h"

typedef uint8_t byte;

TEST(LargeIntMath, compare) {
    LargeIntMath<byte> n1("1");
    EXPECT_EQ(n1.compare(LargeIntMath<byte>("0")), 1);

    LargeIntMath<byte> n2("0");
    EXPECT_EQ(n2.compare(LargeIntMath<byte>("1")), -1);

    LargeIntMath<byte> n3("0");
    EXPECT_EQ(n3.compare(LargeIntMath<byte>("0")), 0);

    LargeIntMath<byte> n4("-1");
    EXPECT_EQ(n4.compare(LargeIntMath<byte>("1")), -1);

    LargeIntMath<byte> n5("1");
    EXPECT_EQ(n5.compare(LargeIntMath<byte>("-1")), 1);

    LargeIntMath<byte> n6("123456789");
    EXPECT_EQ(n6.compare(LargeIntMath<byte>("123456789")), 0);

    LargeIntMath<byte> n7("-123456789");
    EXPECT_EQ(n7.compare(LargeIntMath<byte>("-123456789")), 0);

    LargeIntMath<byte> n8("-257");
    EXPECT_EQ(n8.compare(LargeIntMath<byte>("-258")), 1);

    LargeIntMath<byte> n9("-258");
    EXPECT_EQ(n9.compare(LargeIntMath<byte>("-257")), -1);
}
