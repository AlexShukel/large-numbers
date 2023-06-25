//
// Created by alexs on 2023-05-16.
//

#include "LargeFloat.h"
#include "LargeFloatImplementation.h"
#include "config.h"

namespace LargeNumbers {
    class LargeFloat::Implementation {
    public:
        LargeFloatImplementation<CoefficientType> math;

        Implementation() = default;

        explicit Implementation(const LargeFloatImplementation<CoefficientType> &impl) : math(impl) {}
    };

    const LargeFloat LargeFloat::epsilon = LargeFloat(
            new Implementation(LargeFloatImplementation<CoefficientType>(
                    "0.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001")));

    // uint_8_t pi representation
    const LargeFloat LargeFloat::pi = LargeFloat(
            new Implementation(LargeFloatImplementation<CoefficientType>(LargeIntImplementation<CoefficientType>(
                    {141, 72, 86, 253, 82, 1, 121, 177, 12, 57, 203, 15, 222, 146, 191, 13, 183, 170, 153, 141, 112,
                     153, 104,
                     218, 216, 37, 2, 217, 215, 48, 247, 92, 10, 145, 101, 79, 142, 107, 43, 166, 86, 96, 104, 84, 190,
                     119, 19,
                     208, 56, 230, 33, 40, 69, 137, 108, 78, 236, 152, 250, 46, 8, 208, 49, 159, 41, 34, 56, 9, 164, 68,
                     115,
                     112, 3, 46, 138, 25, 19, 211, 8, 163, 133, 136, 106, 63, 36, 3}, false), 0)));

    // uint_32_t pi representation
//    const LargeFloat LargeFloat::pi = LargeFloat(
//            new Implementation(LargeFloatImplementation<CoefficientType>(LargeIntImplementation<CoefficientType>(
//                    {2073271439, 1392334408, 212957441, 3725577017, 3071131538, 1888328106, 3638192281, 3621323301,
//                     173864752, 2387568017, 1453730667, 3193202784, 953160567, 1160258022, 3964562569, 137296536,
//                     698298832, 2752067618, 57701188, 320440878, 2242054355, 608135816, 3}, false), 0)));


    LargeFloat::LargeFloat() : implementation(new Implementation()) {}

    LargeFloat::LargeFloat(const LargeFloat &other) : implementation(
            new Implementation(*other.implementation)) {}

    LargeFloat &LargeFloat::operator=(const LargeFloat &other) {
        if (&other != this) {
            delete implementation;
            implementation = new Implementation(*other.implementation);
        }

        return *this;
    }

    LargeFloat::LargeFloat(LargeFloat &&other) noexcept: implementation(other.implementation) {
        other.implementation = nullptr;
    }

    LargeFloat &LargeFloat::operator=(LargeFloat &&other) noexcept {
        if (&other != this) {
            delete implementation;
            implementation = other.implementation;
            other.implementation = nullptr;
        }

        return *this;
    }

    LargeFloat::LargeFloat(const std::string &number) : implementation(
            new Implementation(LargeFloatImplementation<CoefficientType>(number))) {}

    LargeFloat::LargeFloat(const LargeInt &n) : implementation(nullptr) {
        // TODO: optimize conversion
        std::string decimal = n.toString();
        decimal += ".0";
        *this = LargeFloat(decimal);
    }

    LargeFloat::LargeFloat(LargeFloat::Implementation *impl) : implementation(impl) {}

    LargeFloat::LargeFloat(int n) : implementation(new Implementation(LargeFloatImplementation<CoefficientType>(n))) {}

    LargeFloat::LargeFloat(double n) : implementation(
            new Implementation(LargeFloatImplementation<CoefficientType>(n))) {}

    LargeFloat::~LargeFloat() {
        delete implementation;
    }

    std::string LargeFloat::toString() const {
        return this->implementation->math.toString();
    }

    LargeFloat LargeFloat::operator*(const LargeFloat &multiplier) const {
        LargeFloat copy = *this;
        copy *= multiplier;
        return copy;
    }

    LargeFloat &LargeFloat::operator*=(const LargeFloat &multiplier) {
        implementation->math.multiply(multiplier.implementation->math);
        return *this;
    }

    LargeFloat LargeFloat::operator/(const LargeFloat &other) const {
        LargeFloat copy = *this;
        copy /= other;
        return copy;
    }

    LargeFloat &LargeFloat::operator/=(const LargeFloat &other) {
        implementation->math.divide(other.implementation->math);
        return *this;
    }

    LargeFloat LargeFloat::operator+(const LargeFloat &other) const {
        LargeFloat copy = *this;
        copy += other;
        return copy;
    }

    LargeFloat &LargeFloat::operator+=(const LargeFloat &other) {
        implementation->math.add(other.implementation->math);
        return *this;
    }

    LargeFloat &LargeFloat::operator++() {
        implementation->math.add(LargeFloatImplementation<CoefficientType>(1));
        return *this;
    }

    const LargeFloat LargeFloat::operator++(int) {
        LargeFloat copy = *this;
        ++(*this);
        return copy;
    }

    LargeFloat LargeFloat::operator+() const {
        LargeFloat copy = *this;
        if (copy.implementation->math.getSign()) {
            copy.implementation->math.negate();
        }
        return copy;
    }

    LargeFloat LargeFloat::operator-(const LargeFloat &other) const {
        LargeFloat copy = *this;
        copy -= other;
        return copy;
    }

    LargeFloat &LargeFloat::operator-=(const LargeFloat &other) {
        implementation->math.subtract(other.implementation->math);
        return *this;
    }

    LargeFloat &LargeFloat::operator--() {
        implementation->math.subtract(LargeFloatImplementation<CoefficientType>(1));
        return *this;
    }

    const LargeFloat LargeFloat::operator--(int) {
        LargeFloat copy = *this;
        --(*this);
        return copy;
    }

    LargeFloat LargeFloat::operator-() const {
        LargeFloat copy = *this;
        copy.implementation->math.negate();
        return copy;
    }

    bool LargeFloat::operator<(const LargeFloat &other) const {
        return implementation->math.compare(other.implementation->math) < 0;
    }

    bool LargeFloat::operator<=(const LargeFloat &other) const {
        return implementation->math.compare(other.implementation->math) <= 0;
    }

    bool LargeFloat::operator>(const LargeFloat &other) const {
        return implementation->math.compare(other.implementation->math) > 0;
    }

    bool LargeFloat::operator>=(const LargeFloat &other) const {
        return implementation->math.compare(other.implementation->math) >= 0;
    }

    bool LargeFloat::operator==(const LargeFloat &other) const {
        return implementation->math.compare(other.implementation->math) == 0;
    }

    bool LargeFloat::operator!=(const LargeFloat &other) const {
        return implementation->math.compare(other.implementation->math) != 0;
    }

    void LargeFloat::ceil() {
        implementation->math.floor();
        implementation->math.add(LargeFloatImplementation<CoefficientType>(1));
    }

    void LargeFloat::floor() {
        implementation->math.floor();
    }

    bool LargeFloat::isZero() const {
        return implementation->math.isZero();
    }

    LargeFloat LargeFloat::abs() const {
        LargeFloat copy = *this;

        if (copy.implementation->math.getSign()) {
            copy.implementation->math.negate();
        }

        return copy;
    }
}
