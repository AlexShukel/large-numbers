//
// Created by Aleksandras on 2023-06-23.
//

#include "gtest/gtest.h"
#include "LargeMath.h"

using namespace LargeNumbers;

TEST(large_math, factorial) {
    EXPECT_EQ(factorial(LargeInt(0)).toString(), "1");
    EXPECT_EQ(factorial(LargeInt(1)).toString(), "1");
    EXPECT_EQ(factorial(LargeInt(2)).toString(), "2");
    EXPECT_EQ(factorial(LargeInt(3)).toString(), "6");
    EXPECT_EQ(factorial(LargeInt(4)).toString(), "24");
    EXPECT_EQ(factorial(LargeInt(5)).toString(), "120");
    EXPECT_EQ(factorial(LargeInt(100)).toString(), "93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000");
}
