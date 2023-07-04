//
// Created by Denis Olshevskiy on 06.06.2023.
//

#pragma once

#include "COperator.h"


class CAddOperator : public COperator {
public:
    /**
	 * default constructor
	 */
    CAddOperator();

    /**
     * destructor
     */
    ~CAddOperator() override;

    /**
	 * function to clone objects for polymorphism
	 */
    std::shared_ptr<COperator> clone() const override;

    /**
	 * Methods execute operator functional.
	 * @param[in] first number of entry to be executed.
	 * @param[in] other second number of entry to be executed.
	 * @returns the result of execution
	 * @throws if the operator is not supported for certain type
	 */
    std::shared_ptr<CNumber> execute(const CIntegerNumber &first, const CDecimalNumber &other) const override;

    std::shared_ptr<CNumber> execute(const CDecimalNumber &first, const CIntegerNumber &other) const override;

    std::shared_ptr<CNumber> execute(const CIntegerNumber &first, const CIntegerNumber &other) const override;

    std::shared_ptr<CNumber> execute(const CDecimalNumber &first, const CDecimalNumber &other) const override;

    /**
	 * Method determTheSize (num).
	 * @param[in] num Number to determine the size.
	 * @returns the size of the number
	 */
    int determTheSize(long long num) const;

    /**
	 * Method mypow (x, power).
	 * @param[in] x Number to power.
     * @param[in] power The power of the number.
	 * @returns number after powering
	 */
    long long my_pow(const int &x, const int &power) const;

    /**
	 * Method apply (first, other).
	 * @param[in] first Number to apply the operator functionality.
     * @param[in] other The second number.
	 * @returns number after applying
	 */
    std::shared_ptr<CNumber> apply(const CNumber &first, const CNumber &other) const override;

    /**
	 * Method apply (first, other).
	 * @param[in] first Number to apply the operator functionality.
	 * @returns number after applying
	 */
    std::shared_ptr<CNumber> apply(const CNumber &number) const override;

    /**
	 * Method hasRemainder().
	 * @returns if the operator has a remainder
	 */
    bool hasRemainder() const override;

    /**
	 * Method isBigger (first, other) to determine if the first number is bigger.
	 * @param[in] first Number to determine.
     * @param[in] other The second number.
	 * @returns true if the first number is bigger, otherwise false
	 */
    bool isBigger(const std::string &first, const std::string &other) const;

    /**
	 * Method splitString (input).
	 * @param[in] input string, that represents a number
	 * @returns decimal part of the number
	 */
    std::string splitString(std::string &input) const;
};

