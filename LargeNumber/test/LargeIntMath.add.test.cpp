#include <gtest/gtest.h>
#include "LargeIntMath.h"
#include "utils.h"

typedef uint8_t byte;

TEST(LargeIntMath, AddPositiveNumbers) {
    LargeIntMath<byte> n1("0");

    LargeIntMath<byte> n2("0");

    LargeIntMath<byte> n3("1");

    LargeIntMath<byte> n4("10");

    LargeIntMath<byte> n5("430971");

    n1.add(n2);
    EXPECT_EQ(n1.toString(), "0");

    n1.add(n3);
    EXPECT_EQ(n1.toString(), "1");

    n1.add(n4);
    EXPECT_EQ(n1.toString(), "11");

    n1.add(n5);
    EXPECT_EQ(n1.toString(), "430982");

    LargeIntMath<byte> n6("18446744073709551615");
    n6.add(n6);
    EXPECT_EQ(n6.toString(), "36893488147419103230");

    LargeIntMath<byte> n7("999999999999999999999999999999999999999999999999999999999999999");
    n7.add(LargeIntMath<byte>("1"));
    EXPECT_EQ(n7.toString(), "1000000000000000000000000000000000000000000000000000000000000000");

    LargeIntMath<byte> n8("1");
    n8.add(LargeIntMath<byte>("999999999999999999999999999999999999999999999999999999999999999"));
    EXPECT_EQ(n8.toString(), "1000000000000000000000000000000000000000000000000000000000000000");
}

TEST(LargeIntMath, AddNegativeNumbers) {
    LargeIntMath<byte> n1("5");

    LargeIntMath<byte> n2("-3");

    LargeIntMath<byte> n3("-6");

    LargeIntMath<byte> n4("-56710");

    LargeIntMath<byte> n5("-5466431547676314564134154242449");

    n1.add(n2);
    EXPECT_EQ(n1.toString(), "2");

    n1.add(n3);
    EXPECT_EQ(n1.toString(), "-4");

    n1.add(n4);
    EXPECT_EQ(n1.toString(), "-56714");

    n1.add(n5);
    EXPECT_EQ(n1.toString(), "-5466431547676314564134154299163");
}

TEST(LargeIntMath, AddReverseNumbers) {
    LargeIntMath<byte> n1("5");
    LargeIntMath<byte> n2("-5");

    n1.add(n2);
    EXPECT_EQ(n1.toString(), "0");

    LargeIntMath<byte> n3("51554986");
    LargeIntMath<byte> n4("-51554986");

    n3.add(n4);
    EXPECT_EQ(n3.toString(), "0");

    LargeIntMath<byte> n5("545645471657146574741567246571561276521675476465152");
    LargeIntMath<byte> n6("-545645471657146574741567246571561276521675476465152");

    n5.add(n6);
    EXPECT_EQ(n5.toString(), "0");
}
