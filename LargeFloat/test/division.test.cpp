//
// Created by Aleksandras on 2023-06-22.
//

#include "gtest/gtest.h"
#include "LargeFloatImplementation.h"

TEST(large_float, division_basic) {
    LargeNumbers::LargeFloatImplementation<uint32_t> zero("0.0");
    LargeNumbers::LargeFloatImplementation<uint32_t> n1("1.0");
    LargeNumbers::LargeFloatImplementation<uint32_t> n2("2.0");
    LargeNumbers::LargeFloatImplementation<uint32_t> n3("4.0");
    LargeNumbers::LargeFloatImplementation<uint32_t> n4("0.0625");

    EXPECT_THROW(n1.divide(zero), std::logic_error);

    n1.divide(n1);
    EXPECT_EQ(n1.toString(), "1.0");

    n1.divide(n2);
    EXPECT_EQ(n1.toString(), "0.5");

    n1.divide(n1);
    EXPECT_EQ(n1.toString(), "1.0");

    n1.divide(n3);
    EXPECT_EQ(n1.toString(), "0.25");

    n1.divide(n4);
    EXPECT_EQ(n1.toString(), "4.0");
}

TEST(large_float, division_without_fraction) {
    LargeNumbers::LargeFloatImplementation<uint32_t> n1("256.0");
    LargeNumbers::LargeFloatImplementation<uint32_t> n2("16.0");
    LargeNumbers::LargeFloatImplementation<uint32_t> n3("-7.0");
    LargeNumbers::LargeFloatImplementation<uint32_t> n4("10.0");
    LargeNumbers::LargeFloatImplementation<uint32_t> one("1.0");

    n1.divide(one);
    EXPECT_EQ(n1.toString(), "256.0");

    n1.divide(n2);
    EXPECT_EQ(n1.toString(), "16.0");

    n1.divide(n3);
    EXPECT_EQ(n1.toString(),
              "-2.2857142857142857142857142857142857142857142857142857142857142857142857142857142857142857142857142857");

    n1 = LargeNumbers::LargeFloatImplementation<uint32_t>("1000.0");

    n1.divide(n4);
    EXPECT_EQ(n1.toString(), "100.0");
}

TEST(large_float, division_large_numbers) {
    LargeNumbers::LargeFloatImplementation<uint32_t> n1("456423123.1534867456123");
    LargeNumbers::LargeFloatImplementation<uint32_t> n2("1254.332335");

    n1.divide(n2);

    EXPECT_EQ(n1.toString(), "363877.3476675834443925899430791601174819430928566471181658567384376645285158817180615853293776405756134797");
}
