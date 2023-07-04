//
// Created by Denis Olshevskiy on 10.06.2023.
//

#include "CFactOperator.h"
#include "CIntegerNumber.h"

CFactOperator::CFactOperator() {
    m_priority = 3;

    m_needed = 1;
}

CFactOperator::~CFactOperator() {

}

std::shared_ptr<COperator> CFactOperator::clone() const {
    return std::make_shared<CFactOperator>(*this);
}

std::shared_ptr<CNumber> CFactOperator::execute(const CDecimalNumber &first, const CDecimalNumber &other) const {
    throw std::logic_error("Bad format");
}

std::shared_ptr<CNumber> CFactOperator::execute(const CDecimalNumber &first, const CIntegerNumber &other) const {
    throw std::logic_error("Bad format");
}

std::shared_ptr<CNumber> CFactOperator::execute(const CIntegerNumber &first, const CDecimalNumber &other) const {
    throw std::logic_error("Bad format");
}

std::shared_ptr<CNumber> CFactOperator::execute(const CIntegerNumber &first, const CIntegerNumber &other) const {
    throw std::logic_error("Bad format");
}

bool CFactOperator::hasRemainder() const {
    return false;
}

std::shared_ptr<CNumber> CFactOperator::apply(const CNumber &first, const CNumber &other) const {
    throw std::logic_error("Bad format");
}

std::shared_ptr<CNumber> CFactOperator::apply(const CNumber &number) const {
    if (number.toString() == "0") return CIntegerNumber("1", true).clone();
    if (!number.getIsPositive()) throw std::logic_error("Factorial for negative numbers doesnt exist");
    return number.factorial();
}