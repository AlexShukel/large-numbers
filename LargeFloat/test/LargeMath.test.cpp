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

TEST(large_math, next_prime) {
    EXPECT_EQ(nextPrime(LargeInt("0")).toString(), "2");
    EXPECT_EQ(nextPrime(LargeInt("1")).toString(), "2");
    EXPECT_EQ(nextPrime(LargeInt("2")).toString(), "3");
    EXPECT_EQ(nextPrime(LargeInt("6")).toString(), "7");
    EXPECT_EQ(nextPrime(LargeInt("3275")).toString(), "3299");
    EXPECT_EQ(nextPrime(LargeInt("6920")).toString(), "6947");
}

TEST(large_math, power) {
    EXPECT_EQ(pow(LargeFloat(0), LargeInt(0)).toString(), "1.0");
    EXPECT_EQ(pow(LargeFloat("0.1"), LargeInt(1)).toString(), "0.1");
    EXPECT_EQ(pow(LargeFloat("0.1"), LargeInt(2)).toString(), "0.01");
    EXPECT_EQ(pow(LargeFloat("0.1"), LargeInt(3)).toString(), "0.001");
    EXPECT_EQ(pow(LargeFloat("1.1"), LargeInt(3)).toString(), "1.331");
    EXPECT_EQ(pow(LargeFloat("94567342.94567132595"), LargeInt(4)).toString(), "79976933344681599935603491186526.49198674427702399196065870258573151927700625");
}
