//
// Created by alexs on 2023-05-16.
//

#include "LargeFloat.h"
#include "LargeFloatImplementation.h"
#include "../../config.h"

namespace LargeNumbers {
    class LargeFloat::Implementation {
    public:
        LargeFloatImplementation<CoefficientType> math;

        Implementation() = default;

        explicit Implementation(const LargeFloatImplementation<CoefficientType> &impl) : math(impl) {}
    };

    LargeFloat::LargeFloat() : implementation(new Implementation()) {}

    LargeFloat::LargeFloat(const LargeNumbers::LargeFloat &other) : implementation(
            new Implementation(*other.implementation)) {}

    LargeFloat::LargeFloat(const std::string &number) : implementation(
            new Implementation(LargeFloatImplementation<CoefficientType>(number))) {}

    LargeFloat::~LargeFloat() {
        delete implementation;
    }

    std::string LargeFloat::toString() const {
        return this->implementation->math.toString();
    }
}
