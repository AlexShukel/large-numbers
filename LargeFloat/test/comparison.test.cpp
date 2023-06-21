//
// Created by alexs on 2023-06-21.
//

#include "gtest/gtest.h"
#include "LargeFloatImplementation.h"

TEST(large_float, comparison_basic) {
    LargeNumbers::LargeFloatImplementation<uint8_t> n1("0.0");
    LargeNumbers::LargeFloatImplementation<uint8_t> n2("1.0");
    LargeNumbers::LargeFloatImplementation<uint8_t> n3("-1.0");

    EXPECT_LT(n1.compare(n2), 0);
    EXPECT_GT(n1.compare(n3), 0);

    EXPECT_GT(n2.compare(n1), 0);
    EXPECT_GT(n2.compare(n3), 0);

    EXPECT_LT(n3.compare(n1), 0);
    EXPECT_LT(n3.compare(n2), 0);
}

TEST(large_float, comparison_large_numbers) {
    LargeNumbers::LargeFloatImplementation<uint8_t> n1("4564165416545413546.145645641531564");
    LargeNumbers::LargeFloatImplementation<uint8_t> n2("4564165416545413546.1456456415315641");
    LargeNumbers::LargeFloatImplementation<uint8_t> n3("4564165416545413546.145645641531563");

    EXPECT_GT(n1.compare(n3), 0);
    EXPECT_LT(n1.compare(n2), 0);

    EXPECT_GT(n2.compare(n1), 0);
    EXPECT_GT(n2.compare(n3), 0);

    EXPECT_LT(n3.compare(n1), 0);
    EXPECT_LT(n3.compare(n2), 0);
}
