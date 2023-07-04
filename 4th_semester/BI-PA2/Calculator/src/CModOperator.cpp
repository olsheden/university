//
// Created by Denis Olshevskiy on 10.06.2023.
//

#include "CIntegerNumber.h"
#include "CModOperator.h"

std::string CModOperator::splitString(std::string &input) const {
    std::string decPart;
    std::string intPart;
    bool begin = true;
    for (size_t i = 0; i < input.size(); i++) {
        if (input[i] == '.') begin = false;
        else if (begin) intPart += input[i];
        else decPart += input[i];
    }
    input = intPart;
    return decPart;
}

CModOperator::CModOperator() {
    m_priority = 2;

    m_needed = 2;
}

CModOperator::~CModOperator() {}

std::shared_ptr<COperator> CModOperator::clone() const {
    return std::make_shared<CModOperator>(*this);
}

std::shared_ptr<CNumber> CModOperator::apply(const CNumber &number) const {
    throw std::logic_error("Bad Format");
}

std::shared_ptr<CNumber> CModOperator::apply(const CNumber &first, const CNumber &other) const {
    bool isPositive = true;
    if (!first.getIsPositive()) isPositive = false;
    std::shared_ptr<CNumber> result = first.divide(other);
    std::string count = result->toString();
    std::string value = splitString(count);
    return CIntegerNumber(value, isPositive).clone();
}

std::shared_ptr<CNumber> CModOperator::execute(const CDecimalNumber &first, const CDecimalNumber &other) const {
    throw std::logic_error("Bad Format");
}

std::shared_ptr<CNumber> CModOperator::execute(const CDecimalNumber &first, const CIntegerNumber &other) const {
    throw std::logic_error("Bad Format");
}

std::shared_ptr<CNumber> CModOperator::execute(const CIntegerNumber &first, const CDecimalNumber &other) const {
    throw std::logic_error("Bad Format");
}

std::shared_ptr<CNumber> CModOperator::execute(const CIntegerNumber &first, const CIntegerNumber &other) const {
    throw std::logic_error("Bad Format");
}

bool CModOperator::hasRemainder() const {
    return false;
}