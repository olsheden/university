//
// Created by Denis Olshevskiy on 10.06.2023.
//

#pragma once

#include <iostream>
#include <memory>
#include <algorithm>
#include "CNumber.h"

//Abstract operator class for making an operator actions with different numbers
class COperator {
protected:
    int m_priority;

    size_t m_needed;
public:

    virtual ~COperator() = default;

    /**
	 * function to clone objects for polymorphism
	 */
    virtual std::shared_ptr<COperator> clone() const = 0;

    /**
	 * Method apply (first, other).
	 * @param[in] first Number to apply the operator functionality.
     * @param[in] other The second number.
	 * @returns number after applying
	 */
    virtual std::shared_ptr<CNumber> apply(const CNumber &first, const CNumber &other) const = 0;

    /**
	 * Method apply (first, other).
	 * @param[in] first Number to apply the operator functionality.
	 * @returns number after applying
	 */
    virtual std::shared_ptr<CNumber> apply(const CNumber &number) const = 0;

    /**
	 * Methods execute operator functional.
	 * @param[in] first number of entry to be executed.
	 * @param[in] other second number of entry to be executed.
	 * @returns the result of execution
	 * @throws if the operator is not supported for certain type
	 */
    virtual std::shared_ptr<CNumber> execute(const CIntegerNumber &first, const CDecimalNumber &other) const = 0;

    virtual std::shared_ptr<CNumber> execute(const CDecimalNumber &first, const CIntegerNumber &other) const = 0;

    virtual std::shared_ptr<CNumber> execute(const CIntegerNumber &first, const CIntegerNumber &other) const = 0;

    virtual std::shared_ptr<CNumber> execute(const CDecimalNumber &first, const CDecimalNumber &other) const = 0;

    /**
	 * Method getPriority().
	 * @returns the priority of the operator
	 */
    int getPriority() const;

    /**
	 * Method getNeeded().
	 * @returns the needed amount of operators
	 */
    size_t getNeeded() const;

    /**
	 * Method hasRemainder().
	 * @returns if the operator has a remainder
	 */
    virtual bool hasRemainder() const = 0;
};
