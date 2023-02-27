#include <gtest/gtest.h>

#define TEST_MODE

#include "LargeIntMath.h"
#include "utils.h"

typedef uint8_t byte;

TEST(LargeIntMath, AddPositiveNumbers) {
    std::vector<byte> c1 = {0};
    LargeIntMath<byte> n1(c1, false);

    std::vector<byte> c2 = {0};
    LargeIntMath<byte> n2(c2, false);

    std::vector<byte> c3 = {1};
    LargeIntMath<byte> n3(c3, false);

    std::vector<byte> c4 = {10};
    LargeIntMath<byte> n4(c4, false);

    std::vector<byte> c5 = {123, 147, 6};
    LargeIntMath<byte> n5(c5, false);

    n1.add(n2);
    EXPECT_EQ(n1.getValue(), 0);

    n1.add(n3);
    EXPECT_EQ(n1.getValue(), 1);

    n1.add(n4);
    EXPECT_EQ(n1.getValue(), 11);

    n1.add(n5);
    EXPECT_EQ(n1.getValue(), 430982);
}

TEST(LargeIntMath, AddNegativeNumbers) {
    std::vector<byte> c1 = {5};
    LargeIntMath<byte> n1(c1, false);

    std::vector<byte> c2;
    getNumberCoefficients(c2, "11", true);
    LargeIntMath<byte> n2(c2, true);

    std::vector<byte> c3;
    getNumberCoefficients(c3, "110", true);
    LargeIntMath<byte> n3(c3, true);

    std::vector<byte> c4;
    getNumberCoefficients(c4, "1101110110000110", true);
    LargeIntMath<byte> n4(c4, true);

    n1.add(n2);
    EXPECT_EQ(n1.getValue(), 2);

    n1.add(n3);
    EXPECT_EQ(n1.getValue(), -4);

    n1.add(n4);
    EXPECT_EQ(n1.getValue(), -56714);
}

TEST(LargeIntMath, AddReverseNumbers) {
    std::vector<byte> c1 = {5};
    LargeIntMath<byte> n1(c1, false);

    std::vector<byte> c2 = {251};
    LargeIntMath<byte> n2(c2, false);

    n1.add(n2);
    EXPECT_EQ(n1.getValue(), 0);

    std::vector<byte> c3;
    getNumberCoefficients(c3, "11000100101010101010101010", false);
    LargeIntMath<byte> n3(c3, false);

    std::vector<byte> c4;
    getNumberCoefficients(c4, "11000100101010101010101010", true);
    LargeIntMath<byte> n4(c4, true);

    n3.add(n4);
    EXPECT_EQ(n3.getValue(), 0);
}
