#include <gtest/gtest.h>
#include <vector>
#include "utils.h"

TEST(utils, integerToCoefficients) {
    std::vector<uint8_t> c1;
    integerToCoefficients(c1, 0);
    EXPECT_EQ(c1.size(), 1);
    EXPECT_EQ(c1[0], 0);

    std::vector<uint8_t> c2;
    integerToCoefficients(c2, 13);
    EXPECT_EQ(c2.size(), 1);
    EXPECT_EQ(c2[0], 13);

    std::vector<uint8_t> c3;
    integerToCoefficients(c3, 256);
    EXPECT_EQ(c3.size(), 2);
    EXPECT_EQ(c3[0], 0);
    EXPECT_EQ(c3[1], 1);
}

