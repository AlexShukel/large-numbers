//
// Created by alexs on 2023-05-16.
//

#include "gtest/gtest.h"
#include "LargeFloatImplementation.h"

namespace LargeNumbers {
    class LargeFloatTester {
    public:
        static void
        testStringConversion(const std::string &number, bool expectedSign, const std::string &expectedMantissa,
                             exponent_type expectedExponent) {
            LargeNumbers::LargeFloatImplementation<uint8_t> realNumber(number);
            EXPECT_EQ(realNumber.mantissa.getSign(), expectedSign);
            EXPECT_EQ(realNumber.mantissa.toString(), expectedMantissa);
            EXPECT_EQ(realNumber.exponent, expectedExponent);
        }
    };
}

TEST(large_float, string_conversion) {
//    LargeNumbers::LargeFloatTester::testStringConversion("0.0", false, "0", 0);
//    LargeNumbers::LargeFloatTester::testStringConversion("1.0", false, "1", 0);
//    LargeNumbers::LargeFloatTester::testStringConversion("-1.0", true, "-1", 0);
//    LargeNumbers::LargeFloatTester::testStringConversion("256.0", false, "1", 1);
    // TODO: decide what to do with negative values
    LargeNumbers::LargeFloatTester::testStringConversion("-256.0", true, "", 1);
}
