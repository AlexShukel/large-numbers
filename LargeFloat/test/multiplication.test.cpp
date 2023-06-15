//
// Created by Aleksandras on 2023-06-15.
//

#include "gtest/gtest.h"
#include "LargeFloatImplementation.h"

TEST(large_float, multiplication_zero) {
    LargeNumbers::LargeFloatImplementation<uint8_t> number("0.0");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("1.0"));
    EXPECT_EQ(number.toString(), "0.0");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("-1.0"));
    EXPECT_EQ(number.toString(), "0.0");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("0.1"));
    EXPECT_EQ(number.toString(), "0.0");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("-0.1"));
    EXPECT_EQ(number.toString(), "0.0");

    number = LargeNumbers::LargeFloatImplementation<uint8_t>("1.0");
    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("0.0"));
    EXPECT_EQ(number.toString(), "0.0");

    number = LargeNumbers::LargeFloatImplementation<uint8_t>("-1.0");
    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("0.0"));
    EXPECT_EQ(number.toString(), "0.0");
}

TEST(large_float, multiplication_without_fraction) {
    LargeNumbers::LargeFloatImplementation<uint8_t> number("1.0");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("1.0"));
    EXPECT_EQ(number.toString(), "1.0");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("-1.0"));
    EXPECT_EQ(number.toString(), "-1.0");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("-1.0"));
    EXPECT_EQ(number.toString(), "1.0");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("2.0"));
    EXPECT_EQ(number.toString(), "2.0");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("-2.0"));
    EXPECT_EQ(number.toString(), "-4.0");

    number = LargeNumbers::LargeFloatImplementation<uint8_t>("2.0");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("256.0"));
    EXPECT_EQ(number.toString(), "512.0");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("-2.0"));
    EXPECT_EQ(number.toString(), "-1024.0");
}

TEST(large_float, multiplication_with_fraction) {
    LargeNumbers::LargeFloatImplementation<uint8_t> number("0.1");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("0.1"));
    EXPECT_EQ(number.toString(), "0.01");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("0.01"));
    EXPECT_EQ(number.toString(), "0.0001");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("10000.0"));
    EXPECT_EQ(number.toString(), "1.0");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("0.0625"));
    EXPECT_EQ(number.toString(), "0.0625");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("0.0625"));
    EXPECT_EQ(number.toString(), "0.00390625");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("0.1"));
    EXPECT_EQ(number.toString(), "0.000390625");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("10.0"));
    EXPECT_EQ(number.toString(), "0.00390625");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("-2.0"));
    EXPECT_EQ(number.toString(), "-0.0078125");
}

TEST(large_float, multiplication_mixed) {
    LargeNumbers::LargeFloatImplementation<uint8_t> number("1.1");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("1.1"));
    EXPECT_EQ(number.toString(), "1.21");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("-2.223"));
    EXPECT_EQ(number.toString(), "-2.68983");
}

TEST(large_float, multiplication_large_numbers) {
    LargeNumbers::LargeFloatImplementation<uint8_t> number("456486768454531453453.456465415416453123");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("7874654153412.146551534564"));
    EXPECT_EQ(number.toString(), "3594675427188164949046079279342197.315943069945180624309620243372");

    number.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("0.0"));
    EXPECT_EQ(number.toString(), "0.0");
}
