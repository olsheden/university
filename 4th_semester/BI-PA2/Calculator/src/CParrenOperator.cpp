//
// Created by Denis Olshevskiy on 10.06.2023.
//

#include "CParrenOperator.h"


CParrenOperator::CParrenOperator() {
    m_priority = 0;

    m_needed = 0;
}

CParrenOperator::~CParrenOperator() {}

std::shared_ptr<COperator> CParrenOperator::clone() const {
    return std::make_shared<CParrenOperator>(*this);
}

std::shared_ptr<CNumber> CParrenOperator::execute(const CDecimalNumber &first, const CDecimalNumber &other) const {
    throw std::logic_error("It doesnt support");
}

std::shared_ptr<CNumber> CParrenOperator::execute(const CDecimalNumber &first, const CIntegerNumber &other) const {
    throw std::logic_error("It doesnt support");
}

std::shared_ptr<CNumber> CParrenOperator::execute(const CIntegerNumber &first, const CDecimalNumber &other) const {
    throw std::logic_error("It doesnt support");
}

std::shared_ptr<CNumber> CParrenOperator::execute(const CIntegerNumber &first, const CIntegerNumber &other) const {
    throw std::logic_error("It doesnt support");
}

std::shared_ptr<CNumber> CParrenOperator::apply(const CNumber &first, const CNumber &other) const {
    throw std::logic_error("It doesnt support");
}

std::shared_ptr<CNumber> CParrenOperator::apply(const CNumber &number) const {
    throw std::logic_error("Bad Format");
}

bool CParrenOperator::hasRemainder() const {
    return false;
}