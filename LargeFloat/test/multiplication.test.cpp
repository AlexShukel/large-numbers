//
// Created by Aleksandras on 2023-06-15.
//

#include "gtest/gtest.h"
#include "LargeFloatImplementation.h"
#include <iostream>

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

LargeNumbers::LargeFloatImplementation<uint8_t> createNumber(const std::string &number) {
    LargeNumbers::LargeFloatImplementation<uint8_t> n(number);
    EXPECT_EQ(n.toString(), number);
    return n;
}

TEST(large_float, high_precision_multiplication_1) {
    LargeNumbers::LargeFloatImplementation<uint8_t>::setDecimalPrecision(100);

    auto n1 = createNumber(
            "0.1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");

    n1.multiply(n1);

    EXPECT_EQ(n1.toString(),
              "0.012345679012345679012345679012345679012345679012345679012345679012345679012345679012345679012345679");

    auto n2 = createNumber(
            "0.2222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222");

    n2.multiply(n2);

    EXPECT_EQ(n2.toString(),
              "0.049382716049382716049382716049382716049382716049382716049382716049382716049382716049382716049382716");
}

TEST(large_float, high_precision_multiplication_2) {
    auto n1 = createNumber(
            "83957209573290750932672903672903804891782184018250185601286.65823579237639207693267290672390673296723906");
    auto n2 = createNumber(
            "0.000000000000000000000000000057281572937653276930262869030632626000603602306023060234274923789048329");

    n1.multiply(n2);

    EXPECT_EQ(n1.toString(),
              "4809201023814296104800879450164.8568490188916090045886280654749145987365251461528353043880702676055919495861824042646682142216209717");
}

TEST(large_float, high_precision_multiplication_3) {
    LargeNumbers::LargeFloatImplementation<uint8_t>::setDecimalPrecision(100);

    LargeNumbers::LargeFloatImplementation<uint8_t> n1("2.3333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333");
    LargeNumbers::LargeFloatImplementation<uint8_t> n2("3.1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");

    n1.multiply(n2);

    EXPECT_EQ(n1.toString(),
              "7.2592592592592592592592592592592592592592592592592592592592592592592592592592592592592592592592592593");
}

TEST(large_float, multiplication_large_numbers) {
    auto n1 = createNumber("456486768454531453453.456465415416453123");
    auto n2 = createNumber("7874654153412.146551534564");

    n1.multiply(n2);
    EXPECT_EQ(n1.toString(), "3594675427188164949046079279342197.315943069945180624309620243372");

    n1.multiply(LargeNumbers::LargeFloatImplementation<uint8_t>("0.0"));
    EXPECT_EQ(n1.toString(), "0.0");
}
