//
// Created by Denis Olshevskiy on 07.06.2023.
//

#include "CDivideOperator.h"
#include "CIntegerNumber.h"
#include "CDecimalNumber.h"

CDivideOperator::CDivideOperator() {
    m_priority = 2;

    m_needed = 2;
}

CDivideOperator::~CDivideOperator() {}

std::shared_ptr<COperator> CDivideOperator::clone() const {
    return std::make_shared<CDivideOperator>(*this);
}

std::string CDivideOperator::splitString(std::string &input) const {
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

bool CDivideOperator::isBigger(const std::string &first, const std::string &other) const {
    std::string intPart1 = first;
    std::string intPart2 = other;
    std::string decPart1 = splitString(intPart1);
    std::string decPart2 = splitString(intPart2);
    if (intPart1.length() > intPart2.length()) return true;
    else if (intPart1.length() < intPart2.length()) return false;
    for (size_t i = 0; i < intPart1.size(); i++) {
        if (intPart1[i] > intPart2[i]) {
            return true;
        } else if (intPart2[i] > intPart1[i]) {
            return false;
        }
    }
    if (decPart1.empty() && decPart2.empty()) return true;
    size_t sizeDec = std::min(decPart1.length(), decPart2.length());
    for (size_t i = 0; i < sizeDec; i++) {
        if (decPart1[i] > decPart2[i]) {
            return true;
        } else if (decPart2[i] > decPart1[i]) {
            return false;
        }
    }
    if (decPart1.length() > decPart2.length()) {
        return true;
    } else return false;
}

std::shared_ptr<CNumber> CDivideOperator::execute(const CIntegerNumber &first, const CDecimalNumber &other) const {
    throw std::logic_error("It doesnt support dividing decimal numbers");
}

std::shared_ptr<CNumber> CDivideOperator::execute(const CDecimalNumber &first, const CIntegerNumber &other) const {
    throw std::logic_error("It doesnt support dividing decimal numbers");
}

std::shared_ptr<CNumber> CDivideOperator::execute(const CIntegerNumber &first, const CIntegerNumber &second) const {
    bool isPositive;
    if (first.getIsPositive() == second.getIsPositive()) isPositive = true;
    else isPositive = false;
    CDecimalNumber result;
    std::shared_ptr<CNumber> divisor = first.clone();
    std::shared_ptr<CNumber> quotient = CIntegerNumber("0", true).clone();
    std::shared_ptr<CNumber> remainder = second.clone();
    CIntegerNumber iter = CIntegerNumber("1", true);


    if (divisor->toString() == "0") throw std::logic_error("The number cant be divided by zero");


    if (second.toString() == "0") {
        result = CDecimalNumber("0.0", true);
        return result.clone();
    }

    while (isBigger(remainder->toString(), divisor->toString())) {
        remainder = remainder->subtract(*divisor);
        quotient = quotient->add(iter);
    }
    std::string decPart = ".";
    decPart += remainder->toString();
    result = CDecimalNumber(quotient->toString() += decPart, isPositive);
    return result.clone();
}

std::shared_ptr<CNumber> CDivideOperator::execute(const CDecimalNumber &first, const CDecimalNumber &other) const {
    throw std::logic_error("It doesnt support dividing decimal numbers");
}

std::shared_ptr<CNumber> CDivideOperator::apply(const CNumber &first, const CNumber &other) const {
    return first.divide(other);
}

std::shared_ptr<CNumber> CDivideOperator::apply(const CNumber &number) const {
    throw std::logic_error("Bad Format");
}

bool CDivideOperator::hasRemainder() const {
    return true;
}
