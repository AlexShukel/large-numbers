# Large numbers

> This library is for educational purposes only!

c++ implementation of arbitrary size and precision numbers and arithmetics with them.

## Large int

Large int is represented as an array of polynomial (a0 + a1 * x + a2 * x^2 + a3 * x^3 + ...) coefficients, where x is a
base of a number.
Coefficients are stored in reverse order (from LSD to MSD), as it is more efficient to push in the end of an array.

The sign is stored separately in bool variable, where "-" is true and "+" is false.
Negative integers are stored in 2's complement form (see https://www.cs.cornell.edu/~tomf/notes/cps104/twoscomp.html).

**EXAMPLE**

Base is defined via template parameter - for simplicity lets use uint8_t - base 2^8 = 256.

| Decimal | Sign | Coefficients |
|---------|------|--------------|
| 0       | +    | 0            |
| 1       | +    | 1            |
| -1      | -    | 255          |
| 256     | +    | 0, 1         |
| -256    | -    | 0, 255       |

## Large float

Large float is represented as mantissa and exponent: M * B^E where M - mantissa, B - base and E - exponent.

**EXAMPLE**

Also lets take base 2^8

| Decimal | Mantissa | Exponent |
|---------|----------|----------|
| 0.0     | 0        | 0        |
| 1.0     | 1        | 0        |
| -1.0    | -1       | 0        |
| 256.0   | 1        | 1        |
| 0.5     | 128      | -1       |
| -0.5    | -128     | -1       |
| 0.75    | 192      | -1       |
| -0.5    | -128     | -1       |

**NOTES**

Some finite decimal fractions cannot be represented in base of 2s power. For example, a number 0.1 is represented as
infinite periodic fraction that is being rounded when converting to decimal representation in string.

## Arithmetic operations (with integers)

1. **Addition**. Just like addition on paper - coefficient by coefficient. Adding negative numbers works automatically
   because they are stored in 2's complement form.
2. **Subtraction**. The same as addition.
3. **Multiplication**. Summing up each term just like on paper - coefficient by coefficient.
4. **Division**. See https://en.wikipedia.org/wiki/Division_algorithm#Integer_division_(unsigned)_with_remainder

## Arithmetic operations (with floats)

1. **Addition**. Firstly we adjust exponents of 2 numbers to be equal and then perform integer addition with mantissa.
2. **Subtraction**. The same as addition.
3. **Multiplication**. Multiply mantissas and add exponents. Remove overflowing coefficients.
4. **Division**. See https://en.wikipedia.org/wiki/Division_algorithm#Newton%E2%80%93Raphson_division
