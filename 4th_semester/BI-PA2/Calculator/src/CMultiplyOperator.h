//
// Created by Denis Olshevskiy on 07.06.2023.
//

#pragma once

#include "COperator.h"

// Class represents the multiply operator in the calculator.
// It derives from the COperator base class.
class CMultiplyOperator : public COperator {
public:
    CMultiplyOperator();

    ~CMultiplyOperator() override;

    std::shared_ptr<COperator> clone() const override;

    std::shared_ptr<CNumber> execute(const CIntegerNumber &first, const CDecimalNumber &other) const override;

    std::shared_ptr<CNumber> execute(const CDecimalNumber &first, const CIntegerNumber &other) const override;

    std::shared_ptr<CNumber> execute(const CIntegerNumber &first, const CIntegerNumber &other) const override;

    std::shared_ptr<CNumber> execute(const CDecimalNumber &first, const CDecimalNumber &other) const override;

    std::string turnToDecimal(const std::string &number, const int &dotPos) const;

    std::shared_ptr<CNumber> apply(const CNumber &first, const CNumber &other) const override;

    std::shared_ptr<CNumber> apply(const CNumber &number) const override;

    bool hasRemainder() const override;
};

