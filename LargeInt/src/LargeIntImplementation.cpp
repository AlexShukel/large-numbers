//
// Created by alexs on 2023-05-14.
//

#include "LargeIntImplementation.h"
#include "utils.h"
#include <regex>
#include <bitset>
#include <stdexcept>

namespace LargeNumbers {
    template<class T>
    const T LargeIntImplementation<T>::MAX_COEFFICIENT_VALUE = static_cast<T>(std::bitset<COEFFICIENT_BIT_SIZE>(
            0).flip().to_ulong());

    template<class T>
    LargeIntImplementation<T>::LargeIntImplementation(): sign(false) {}

    template<class T>
    LargeIntImplementation<T>::LargeIntImplementation(const std::string &number) {
        if (!std::regex_match(number, std::regex("^-?\\d+$"))) {
            throw std::invalid_argument(R"(LargeInt validation error: number does not match regex format "^-?\d+$")");
        }

        sign = number[0] == '-';
        std::string normalizedDecimal = normalizeDecimalString(number);

        if (isStringZero(normalizedDecimal)) {
            sign = false;
            coefficients.push_back(0);
            return;
        }

        std::bitset<COEFFICIENT_BIT_SIZE> coefficient = 0;
        int coefficientSize = 0;

        while (!isStringZero(normalizedDecimal)) {
            coefficient >>= 1;
            coefficient[COEFFICIENT_BIT_SIZE - 1] = charToDigit(normalizedDecimal[normalizedDecimal.size() - 1]) % 2;
            ++coefficientSize;

            if (coefficientSize == COEFFICIENT_BIT_SIZE) {
                coefficients.push_back(static_cast<T>(coefficient.to_ulong()));
                coefficient.reset();
                coefficientSize = 0;
            }

            uint8_t nextAdditive = 0;
            for (char &character: normalizedDecimal) {
                uint8_t additive = nextAdditive;
                uint8_t digit = charToDigit(character);

                if (digit % 2 == 1) {
                    nextAdditive = 5;
                } else {
                    nextAdditive = 0;
                }

                character = digitToChar(digit / 2 + additive);
            }
        }

        if (coefficientSize > 0) {
            coefficient >>= COEFFICIENT_BIT_SIZE - coefficientSize;
            coefficients.push_back(static_cast<T>(coefficient.to_ulong()));
        }

        if (sign) {
            toTwosComplement();
        }
    }

    template<class T>
    LargeIntImplementation<T>::LargeIntImplementation(const LargeIntImplementation<T> &other): sign(other.sign),
                                                                                               coefficients(
                                                                                                       other.coefficients) {}

    template<class T>
    LargeIntImplementation<T>::LargeIntImplementation(const std::vector<T> &coefficients, bool sign): coefficients(
            coefficients), sign(sign) {}

    template<class T>
    void
    LargeIntImplementation<T>::coefficientsToBinary(std::string &binary, const std::vector<T> &coefficientsCopy) const {
        binary.resize(coefficientsCopy.size() * COEFFICIENT_BIT_SIZE);
        int index = binary.size() - COEFFICIENT_BIT_SIZE;

        for (T c: coefficientsCopy) {
            std::bitset<COEFFICIENT_BIT_SIZE> coefficient = c;

            coefficient.to_string().copy(&binary[index], COEFFICIENT_BIT_SIZE);

            index -= COEFFICIENT_BIT_SIZE;
        }
    }

    template<class T>
    std::string LargeIntImplementation<T>::toString() const {
        LargeIntImplementation<T> copy = *this;
        std::string decimal;

        if (sign) {
            copy.negate();
        }

        std::string binary;
        coefficientsToBinary(binary, copy.coefficients);

        while (!isStringZero(binary)) {
            uint8_t remainder = euclideanDivision(binary);
            decimal.push_back(digitToChar(remainder));
        }

        if (decimal.empty()) {
            decimal.push_back('0');
        } else if (sign) {
            decimal.push_back('-');
        }

        std::reverse(decimal.begin(), decimal.end());

        return decimal;
    }

