#include <gtest/gtest.h>
#include "LargeNumbers.h"
#include "../testUtils.h"

typedef uint8_t byte;
typedef LargeDoubleMath<byte> Math;

#include <iostream>

TEST(LargeDoubleMath, addition) {
    {
        Math number("0.0");
        number.add(Math("0.0"));
        expectVectorsEquality(number.getMantissa().getCoefficients(), {});
        EXPECT_EQ(number.getExponent(), 1);
        EXPECT_EQ(number.getSign(), false);
    }

    {
        Math number("0.25");
        number.add(Math("0.0"));
        expectVectorsEquality(number.getMantissa().getCoefficients(), {64});
        EXPECT_EQ(number.getExponent(), 0);
        EXPECT_EQ(number.getSign(), false);
    }

    {
        Math number("13.25");
        number.add(Math("1.5"));
        expectVectorsEquality(number.getMantissa().getCoefficients(), {192, 14});
        EXPECT_EQ(number.getExponent(), 1);
        EXPECT_EQ(number.getSign(), false);
    }

    {
        Math number("0.25");
        number.add(Math("1000.0625"));
        expectVectorsEquality(number.getMantissa().getCoefficients(), {80, 232, 3});
        EXPECT_EQ(number.getExponent(), 2);
        EXPECT_EQ(number.getSign(), false);
    }

    {
        Math number("0.25");
        number.add(Math("0.0625"));
        expectVectorsEquality(number.getMantissa().getCoefficients(), {80});
        EXPECT_EQ(number.getExponent(), 0);
        EXPECT_EQ(number.getSign(), false);
    }

    {
        Math number("-0.25");
        number.add(Math("0.5"));
        expectVectorsEquality(number.getMantissa().getCoefficients(), {64});
        EXPECT_EQ(number.getExponent(), 0);
        EXPECT_EQ(number.getSign(), false);
    }

    {
        Math number("-0.25");
        number.add(Math("-0.25"));
        expectVectorsEquality(number.getMantissa().getCoefficients(), {128});
        EXPECT_EQ(number.getExponent(), 0);
        EXPECT_EQ(number.getSign(), true);
    }

    {
        Math number("-0.25");
        number.add(Math("-0.5"));
        expectVectorsEquality(number.getMantissa().getCoefficients(), {64});
        EXPECT_EQ(number.getExponent(), 0);
        EXPECT_EQ(number.getSign(), true);
    }

    {
        Math number("-513.25");
        number.add(Math("-100.5"));
        expectVectorsEquality(number.getMantissa().getCoefficients(), {64, 154, 253});
        EXPECT_EQ(number.getExponent(), 2);
        EXPECT_EQ(number.getSign(), true);
    }
}
