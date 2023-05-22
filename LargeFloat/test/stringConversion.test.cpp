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
    };
}

TEST(large_float, string_conversion_no_fraction) {
    LargeNumbers::LargeFloatTester::detailedTestStringConversion("0.0", false, {0}, 0);
    LargeNumbers::LargeFloatTester::detailedTestStringConversion("1.0", false, {1}, 0);
    LargeNumbers::LargeFloatTester::detailedTestStringConversion("-1.0", true, {255}, 0);
    LargeNumbers::LargeFloatTester::detailedTestStringConversion("256.0", false, {1}, 1);
    LargeNumbers::LargeFloatTester::detailedTestStringConversion("-256.0", true, {255}, 1);
    LargeNumbers::LargeFloatTester::detailedTestStringConversion("-257.0", true, {255, 254}, 1);
}

TEST(large_float, string_conversion_with_fraction) {
    LargeNumbers::LargeFloatTester::detailedTestStringConversion("0.5", false, {128}, -1);
    LargeNumbers::LargeFloatTester::detailedTestStringConversion("0.25", false, {64}, -1);
    LargeNumbers::LargeFloatTester::detailedTestStringConversion("0.125", false, {32}, -1);
    LargeNumbers::LargeFloatTester::detailedTestStringConversion("0.0625", false, {16}, -1);
    LargeNumbers::LargeFloatTester::detailedTestStringConversion("0.03125", false, {8}, -1);

    LargeNumbers::LargeFloatTester::detailedTestStringConversion("-0.5", true, {128}, -1);
    LargeNumbers::LargeFloatTester::detailedTestStringConversion("-0.25", true, {192}, -1);
    LargeNumbers::LargeFloatTester::detailedTestStringConversion("-0.125", true, {224}, -1);

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
