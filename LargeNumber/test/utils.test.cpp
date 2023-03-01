#include <gtest/gtest.h>
#include <vector>
#include "utils.h"

TEST(utils, getBinary) {
    EXPECT_EQ("0", getBinary("0"));
    EXPECT_EQ("1", getBinary("1"));
    EXPECT_EQ("10", getBinary("2"));
    EXPECT_EQ("101", getBinary("5"));
    EXPECT_EQ("10000000", getBinary("128"));
}

TEST(utils, getCoefficientsFromBinaryPositive) {
    std::vector<uint8_t> v1;
    getCoefficientsFromBinary<uint8_t>(v1, "0", false);
    ASSERT_EQ(v1.size(), 1);
    EXPECT_EQ(v1[0], 0);

    std::vector<uint8_t> v2;
    getCoefficientsFromBinary<uint8_t>(v2, "1", false);
    ASSERT_EQ(v2.size(), 1);
    EXPECT_EQ(v2[0], 1);

    std::vector<uint8_t> v3;
    getCoefficientsFromBinary<uint8_t>(v3, "11111111", false);
    ASSERT_EQ(v3.size(), 1);
    EXPECT_EQ(v3[0], 255);

    std::vector<uint8_t> v4;
    getCoefficientsFromBinary<uint8_t>(v4, "1010110011111111", false);
    ASSERT_EQ(v4.size(), 2);
    EXPECT_EQ(v4[0], 255);
    EXPECT_EQ(v4[1], 172);

    std::vector<uint8_t> v5;
    getCoefficientsFromBinary<uint8_t>(v5, "11010110011111111", false);
    ASSERT_EQ(v5.size(), 3);
    EXPECT_EQ(v5[0], 255);
    EXPECT_EQ(v5[1], 172);
    EXPECT_EQ(v5[2], 1);
}

TEST(utils, getCoefficientsFromBinaryNegative) {
    std::vector<uint8_t> v1;
    getCoefficientsFromBinary<uint8_t>(v1, "0", true);
    ASSERT_EQ(v1.size(), 1);
    EXPECT_EQ(v1[0], 0);

    std::vector<uint8_t> v2;
    getCoefficientsFromBinary<uint8_t>(v2, "1", true);
    ASSERT_EQ(v2.size(), 1);
    EXPECT_EQ(v2[0], 255);

    std::vector<uint8_t> v3;
    getCoefficientsFromBinary<uint8_t>(v3, "11111111", true);
    ASSERT_EQ(v3.size(), 1);
    EXPECT_EQ(v3[0], 1);

    std::vector<uint8_t> v4;
    getCoefficientsFromBinary<uint8_t>(v4, "1010110011111111", true);
    ASSERT_EQ(v4.size(), 2);
    EXPECT_EQ(v4[0], 1);
    EXPECT_EQ(v4[1], 83);

    std::vector<uint8_t> v5;
    getCoefficientsFromBinary<uint8_t>(v5, "11010110011111111", true);
    ASSERT_EQ(v5.size(), 3);
    EXPECT_EQ(v5[0], 1);
    EXPECT_EQ(v5[1], 83);
    EXPECT_EQ(v5[2], 254);
}

TEST(utils, getBinaryFromCoefficients) {
    std::string b1;
    std::vector<uint8_t> c1 = {13};
    getBinaryFromCoefficients(b1, c1, false);
    EXPECT_EQ(b1, "1101");

    std::string b2;
    std::vector<uint8_t> c2 = {2, 5};
    getBinaryFromCoefficients(b2, c2, false);
    EXPECT_EQ(b2, "10100000010");

    std::string b3;
    std::vector<uint8_t> c3 = {111};
    getBinaryFromCoefficients(b3, c3, true);
    EXPECT_EQ(b3, "10010001");

    std::string b4;
    std::vector<uint8_t> c4 = {13, 157};
    getBinaryFromCoefficients(b4, c4, true);
    EXPECT_EQ(b4, "110001011110011");
}

TEST(utils, getDecimal) {
    EXPECT_EQ(getDecimal("0", false), "0");
    EXPECT_EQ(getDecimal("1", false), "1");
    EXPECT_EQ(getDecimal("10", false), "2");
    EXPECT_EQ(getDecimal("100011101000100101", false), "145957");

    EXPECT_EQ(getDecimal("0", true), "-0");
    EXPECT_EQ(getDecimal("1", true), "-1");
    EXPECT_EQ(getDecimal("10", true), "-2");
    EXPECT_EQ(getDecimal("100011101000100101", true), "-145957");
}
