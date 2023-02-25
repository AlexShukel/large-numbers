#include <vector>

#include <gtest/gtest.h>

#include "CoefficientsIterator.h"

TEST(CoefficientsIterator, ShouldIterateForward) {
    std::vector<uint8_t> v = {6, 7, 1, 10};

    CoefficientsIterator<uint8_t> iterator(&v.front(), v.size());
    CoefficientsIterator<uint8_t> end(&v.back() + 1, v.size());

    int i = 0;
    while (iterator != end) {
        EXPECT_EQ(*iterator, v[i]);

        ++iterator;
        ++i;
    }

    EXPECT_EQ(i, v.size());
}

// *iterator should return zeros when iterating after end
TEST(CoefficientsIterator, ShouldReturnZeros) {
    std::vector<uint8_t> v = {0};

    CoefficientsIterator<uint8_t> iterator(&v.front(), v.size());

    for (int i = 0; i < 10; ++i) {
        ++iterator;
        EXPECT_EQ(*iterator, 0);
    }
}
