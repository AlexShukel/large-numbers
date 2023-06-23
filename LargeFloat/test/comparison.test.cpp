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

TEST(large_float, comparison_equal_elements) {
    LargeNumbers::LargeFloatImplementation<uint8_t> n1("0.0");
    LargeNumbers::LargeFloatImplementation<uint8_t> n2("1.0");

    EXPECT_EQ(n1.compare(n1), 0);
    EXPECT_TRUE(n1.compare(n2) != 0);
}

TEST(large_float, comparison_edge_cases) {
    LargeNumbers::LargeFloatImplementation<uint8_t> n1("256.0");
    LargeNumbers::LargeFloatImplementation<uint8_t> n2("65536.0");

    EXPECT_LT(n1.compare(n2), 0);
    EXPECT_GT(n2.compare(n1), 0);

    LargeNumbers::LargeFloatImplementation<uint8_t> n3("0.1");
    LargeNumbers::LargeFloatImplementation<uint8_t> n4("0.2");

    EXPECT_LT(n3.compare(n4), 0);
    EXPECT_GT(n4.compare(n3), 0);

    LargeNumbers::LargeFloatImplementation<uint8_t> n5("0.125");
    LargeNumbers::LargeFloatImplementation<uint8_t> n6("0.25");

    EXPECT_LT(n5.compare(n6), 0);
    EXPECT_GT(n6.compare(n5), 0);

    LargeNumbers::LargeFloatImplementation<uint8_t> n7("0.5");
    LargeNumbers::LargeFloatImplementation<uint8_t> n8("128.0");

    EXPECT_LT(n7.compare(n8), 0);
    EXPECT_GT(n8.compare(n7), 0);
}

TEST(large_float, comparison_crash_test) {
    LargeNumbers::LargeFloatImplementation<uint8_t> n1("512.0");
    LargeNumbers::LargeFloatImplementation<uint8_t> n2("0.0");
    LargeNumbers::LargeFloatImplementation<uint8_t> n3("0.5");
    LargeNumbers::LargeFloatImplementation<uint8_t> n4("-1.25");

    EXPECT_GT(n1.compare(n2), 0);
    EXPECT_GT(n1.compare(n3), 0);
    EXPECT_GT(n1.compare(n4), 0);

    EXPECT_LT(n2.compare(n1), 0);
    EXPECT_LT(n2.compare(n3), 0);
    EXPECT_GT(n2.compare(n4), 0);

    EXPECT_LT(n3.compare(n1), 0);
    EXPECT_GT(n3.compare(n2), 0);
    EXPECT_GT(n3.compare(n4), 0);

    EXPECT_LT(n4.compare(n1), 0);
    EXPECT_LT(n4.compare(n2), 0);
    EXPECT_LT(n4.compare(n3), 0);
}
