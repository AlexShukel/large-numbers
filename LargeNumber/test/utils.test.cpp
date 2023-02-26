#include <gtest/gtest.h>
#include <vector>
#include "utils.h"

TEST(utils, isZero) {
    EXPECT_EQ(true, isZero(""));
    EXPECT_EQ(true, isZero("0"));
    EXPECT_EQ(true, isZero("00000"));

    EXPECT_EQ(false, isZero("a"));
    EXPECT_EQ(false, isZero("1"));
    EXPECT_EQ(false, isZero("9999"));
}

TEST(utils, getBinary) {
    EXPECT_EQ("0", getBinary("0"));
    EXPECT_EQ("1", getBinary("1"));
    EXPECT_EQ("10", getBinary("2"));
    EXPECT_EQ("101", getBinary("5"));
    EXPECT_EQ("10000000", getBinary("128"));
}

TEST(utils, getNumberCoefficients) {
    std::vector<uint8_t> v1;
    getNumberCoefficients<uint8_t>(v1, "0");
    ASSERT_EQ(v1.size(), 1);
    EXPECT_EQ(v1[0], 0);

    std::vector<uint8_t> v2;
    getNumberCoefficients<uint8_t>(v2, "1");
    ASSERT_EQ(v2.size(), 1);
    EXPECT_EQ(v2[0], 1);

    std::vector<uint8_t> v3;
    getNumberCoefficients<uint8_t>(v3, "11111111");
    ASSERT_EQ(v3.size(), 1);
    EXPECT_EQ(v3[0], 255);

    std::vector<uint8_t> v4;
    getNumberCoefficients<uint8_t>(v4, "1010110011111111");
    ASSERT_EQ(v4.size(), 2);
    EXPECT_EQ(v4[0], 255);
    EXPECT_EQ(v4[1], 172);

    std::vector<uint8_t> v5;
    getNumberCoefficients<uint8_t>(v5, "11010110011111111");
    ASSERT_EQ(v5.size(), 3);
    EXPECT_EQ(v5[0], 255);
    EXPECT_EQ(v5[1], 172);
    EXPECT_EQ(v5[2], 1);
}
