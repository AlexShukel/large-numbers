#include <gtest/gtest.h>
#include "LargeDoubleMath.h"
#include "../testUtils.h"

typedef uint8_t byte;
typedef LargeDoubleMath<byte> Math;

class LargeIntMathTester {
public:
    static void validateCoefficients(LargeIntMath<byte> &math, const std::vector<byte> &coefficients) {
        expectVectorsEquality(math.coefficients, coefficients);
    }
};

TEST(LargeDoubleMath, multiplication) {
    {
        Math number("1.0");
        number.multiply(Math("0.0"));
        LargeIntMathTester::validateCoefficients(number.getMantissa(), {});
        EXPECT_EQ(number.getExponent(), 1);
        EXPECT_EQ(number.getSign(), false);
    }

    {
        Math number("1.0");
        number.multiply(Math("1.0"));

        LargeIntMathTester::validateCoefficients(number.getMantissa(), {1});

        EXPECT_EQ(number.getExponent(), 1);
        EXPECT_EQ(number.getSign(), false);
    }

    {
        Math number("0.25");
        number.multiply(Math("0.5"));

        LargeIntMathTester::validateCoefficients(number.getMantissa(), {32});

        EXPECT_EQ(number.getExponent(), 0);
        EXPECT_EQ(number.getSign(), false);
    }

    {
        Math number("0.0");
        number.multiply(Math("0.0"));

        LargeIntMathTester::validateCoefficients(number.getMantissa(), {});

        EXPECT_EQ(number.getExponent(), 1);
        EXPECT_EQ(number.getSign(), false);
    }

    {
        Math number("12345645134556142341546.1234654531657486415");
        number.multiply(Math("0.0"));

        LargeIntMathTester::validateCoefficients(number.getMantissa(), {});

        EXPECT_EQ(number.getExponent(), 1);
        EXPECT_EQ(number.getSign(), false);
    }

    {
        Math number("10.25");
        number.multiply(Math("0.5"));

        LargeIntMathTester::validateCoefficients(number.getMantissa(), {32, 5});

        EXPECT_EQ(number.getExponent(), 1);
        EXPECT_EQ(number.getSign(), false);
    }
}
