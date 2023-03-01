#include <gtest/gtest.h>
#include "LargeIntMath.h"

typedef uint8_t byte;

TEST(LargeIntMath, positiveToString) {
    std::vector<byte> c0 = {0};
    LargeIntMath<byte> n0(c0, false);
    EXPECT_EQ(n0.toString(), "0");

    std::vector<byte> c1 = {1};
    LargeIntMath<byte> n1(c1, false);
    EXPECT_EQ(n1.toString(), "1");

    std::vector<byte> c2 = {13, 63};
    LargeIntMath<byte> n2(c2, false);
    EXPECT_EQ(n2.toString(), "16141");
}

TEST(LargeIntMath, negativeToString) {
    std::vector<byte> c0 = {0};
    LargeIntMath<byte> n0(c0, true);
    EXPECT_EQ(n0.toString(), "-0");

    std::vector<byte> c1 = {1};
    LargeIntMath<byte> n1(c1, true);
    EXPECT_EQ(n1.toString(), "-255");

    std::vector<byte> c2 = {13, 63};
    LargeIntMath<byte> n2(c2, true);
    EXPECT_EQ(n2.toString(), "-49395");
}
