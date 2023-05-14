//
// Created by alexs on 2023-05-14.
//

#include "LargeInt.h"
#include "LargeIntImplementation.h"
#include "config.h"

namespace LargeNumbers {
    class LargeInt::Implementation {
    public:
        LargeIntImplementation<CoefficientType> implementation;

        Implementation() = default;

        explicit Implementation(const LargeIntImplementation<CoefficientType> &impl) : implementation(impl) {}
    };

    LargeInt::LargeInt() : implementation(new Implementation()) {}

    LargeInt::LargeInt(const LargeInt &other) : implementation(new Implementation(*other.implementation)) {}

    LargeInt::LargeInt(const std::string &number) : implementation(
            new Implementation(LargeIntImplementation<CoefficientType>(number))) {}

    LargeInt::~LargeInt() {
        delete implementation;
    }

    std::string LargeInt::toString() const {
        return implementation->implementation.toString();
    }
}
