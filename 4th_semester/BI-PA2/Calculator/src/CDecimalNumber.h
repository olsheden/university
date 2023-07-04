/**
 * @author Denis Olshevskiy <olsheden@fit.cvut.cz>
 * @date 12.05.2021
 */
#pragma once

#include "CNumber.h"
#include "CIntegerNumber.h"

class CDecimalNumber : public CNumber {
private:
    //int part of the number
    std::vector<long long> m_intValue;

    //float part of the number
    std::vector<long long> m_decValue;

    int decZeroes;
public:
    CDecimalNumber(/* args */);

    /**
     * Constructor for CDecimalNumber with specified integer and decimal values, decimal zeroes,
     * exponent, and sign.
     *
     * @param intValue The vector representing the integer part of the decimal number.
     * @param decValue The vector representing the decimal part of the number.
     * @param decZeroes The number of decimal places.
     * @param exponent The exponent of the decimal number.
     * @param isPositive The sign of the decimal number.
     */
    CDecimalNumber(const std::vector<long long> &intValue, const std::vector<long long> &decValue, const int &decZeroes,
                   const int &exponent, const bool &isPositive);

    /**
     * Constructor for CDecimalNumber from a string representation and sign.
     *
     * @param input The string representation of the decimal number.
     * @param isPositive The sign of the decimal number.
     */
    CDecimalNumber(const std::string &input, const bool &isPositive);

    /**
     * Destructor for CDecimalNumber.
     */
    ~CDecimalNumber() override;

    /**
     * Creates a clone of the CDecimalNumber object.
     *
     * @returns A shared pointer to the cloned CNumber object.
     */
    std::shared_ptr<CNumber> clone() const override;

    /**
     * Determines the size of a number.
     *
     * @param num The number to determine the size of.
     * @returns The size of the number.
     */
    size_t determTheSize(long long num) const;

    /**
     * Calculates the power of a number.
     *
     * @param x The base number.
     * @param power The power to raise the number to.
     * @returns The number raised to the specified power.
     */
    long long my_pow(const int &x, const int &power) const;

    /**
     * Returns a reference to the decimal value of the CDecimalNumber.
     *
     * @returns A reference to the decimal value.
     */
    std::vector<long long> &getDecValue();

    /**
     * Returns a constant reference to the decimal value of the CDecimalNumber.
     *
     * @returns A constant reference to the decimal value.
     */
    const std::vector<long long> &getDecValue() const;

    /**
     * Returns a reference to the integer value of the CDecimalNumber.
     *
     * @returns A reference to the integer value.
     */
    std::vector<long long> &getIntValue();

    /**
     * Returns a constant reference to the integer value of the CDecimalNumber.
     *
     * @returns A constant reference to the integer value.
     */
    const std::vector<long long> &getIntValue() const;

    /**
     * Adds another number to the CDecimalNumber.
     *
     * @param other The number to add.
     * @returns A shared pointer to the result of the addition.
     */
    std::shared_ptr<CNumber> add(const CNumber &other) const override;

    /**
     * Subtracts another number from the CDecimalNumber.
     *
     * @param other The number to subtract.
     * @returns A shared pointer to the result of the subtraction.
     */
    std::shared_ptr<CNumber> subtract(const CNumber &other) const override;

    /**
     * Multiplies the CDecimalNumber by another number.
     *
     * @param other The number to multiply by.
     * @returns A shared pointer to the result of the multiplication.
     */
    std::shared_ptr<CNumber> multiply(const CNumber &other) const override;

    /**
     * Divides the CDecimalNumber by another number.
     *
     * @param other The number to divide by.
     * @returns A shared pointer to the result of the division.
     */
    std::shared_ptr<CNumber> divide(const CNumber &other) const override;

    std::shared_ptr<CNumber> addIntOrFl(const CIntegerNumber &other) const override;

    std::shared_ptr<CNumber> subtractIntOrFl(const CIntegerNumber &other) const override;

    std::shared_ptr<CNumber> multiplyIntOrFl(const CIntegerNumber &other) const override;

    std::shared_ptr<CNumber> divideIntOrFl(const CIntegerNumber &other) const override;

    std::shared_ptr<CNumber> addIntOrFl(const CDecimalNumber &other) const override;

    std::shared_ptr<CNumber> subtractIntOrFl(const CDecimalNumber &other) const override;

    std::shared_ptr<CNumber> multiplyIntOrFl(const CDecimalNumber &other) const override;

    std::shared_ptr<CNumber> divideIntOrFl(const CDecimalNumber &other) const override;

    /**
     * Prints the CDecimalNumber.
     */
    void print() const override;

    /**
     * Splits a string representation of a number and returns the decimal part.
     *
     * @param input The string representation of the number.
     * @returns The decimal part of the number.
     */
    std::string splitString(std::string &input) const;

    /**
     * Converts the CDecimalNumber to a string representation.
     *
     * @returns The string representation of the CDecimalNumber.
     */
    std::string toString() const override;

    /**
     * Raises the CDecimalNumber to the power of another number.
     *
     * @param other The number to raise the CDecimalNumber to.
     * @returns A shared pointer to the result of the exponentiation.
     */
    std::shared_ptr<CNumber> power(const CNumber &other) const override;

    /**
     * Raises the CDecimalNumber to the power of an integer number.
     *
     * @param other The integer number to raise the CDecimalNumber to.
     * @returns A shared pointer to the result of the exponentiation.
     */
    std::shared_ptr<CNumber> powerInt(const CIntegerNumber &other) const override;

    /**
     * Raises the CNumber to the power of an integer number.
     *
     * @param other The integer number to raise the CNumber to.
     * @returns A shared pointer to the result of the exponentiation.
     */
    std::shared_ptr<CNumber> powerFloat(const CDecimalNumber &other) const override;

    /**
     * Calculates the factorial of the CDecimalNumber.
     *
     * @returns A shared pointer to the result of the factorial calculation.
     */
    std::shared_ptr<CNumber> factorial() const override;

    /**
     * Rounds the CDecimalNumber to the nearest integer.
     *
     * @returns A shared pointer to the rounded CNumber object.
     */
    std::shared_ptr<CNumber> round() const override;
};