    template<class T>
    T LargeIntImplementation<T>::getSupplementDigit() const {
        return sign ? MAX_COEFFICIENT_VALUE : 0;
    }

    template<class T>
    void LargeIntImplementation<T>::normalize() {
        T meaninglessValue = getSupplementDigit();
        trimBack(coefficients, meaninglessValue);
    }

    template<class T>
    bool LargeIntImplementation<T>::isZero() const {
        return coefficients.size() == 1 && coefficients[0] == 0 && !sign;
    }

    template<class T>
    void LargeIntImplementation<T>::negate() {
        if (isZero()) {
            return;
        }

        sign = !sign;
        toTwosComplement();
    }

    template<class T>
    void LargeIntImplementation<T>::shiftLeft(size_t shift) {
        coefficients.insert(coefficients.begin(), shift, 0);
    }

    template<class T>
    void LargeIntImplementation<T>::shiftRight(size_t shift) {
        coefficients.erase(coefficients.begin(), coefficients.begin() + shift);
    }

    template<class T>
    void LargeIntImplementation<T>::add(const LargeIntImplementation<T> &addend) {
        bool oldSign = sign;

        auto comparisonResult = abs().compare(addend.abs());

        if (comparisonResult == 0) {
            sign = false;
            coefficients.clear();
            coefficients.push_back(0);
            return;
        }

        if (sign != addend.sign && comparisonResult < 0) {
            sign = addend.sign;
        }

        auto firstIt = coefficients.begin();
        auto secondIt = addend.coefficients.begin();

        T carry = 0;

        while (firstIt != coefficients.end() || secondIt != addend.coefficients.end()) {
            T firstMember = firstIt != coefficients.end() ? *firstIt : getSupplementDigit();
            T secondMember = secondIt != addend.coefficients.end() ? *secondIt : addend.getSupplementDigit();

            T sum = firstMember + secondMember + carry;

            carry = (firstMember > sum) || (secondMember > sum) ||
                    (carry && (firstMember == sum || secondMember == sum));

            if (firstIt != coefficients.end()) {
                *firstIt = sum;
                ++firstIt;
            } else {
                coefficients.push_back(sum);
                firstIt = coefficients.end();
            }

            if (secondIt != addend.coefficients.end()) {
                ++secondIt;
            }
        }

        if (!oldSign && !addend.sign) {
            coefficients.push_back(carry);
        }

        this->normalize();
    }

    template<class T>
    void LargeIntImplementation<T>::subtract(LargeIntImplementation<T> subtrahend) {
        subtrahend.negate();
        this->add(subtrahend);
    }

    template<class T>
    void LargeIntImplementation<T>::multiplyByCoefficient(T coefficient) {
        T carry = 0;
        uint64_t base = MAX_COEFFICIENT_VALUE + 1;
        for (T &current: coefficients) {
            uint64_t temp = carry + current * coefficient;
            current = static_cast<T>(temp % base);
            carry = static_cast<T>(temp / base);
        }

        if (carry > 0) {
            coefficients.push_back(carry);
        }
    }

    template<class T>
    void LargeIntImplementation<T>::multiply(LargeIntImplementation<T> multiplier) {
        bool productSign = sign ^ multiplier.sign;

        if (this->sign) {
            this->negate();
        }

        if (multiplier.sign) {
            multiplier.negate();
        }

        LargeIntImplementation<T> product;

        for (size_t i = 0; i < multiplier.coefficients.size(); ++i) {
            auto temp = *this;
            temp.multiplyByCoefficient(multiplier.coefficients[i]);
            temp.shiftLeft(i);
            product.add(temp);
        }

        if (productSign) {
            product.negate();
        }

        product.normalize();
        *this = product;
    }

