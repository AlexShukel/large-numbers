#include <gtest/gtest.h>
#include "LargeDoubleMath.h"
#include "../testUtils.h"

typedef uint8_t byte;
typedef LargeDoubleMath<byte> Math;

TEST(LargeDoubleMath, multiplication) {
    {
        Math number("1.0");
        number.multiply(Math("0.0"));
        expectVectorsEquality(number.getMantissa().getCoefficients(), {});
        EXPECT_EQ(number.getExponent(), 1);
        EXPECT_EQ(number.getSign(), false);
    }

    {
        Math number("1.0");
        number.multiply(Math("1.0"));

        expectVectorsEquality(number.getMantissa().getCoefficients(), {1});

        EXPECT_EQ(number.getExponent(), 1);
        EXPECT_EQ(number.getSign(), false);
    }

    {
        Math number("0.25");
        number.multiply(Math("0.5"));

        expectVectorsEquality(number.getMantissa().getCoefficients(), {32});

        EXPECT_EQ(number.getExponent(), 0);
        EXPECT_EQ(number.getSign(), false);
    }

    {
        Math number("0.0");
        number.multiply(Math("0.0"));

        expectVectorsEquality(number.getMantissa().getCoefficients(), {});

        EXPECT_EQ(number.getExponent(), 1);
        EXPECT_EQ(number.getSign(), false);
    }

    {
        Math number("12345645134556142341546.1234654531657486415");
        number.multiply(Math("0.0"));

        expectVectorsEquality(number.getMantissa().getCoefficients(), {});

        EXPECT_EQ(number.getExponent(), 1);
        EXPECT_EQ(number.getSign(), false);
    }

    {
        Math number("10.25");
        number.multiply(Math("0.5"));

        expectVectorsEquality(number.getMantissa().getCoefficients(), {32, 5});

        EXPECT_EQ(number.getExponent(), 1);
        EXPECT_EQ(number.getSign(), false);
    }
}
