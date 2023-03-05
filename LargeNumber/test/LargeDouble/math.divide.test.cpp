#include <gtest/gtest.h>
#include "LargeDoubleMath.h"
#include "../testUtils.h"

typedef uint8_t byte;
typedef LargeDoubleMath<byte> Math;

TEST(LargeDoubleMath, division) {
    {
        Math number("4.0");
        number.divide(Math("2.0"));
        expectVectorsEquality(number.getMantissa().getCoefficients(), {2});
        EXPECT_EQ(number.getExponent(), 1);
        EXPECT_EQ(number.getSign(), false);
    }
}
