//
// Created by alexs on 2023-06-21.
//

#include "LargeMath.h"
#include "bubbleSort.h"
#include <cassert>
#include <iostream>

using namespace LargeNumbers;

int myFind(LargeFloat *numbers, const LargeFloat &number, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        if (numbers[i] == number) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

void testFind() {
    LargeFloat numbers[] = {LargeFloat("512.0"), LargeFloat("0.0"), LargeFloat("1.5"), LargeFloat("-1.25")};
    const size_t n = sizeof(numbers) / sizeof(LargeFloat);
    assert(myFind(numbers, LargeFloat("1.5"), n) == 2);
    assert(myFind(numbers, LargeFloat("0.5"), n) == -1);
}

bool compare(const LargeFloat &a, const LargeFloat &b) {
    return a < b;
}

void checkArrayIsSorted(LargeFloat *arr, size_t n) {
    for (size_t i = 1; i < n; ++i) {
        assert(arr[i - 1] <= arr[i]);
    }
}

void testSort() {
    LargeFloat numbers[] = {LargeFloat("512.0"), LargeFloat("0.0"), LargeFloat("1.5"), LargeFloat("-1.25")};
    const size_t n = sizeof(numbers) / sizeof(LargeFloat);
    bubbleSort(numbers, numbers + n, compare);
    checkArrayIsSorted(numbers, n);
}

LargeFloat findPrime(LargeFloat n) {
    n.floor();

    std::string decimal = n.toString();
    decimal.erase(decimal.end() - 2, decimal.end());
    LargeInt integer(decimal);

    return LargeFloat(LargeNumbers::nextPrime(integer));
}

void testPrime() {
    assert(findPrime(LargeFloat("0.0")).toString() == "2.0");
    assert(findPrime(LargeFloat("0.1")).toString() == "2.0");
    assert(findPrime(LargeFloat(
            "1.9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999")).toString() ==
           "2.0");
    assert(findPrime(LargeFloat("2.15")).toString() == "3.0");
    assert(findPrime(LargeFloat("6.33")).toString() == "7.0");
    assert(findPrime(LargeFloat("3275.0")).toString() == "3299.0");
    assert(findPrime(LargeFloat("6920.0")).toString() == "6947.0");
}

void testFactorial() {
    assert(factorial(LargeInt(0)).toString() == "1");
    assert(factorial(LargeInt(1)).toString() == "1");
    assert(factorial(LargeInt(2)).toString() == "2");
    assert(factorial(LargeInt(3)).toString() == "6");
    assert(factorial(LargeInt(4)).toString() == "24");
    assert(factorial(LargeInt(5)).toString() == "120");
}

void testPow() {
    assert(pow(LargeFloat(0), 0).toString() == "1.0");
    assert(pow(LargeFloat("0.1"), 1).toString() == "0.1");
    assert(pow(LargeFloat("0.1"), 2).toString() == "0.01");
    assert(pow(LargeFloat("0.1"), 3).toString() == "0.001");
    assert(pow(LargeFloat("1.1"), 3).toString() == "1.331");
    assert(pow(LargeFloat("94567342.94567132595"), 4).toString() ==
           "79976933344681599935603491186526.49198674427702399196065870258573151927700625");
}

void testLn() {
    assert(ln(LargeFloat(1)).toString() == "0.0");
    assert(ln(LargeFloat(0.5)).toString() ==
           "-0.6931471805599453094172321214581765680755001343602552541206800094933936219696947156058633269964186875");
    assert(ln(LargeFloat("1.1")).toString() ==
           "0.0953101798043248600439521232807650922206053653086441991852398081630010142358842328390575029130364931");
}

void testSin() {
    assert(sin(LargeFloat(0)).toString() == "0.0");
    assert(sin(LargeFloat(1)).toString() == "0.8414709848078965066525023216302989996225630607983710656727517099919104043912396689486397435430526959");
    assert(sin(LargeFloat(2)).toString() == "0.9092974268256816953960198659117448427022549714478902683789730115309673015407835446201266889249593803");
    assert(sin(LargeFloat(6)).toString() == "-0.2794154981989258728115554466118947596279948643182043184833513696533111540586443348546689384528422476");

    assert(sin(LargeFloat::pi / LargeFloat(2)).toString() == "1.0");
    assert(sin(LargeFloat::pi).toString() == "0.0");

    assert(sin(LargeFloat(7)).toString() == "0.6569865987187890903969990915936351779368700104974900746578543341892928371312270315099351216010552127");
    assert(sin(LargeFloat("0.5")).toString() == "0.4794255386042030002732879352155713880818033679406006751886166131255350002878148322096312746843482691");
    assert(sin(LargeFloat("-0.5")).toString() == "-0.4794255386042030002732879352155713880818033679406006751886166131255350002878148322096312746843482691");
}

void testAvg() {
    LargeFloat numbers[] = {LargeFloat("512.0"), LargeFloat("0.0"), LargeFloat("1.5"), LargeFloat("-1.25")};
    const int n = sizeof(numbers) / sizeof(LargeFloat);

    LargeFloat sum(0);

    for (const auto &number: numbers) {
        sum += number;
    }

    auto average = sum / LargeFloat(n);
    assert(average.toString() == "128.0625");
}

void testSqrt() {
    assert(sqrt(LargeFloat(1)).toString() == "1.0");
    assert(sqrt(LargeFloat(2)).toString() ==
           "1.4142135623730950488016887242096980785696718753769480731766797379907324784621070388503875343276415727");
    assert(sqrt(LargeFloat("0.5")).toString() ==
           "0.7071067811865475244008443621048490392848359376884740365883398689953662392310535194251937671638207864");
    assert(sqrt(LargeFloat(4)).toString() == "2.0");
    assert(sqrt(LargeFloat(13)).toString() ==
           "3.6055512754639892931192212674704959462512965738452462127104530562271669482930104452046190820184907177");
    assert(sqrt(LargeFloat("123.456")).toString() ==
           "11.1110755554986664846214940411821923411863251901176006838596002616709755161536775238954125654646046818");
}

void testPi() {
    assert(pi(1).toString() == "3.1");
    assert(pi(2).toString() == "3.14");

    assert(pi(50).toString() == "3.14159265358979323846264338327950288419716939937511");

    assert(pi(100).toString() ==
           "3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117068");
}

int main() {
    testFactorial();
    testPrime();
    testPow();
    testLn();
    testSin();
    testSqrt();
    testPi();
    testAvg();
    testFind();
    testSort();

    std::cout << "Tests passed successfully!" << std::endl;
    return 0;
}
