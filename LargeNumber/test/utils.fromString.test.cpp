#include <gtest/gtest.h>
#include <vector>
#include <bitset>
#include "utils.h"

const int SUFFICIENT_PRECISION = LargeDoubleUtils<uint8_t>::PRECISION;

TEST(utils, getCoefficientsFromPositive) {
    std::vector<uint8_t> c1;
    std::string n1 = "0";
    LargeIntUtils<uint8_t>::getCoefficients(c1, n1, false);
    EXPECT_EQ(c1.size(), 1);
    EXPECT_EQ(c1[0], 0);

    std::vector<uint8_t> c2;
    std::string n2 = "1";
    LargeIntUtils<uint8_t>::getCoefficients(c2, n2, false);
    EXPECT_EQ(c2.size(), 1);
    EXPECT_EQ(c2[0], 1);

    std::vector<uint8_t> c3;
    std::string n3 = "255";
    LargeIntUtils<uint8_t>::getCoefficients(c3, n3, false);
    EXPECT_EQ(c3.size(), 1);
    EXPECT_EQ(c3[0], 255);

    std::vector<uint8_t> c4;
    std::string n4 = "256";
    LargeIntUtils<uint8_t>::getCoefficients(c4, n4, false);
    EXPECT_EQ(c4.size(), 2);
    EXPECT_EQ(c4[0], 0);
    EXPECT_EQ(c4[1], 1);

    std::vector<uint8_t> c5;
    std::string n5 = "257";
    LargeIntUtils<uint8_t>::getCoefficients(c5, n5, false);
    EXPECT_EQ(c5.size(), 2);
    EXPECT_EQ(c5[0], 1);
    EXPECT_EQ(c5[1], 1);

    std::vector<uint8_t> c6;
    std::string n6 = "109823";
    LargeIntUtils<uint8_t>::getCoefficients(c6, n6, false);
    EXPECT_EQ(c6.size(), 3);
    EXPECT_EQ(c6[0], 255);
    EXPECT_EQ(c6[1], 172);
    EXPECT_EQ(c6[2], 1);
}

TEST(utils, getCoefficientsFromNegative) {
    std::vector<uint8_t> c1;
    std::string n1 = "0";
    LargeIntUtils<uint8_t>::getCoefficients(c1, n1, true);
    EXPECT_EQ(c1.size(), 1);
    EXPECT_EQ(c1[0], 0);

    std::vector<uint8_t> c2;
    std::string n2 = "1";
    LargeIntUtils<uint8_t>::getCoefficients(c2, n2, true);
    EXPECT_EQ(c2.size(), 1);
    EXPECT_EQ(c2[0], 255);

    std::vector<uint8_t> c3;
    std::string n3 = "256";
    LargeIntUtils<uint8_t>::getCoefficients(c3, n3, true);
    EXPECT_EQ(c3.size(), 2);
    EXPECT_EQ(c3[0], 0);
    EXPECT_EQ(c3[1], 255);
}

TEST(utils, toTwosComplement) {
    std::vector<uint8_t> c1 = {0};
    LargeIntUtils<uint8_t>::toTwosComplement(c1);
    EXPECT_EQ(c1[0], 0);

    std::vector<uint8_t> c2 = {1};
    LargeIntUtils<uint8_t>::toTwosComplement(c2);
    EXPECT_EQ(c2[0], 255);

    std::vector<uint8_t> c3 = {128};
    LargeIntUtils<uint8_t>::toTwosComplement(c3);
    EXPECT_EQ(c3[0], 128);
}

TEST(utils, getDoubleCoefficients) {
    std::vector<uint8_t> c1;
    std::string f1 = "25";
    LargeDoubleUtils<uint8_t>::getFractionCoefficients(c1, f1);
    EXPECT_EQ(c1.size(), 1);
    EXPECT_EQ(c1[0], 64);

    std::vector<uint8_t> c2;
    std::string f2 = "0";
    LargeDoubleUtils<uint8_t>::getFractionCoefficients(c2, f2);
    EXPECT_EQ(c2.size(), 1);
    EXPECT_EQ(c2[0], 0);

    std::vector<uint8_t> c3;
    std::string f3 = "125";
    LargeDoubleUtils<uint8_t>::getFractionCoefficients(c3, f3);
    EXPECT_EQ(c3.size(), 1);
    EXPECT_EQ(c3[0], 32);

    // WIth periodic fractions:

    std::vector<uint8_t> c4;
    std::string f4 = "1";
    LargeDoubleUtils<uint8_t>::getFractionCoefficients(c4, f4);
    EXPECT_EQ(c4.size(), SUFFICIENT_PRECISION);
    EXPECT_EQ(c4[0], std::bitset<8>(0b00011001).to_ulong());
    unsigned long pv1 = std::bitset<8>(0b10011001).to_ulong();
    for (auto it = c4.begin() + 1; it != c4.end(); ++it) {
        EXPECT_EQ(*it, pv1);
    }

    std::vector<uint8_t> c5;
    std::string f5 = "2";
    LargeDoubleUtils<uint8_t>::getFractionCoefficients(c5, f5);
    EXPECT_EQ(c5.size(), SUFFICIENT_PRECISION);
    unsigned long periodicValue = std::bitset<8>(0b00110011).to_ulong();
    for (unsigned char c: c5) {
        EXPECT_EQ(c, periodicValue);
    }
}

// Should convert a double represented in string into coefficients and exponent
TEST(utils, parseLargeDouble) {
    std::string n1 = "0.0";
    auto r1 = LargeDoubleUtils<uint8_t>::parseLargeDouble(n1);
    EXPECT_EQ(std::get<0>(r1).toString(), "0");
    EXPECT_EQ(std::get<1>(r1), -1);
    EXPECT_EQ(std::get<2>(r1), false);

    std::string n2 = "-0.0";
    auto r2 = LargeDoubleUtils<uint8_t>::parseLargeDouble(n2);
    EXPECT_EQ(std::get<0>(r2).toString(), "0");
    EXPECT_EQ(std::get<1>(r2), -1);
    EXPECT_EQ(std::get<2>(r2), true);

    std::string n3 = "0.25";
    auto r3 = LargeDoubleUtils<uint8_t>::parseLargeDouble(n3);
    EXPECT_EQ(std::get<0>(r3).toString(), "16384");
    EXPECT_EQ(std::get<1>(r3), -1);
    EXPECT_EQ(std::get<2>(r3), false);

    std::string n4 = "0.5";
    auto r4 = LargeDoubleUtils<uint8_t>::parseLargeDouble(n4);
    EXPECT_EQ(std::get<0>(r4).toString(), "32768");
    EXPECT_EQ(std::get<1>(r4), -1);
    EXPECT_EQ(std::get<2>(r4), false);

    std::string n5 = "0.1";
    auto r5 = LargeDoubleUtils<uint8_t>::parseLargeDouble(n5);
    EXPECT_EQ(std::get<1>(r5), -41);
    EXPECT_EQ(std::get<2>(r5), false);
}
