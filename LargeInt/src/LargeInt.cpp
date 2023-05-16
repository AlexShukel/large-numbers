//
// Created by alexs on 2023-05-14.
//

#include "LargeInt.h"
#include "LargeIntImplementation.h"
#include "config.h"

namespace LargeNumbers {
    class LargeInt::Implementation {
    public:
        LargeIntImplementation<CoefficientType> math;

        Implementation() = default;

        explicit Implementation(const LargeIntImplementation<CoefficientType> &impl) : math(impl) {}
    };

    LargeInt::LargeInt() : implementation(new Implementation()) {}

    LargeInt::LargeInt(const LargeInt &other) : implementation(new Implementation(*other.implementation)) {}

    LargeInt::LargeInt(const std::string &number) : implementation(
            new Implementation(LargeIntImplementation<CoefficientType>(number))) {}

    LargeInt::~LargeInt() {
        delete implementation;
    }

    LargeInt &LargeInt::operator=(const LargeNumbers::LargeInt &other) {
        if (implementation != other.implementation) {
            delete implementation;
            implementation = new Implementation(*other.implementation);
        }

        return *this;
    }

    LargeInt LargeInt::operator+(const LargeNumbers::LargeInt &other) {
        LargeInt copy = *this;
        copy.implementation->math.add(other.implementation->math);
        return copy;
    }

    LargeInt &LargeInt::operator++() {
        this->implementation->math.add(LargeIntImplementation<CoefficientType>("1"));
        return *this;
    }

    const LargeInt LargeInt::operator++(int) {
        LargeInt copy = *this;
        ++(*this);
        return copy;
    }

    LargeInt &LargeInt::operator+=(const LargeNumbers::LargeInt &other) {
        this->implementation->math.add(other.implementation->math);
        return *this;
    }

    LargeInt LargeInt::operator-(const LargeNumbers::LargeInt &other) const {
        LargeInt copy = *this;
        copy.implementation->math.subtract(other.implementation->math);
        return copy;
    }

    LargeInt &LargeInt::operator--() {
        this->implementation->math.subtract(LargeIntImplementation<CoefficientType>("1"));
        return *this;
    }

    const LargeInt LargeInt::operator--(int) {
        LargeInt copy = *this;
        --(*this);
        return copy;
    }

    LargeInt &LargeInt::operator-=(const LargeNumbers::LargeInt &other) {
        this->implementation->math.subtract(other.implementation->math);
        return *this;
    }

    LargeInt LargeInt::operator*(const LargeNumbers::LargeInt &other) {
        LargeInt copy = *this;
        copy.implementation->math.multiply(other.implementation->math);
        return copy;
    }

    LargeInt &LargeInt::operator*=(const LargeNumbers::LargeInt &other) {
        this->implementation->math.multiply(other.implementation->math);
        return *this;
    }

    LargeInt LargeInt::operator/(const LargeNumbers::LargeInt &other) {
        LargeInt copy = *this;
        copy.implementation->math.divide(other.implementation->math);
        return copy;
    }

    LargeInt &LargeInt::operator/=(const LargeNumbers::LargeInt &other) {
        this->implementation->math.divide(other.implementation->math);
        return *this;
    }

    std::string LargeInt::toString() const {
        return implementation->math.toString();
    }

    bool LargeInt::operator==(const LargeInt &other) const {
        return this->implementation->math.compare(other.implementation->math) == 0;
    }

    bool LargeInt::operator!=(const LargeInt &other) const {
        return this->implementation->math.compare(other.implementation->math) != 0;
    }

    bool LargeInt::operator<(const LargeInt &other) const {
        return this->implementation->math.compare(other.implementation->math) < 0;
    }

    bool LargeInt::operator>(const LargeInt &other) const {
        return this->implementation->math.compare(other.implementation->math) > 0;
    }

    bool LargeInt::operator<=(const LargeInt &other) const {
        return this->implementation->math.compare(other.implementation->math) <= 0;
    }

    bool LargeInt::operator>=(const LargeInt &other) const {
        return this->implementation->math.compare(other.implementation->math) >= 0;
    }
}
