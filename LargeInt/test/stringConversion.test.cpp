//
// Created by alexs on 2023-05-14.
//

#include "gtest/gtest.h"
#include "LargeIntImplementation.h"
#include "testUtils.h"

namespace LargeNumbers {
    class LargeIntTester {
    public:
        static void testStringConversion(const std::string &number, bool expectedSign,
                                         const std::vector<uint8_t> &expectedCoefficients) {
            LargeNumbers::LargeIntImplementation<uint8_t> integer(number);
            expectVectorsEquality(integer.coefficients, expectedCoefficients);
            EXPECT_EQ(integer.sign, expectedSign);
            EXPECT_EQ(integer.toString(), number);
        }
    };
}

TEST(large_int, string_conversion) {
    LargeNumbers::LargeIntTester::testStringConversion("0", false, {0});
    LargeNumbers::LargeIntTester::testStringConversion("1", false, {1});
    LargeNumbers::LargeIntTester::testStringConversion("255", false, {255});
    LargeNumbers::LargeIntTester::testStringConversion("256", false, {0, 1});
    LargeNumbers::LargeIntTester::testStringConversion("257", false, {1, 1});
    LargeNumbers::LargeIntTester::testStringConversion("300", false, {44, 1});
    LargeNumbers::LargeIntTester::testStringConversion("1025", false, {1, 4});
    LargeNumbers::LargeIntTester::testStringConversion("67268955", false, {91, 113, 2, 4});
    LargeNumbers::LargeIntTester::testStringConversion("72057594037927935", false, {255, 255, 255, 255, 255, 255, 255});
    LargeNumbers::LargeIntTester::testStringConversion("18446744073709551615", false,
                                                       {255, 255, 255, 255, 255, 255, 255, 255});
    LargeNumbers::LargeIntTester::testStringConversion("18446744073709551616", false,
                                                       {0, 0, 0, 0, 0, 0, 0, 0, 1});

    // Negative numbers are stored in two's complement form
    LargeNumbers::LargeIntTester::testStringConversion("-1", true, {255});
    LargeNumbers::LargeIntTester::testStringConversion("-255", true, {1});
    LargeNumbers::LargeIntTester::testStringConversion("-256", true, {0, 255});
    LargeNumbers::LargeIntTester::testStringConversion("-257", true, {255, 254});
}
