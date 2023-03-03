#include <gtest/gtest.h>
#include <vector>

#define TEST_MODE

#include "LargeIntMath.h"

typedef uint8_t byte;

TEST(LargeIntMath, settingCorrectCoefficients) {
    LargeIntMath<byte> n1("0");
    std::vector<byte> c1 = n1.getCoefficients();
    EXPECT_EQ(c1.size(), 1);
    EXPECT_EQ(c1[0], 0);

    LargeIntMath<byte> n2("13");
    std::vector<byte> c2 = n2.getCoefficients();
    EXPECT_EQ(c2.size(), 1);
    EXPECT_EQ(c2[0], 13);

    LargeIntMath<byte> n3("313");
    std::vector<byte> c3 = n3.getCoefficients();
    EXPECT_EQ(c3.size(), 2);
    EXPECT_EQ(c3[0], 57);
    EXPECT_EQ(c3[1], 1);

    LargeIntMath<byte> n4("1025");
    std::vector<byte> c4 = n4.getCoefficients();
    EXPECT_EQ(c4.size(), 2);
    EXPECT_EQ(c4[0], 1);
    EXPECT_EQ(c4[1], 4);

    LargeIntMath<byte> n5("-1");
    std::vector<byte> c5 = n5.getCoefficients();
    EXPECT_EQ(c5.size(), 1);
    EXPECT_EQ(c5[0], 255);

    LargeIntMath<byte> n6("-2468");
    std::vector<byte> c6 = n6.getCoefficients();
    EXPECT_EQ(c6.size(), 2);
    EXPECT_EQ(c6[0], 92);
    EXPECT_EQ(c6[1], 246);
}

TEST(LargeIntMath, settingCorrectSign) {
    LargeIntMath<byte> n1("1");
    EXPECT_EQ(n1.getSign(), false);

    LargeIntMath<byte> n2("+1");
    EXPECT_EQ(n2.getSign(), false);

    LargeIntMath<byte> n3("-1");
    EXPECT_EQ(n3.getSign(), true);
}
