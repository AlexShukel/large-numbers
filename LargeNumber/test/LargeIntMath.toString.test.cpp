#include <gtest/gtest.h>
#include "LargeIntMath.h"

typedef uint8_t byte;

TEST(LargeIntMath, positiveToString) {
    LargeIntMath<byte> n0("0");
    EXPECT_EQ(n0.toString(), "0");

    LargeIntMath<byte> n1("1");
    EXPECT_EQ(n1.toString(), "1");

    LargeIntMath<byte> n2("16141");
    EXPECT_EQ(n2.toString(), "16141");
}

TEST(LargeIntMath, negativeToString) {
    LargeIntMath<byte> n0("-0");
    EXPECT_EQ(n0.toString(), "0");

    LargeIntMath<byte> n1("-255");
    EXPECT_EQ(n1.toString(), "-255");

    LargeIntMath<byte> n2("-49395");
    EXPECT_EQ(n2.toString(), "-49395");
}
