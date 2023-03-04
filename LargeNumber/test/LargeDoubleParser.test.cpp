#include <gtest/gtest.h>
#include <string>
#include "LargeDoubleParser.h"
#include "LargeIntMath.h"
#include "config.h"

typedef uint8_t byte;
typedef LargeDoubleParser<byte> Parser;

// Should convert string to LargeDoubleMath
TEST(LargeDoubleParser, convertFromString) {
    // Should throw error
    {
        LargeIntMath<byte> mantissa;
        exponent_type exponent;
        bool sign;

        std::string n1 = "";
        std::string n2 = "0";
        std::string n3 = ".";
        std::string n4 = ".0";
        EXPECT_ANY_THROW(Parser::fromString(mantissa, exponent, sign, n1));
        EXPECT_ANY_THROW(Parser::fromString(mantissa, exponent, sign, n2));
        EXPECT_ANY_THROW(Parser::fromString(mantissa, exponent, sign, n3));
        EXPECT_ANY_THROW(Parser::fromString(mantissa, exponent, sign, n4));
    }

    {
        LargeIntMath<byte> mantissa;
        exponent_type exponent;
        bool sign;
        std::string number = "0.0";

        Parser::fromString(mantissa, exponent, sign, number);

        EXPECT_EQ(mantissa.toString(), "0");
        EXPECT_EQ(exponent, -1);
        EXPECT_EQ(sign, false);
    }

    {
        LargeIntMath<byte> mantissa;
        exponent_type exponent;
        bool sign;
        std::string number = "-0.0";

        Parser::fromString(mantissa, exponent, sign, number);

        EXPECT_EQ(mantissa.toString(), "0");
        EXPECT_EQ(exponent, -1);
        EXPECT_EQ(sign, true);
    }

    {
        LargeIntMath<byte> mantissa;
        exponent_type exponent;
        bool sign;
        std::string number = "0.25";

        Parser::fromString(mantissa, exponent, sign, number);

        EXPECT_EQ(mantissa.toString(), "16384");
        EXPECT_EQ(exponent, -1);
        EXPECT_EQ(sign, false);
    }

    {
        LargeIntMath<byte> mantissa;
        exponent_type exponent;
        bool sign;
        std::string number = "0.5";

        Parser::fromString(mantissa, exponent, sign, number);

        EXPECT_EQ(mantissa.toString(), "32768");
        EXPECT_EQ(exponent, -1);
        EXPECT_EQ(sign, false);
    }

    {
        LargeIntMath<byte> mantissa;
        exponent_type exponent;
        bool sign;
        std::string number = "0.1";

        Parser::fromString(mantissa, exponent, sign, number);

        EXPECT_EQ(exponent, -41);
        EXPECT_EQ(sign, false);
    }
}
