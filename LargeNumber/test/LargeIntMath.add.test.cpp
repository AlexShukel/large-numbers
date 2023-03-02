#include <gtest/gtest.h>

#define TEST_MODE

#include "LargeIntMath.h"
#include "utils.h"

typedef uint8_t byte;

TEST(LargeIntMath, AddPositiveNumbers) {
    LargeIntMath<byte> n1("0");

    LargeIntMath<byte> n2("0");

    LargeIntMath<byte> n3("1");

    LargeIntMath<byte> n4("10");

    LargeIntMath<byte> n5("430971");
    
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
    LargeIntMath<byte> n1("5");

    LargeIntMath<byte> n2("-3");

    LargeIntMath<byte> n3("-6");

    LargeIntMath<byte> n4("-56710");

    n1.add(n2);
    EXPECT_EQ(n1.getValue(), 2);

    n1.add(n3);
    EXPECT_EQ(n1.getValue(), -4);

    n1.add(n4);
    EXPECT_EQ(n1.getValue(), -56714);
}

TEST(LargeIntMath, AddReverseNumbers) {
    LargeIntMath<byte> n1("5");

    LargeIntMath<byte> n2("251");

    n1.add(n2);
    EXPECT_EQ(n1.getValue(), 0);

    LargeIntMath<byte> n3("51554986");

    LargeIntMath<byte> n4("-51554986");

    n3.add(n4);
    EXPECT_EQ(n3.getValue(), 0);
}
