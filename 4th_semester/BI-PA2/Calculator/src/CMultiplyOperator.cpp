//
// Created by Denis Olshevskiy on 07.06.2023.
//

#include "CMultiplyOperator.h"
#include "CIntegerNumber.h"
#include "CDecimalNumber.h"

CMultiplyOperator::CMultiplyOperator() {
    m_priority = 2;

    m_needed = 2;
}

CMultiplyOperator::~CMultiplyOperator() {}

std::shared_ptr<COperator> CMultiplyOperator::clone() const {
    return std::make_shared<CMultiplyOperator>(*this);
}

std::string CMultiplyOperator::turnToDecimal(const std::string &number, const int &dotPos) const {
    size_t size = number.size();
    int count = 0;
    std::string result;
    bool begin = true;
    while (size > 0) {
        if (number[size - 1] == '0' && begin) {
            size--;
            count++;
            continue;
        } else begin = false;
        result += number[size - 1];
        count++;
        size--;
        if (count == dotPos) result += '.';
    }
    std::reverse(result.begin(), result.end());
    return result;
}

std::shared_ptr<CNumber> CMultiplyOperator::execute(const CIntegerNumber &first, const CDecimalNumber &other) const {
    std::string number1 = first.toString();
    std::string number2 = other.toString();
    bool isPositive;
    if (first.getIsPositive() == other.getIsPositive()) isPositive = true;
    else isPositive = false;
    std::string number2Dec = other.splitString(number2);
    size_t dotPos = number2Dec.size();
    number2 += number2Dec;
    if (number1 == "0" || number2 == "0") {
        CIntegerNumber result = CIntegerNumber("0", true);
        return result.clone();
    }
    std::string resultStr(number1.size() + number2.size(), 0);
    for (size_t i = number1.size(); i > 0; i--) {
        for (size_t k = number2.size(); k > 0; k--) {
            int value = (number1[i - 1] - '0') * (number2[k - 1] - '0') + resultStr[i + k - 1];
            resultStr[i + k - 1] = value % 10;
            resultStr[i + k - 2] += value / 10;
        }
    }
    for (char &element: resultStr) {
        element += '0';
    }
    resultStr = turnToDecimal(resultStr, dotPos);
    CDecimalNumber result = CDecimalNumber(resultStr, isPositive);
    return result.clone();
}

std::shared_ptr<CNumber> CMultiplyOperator::execute(const CDecimalNumber &first, const CIntegerNumber &other) const {
    return execute(other, first);
}

std::shared_ptr<CNumber> CMultiplyOperator::execute(const CIntegerNumber &first, const CIntegerNumber &other) const {
    std::string number1 = first.toString();
    std::string number2 = other.toString();
    bool isPositive;
    if (first.getIsPositive() == other.getIsPositive()) isPositive = true;
    else isPositive = false;
    if (number1 == "0" || number2 == "0") {
        CIntegerNumber result = CIntegerNumber("0", true);
        return result.clone();
    }
    std::string resultStr(number1.size() + number2.size(), 0);
    for (size_t i = number1.size(); i > 0; i--) {
        for (size_t k = number2.size(); k > 0; k--) {
            int value = (number1[i - 1] - '0') * (number2[k - 1] - '0') + resultStr[i + k - 1];
            resultStr[i + k - 1] = value % 10;
            resultStr[i + k - 2] += value / 10;
        }
    }
    for (char &element: resultStr) {
        element += '0';
    }
    CIntegerNumber result = CIntegerNumber(resultStr, isPositive);
    return result.clone();
}

std::shared_ptr<CNumber> CMultiplyOperator::execute(const CDecimalNumber &first, const CDecimalNumber &other) const {
    std::string number1 = first.toString();
    std::string number2 = other.toString();
    bool isPositive;
    if (first.getIsPositive() == other.getIsPositive()) isPositive = true;
    else isPositive = false;
    std::string number1Dec = first.splitString(number1);
    std::string number2Dec = other.splitString(number2);
    size_t dotPos1 = number1Dec.size();
    size_t dotPos2 = number2Dec.size();
    number1 += number1Dec;
    number2 += number2Dec;
    if (number1 == "0" || number2 == "0") {
        CIntegerNumber result = CIntegerNumber("0", true);
        return result.clone();
    }
    std::string resultStr(number1.size() + number2.size(), 0);
    for (size_t i = number1.size(); i > 0; i--) {
        for (size_t k = number2.size(); k > 0; k--) {
            int value = (number1[i - 1] - '0') * (number2[k - 1] - '0') + resultStr[i + k - 1];
            resultStr[i + k - 1] = value % 10;
            resultStr[i + k - 2] += value / 10;
        }
    }
    for (char &element: resultStr) {
        element += '0';
    }
    resultStr = turnToDecimal(resultStr, dotPos1 + dotPos2);
    CDecimalNumber result = CDecimalNumber(resultStr, isPositive);
    return result.clone();
}

std::shared_ptr<CNumber> CMultiplyOperator::apply(const CNumber &first, const CNumber &other) const {
    return first.multiply(other);
}

std::shared_ptr<CNumber> CMultiplyOperator::apply(const CNumber &number) const {
    throw std::logic_error("Bad Format");
}

bool CMultiplyOperator::hasRemainder() const {
    return false;
}