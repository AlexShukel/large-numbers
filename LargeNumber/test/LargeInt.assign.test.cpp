#include <gtest/gtest.h>
#include "LargeInt.h"

TEST(LargeInt, assignment) {
    LargeInt<uint8_t> a("123");
    LargeInt<uint8_t> b = a;
    EXPECT_EQ(b.toString(), "123");

    a = a;
    EXPECT_EQ(a.toString(), "123");

    a = LargeInt<uint8_t>("1");
    EXPECT_EQ(a.toString(), "1");
}
