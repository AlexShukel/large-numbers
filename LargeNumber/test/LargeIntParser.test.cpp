#include <gtest/gtest.h>
#include <string>
#include "LargeIntParser.h"

typedef uint8_t byte;
typedef LargeIntParser<byte> Parser;

// Should convert string to LargeIntMath class
TEST(LargeIntParser, convertFromString) {
    // Should throw error
    {
        std::vector<byte> coefficients;
        bool sign;

        std::string n1;
        EXPECT_ANY_THROW(Parser::fromString(coefficients, sign, n1));
        std::string n2 = "aaa";
        EXPECT_ANY_THROW(Parser::fromString(coefficients, sign, n2));
    }

    // Should fromString zero
    {
        std::string number = "0";
        std::vector<byte> coefficients;
        bool sign;

        Parser::fromString(coefficients, sign, number);
        EXPECT_EQ(coefficients.size(), 0);
        EXPECT_EQ(sign, false);
    }

    // Should fromString number
    {
        std::string number = "123";
        std::vector<byte> coefficients;
        bool sign;

        Parser::fromString(coefficients, sign, number);
        EXPECT_EQ(coefficients.size(), 1);
        EXPECT_EQ(coefficients[0], 123);
        EXPECT_EQ(sign, false);
    }

    // Should fromString negative number
    {
        std::string number = "-1";
        std::vector<byte> coefficients;
        bool sign;

        Parser::fromString(coefficients, sign, number);
        EXPECT_EQ(coefficients.size(), 1);
        EXPECT_EQ(coefficients[0], 255);
        EXPECT_EQ(sign, true);
    }

    // Should fromString large number
    {
        std::string number = "109823";
        std::vector<byte> coefficients;
        bool sign;

        Parser::fromString(coefficients, sign, number);
        EXPECT_EQ(coefficients.size(), 3);
        EXPECT_EQ(coefficients[0], 255);
        EXPECT_EQ(coefficients[1], 172);
        EXPECT_EQ(coefficients[2], 1);
        EXPECT_EQ(sign, false);
    }
}

// Should convert integer to LargeIntMath class
TEST(LargeIntParser, convertFromInteger) {
    // Should convert zero
    {
        int number = 0;
        std::vector<byte> coefficients;
        bool sign;
        Parser::fromInteger(coefficients, sign, number);
        EXPECT_EQ(coefficients.size(), 1);
        EXPECT_EQ(coefficients[0], 0);
    }

    // Should convert a number
    {
        int number = 244;
        std::vector<byte> coefficients;
        bool sign;
        Parser::fromInteger(coefficients, sign, number);
        EXPECT_EQ(coefficients.size(), 1);
        EXPECT_EQ(coefficients[0], 244);
    }

    // Should convert negative number
    {
        int number = -255;
        std::vector<byte> coefficients;
        bool sign;
        Parser::fromInteger(coefficients, sign, number);
        EXPECT_EQ(coefficients.size(), 1);
        EXPECT_EQ(coefficients[0], 1);
    }
}

TEST(LargeIntParser, convertToString) {
    {
        std::vector<byte> coefficients = {0};
        EXPECT_EQ(Parser::toString(coefficients, false), "0");
    }

    {
        std::vector<byte> coefficients = {13};
        EXPECT_EQ(Parser::toString(coefficients, false), "13");
    }

    {
        std::vector<byte> coefficients = {10};
        EXPECT_EQ(Parser::toString(coefficients, true), "-246");
    }

    {
        std::vector<byte> coefficients = {100, 3, 3, 3};
        EXPECT_EQ(Parser::toString(coefficients, false), "50529124");
    }
}
