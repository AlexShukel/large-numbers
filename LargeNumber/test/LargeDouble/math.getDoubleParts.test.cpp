#include <gtest/gtest.h>
#include "LargeNumbers.h"
#include "../testUtils.h"

typedef uint8_t byte;
typedef LargeDoubleMath<byte> Math;

TEST(LargeDoubleMath, getIntegralCoefficients) {
    {
        Math number(LargeIntMath<byte>({11, 1, 4, 56, 78}, false), 2);
        expectVectorsEquality(number.getIntegralCoefficients(), {56, 78});
    }

    {
        Math number(LargeIntMath<byte>({11, 1, 4, 56, 78}, false), 0);
        expectVectorsEquality(number.getIntegralCoefficients(), {});
    }

    {
        Math number(LargeIntMath<byte>({56, 78}, false), 4);
        expectVectorsEquality(number.getIntegralCoefficients(), {0, 0, 56, 78});
    }

    {
        Math number(LargeIntMath<byte>({56, 78}, false), 2);
        expectVectorsEquality(number.getIntegralCoefficients(), {56, 78});
    }

    {
        Math number(LargeIntMath<byte>({}, false), 2);
        expectVectorsEquality(number.getIntegralCoefficients(), {});
    }

    {
        Math number(LargeIntMath<byte>({56, 12, 3, 5}, false), -2);
        expectVectorsEquality(number.getIntegralCoefficients(), {});
    }
}


TEST(LargeDoubleMath, getFractionalCoefficients) {
    {
        Math number(LargeIntMath<byte>({11, 1, 4, 56, 78}, false), 2);
        expectVectorsEquality(number.getFractionalCoefficients(), {11, 1, 4});
    }

    {
        Math number(LargeIntMath<byte>({11, 1, 4, 56, 78}, false), 0);
        expectVectorsEquality(number.getFractionalCoefficients(), {11, 1, 4, 56, 78});
    }

    {
        Math number(LargeIntMath<byte>({56, 78}, false), 4);
        expectVectorsEquality(number.getFractionalCoefficients(), {});
    }

    {
        Math number(LargeIntMath<byte>({56, 78}, false), 2);
        expectVectorsEquality(number.getFractionalCoefficients(), {});
    }

    {
        Math number(LargeIntMath<byte>({}, false), 2);
        expectVectorsEquality(number.getFractionalCoefficients(), {});
    }

    {
        Math number(LargeIntMath<byte>({56, 12, 3, 5}, false), -2);
        expectVectorsEquality(number.getFractionalCoefficients(), {56, 12, 3, 5, 0, 0});
    }
}
