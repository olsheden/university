//
// Created by Denis Olshevskiy on 10.06.2023.
//

#include "COperator.h"

/**
 * CFactOperator is a class that represents a factorial operator.
 * It inherits from the COperator class.
*/
class CFactOperator : public COperator {
public:
    /**
     * Default constructor for CFactOperator.
     */
    CFactOperator();

    /**
     * Destructor for CFactOperator.
     */
    ~CFactOperator() override;

    /**
     * Clones the CFactOperator object.
     *
     * @returns A shared pointer to the cloned COperator object.
     */
    std::shared_ptr<COperator> clone() const override;

    /**
     * Executes the factorial operation on two decimal numbers.
     *
     * @param first The first decimal number.
     * @param other The second decimal number.
     * @returns A shared pointer to the result of the factorial operation.
     */
    std::shared_ptr<CNumber> execute(const CDecimalNumber &first, const CDecimalNumber &other) const override;

    /**
     * Executes the factorial operation on a decimal number and an integer number.
     *
     * @param first The decimal number.
     * @param other The integer number.
     * @returns A shared pointer to the result of the factorial operation.
     */
    std::shared_ptr<CNumber> execute(const CDecimalNumber &first, const CIntegerNumber &other) const override;

    /**
     * Executes the factorial operation on an integer number and a decimal number.
     *
     * @param first The integer number.
     * @param other The decimal number.
     * @returns A shared pointer to the result of the factorial operation.
     */
    std::shared_ptr<CNumber> execute(const CIntegerNumber &first, const CDecimalNumber &other) const override;

    /**
     * Executes the factorial operation on two integer numbers.
     *
     * @param first The first integer number.
     * @param other The second integer number.
     * @returns A shared pointer to the result of the factorial operation.
     */
    std::shared_ptr<CNumber> execute(const CIntegerNumber &first, const CIntegerNumber &other) const override;

    /**
     * Checks if the operation has a remainder.
     *
     * @returns True if the operation has a remainder, false otherwise.
     */
    bool hasRemainder() const override;

    /**
     * Applies the factorial operator on two numbers.
     *
     * @param first The first number.
     * @param other The second number.
     * @returns A shared pointer to the result of applying the factorial operator.
     */
    std::shared_ptr<CNumber> apply(const CNumber &first, const CNumber &other) const override;

    /**
     * Applies the factorial operator on a single number.
     *
     * @param number The number to apply the factorial operator on.
     * @returns A shared pointer to the result of applying the factorial operator.
     */
    std::shared_ptr<CNumber> apply(const CNumber &number) const override;
};
