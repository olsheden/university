//
// Created by Denis Olshevskiy on 07.06.2023.
//

#pragma once

#include "COperator.h"

class CDivideOperator : public COperator {
public:
    // Default constructor
    CDivideOperator();

    // Destructor
    ~CDivideOperator() override;

    /**
    Clones the CDivideOperator object.
    @returns A shared pointer to the cloned CDivideOperator object.
    */
    std::shared_ptr<COperator> clone() const override;

    /**
    Executes the division operator on an integer number and a decimal number.
    @param first The integer number to be divided.
    @param other The decimal number to divide by.
    @returns A shared pointer to the result of the division.
    */
    std::shared_ptr<CNumber> execute(const CIntegerNumber &first, const CDecimalNumber &other) const override;

    /**
    Executes the division operator on a decimal number and an integer number.
    @param first The decimal number to be divided.
    @param other The integer number to divide by.
    @returns A shared pointer to the result of the division.
    */
    std::shared_ptr<CNumber> execute(const CDecimalNumber &first, const CIntegerNumber &other) const override;

    /**
    Executes the division operator on two integer numbers.
    @param first The first integer number.
    @param other The second integer number.
    @returns A shared pointer to the result of the division.
    */
    std::shared_ptr<CNumber> execute(const CIntegerNumber &first, const CIntegerNumber &other) const override;

    /**
    Executes the division operator on two decimal numbers.
    @param first The first decimal number.
    @param other The second decimal number.
    @returns A shared pointer to the result of the division.
    */
    std::shared_ptr<CNumber> execute(const CDecimalNumber &first, const CDecimalNumber &other) const override;

    /**
    Determines if the first number is bigger than the second number.
    @param first The first number.
    @param other The second number.
    @returns True if the first number is bigger, otherwise false.
    */
    bool isBigger(const std::string &first, const std::string &other) const;

    /**
    Splits a string representation of a number and returns the decimal part.
    @param input The string representation of the number.
    @returns The decimal part of the number.
    */
    std::string splitString(std::string &input) const;

    /**
    Applies the division operator functionality to two numbers.
    @param first The first number to apply the operator functionality.
    @param other The second number.
    @returns A shared pointer to the result of applying the operator.
    */
    std::shared_ptr<CNumber> apply(const CNumber &first, const CNumber &other) const override;

    /**
    Applies the division operator functionality to a single number.
    @param number The number to apply the operator functionality.
    @returns A shared pointer to the result of applying the operator.
    */
    std::shared_ptr<CNumber> apply(const CNumber &number) const override;

    /**
    Checks if the operator has a remainder.
    @returns True if the operator has a remainder, otherwise false.
    */
    bool hasRemainder() const override;
};
