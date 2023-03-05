#include <gtest/gtest.h>
#include <string>
#include <bitset>
#include "LargeDoubleParser.h"
#include "config.h"
#include "testUtils.h"

typedef uint8_t byte;
typedef LargeDoubleParser<byte> Parser;

TEST(LargeDoubleParser, getFractionCoefficients) {
    {
        std::vector<byte> coefficients;
        std::string fraction = "0";
        Parser::getFractionCoefficients(coefficients, fraction);
        expectVectorsEquality(coefficients, {});
    }

    {
        std::vector<byte> coefficients;
        std::string fraction = "5";
        Parser::getFractionCoefficients(coefficients, fraction);
        EXPECT_EQ(coefficients.size(), 1);
        EXPECT_EQ(coefficients[0], 128);
    }

    {
        std::vector<byte> coefficients;
        std::string fraction = "25";
        Parser::getFractionCoefficients(coefficients, fraction);
        EXPECT_EQ(coefficients.size(), 1);
        EXPECT_EQ(coefficients[0], 64);
    }

    {
        std::vector<byte> coefficients;
        std::string fraction = "125";
        Parser::getFractionCoefficients(coefficients, fraction);
        EXPECT_EQ(coefficients.size(), 1);
        EXPECT_EQ(coefficients[0], 32);
    }

    {
        std::vector<byte> coefficients;
        std::string fraction = "2";
        Parser::getFractionCoefficients(coefficients, fraction);
        EXPECT_EQ(coefficients.size(), Parser::getPrecision());
        unsigned long periodicValue = std::bitset<8>(0b00110011).to_ulong();
        for (auto c: coefficients) {
            EXPECT_EQ(c, periodicValue);
        }
    }
}

TEST(LargeDoubleParser, convertFromString) {
    {
        std::string number = "0.0";
        LargeDoubleMath<byte> myNumber = Parser::fromString(number);
        EXPECT_EQ(myNumber.getMantissa().getCoefficients().size(), 0);
        EXPECT_EQ(myNumber.getExponent(), 1);
        EXPECT_EQ(myNumber.getSign(), false);
    }

    {
        std::string number = "0.25";
        LargeDoubleMath<byte> myNumber = Parser::fromString(number);
        EXPECT_EQ(myNumber.getMantissa().getCoefficients().size(), 1);
        EXPECT_EQ(myNumber.getMantissa().getCoefficients()[0], 64);
        EXPECT_EQ(myNumber.getExponent(), 0);
        EXPECT_EQ(myNumber.getSign(), false);
    }

    {
        std::string number = "256.0";
        LargeDoubleMath<byte> myNumber = Parser::fromString(number);
        EXPECT_EQ(myNumber.getMantissa().getCoefficients().size(), 1);
        EXPECT_EQ(myNumber.getMantissa().getCoefficients()[0], 1);
        EXPECT_EQ(myNumber.getExponent(), 2);
        EXPECT_EQ(myNumber.getSign(), false);
    }
}

TEST(LargeDoubleParser, convertToString) {
    {
        EXPECT_EQ(Parser::toString(LargeDoubleMath<byte>("12341.1")), "12341.1");
    }

    {
        EXPECT_EQ(Parser::toString(LargeDoubleMath<byte>("0.0")), "0.0");
    }

    {
        EXPECT_EQ(Parser::toString(LargeDoubleMath<byte>("123.0")), "123.0");
    }

    {
        EXPECT_EQ(Parser::toString(LargeDoubleMath<byte>("-5.5")), "-5.5");
    }

    {
        EXPECT_EQ(Parser::toString(LargeDoubleMath<byte>("-000000000000.5")), "-0.5");
    }

    {
        EXPECT_EQ(Parser::toString(LargeDoubleMath<byte>("-0.0005")), "-0.0005");
    }
}
