//
// Created by Denis Olshevskiy on 06.06.2023.
//

#include "CAddOperator.h"
#include "CIntegerNumber.h"
#include "CDecimalNumber.h"
#include "COperator.h"

CAddOperator::CAddOperator() {
    m_priority = 1;

    m_needed = 2;
}

CAddOperator::~CAddOperator() {}

std::shared_ptr<COperator> CAddOperator::clone() const {
    return std::make_shared<CAddOperator>(*this);
}

std::string CAddOperator::splitString(std::string &input) const {
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

bool CAddOperator::isBigger(const std::string &first, const std::string &other) const {
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
    if (decPart1.empty() && decPart2.empty()) return false;
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

int CAddOperator::determTheSize(long long num) const {
    int size = 0;
    if (num == 0) return 1;
    while (num != 0) {
        num /= 10;
        size++;
    }
    return size;
}

long long CAddOperator::my_pow(const int &x, const int &power) const {
    int i = 0;
    long long result = 1;
    while (i < power) {
        result *= x;
        i++;
    }
    return result;
}

std::shared_ptr<CNumber> CAddOperator::execute(const CIntegerNumber &first, const CDecimalNumber &other) const {
    std::string resultStr;
    int carry = 0;
    std::string number1 = other.toString();
    std::string number2 = first.toString();
    std::string number1Dec = other.splitString(number1);
    size_t i = number1.length();
    size_t k = number2.length();

    while (i > 0 || k > 0 || carry > 0) {
        int value1;
        int value2;
        if (number1[i - 1] == '.') i--;
        if (number2[k - 1] == '.') k--;
        if (i > 0) value1 = number1[i - 1] - '0';
        else value1 = 0;
        if (k > 0) value2 = number2[k - 1] - '0';
        else value2 = 0;
        int sum = value1 + value2 + carry;
        carry = sum / 10;
        sum %= 10;
        resultStr += std::to_string(sum);
        if (i > 0)i--;
        if (k > 0)k--;
    }
    std::reverse(resultStr.begin(), resultStr.end());
    resultStr += '.';
    resultStr += number1Dec;
    CDecimalNumber result = CDecimalNumber(resultStr, true);
    return result.clone();
}

std::shared_ptr<CNumber> CAddOperator::execute(const CDecimalNumber &first, const CIntegerNumber &other) const {
    return execute(other, first);
}

std::shared_ptr<CNumber> CAddOperator::execute(const CIntegerNumber &first, const CIntegerNumber &other) const {
    std::string resultStr;
    int carry = 0;
    std::string number1 = other.toString();
    std::string number2 = first.toString();
    size_t i = number1.length();
    size_t k = number2.length();

    while (i > 0 || k > 0 || carry > 0) {
        int value1;
        int value2;
        if (i > 0) value1 = number1[i - 1] - '0';
        else value1 = 0;
        if (k > 0) value2 = number2[k - 1] - '0';
        else value2 = 0;
        int sum = value1 + value2 + carry;
        carry = sum / 10;
        sum %= 10;
        resultStr += std::to_string(sum);
        if (i > 0)i--;
        if (k > 0)k--;
    }
    std::reverse(resultStr.begin(), resultStr.end());
    CIntegerNumber result = CIntegerNumber(resultStr, true);
    return result.clone();
}

std::shared_ptr<CNumber> CAddOperator::execute(const CDecimalNumber &first, const CDecimalNumber &other) const {
    std::string resultStr;
    int carry = 0;
    std::string number1 = other.toString();
    std::string number2 = first.toString();
    std::string number1Dec = other.splitString(number1);
    std::string number2Dec = other.splitString(number2);

    size_t size1 = number1Dec.size();
    size_t size2 = number2Dec.size();
    size_t maxsize = std::max(size1, size2);
    for (size_t j = 0; j < maxsize - size1; j++) number1Dec += '0';
    for (size_t j = 0; j < maxsize - size2; j++) number2Dec += '0';
    size_t i = number1Dec.length();
    size_t k = number2Dec.length();
    std::string resultDecStr;
    while (i > 0 || k > 0 || carry > 0) {
        int value1;
        int value2;
        if (number1Dec[i - 1] == '.') i--;
        if (number2Dec[k - 1] == '.') k--;
        if (i > 0) value1 = number1Dec[i - 1] - '0';
        else value1 = 0;
        if (k > 0) value2 = number2Dec[k - 1] - '0';
        else value2 = 0;
        int sum = value1 + value2 + carry;
        carry = sum / 10;
        sum %= 10;
        resultDecStr += std::to_string(sum);
        if (i > 0)i--;
        if (k > 0)k--;
        if (k == 0 && i == 0) break;
    }
    std::reverse(resultDecStr.begin(), resultDecStr.end());

    i = number1.length();
    k = number2.length();

    while (i > 0 || k > 0 || carry > 0) {
        int value1;
        int value2;
        if (number1[i - 1] == '.') i--;
        if (number2[k - 1] == '.') k--;
        if (i > 0) value1 = number1[i - 1] - '0';
        else value1 = 0;
        if (k > 0) value2 = number2[k - 1] - '0';
        else value2 = 0;
        int sum = value1 + value2 + carry;
        carry = sum / 10;
        sum %= 10;
        resultStr += std::to_string(sum);
        if (i > 0)i--;
        if (k > 0)k--;
    }
    std::reverse(resultStr.begin(), resultStr.end());
    resultStr += '.';

    resultStr += resultDecStr;
    CDecimalNumber result = CDecimalNumber(resultStr, true);
    return result.clone();
}

std::shared_ptr<CNumber> CAddOperator::apply(const CNumber &first, const CNumber &other) const {
    if (first.getIsPositive() == other.getIsPositive()) {
        std::shared_ptr<CNumber> result = first.add(other);
        if (first.getIsPositive()) result->setPositive(true);
        else result->setPositive(false);
        return result;
    } else {
        std::shared_ptr<CNumber> result = first.subtract(other);
        if (isBigger(other.toString(), first.toString())) {
            result->setPositive(other.getIsPositive());
        } else result->setPositive(first.getIsPositive());
        return result;
    }
}

std::shared_ptr<CNumber> CAddOperator::apply(const CNumber &number) const {
    throw std::logic_error("Bad Format");
}

bool CAddOperator::hasRemainder() const {
    return false;
}