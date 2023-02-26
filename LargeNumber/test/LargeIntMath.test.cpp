#include <gtest/gtest.h>

#define TEST_MODE

#include "LargeIntMath.h"


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

    std::vector<byte> c2 = {3};
    LargeIntMath<byte> n2(c2, true);

    n1.add(n2);
    EXPECT_EQ(n1.getValue(), 2);
}
