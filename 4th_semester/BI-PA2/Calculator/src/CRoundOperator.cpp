//
// Created by Denis Olshevskiy on 10.06.2023.
//

#include "CRoundOperator.h"

CRoundOperator::CRoundOperator() {
    m_needed = 1;

    m_priority = 3;
}

CRoundOperator::~CRoundOperator() {}

std::shared_ptr<COperator> CRoundOperator::clone() const {
    return std::make_shared<CRoundOperator>(*this);
}

std::shared_ptr<CNumber> CRoundOperator::execute(const CDecimalNumber &first, const CDecimalNumber &other) const {
    throw std::logic_error("Bad format");
}

std::shared_ptr<CNumber> CRoundOperator::execute(const CDecimalNumber &first, const CIntegerNumber &other) const {
    throw std::logic_error("Bad format");
}

std::shared_ptr<CNumber> CRoundOperator::execute(const CIntegerNumber &first, const CDecimalNumber &other) const {
    throw std::logic_error("Bad format");
}

std::shared_ptr<CNumber> CRoundOperator::execute(const CIntegerNumber &first, const CIntegerNumber &other) const {
    throw std::logic_error("Bad format");
}

std::shared_ptr<CNumber> CRoundOperator::apply(const CNumber &first, const CNumber &other) const {
    throw std::logic_error("Bad format");
}

std::shared_ptr<CNumber> CRoundOperator::apply(const CNumber &number) const {
    return number.round();
}

bool CRoundOperator::hasRemainder() const {
    return false;
}