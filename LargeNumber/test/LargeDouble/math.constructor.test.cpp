#include <gtest/gtest.h>
#include "LargeNumbers.h"

typedef uint8_t byte;

TEST(LargeDoubleMath, constructorShouldThrow) {
    EXPECT_ANY_THROW(LargeDoubleMath<byte>(""));
    EXPECT_ANY_THROW(LargeDoubleMath<byte>("0"));
    EXPECT_ANY_THROW(LargeDoubleMath<byte>(".0"));
}

TEST(LargeDoubleMath, constructor) {
    LargeDoubleMath<byte> n1("0.5");
}
