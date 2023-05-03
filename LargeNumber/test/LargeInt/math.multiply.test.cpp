#include <gtest/gtest.h>
#include <vector>
#include "LargeIntMath.h"
#include "../testUtils.h"

typedef uint8_t byte;

TEST(LargeIntMath, multiplyByCoefficient) {
    LargeIntMath<byte> n1("0");
    n1.multiplyByCoefficient(0);
    expectVectorsEquality(n1.getCoefficients(), {});

    LargeIntMath<byte> n2("0");
    n2.multiplyByCoefficient(1);
    expectVectorsEquality(n2.getCoefficients(), {});

    LargeIntMath<byte> n3("3");
    n3.multiplyByCoefficient(2);
    expectVectorsEquality(n3.getCoefficients(), {6});

    LargeIntMath<byte> n4("255");
    n4.multiplyByCoefficient(2);
    expectVectorsEquality(n4.getCoefficients(), {254, 1});

    LargeIntMath<byte> n5("65535");
    n5.multiplyByCoefficient(255);
    expectVectorsEquality(n5.getCoefficients(), {1, 255, 254});
    EXPECT_EQ(n5.toString(), "16711425");
}

TEST(LargeIntMath, multiplyPositiveNumbers) {
    LargeIntMath<byte> n1("1");
    n1.multiply(LargeIntMath<byte>("0"));
    expectVectorsEquality(n1.getCoefficients(), {});

    LargeIntMath<byte> n2({1}, false);
    n2.multiply(LargeIntMath<byte>({1}, false));
    expectVectorsEquality(n2.getCoefficients(), {1});

    LargeIntMath<byte> n3({2}, false);
    n3.multiply(LargeIntMath<byte>({3}, false));
    expectVectorsEquality(n3.getCoefficients(), {6});

    LargeIntMath<byte> n4({1}, false);
    n4.multiply(LargeIntMath<byte>({0, 0, 3}, false));
    expectVectorsEquality(n4.getCoefficients(), {0, 0, 3});

    LargeIntMath<byte> n5({61, 79, 63}, false);
    n5.multiply(LargeIntMath<byte>({}, false));
    expectVectorsEquality(n5.getCoefficients(), {});
}

TEST(LargeIntMath, multiplyNegativeNumbers) {
    LargeIntMath<byte> n1({}, true);
    n1.multiply(LargeIntMath<byte>({}, false));
    expectVectorsEquality(n1.getCoefficients(), {});

    LargeIntMath<byte> n2({1}, false);
    n2.multiply(LargeIntMath<byte>({1}, true));
    EXPECT_EQ(n2.getSign(), true);
    expectVectorsEquality(n2.getCoefficients(), {1});

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
