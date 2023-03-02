#include <gtest/gtest.h>
#include <vector>
#include "utils.h"

TEST(utils, getCoefficientsFromPositive) {
    std::vector<uint8_t> c1;
    std::string n1 = "0";
    getCoefficients(c1, n1, false);
    EXPECT_EQ(c1.size(), 1);
    EXPECT_EQ(c1[0], 0);

    std::vector<uint8_t> c2;
    std::string n2 = "1";
    getCoefficients(c2, n2, false);
    EXPECT_EQ(c2.size(), 1);
    EXPECT_EQ(c2[0], 1);

    std::vector<uint8_t> c3;
    std::string n3 = "255";
    getCoefficients(c3, n3, false);
    EXPECT_EQ(c3.size(), 1);
    EXPECT_EQ(c3[0], 255);

    std::vector<uint8_t> c4;
    std::string n4 = "256";
    getCoefficients(c4, n4, false);
    EXPECT_EQ(c4.size(), 2);
    EXPECT_EQ(c4[0], 0);
    EXPECT_EQ(c4[1], 1);

    std::vector<uint8_t> c5;
    std::string n5 = "257";
    getCoefficients(c5, n5, false);
    EXPECT_EQ(c5.size(), 2);
    EXPECT_EQ(c5[0], 1);
    EXPECT_EQ(c5[1], 1);

    std::vector<uint8_t> c6;
    std::string n6 = "109823";
    getCoefficients(c6, n6, false);
    EXPECT_EQ(c6.size(), 3);
    EXPECT_EQ(c6[0], 255);
    EXPECT_EQ(c6[1], 172);
    EXPECT_EQ(c6[2], 1);
}

TEST(utils, getCoefficientsFromNegative) {
    std::vector<uint8_t> c1;
    std::string n1 = "0";
    getCoefficients(c1, n1, true);
    EXPECT_EQ(c1.size(), 1);
    EXPECT_EQ(c1[0], 0);

    std::vector<uint8_t> c2;
    std::string n2 = "1";
    getCoefficients(c2, n2, true);
    EXPECT_EQ(c2.size(), 1);
    EXPECT_EQ(c2[0], 255);

    std::vector<uint8_t> c3;
    std::string n3 = "256";
    getCoefficients(c3, n3, true);
    EXPECT_EQ(c3.size(), 2);
    EXPECT_EQ(c3[0], 0);
    EXPECT_EQ(c3[1], 255);
}

TEST(utils, toTwosComplement) {
    std::vector<uint8_t> c1 = {0};
    toTwosComplement(c1);
    EXPECT_EQ(c1[0], 0);

    std::vector<uint8_t> c2 = {1};
    toTwosComplement(c2);
    EXPECT_EQ(c2[0], 255);

    std::vector<uint8_t> c3 = {128};
    toTwosComplement(c3);
    EXPECT_EQ(c3[0], 128);
}
