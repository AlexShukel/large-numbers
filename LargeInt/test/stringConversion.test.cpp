//
// Created by alexs on 2023-05-14.
//

#include "gtest/gtest.h"
#include "LargeIntImplementation.h"
#include "testUtils.h"

namespace LargeNumbers {
    class LargeIntTester {
    public:
        template<class T>
        static void testStringConversion(const std::string &number, bool expectedSign,
                                         const std::vector<T> &expectedCoefficients) {
            testStringConversion(number, expectedSign, expectedCoefficients, number);
        }

        template<class T>
        static void testStringConversion(const std::string &number, bool expectedSign,
                                         const std::vector<T> &expectedCoefficients,
                                         const std::string &expectedNumber) {
            LargeNumbers::LargeIntImplementation<T> integer(number);
            expectVectorsEquality(integer.coefficients, expectedCoefficients);
            EXPECT_EQ(integer.sign, expectedSign);
            EXPECT_EQ(integer.toString(), expectedNumber);
        }
    };
}

TEST(large_int, string_conversion) {
    LargeNumbers::LargeIntTester::testStringConversion<uint8_t>("0", false, {0});
    LargeNumbers::LargeIntTester::testStringConversion<uint8_t>("1", false, {1});
    LargeNumbers::LargeIntTester::testStringConversion<uint8_t>("255", false, {255});
    LargeNumbers::LargeIntTester::testStringConversion<uint8_t>("256", false, {0, 1});
    LargeNumbers::LargeIntTester::testStringConversion<uint8_t>("257", false, {1, 1});
    LargeNumbers::LargeIntTester::testStringConversion<uint8_t>("300", false, {44, 1});
    LargeNumbers::LargeIntTester::testStringConversion<uint8_t>("1025", false, {1, 4});
    LargeNumbers::LargeIntTester::testStringConversion<uint8_t>("67268955", false, {91, 113, 2, 4});
    LargeNumbers::LargeIntTester::testStringConversion<uint8_t>("72057594037927935", false, {255, 255, 255, 255, 255, 255, 255});
    LargeNumbers::LargeIntTester::testStringConversion<uint8_t>("18446744073709551615", false,
                                                       {255, 255, 255, 255, 255, 255, 255, 255});
    LargeNumbers::LargeIntTester::testStringConversion<uint8_t>("18446744073709551616", false,
                                                       {0, 0, 0, 0, 0, 0, 0, 0, 1});

    // Negative numbers are stored in two's complement form
    LargeNumbers::LargeIntTester::testStringConversion<uint8_t>("-1", true, {255});
    LargeNumbers::LargeIntTester::testStringConversion<uint8_t>("-255", true, {1});
    LargeNumbers::LargeIntTester::testStringConversion<uint8_t>("-256", true, {0, 255});
    LargeNumbers::LargeIntTester::testStringConversion<uint8_t>("-65536", true, {0, 0, 255});
    LargeNumbers::LargeIntTester::testStringConversion<uint8_t>("-257", true, {255, 254});

    // Zeros should not be taken into account
    LargeNumbers::LargeIntTester::testStringConversion<uint8_t>("-01", true, {255}, "-1");
    LargeNumbers::LargeIntTester::testStringConversion<uint8_t>("-000000001", true, {255}, "-1");
    LargeNumbers::LargeIntTester::testStringConversion<uint8_t>("01", false, {1}, "1");
    LargeNumbers::LargeIntTester::testStringConversion<uint8_t>("00000000001", false, {1}, "1");
}

TEST(large_int, string_conversion_32_t) {
    LargeNumbers::LargeIntTester::testStringConversion<uint32_t>("0", false, {0});
    LargeNumbers::LargeIntTester::testStringConversion<uint32_t>("1", false, {1});
    LargeNumbers::LargeIntTester::testStringConversion<uint32_t>("4294967296", false, {0, 1});
    LargeNumbers::LargeIntTester::testStringConversion<uint32_t>("-4294967296", true, {0, 4294967295});
    LargeNumbers::LargeIntTester::testStringConversion<uint32_t>("18446744073709551616", false, {0, 0, 1});
}
