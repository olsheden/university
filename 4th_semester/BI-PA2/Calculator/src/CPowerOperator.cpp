//
// Created by Denis Olshevskiy on 10.06.2023.
//

#include "CPowerOperator.h"
#include "CMultiplyOperator.h"
#include "CIntegerNumber.h"
#include "CModOperator.h"
#include "CDecimalNumber.h"

CPowerOperator::CPowerOperator() {
    m_priority = 3;

    m_needed = 2;
}

CPowerOperator::~CPowerOperator() {}

std::shared_ptr<COperator> CPowerOperator::clone() const {
    return std::make_shared<CPowerOperator>(*this);
}

std::shared_ptr<CNumber> CPowerOperator::execute(const CDecimalNumber &first, const CDecimalNumber &other) const {
    throw std::logic_error("It doesnt support");
}

std::shared_ptr<CNumber> CPowerOperator::execute(const CDecimalNumber &first, const CIntegerNumber &other) const {
    throw std::logic_error("It doesnt support");
}

std::shared_ptr<CNumber> CPowerOperator::execute(const CIntegerNumber &first, const CDecimalNumber &other) const {
    std::shared_ptr<CNumber> count = first.clone();
    std::shared_ptr<CNumber> result = other.clone();
    if (!first.getIsPositive()) throw std::logic_error("The power is negative");
    CIntegerNumber iterMinus = CIntegerNumber("1", true);
    if (count->toString() == "0") return iterMinus.clone();
    while (count->toString() != "1") {
        result = result->multiplyIntOrFl(other);
        count = count->subtract(iterMinus);
    }
    CModOperator modfunc;
    return result;
}

std::shared_ptr<CNumber> CPowerOperator::execute(const CIntegerNumber &first, const CIntegerNumber &other) const {
    std::shared_ptr<CNumber> count = first.clone();
    std::shared_ptr<CNumber> result = other.clone();
    if (!first.getIsPositive()) throw std::logic_error("The power is negative");
    CIntegerNumber iterMinus = CIntegerNumber("1", true);
    if (count->toString() == "0") return iterMinus.clone();
    while (count->toString() != "1") {
        result = result->multiplyIntOrFl(other);
        count = count->subtract(iterMinus);
    }
    CModOperator modfunc;
    return result;
}

std::shared_ptr<CNumber> CPowerOperator::apply(const CNumber &first, const CNumber &other) const {
    return first.power(other);
}

std::shared_ptr<CNumber> CPowerOperator::apply(const CNumber &number) const {
    throw std::logic_error("Bad Format");
}

bool CPowerOperator::hasRemainder() const {
    return false;
}