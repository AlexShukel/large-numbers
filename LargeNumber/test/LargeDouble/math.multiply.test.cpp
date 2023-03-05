#include <gtest/gtest.h>
#include "LargeDoubleMath.h"

typedef uint8_t byte;
typedef LargeDoubleMath<byte> Math;

TEST(LargeDoubleMath, multiplication) {
    {
        Math number("1.0");
        number.multiply(Math("0.0"));
        EXPECT_EQ(number.getMantissa().getCoefficients().empty(), true);
        EXPECT_EQ(number.getExponent(), 1);
        EXPECT_EQ(number.getSign(), false);
    }

    {
        Math number("1.0");
        number.multiply(Math("1.0"));

        auto coefficients = number.getMantissa().getCoefficients();
        EXPECT_EQ(coefficients.size(), 1);
        EXPECT_EQ(coefficients[0], 1);

        EXPECT_EQ(number.getExponent(), 1);
        EXPECT_EQ(number.getSign(), false);
    }

    {
        Math number("0.25");
        number.multiply(Math("0.5"));

        auto coefficients = number.getMantissa().getCoefficients();
        EXPECT_EQ(coefficients.size(), 1);
        EXPECT_EQ(coefficients[0], 32);

        EXPECT_EQ(number.getExponent(), 0);
        EXPECT_EQ(number.getSign(), false);
    }
}
