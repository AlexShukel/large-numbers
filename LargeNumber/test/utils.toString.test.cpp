#include <gtest/gtest.h>
#include <vector>
#include "utils.h"

TEST(utils, getDecimalFromPositive) {
    std::string d1;
    std::vector<uint8_t> c1 = {0};
    getDecimal(d1, c1, false);
    EXPECT_EQ(d1, "0");

    std::string d2;
    std::vector<uint8_t> c2 = {1};
    getDecimal(d2, c2, false);
    EXPECT_EQ(d2, "1");

    std::string d3;
    std::vector<uint8_t> c3 = {128};
    getDecimal(d3, c3, false);
    EXPECT_EQ(d3, "128");

    std::string d4;
    std::vector<uint8_t> c4 = {45, 64, 14, 7};
    getDecimal(d4, c4, false);
    EXPECT_EQ(d4, "118374445");
}

TEST(utils, getDecimalFromNegative) {
    std::string d1;
    std::vector<uint8_t> c1 = {0};
    getDecimal(d1, c1, true);
    EXPECT_EQ(d1, "0");

    std::string d2;
    std::vector<uint8_t> c2 = {1};
    getDecimal(d2, c2, true);
    EXPECT_EQ(d2, "-255");

    std::string d3;
    std::vector<uint8_t> c3 = {128};
    getDecimal(d3, c3, true);
    EXPECT_EQ(d3, "-128");

    std::string d4;
    std::vector<uint8_t> c4 = {45, 64, 14, 7};
    getDecimal(d4, c4, true);
    EXPECT_EQ(d4, "-4176592851");
}
