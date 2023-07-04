/**
 * @author Denis Olshevskiy <olsheden@fit.cvut.cz>
 * @date 12.05.2021
 */
#pragma once

#include "./CNumber.h"

class CIntegerNumber : public CNumber {
private:

    //value of the number
    std::vector<long long> m_value;
public:
    /**
     * Default constructor for CIntegerNumber.
     */
    CIntegerNumber(/* args */);

    /**
     * Constructor for CIntegerNumber that initializes the value, exponent, and sign of the number.
     *
     * @param value The value of the number.
     * @param exponent The exponent of the number.
     * @param isPositive The sign of the number (true if positive, false if negative).
     */
    CIntegerNumber(const std::vector<long long> &value, const int &exponent, const bool &isPositive);

    /**
     * Constructor for CIntegerNumber that initializes the number from a string representation.
     *
     * @param input The string representation of the number.
     * @param isPositive The sign of the number (true if positive, false if negative).
     */
    CIntegerNumber(const std::string &input, const bool &isPositive);

    /**
     * Destructor for CIntegerNumber.
     */
    ~CIntegerNumber() override;

    /**
     * Clones the CIntegerNumber object.
     *
     * @returns A shared pointer to the cloned CNumber object.
     */
    std::shared_ptr<CNumber> clone() const override;

    /**
     * Gets the internal value of the integer number.
     *
     * @returns A reference to the internal value vector of the integer number.
     */
    std::vector<long long> &getIntValue();


    /**
     * Gets the internal value of the integer number (const version).
     *
     * @returns A const reference to the internal value vector of the integer number.
     */
    const std::vector<long long> &getIntValue() const;

    /**
     * Adds another number to the integer number.
     *
     * @param other The number to add.
     * @returns A shared pointer to the result of the addition operation.
     */
    std::shared_ptr<CNumber> add(const CNumber &other) const override;

    /**
     * Subtracts another number from the integer number.
     *
     * @param other The number to subtract.
     * @returns A shared pointer to the result of the subtraction operation.
     */
    std::shared_ptr<CNumber> subtract(const CNumber &other) const override;

    /**
     * Multiplies the integer number by another number.
     *
     * @param other The number to multiply by.
     * @returns A shared pointer to the result of the multiplication operation.
     */
    std::shared_ptr<CNumber> multiply(const CNumber &other) const override;

    /**
     * Divides the integer number by another number.
     *
     * @param other The number to divide by.
     * @returns A shared pointer to the result of the division operation.
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
     * Computes the factorial of the integer number.
     *
     * @returns A shared pointer to the result of the factorial operation.
     */
    std::shared_ptr<CNumber> factorial() const override;

    /**
     * Reforms the internal representation of the integer number based on a string input.
     *
     * @param input The string input.
     * @returns A reference to the modified CIntegerNumber object.
     */
    CIntegerNumber &reform(const std::string &input);

    /**
     * Computes the power of an integer number.
     *
     * @param x The base number.
     * @param power The exponent.
     * @returns The result of raising the base number to the power.
     */
    long long my_pow(const int &x, const int &power) const;

    /**
     * Determines the size of a long long number.
     *
     * @param num The long long number.
     * @returns The size of the number in digits.
     */
    size_t determTheSize(long long num) const;

    /**
     * Prints the integer number.
     */
    void print() const override;

    /**
     * Converts the integer number to a string representation.
     *
     * @returns The string representation of the integer number.
     */
    std::string toString() const override;

    /**
    * Computes the power of the integer number.
    *
    * @param other The number representing the exponent.
    * @returns A shared pointer to the result of the power operation.
    */
    std::shared_ptr<CNumber> power(const CNumber &other) const override;

    /**
     * Computes the power of the integer number.
     *
     * @param other The number representing the exponent.
     * @returns A shared pointer to the result of the power operation.
     */
    std::shared_ptr<CNumber> powerInt(const CIntegerNumber &other) const override;

    /**
     * Computes the power of the integer number.
     *
     * @param other The number representing the exponent.
     * @returns A shared pointer to the result of the power operation.
     */
    std::shared_ptr<CNumber> powerFloat(const CDecimalNumber &other) const override;

    /**
     * Rounds the integer number to the nearest integer.
     *
     * @returns A shared pointer to the rounded integer number.
     */
    std::shared_ptr<CNumber> round() const override;
};
