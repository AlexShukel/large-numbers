#include <gtest/gtest.h>
#include "utils.h"

TEST(utils, vectorUtils) {
    // trimFront
    {
        std::vector<uint8_t> v1 = {};
        EXPECT_EQ(trimFront(v1, (uint8_t) 0), 0);
        EXPECT_EQ(v1.empty(), true);

        std::vector<uint8_t> v2 = {1};
        EXPECT_EQ(trimFront(v2, (uint8_t) 0), 0);
        EXPECT_EQ(v2.size(), 1);
        EXPECT_EQ(v2[0], 1);

        std::vector<uint8_t> v3 = {1, 1, 1, 1};
        EXPECT_EQ(trimFront(v3, (uint8_t) 0), 0);
        EXPECT_EQ(v3.size(), 4);
        EXPECT_EQ(std::all_of(v3.begin(), v3.end(), [](uint8_t value) { return value == 1; }), true);

        std::vector<uint8_t> v4 = {0, 0, 0, 1};
        EXPECT_EQ(trimFront(v4, (uint8_t) 0), 3);
        EXPECT_EQ(v4.size(), 1);
        EXPECT_EQ(v4[0], 1);

        std::vector<uint8_t> v5 = {0, 1};
        EXPECT_EQ(trimFront(v5, (uint8_t) 0), 1);
        EXPECT_EQ(v5.size(), 1);
        EXPECT_EQ(v5[1], 1);
    }

    // trimBack
    {
        std::vector<uint8_t> v1 = {};
        EXPECT_EQ(trimBack(v1, (uint8_t) 0), 0);
        EXPECT_EQ(v1.empty(), true);

        std::vector<uint8_t> v2 = {1};
        EXPECT_EQ(trimBack(v2, (uint8_t) 0), 0);
        EXPECT_EQ(v2.size(), 1);
        EXPECT_EQ(v2[0], 1);

        std::vector<uint8_t> v3 = {1, 1, 1, 1};
        EXPECT_EQ(trimBack(v3, (uint8_t) 0), 0);
        EXPECT_EQ(v3.size(), 4);
        EXPECT_EQ(std::all_of(v3.begin(), v3.end(), [](uint8_t value) { return value == 1; }), true);

        std::vector<uint8_t> v4 = {1, 0};
        EXPECT_EQ(trimBack(v4, (uint8_t) 0), 1);
        EXPECT_EQ(v4.size(), 1);
        EXPECT_EQ(v4[0], 1);

        std::vector<uint8_t> v5 = {1, 0, 0, 0};
        EXPECT_EQ(trimBack(v5, (uint8_t) 0), 3);
        EXPECT_EQ(v5.size(), 1);
        EXPECT_EQ(v5[0], 1);
    }
}
