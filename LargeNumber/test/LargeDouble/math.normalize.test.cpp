#include <gtest/gtest.h>
#include "LargeNumbers.h"

typedef uint8_t byte;
typedef LargeDoubleMath<byte> Math;

TEST(LargeDoubleMath, normalize) {
    {
        exponent_type exponent = 0;
        std::vector<byte> coefficients = {0, 0, 13, 121, 0, 0, 0};
        bool sign = false;

        LargeIntMath<byte> mantissa(coefficients, sign);

        Math math(mantissa, exponent);

        math.normalize();

        EXPECT_EQ(math.getExponent(), -3);

        auto newCoefficients = math.getMantissa().getCoefficients();

        EXPECT_EQ(newCoefficients.size(), 2);
        EXPECT_EQ(newCoefficients[0], 13);
        EXPECT_EQ(newCoefficients[1], 121);
    }

    {
        exponent_type exponent = 0;
        std::vector<byte> coefficients = {0, 0, 13, 121, 255, 255, 255};
        bool sign = true;

        LargeIntMath<byte> mantissa(coefficients, sign);

        Math math(mantissa, exponent);

        math.normalize();

        EXPECT_EQ(math.getExponent(), -3);

        auto newCoefficients = math.getMantissa().getCoefficients();

        EXPECT_EQ(newCoefficients.size(), 2);
        EXPECT_EQ(newCoefficients[0], 13);
        EXPECT_EQ(newCoefficients[1], 121);
    }

    {
        exponent_type exponent = 0;
        std::vector<byte> coefficients = {13, 121};
        bool sign = false;

        LargeIntMath<byte> mantissa(coefficients, sign);

        Math math(mantissa, exponent);

        math.normalize();

        EXPECT_EQ(math.getExponent(), 0);

        auto newCoefficients = math.getMantissa().getCoefficients();

        EXPECT_EQ(newCoefficients.size(), 2);
        EXPECT_EQ(newCoefficients[0], 13);
        EXPECT_EQ(newCoefficients[1], 121);
    }

    {
        exponent_type exponent = 0;
        std::vector<byte> coefficients = {1};
        bool sign = false;

        LargeIntMath<byte> mantissa(coefficients, sign);

        Math math(mantissa, exponent);

        math.normalize();

        EXPECT_EQ(math.getExponent(), 0);

        auto newCoefficients = math.getMantissa().getCoefficients();

        EXPECT_EQ(newCoefficients.size(), 1);
        EXPECT_EQ(newCoefficients[0], 1);
    }

    {
        exponent_type exponent = 0;
        std::vector<byte> coefficients = {0, 0, 0, 0};
        bool sign = false;

        LargeIntMath<byte> mantissa(coefficients, sign);

        Math math(mantissa, exponent);

        math.normalize();

        EXPECT_EQ(math.getExponent(), 1);

        auto newCoefficients = math.getMantissa().getCoefficients();

        EXPECT_EQ(newCoefficients.size(), 0);
    }
}
