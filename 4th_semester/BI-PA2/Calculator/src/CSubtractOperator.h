//
// Created by Denis Olshevskiy on 07.06.2023.
//


#pragma once

#include "COperator.h"

class CSubtractOperator : public COperator {
public:
    CSubtractOperator();

    ~CSubtractOperator() override;

    std::shared_ptr<COperator> clone() const override;

    std::shared_ptr<CNumber> execute(const CIntegerNumber &first, const CDecimalNumber &other) const override;

    std::shared_ptr<CNumber> execute(const CDecimalNumber &first, const CIntegerNumber &other) const override;

    std::shared_ptr<CNumber> execute(const CIntegerNumber &first, const CIntegerNumber &other) const override;

    std::shared_ptr<CNumber> execute(const CDecimalNumber &first, const CDecimalNumber &other) const override;

    bool isBigger(const std::string &first, const std::string &other) const;

    std::string splitString(std::string &input) const;

    std::shared_ptr<CNumber> apply(const CNumber &first, const CNumber &other) const override;

    std::shared_ptr<CNumber> apply(const CNumber &number) const override;

    bool hasRemainder() const override;
};
