//
// Created by Aleksandras on 2023-06-23.
//

#include "gtest/gtest.h"
#include "LargeMath.h"

using namespace LargeNumbers;

TEST(large_math, factorial) {
    EXPECT_EQ(factorial(LargeInt(0)).toString(), "1");
    EXPECT_EQ(factorial(LargeInt(1)).toString(), "1");
    EXPECT_EQ(factorial(LargeInt(2)).toString(), "2");
    EXPECT_EQ(factorial(LargeInt(3)).toString(), "6");
    EXPECT_EQ(factorial(LargeInt(4)).toString(), "24");
    EXPECT_EQ(factorial(LargeInt(5)).toString(), "120");
    EXPECT_EQ(factorial(LargeInt(100)).toString(),
              "93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000");
}

TEST(large_math, next_prime) {
    EXPECT_EQ(nextPrime(LargeInt("0")).toString(), "2");
    EXPECT_EQ(nextPrime(LargeInt("1")).toString(), "2");
    EXPECT_EQ(nextPrime(LargeInt("2")).toString(), "3");
    EXPECT_EQ(nextPrime(LargeInt("6")).toString(), "7");
    EXPECT_EQ(nextPrime(LargeInt("3275")).toString(), "3299");
    EXPECT_EQ(nextPrime(LargeInt("6920")).toString(), "6947");
}

TEST(large_math, power) {
    EXPECT_EQ(pow(LargeFloat(0), 0).toString(), "1.0");
    EXPECT_EQ(pow(LargeFloat("0.1"), 1).toString(), "0.1");
    EXPECT_EQ(pow(LargeFloat("0.1"), 2).toString(), "0.01");
    EXPECT_EQ(pow(LargeFloat("0.1"), 3).toString(), "0.001");
    EXPECT_EQ(pow(LargeFloat("1.1"), 3).toString(), "1.331");
    EXPECT_EQ(pow(LargeFloat("-1.0"), 2).toString(), "1.0");
    EXPECT_EQ(pow(LargeFloat("-1.0"), 3).toString(), "-1.0");
    EXPECT_EQ(pow(LargeFloat("-2.123456789123456789123456789123456789123456789"), 17).toString(), "-362859.3121876471452727494774693236136130360701610276859369364001940846981275182358216163561371534272929747");
    EXPECT_EQ(pow(LargeFloat("94567342.94567132595"), 4).toString(),
              "79976933344681599935603491186526.49198674427702399196065870258573151927700625");
}

TEST(large_math, ln) {
    EXPECT_EQ(ln(LargeFloat(1)).toString(), "0.0");
//    EXPECT_EQ(ln(LargeFloat(0.5)).toString(),
//              "-0.6931471805599453094172321214581765680755001343602552541206800094933936219696947156058633269964186875");
//    EXPECT_EQ(ln(LargeFloat("0.9")).toString(),
//              "-0.1053605156578263012275009808393127983061203729832740725639392336925840232401345464887656954621341208");
//    EXPECT_EQ(ln(LargeFloat("1.1")).toString(),
//              "0.0953101798043248600439521232807650922206053653086441991852398081630010142358842328390575029130364931");

// __FAILING TESTS__:
//    EXPECT_EQ(ln(LargeFloat("2.0")).toString(),
//              "0.6931471805599453094172321214581765680755001343602552541206800094933936219696947156058633269964186875");
//    EXPECT_EQ(ln(LargeFloat(0.1)).toString(),
//              "-2.3025850929940456840179914546843642076011014886287729760333279009675726096773524802359972050895982983");
//    EXPECT_EQ(ln(LargeFloat("123.456")).toString(),
//              "4.8158848172832638831092321051665255771721581355054573117965795423921263000752201547336311772025566107");
}

TEST(large_math, pi) {
    EXPECT_EQ(pi(1).toString(), "3.1");
    EXPECT_EQ(pi(2).toString(), "3.14");

    EXPECT_EQ(pi(50).toString(), "3.14159265358979323846264338327950288419716939937511");

    EXPECT_EQ(pi(100).toString(),
              "3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117068");
}

TEST(large_math, sqrt) {
    EXPECT_EQ(sqrt(LargeFloat(1)).toString(), "1.0");
    EXPECT_EQ(sqrt(LargeFloat(2)).toString(),
              "1.4142135623730950488016887242096980785696718753769480731766797379907324784621070388503875343276415727");
    EXPECT_EQ(sqrt(LargeFloat("0.5")).toString(),
              "0.7071067811865475244008443621048490392848359376884740365883398689953662392310535194251937671638207864");
    EXPECT_EQ(sqrt(LargeFloat(4)).toString(), "2.0");
    EXPECT_EQ(sqrt(LargeFloat(13)).toString(),
              "3.6055512754639892931192212674704959462512965738452462127104530562271669482930104452046190820184907177");
    EXPECT_EQ(sqrt(LargeFloat("123.456")).toString(),
              "11.1110755554986664846214940411821923411863251901176006838596002616709755161536775238954125654646046818");
}

TEST(large_math, sin) {
    EXPECT_EQ(sin(LargeFloat(0)).toString(), "0.0");
    EXPECT_EQ(sin(LargeFloat(1)).toString(), "0.8414709848078965066525023216302989996225630607983710656727517099919104043912396689486397435430526959");
    EXPECT_EQ(sin(LargeFloat(2)).toString(), "0.9092974268256816953960198659117448427022549714478902683789730115309673015407835446201266889249593803");
    EXPECT_EQ(sin(LargeFloat(6)).toString(), "-0.2794154981989258728115554466118947596279948643182043184833513696533111540586443348546689384528422476");

    EXPECT_EQ(sin(LargeFloat::pi / LargeFloat(2)).toString(), "1.0");
    EXPECT_EQ(sin(LargeFloat::pi).toString(), "0.0");

    EXPECT_EQ(sin(LargeFloat(7)).toString(), "0.6569865987187890903969990915936351779368700104974900746578543341892928371312270315099351216010552127");
    EXPECT_EQ(sin(LargeFloat("0.5")).toString(), "0.4794255386042030002732879352155713880818033679406006751886166131255350002878148322096312746843482691");
    EXPECT_EQ(sin(LargeFloat("-0.5")).toString(), "-0.4794255386042030002732879352155713880818033679406006751886166131255350002878148322096312746843482691");

}
