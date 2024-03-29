//
// Created by alexs on 2023-05-16.
//

#include "gtest/gtest.h"
#include "LargeFloatImplementation.h"
#include "testUtils.h"

namespace LargeNumbers {
    class LargeFloatTester {
    public:
        static void
        detailedTestStringConversion(const std::string &number, bool expectedSign,
                                     const std::vector<uint8_t> &expectedMantissaCoefficients,
                                     exponent_type expectedExponent) {
            LargeNumbers::LargeFloatImplementation<uint8_t> realNumber(number);
            EXPECT_EQ(realNumber.mantissa.getSign(), expectedSign);
            expectVectorsEquality(realNumber.mantissa.coefficients, expectedMantissaCoefficients);
            EXPECT_EQ(realNumber.exponent, expectedExponent);
            EXPECT_EQ(realNumber.toString(), number);
        }

        static void
        testStringConversion(const std::string &number) {
            LargeNumbers::LargeFloatImplementation<uint8_t> realNumber(number);
            EXPECT_EQ(realNumber.toString(), number);
        }

        static void
        testStringConversion(const std::string &number, const std::string &expected) {
            LargeNumbers::LargeFloatImplementation<uint8_t> realNumber(number);
            EXPECT_EQ(realNumber.toString(), expected);
        }
    };
}

TEST(large_float, string_conversion_no_fraction) {
    LargeNumbers::LargeFloatTester::detailedTestStringConversion("0.0", false, {0}, 0);
    LargeNumbers::LargeFloatTester::detailedTestStringConversion("1.0", false, {1}, 0);
    LargeNumbers::LargeFloatTester::detailedTestStringConversion("-1.0", true, {255}, 0);
    LargeNumbers::LargeFloatTester::detailedTestStringConversion("256.0", false, {1}, 1);
    LargeNumbers::LargeFloatTester::detailedTestStringConversion("-256.0", true, {255}, 1);
    LargeNumbers::LargeFloatTester::detailedTestStringConversion("-257.0", true, {255, 254}, 1);
    LargeNumbers::LargeFloatTester::detailedTestStringConversion("-65536.0", true, {255}, 2);
    LargeNumbers::LargeFloatTester::detailedTestStringConversion("65536.0", false, {1}, 2);
}

TEST(large_float, string_conversion_with_fraction) {
    LargeNumbers::LargeFloatTester::detailedTestStringConversion("0.5", false, {128}, -1);
    LargeNumbers::LargeFloatTester::detailedTestStringConversion("0.25", false, {64}, -1);
    LargeNumbers::LargeFloatTester::detailedTestStringConversion("0.125", false, {32}, -1);
    LargeNumbers::LargeFloatTester::detailedTestStringConversion("0.0625", false, {16}, -1);
    LargeNumbers::LargeFloatTester::detailedTestStringConversion("0.03125", false, {8}, -1);
    LargeNumbers::LargeFloatTester::detailedTestStringConversion("0.0078125", false, {2}, -1);

    LargeNumbers::LargeFloatTester::detailedTestStringConversion("-0.5", true, {128}, -1);
    LargeNumbers::LargeFloatTester::detailedTestStringConversion("-0.25", true, {192}, -1);
    LargeNumbers::LargeFloatTester::detailedTestStringConversion("-0.125", true, {224}, -1);
    LargeNumbers::LargeFloatTester::detailedTestStringConversion("-0.0625", true, {240}, -1);
    LargeNumbers::LargeFloatTester::detailedTestStringConversion("-0.03125", true, {248}, -1);
    LargeNumbers::LargeFloatTester::detailedTestStringConversion("-0.0078125", true, {254}, -1);

    LargeNumbers::LargeFloatTester::detailedTestStringConversion("0.75", false, {192}, -1);
    LargeNumbers::LargeFloatTester::detailedTestStringConversion("0.001953125", false, {128}, -2);
    LargeNumbers::LargeFloatTester::detailedTestStringConversion("-0.001953125", true, {128}, -2);

    LargeNumbers::LargeFloatTester::detailedTestStringConversion("1.001953125", false, {128, 0, 1}, 0);
    LargeNumbers::LargeFloatTester::detailedTestStringConversion("-1.001953125", true, {128, 255, 254}, 0);

    LargeNumbers::LargeFloatTester::detailedTestStringConversion("256.001953125", false, {128, 0, 0, 1}, 1);
    LargeNumbers::LargeFloatTester::detailedTestStringConversion("-256.001953125", true, {128, 255, 255, 254}, 1);

    LargeNumbers::LargeFloatTester::detailedTestStringConversion("259.001953125", false, {128, 0, 3, 1}, 1);
    LargeNumbers::LargeFloatTester::detailedTestStringConversion("-259.001953125", true, {128, 255, 252, 254}, 1);
}

TEST(large_float, float_rounding) {
    LargeNumbers::LargeFloatTester::testStringConversion("0.1");
    LargeNumbers::LargeFloatTester::testStringConversion("0.3");
    LargeNumbers::LargeFloatTester::testStringConversion("0.01");
    LargeNumbers::LargeFloatTester::testStringConversion("0.9");
    LargeNumbers::LargeFloatTester::testStringConversion("0.91");
    LargeNumbers::LargeFloatTester::testStringConversion("0.95");
    LargeNumbers::LargeFloatTester::testStringConversion("0.55555555555555555555555555555555555555555555555555");
    LargeNumbers::LargeFloatTester::testStringConversion("0.12345678912345678912345678912345678912345678912345");

    // 100 char precision
    LargeNumbers::LargeFloatTester::testStringConversion(
            "0.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");
    LargeNumbers::LargeFloatTester::testStringConversion(
            "0.9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999");
}

TEST(large_float, after_max_precision) {
    // 101 char precision
    LargeNumbers::LargeFloatImplementation<uint8_t>::setDecimalPrecision(100);

    LargeNumbers::LargeFloatTester::testStringConversion(
            "0.00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001",
            "0.0");

    LargeNumbers::LargeFloatTester::testStringConversion(
            "0.00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000004",
            "0.0");

    LargeNumbers::LargeFloatTester::testStringConversion(
            "0.00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000005",
            "0.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");

    LargeNumbers::LargeFloatTester::testStringConversion(
            "0.99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999991",
            "0.9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999");

    LargeNumbers::LargeFloatTester::testStringConversion(
            "0.99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999995",
            "1.0");

    LargeNumbers::LargeFloatTester::testStringConversion(
            "0.99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999",
            "1.0");

    LargeNumbers::LargeFloatTester::testStringConversion(
            "0.99999999999999999999999999999999999999989999999999999999999999999999999999999999999999999999999999995",
            "0.9999999999999999999999999999999999999999");
}