    template<class T>
    LargeIntImplementation<T> LargeIntImplementation<T>::divide(LargeIntImplementation<T> divisor) {
        if (divisor.isZero()) {
            throw std::logic_error("Can not divide by zero!");
        }

        LargeIntImplementation<T> initial = *this;

        bool prevSign = sign;
        bool quotientSign = sign ^ divisor.sign;

        if (this->sign) {
            this->negate(); // Adjust signs to be both positive
        }

        if (divisor.sign) {
            divisor.negate(); // Adjust signs to be both positive
        }

        auto comparisonResult = this->compare(divisor);

        // Return early if divisor is greater than this
        if (comparisonResult < 0) {
            coefficients.clear();
            coefficients.push_back(0);
            sign = false;
            return initial;
        }

        // Return early if divisor is equal to this
        if (comparisonResult == 0) {
            coefficients.clear();
            coefficients.push_back(1);
            if (quotientSign) {
                this->negate();
            }
            return LargeIntImplementation<T>("0");
        }

        LargeIntImplementation<T> remainder = *this;
        LargeIntImplementation<T> shiftedDivisor = divisor;
        size_t maxShift = 0;
        while (remainder.compare(shiftedDivisor) > 0) {
            shiftedDivisor.shiftLeft(1);
            ++maxShift;
        }

        coefficients.clear();
        coefficients.resize(maxShift, 0);

        while (remainder.compare(divisor) >= 0) {
            shiftedDivisor = divisor;
            size_t shift = 0;
            while (remainder.compare(shiftedDivisor) >= 0) {
                shiftedDivisor.shiftLeft(1);
                ++shift;
            }
            shiftedDivisor.shiftRight(1);
            --shift;

            remainder.subtract(shiftedDivisor);
            ++coefficients[shift];
        }

        if (quotientSign) {
            negate();
        }
        normalize();

        if (prevSign) {
            remainder.negate();
        }
        remainder.normalize();

        return remainder;
    }

    template<class T>
    int LargeIntImplementation<T>::compare(const LargeIntImplementation<T> &other) const {
        if (sign && !other.sign) {
            return -1;
        }

        if (!sign && other.sign) {
            return 1;
        }

        if (other.coefficients.size() > coefficients.size()) {
            return -1;
        }

        if (coefficients.size() > other.coefficients.size()) {
            return 1;
        }

        // Signs and sized of coefficients are equal now

        size_t i = coefficients.size() - 1;
        while (true) {
            if (coefficients[i] > other.coefficients[i]) {
                return 1;
            }

            if (coefficients[i] < other.coefficients[i]) {
                return -1;
            }

            if (i == 0) {
                break;
            }
            --i;
        }

        return 0;
    }

    template<class T>
    bool LargeIntImplementation<T>::getSign() const {
        return sign;
    }

    template<class T>
    std::string LargeIntImplementation<T>::normalizeDecimalString(const std::string &number) {
        bool numberSign = number[0] == '-';
        auto from = std::find_if_not(number.begin() + numberSign, number.end(), [](const char &c) {
            return c == '0';
        });

        if (from == number.end()) {
            return number;
        }

        return std::string(from, number.end());
    }

    template<class T>
    void LargeIntImplementation<T>::invertCoefficients() {
        for (auto &c: coefficients) {
            c = ~c;
        }
    }

    template<class T>
    void LargeIntImplementation<T>::toTwosComplement() {
        LargeIntImplementation<T> one({1}, false);
        invertCoefficients();
        add(one);
    }

    template<class T>
    LargeIntImplementation<T> LargeIntImplementation<T>::abs() const {
        LargeIntImplementation<T> copy = *this;
        if (copy.sign) {
            copy.negate();
        }
        return copy;
    }

    // For debugging
    template
    class LargeIntImplementation<uint8_t>;

    // For final result
    template
    class LargeIntImplementation<uint32_t>;
}
