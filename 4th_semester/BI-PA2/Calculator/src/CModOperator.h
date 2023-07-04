//
// Created by Denis Olshevskiy on 10.06.2023.
//

#include "COperator.h"

// CModOperator class represents the modulo operator in the calculator.
// It derives from the COperator base class.
class CModOperator : public COperator {
public:
    // Constructor
    CModOperator();

    // Destructor
    ~CModOperator();

    std::shared_ptr<COperator> clone() const override;

    std::shared_ptr<CNumber> execute(const CDecimalNumber &first, const CDecimalNumber &other) const override;

    std::shared_ptr<CNumber> execute(const CDecimalNumber &first, const CIntegerNumber &other) const override;

    std::shared_ptr<CNumber> execute(const CIntegerNumber &first, const CDecimalNumber &other) const override;

    std::shared_ptr<CNumber> execute(const CIntegerNumber &first, const CIntegerNumber &other) const override;

    std::shared_ptr<CNumber> apply(const CNumber &number) const override;

    std::shared_ptr<CNumber> apply(const CNumber &first, const CNumber &other) const override;

    //returns if it has remainder
    bool hasRemainder() const override;

    // Split the input string into operands and return the remainder as a string
    std::string splitString(std::string &input) const;
};
