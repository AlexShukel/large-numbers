#include <gtest/gtest.h>
#include "LargeNumbers.h"

typedef uint8_t byte;

TEST(LargeDoubleMath, constructorShouldThrow) {
    EXPECT_ANY_THROW(LargeDoubleMath<byte>(""));
    EXPECT_ANY_THROW(LargeDoubleMath<byte>("0"));
    EXPECT_ANY_THROW(LargeDoubleMath<byte>(".0"));
}

TEST(LargeDoubleMath, constructor) {
    {
        LargeDoubleMath<byte> number("0.5");
        EXPECT_EQ(number.getSign(), false);
        EXPECT_EQ(number.getMantissa().getCoefficients().size(), 1);
        EXPECT_EQ(number.getMantissa().getCoefficients()[0], 128);
        EXPECT_EQ(number.getExponent(), 0);
    }

    {
        LargeDoubleMath<byte> number("256.0");
        EXPECT_EQ(number.getSign(), false);
        EXPECT_EQ(number.getMantissa().getCoefficients().size(), 1);
        EXPECT_EQ(number.getMantissa().getCoefficients()[0], 1);
        EXPECT_EQ(number.getExponent(), 2);
    }

}
