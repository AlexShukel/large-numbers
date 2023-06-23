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

    LargeFloat::LargeFloat(const std::string &number) : implementation(
            new Implementation(LargeFloatImplementation<CoefficientType>(number))) {}

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

    LargeFloat::LargeFloat(int n) : implementation(new Implementation(LargeFloatImplementation<CoefficientType>(n))) {}

    LargeFloat::LargeFloat(const LargeInt &n) : implementation(nullptr) {
        std::string decimal = n.toString();
        decimal += ".0";
        *this = LargeFloat(decimal);
    }

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

    LargeFloat LargeFloat::operator/(const LargeNumbers::LargeFloat &other) const {
        LargeFloat copy = *this;
        copy /= other;
        return copy;
    }

    LargeFloat &LargeFloat::operator/=(const LargeNumbers::LargeFloat &other) {
        implementation->math.divide(other.implementation->math);
        return *this;
    }

    LargeFloat LargeFloat::operator+(const LargeNumbers::LargeFloat &other) const {
        LargeFloat copy = *this;
        copy += other;
        return copy;
    }

    LargeFloat &LargeFloat::operator+=(const LargeNumbers::LargeFloat &other) {
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
        if (copy.implementation->math.isNegative()) {
            copy.implementation->math.negate();
        }
        return copy;
    }

    LargeFloat LargeFloat::operator-(const LargeNumbers::LargeFloat &other) const {
        LargeFloat copy = *this;
        copy -= other;
        return copy;
    }

    LargeFloat &LargeFloat::operator-=(const LargeNumbers::LargeFloat &other) {
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
        implementation->math.ceil();
    }
}
