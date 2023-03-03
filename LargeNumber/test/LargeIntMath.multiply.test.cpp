#include <gtest/gtest.h>
#include <vector>
#include "LargeIntMath.h"

typedef uint8_t byte;

TEST(LargeIntMath, multiplyByCoefficient) {
    LargeIntMath<byte> n1("0");
    n1.multiplyByCoefficient(0);
    EXPECT_EQ(n1.toString(), "0");

    LargeIntMath<byte> n2("0");
    n2.multiplyByCoefficient(1);
    EXPECT_EQ(n2.toString(), "0");

    LargeIntMath<byte> n3("3");
    n3.multiplyByCoefficient(2);
    EXPECT_EQ(n3.toString(), "6");

    LargeIntMath<byte> n4("255");
    n4.multiplyByCoefficient(2);
    EXPECT_EQ(n4.toString(), "510");

    LargeIntMath<byte> n5("65535");
    n5.multiplyByCoefficient(255);
    EXPECT_EQ(n5.toString(), "16711425");
}

TEST(LargeIntMath, multiplyPositiveNumbers) {
    LargeIntMath<byte> n1("1");
    n1.multiply(LargeIntMath<byte>("0"));
    EXPECT_EQ(n1.toString(), "0");

    LargeIntMath<byte> n2("1");
    n2.multiply(LargeIntMath<byte>("1"));
    EXPECT_EQ(n2.toString(), "1");

    LargeIntMath<byte> n3("2");
    n3.multiply(LargeIntMath<byte>("3"));
    EXPECT_EQ(n3.toString(), "6");

    LargeIntMath<byte> n4("1");
    n4.multiply(LargeIntMath<byte>("1231456465"));
    EXPECT_EQ(n4.toString(), "1231456465");

    LargeIntMath<byte> n5("1231456465");
    n5.multiply(LargeIntMath<byte>("1"));
    EXPECT_EQ(n5.toString(), "1231456465");

    LargeIntMath<byte> n6("12345");
    n6.multiply(LargeIntMath<byte>("78941"));
    EXPECT_EQ(n6.toString(), "974526645");

    LargeIntMath<byte> n7("65535");
    n7.multiply(LargeIntMath<byte>("255"));
    EXPECT_EQ(n7.toString(), "16711425");

    LargeIntMath<byte> n8("78945163456465");
    n8.multiply(LargeIntMath<byte>("789451312354"));
    EXPECT_EQ(n8.toString(), "62323362894707336995668610");
}

TEST(LargeIntMath, multiplyNegativeNumbers) {
    LargeIntMath<byte> n1("-0");
    n1.multiply(LargeIntMath<byte>("0"));
    EXPECT_EQ(n1.toString(), "0");

    LargeIntMath<byte> n2("1");
    n2.multiply(LargeIntMath<byte>("-1"));
    EXPECT_EQ(n2.toString(), "-1");

    LargeIntMath<byte> n3("-1");
    n3.multiply(LargeIntMath<byte>("-1"));
    EXPECT_EQ(n3.toString(), "1");

    LargeIntMath<byte> n4("-5");
    n4.multiply(LargeIntMath<byte>("2"));
    EXPECT_EQ(n4.toString(), "-10");

    LargeIntMath<byte> n5("-5");
    n5.multiply(LargeIntMath<byte>("-2"));
    EXPECT_EQ(n5.toString(), "10");

    LargeIntMath<byte> n6("-78945163456465");
    n6.multiply(LargeIntMath<byte>("789451312354"));
    EXPECT_EQ(n6.toString(), "-62323362894707336995668610");
}
