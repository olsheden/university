#pragma once

#include <iostream>
#include <vector>
#include <memory>

class CDecimalNumber;

class CIntegerNumber;

//Abstract CNumber class for working with unlimited numbers
class CNumber {
protected:
    long long m_exponent;
    bool m_isPositive;
public:
    virtual ~CNumber() = default;

    /**
     * Creates a clone of the CNumber object.
     *
     * @returns A shared pointer to the cloned CNumber object.
     */
    virtual std::shared_ptr<CNumber> clone() const = 0;

    /**
     * Adds another number to the CNumber.
     *
     * @param other The number to add.
     * @returns A shared pointer to the result of the addition.
     */
    virtual std::shared_ptr<CNumber> add(const CNumber &other) const = 0;

    /**
     * Subtracts another number from the CNumber.
     *
     * @param other The number to subtract.
     * @returns A shared pointer to the result of the subtraction.
     */
    virtual std::shared_ptr<CNumber> subtract(const CNumber &other) const = 0;

    /**
     * Multiplies the CNumber by another number.
     *
     * @param other The number to multiply by.
     * @returns A shared pointer to the result of the multiplication.
     */
    virtual std::shared_ptr<CNumber> multiply(const CNumber &other) const = 0;

    /**
     * Divides the CNumber by another number.
     *
     * @param other The number to divide by.
     * @returns A shared pointer to the result of the division.
     */
    virtual std::shared_ptr<CNumber> divide(const CNumber &other) const = 0;

    virtual std::shared_ptr<CNumber> addIntOrFl(const CIntegerNumber &other) const = 0;

    virtual std::shared_ptr<CNumber> subtractIntOrFl(const CIntegerNumber &other) const = 0;

    virtual std::shared_ptr<CNumber> multiplyIntOrFl(const CIntegerNumber &other) const = 0;

    virtual std::shared_ptr<CNumber> divideIntOrFl(const CIntegerNumber &other) const = 0;

    virtual std::shared_ptr<CNumber> addIntOrFl(const CDecimalNumber &other) const = 0;

    virtual std::shared_ptr<CNumber> subtractIntOrFl(const CDecimalNumber &other) const = 0;

    virtual std::shared_ptr<CNumber> multiplyIntOrFl(const CDecimalNumber &other) const = 0;

    virtual std::shared_ptr<CNumber> divideIntOrFl(const CDecimalNumber &other) const = 0;

    /**
     * Converts the CNumber to a string representation.
     *
     * @returns The string representation of the CNumber.
     */
    virtual std::string toString() const = 0;

    /**
     * Prints the CDecimalNumber.
     */
    virtual void print() const = 0;

    /**
     * Raises the CNumber to the power of another number.
     *
     * @param other The number to raise the CNumber to.
     * @returns A shared pointer to the result of the exponentiation.
     */
    virtual std::shared_ptr<CNumber> power(const CNumber &other) const = 0;

    /**
     * Raises the CNumber to the power of an integer number.
     *
     * @param other The integer number to raise the CNumber to.
     * @returns A shared pointer to the result of the exponentiation.
     */
    virtual std::shared_ptr<CNumber> powerInt(const CIntegerNumber &other) const = 0;

    /**
     * Raises the CNumber to the power of an integer number.
     *
     * @param other The integer number to raise the CNumber to.
     * @returns A shared pointer to the result of the exponentiation.
     */
    virtual std::shared_ptr<CNumber> powerFloat(const CDecimalNumber &other) const = 0;

    /**
     * Calculates the factorial of the CNumber.
     *
     * @returns A shared pointer to the result of the factorial calculation.
     */
    virtual std::shared_ptr<CNumber> factorial() const = 0;

    /**
     * Rounds the CNumber to the nearest integer.
     *
     * @returns A shared pointer to the rounded CNumber object.
     */
    virtual std::shared_ptr<CNumber> round() const = 0;

    bool getIsPositive() const;

    bool &getIsPositive();

    void setPositive(const bool &isPositive);
};
