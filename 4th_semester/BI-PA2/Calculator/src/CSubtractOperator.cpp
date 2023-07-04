//
// Created by Denis Olshevskiy on 07.06.2023.
//

#include "CSubtractOperator.h"
#include "CIntegerNumber.h"
#include "CDecimalNumber.h"

CSubtractOperator::CSubtractOperator() {
    m_priority = 1;

    m_needed = 2;
}

CSubtractOperator::~CSubtractOperator() {}

std::shared_ptr<COperator> CSubtractOperator::clone() const {
    return std::make_shared<CSubtractOperator>(*this);
}

std::string CSubtractOperator::splitString(std::string &input) const {
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

bool CSubtractOperator::isBigger(const std::string &first, const std::string &other) const {
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

std::shared_ptr<CNumber> CSubtractOperator::execute(const CIntegerNumber &first, const CDecimalNumber &other) const {
    std::string number1 = other.toString();
    std::string number2 = first.toString();
    std::string resultDecStr;
    if (isBigger(number2, number1)) return execute(other, first);
    std::string number1Dec = splitString(number1);
    std::string number2Dec;
    for (size_t i = 0; i < number1Dec.size(); i++) number2Dec += '0';

    int carry = 0;
    size_t i = number1Dec.length();
    size_t k = number2Dec.length();

    while (i > 0 || k > 0 || carry != 0) {
        int value1;
        int value2;
        if (i > 0) {
            value1 = number1Dec[i - 1] - '0';
        } else value1 = 0;
        if (k > 0) {
            value2 = number2Dec[k - 1] - '0';
        } else value2 = 0;

        int diff = value1 - value2 - carry;
        if (diff < 0) {
            carry = 1;
        } else carry = 0;

        if (diff < 0) {
            diff += 10;
        }

        resultDecStr += std::to_string(diff);

        if (i > 0) i--;
        if (k > 0) k--;
        if (i == 0 && k == 0) break;
    }

    std::reverse(resultDecStr.begin(), resultDecStr.end());

    std::string resultStr;
    i = number1.length();
    k = number2.length();


    while (i > 0 || k > 0 || carry != 0) {
        int value1;
        int value2;
        if (i > 0) {
            value1 = number1[i - 1] - '0';
        } else value1 = 0;
        if (k > 0) {
            value2 = number2[k - 1] - '0';
        } else value2 = 0;

        int diff = value1 - value2 - carry;
        if (diff < 0) {
            carry = 1;
        } else carry = 0;

        if (diff < 0) {
            diff += 10;
        }

        resultStr += std::to_string(diff);

        if (i > 0) i--;
        if (k > 0) k--;
    }

    std::reverse(resultStr.begin(), resultStr.end());

    // Remove leading zeros
    resultStr.erase(0, resultStr.find_first_not_of('0'));
    resultStr += '.';
    resultStr += resultDecStr;
    CDecimalNumber result = CDecimalNumber(resultStr, true);
    return result.clone();
}

std::shared_ptr<CNumber> CSubtractOperator::execute(const CDecimalNumber &first, const CIntegerNumber &other) const {
    std::string number1 = other.toString();
    std::string number2 = first.toString();
    if (isBigger(number2, number1)) return first.subtract(other);
    std::string resultDecStr;
    std::string number2Dec = splitString(number2);
    std::string number1Dec;
    for (size_t i = 0; i < number2Dec.size(); i++) number1Dec += '0';
    int carry = 0;
    size_t i = number1Dec.length();
    size_t k = number2Dec.length();

    while (i > 0 || k > 0 || carry != 0) {
        int value1;
        int value2;
        if (i > 0) {
            value1 = number1Dec[i - 1] - '0';
        } else value1 = 0;
        if (k > 0) {
            value2 = number2Dec[k - 1] - '0';
        } else value2 = 0;

        int diff = value1 - value2 - carry;
        if (diff < 0) {
            carry = 1;
        } else carry = 0;

        if (diff < 0) {
            diff += 10;
        }

        resultDecStr += std::to_string(diff);

        if (i > 0) i--;
        if (k > 0) k--;
        if (i == 0 && k == 0) break;
    }

    std::reverse(resultDecStr.begin(), resultDecStr.end());

    std::string resultStr;
    i = number1.length();
    k = number2.length();


    while (i > 0 || k > 0 || carry != 0) {
        int value1;
        int value2;
        if (i > 0) {
            value1 = number1[i - 1] - '0';
        } else value1 = 0;
        if (k > 0) {
            value2 = number2[k - 1] - '0';
        } else value2 = 0;

        int diff = value1 - value2 - carry;
        if (diff < 0) {
            carry = 1;
        } else carry = 0;

        if (diff < 0) {
            diff += 10;
        }

        resultStr += std::to_string(diff);

        if (i > 0) i--;
        if (k > 0) k--;
    }

    std::reverse(resultStr.begin(), resultStr.end());

    // Remove leading zeros
    resultStr.erase(0, resultStr.find_first_not_of('0'));
    resultStr += '.';
    resultStr += resultDecStr;
    CDecimalNumber result = CDecimalNumber(resultStr, true);
    return result.clone();
}

std::shared_ptr<CNumber> CSubtractOperator::execute(const CIntegerNumber &first, const CIntegerNumber &other) const {
    std::string number1 = other.toString();
    std::string number2 = first.toString();
    std::string resultStr;
    int carry = 0;
    size_t i = number1.length();
    size_t k = number2.length();
    if (isBigger(number2, number1)) return first.subtract(other);
    while (i > 0 || k > 0 || carry != 0) {
        int value1;
        int value2;
        if (i > 0) {
            value1 = number1[i - 1] - '0';
        } else value1 = 0;
        if (k > 0) {
            value2 = number2[k - 1] - '0';
        } else value2 = 0;

        int diff = value1 - value2 - carry;
        if (diff < 0) {
            carry = 1;
        } else carry = 0;

        if (diff < 0) {
            diff += 10;
        }

        resultStr += std::to_string(diff);

        if (i > 0) i--;
        if (k > 0) k--;
    }

    std::reverse(resultStr.begin(), resultStr.end());

    // Remove leading zeros
    resultStr.erase(0, resultStr.find_first_not_of('0'));
    if (resultStr.empty()) resultStr += '0';
    CIntegerNumber result = CIntegerNumber(resultStr, true);
    return result.clone();
}

std::shared_ptr<CNumber> CSubtractOperator::execute(const CDecimalNumber &first, const CDecimalNumber &other) const {
    std::string number1 = other.toString();
    std::string number2 = first.toString();
    if (isBigger(number2, number1)) return execute(other, first);
    std::string resultDecStr;
    std::string number2Dec = splitString(number2);
    std::string number1Dec = splitString(number1);
    size_t size1 = number1Dec.size();
    size_t size2 = number2Dec.size();
    size_t maxSize = std::max(size1, size2);
    for (size_t i = 0; i < maxSize - size1; i++) number1Dec += '0';
    for (size_t i = 0; i < maxSize - size2; i++) number2Dec += '0';

    int carry = 0;
    size_t i = number1Dec.length();
    size_t k = number2Dec.length();

    while (i > 0 || k > 0 || carry != 0) {
        int value1;
        int value2;
        if (i > 0) {
            value1 = number1Dec[i - 1] - '0';
        } else value1 = 0;
        if (k > 0) {
            value2 = number2Dec[k - 1] - '0';
        } else value2 = 0;

        int diff = value1 - value2 - carry;
        if (diff < 0) {
            carry = 1;
        } else carry = 0;

        if (diff < 0) {
            diff += 10;
        }

        resultDecStr += std::to_string(diff);

        if (i > 0) i--;
        if (k > 0) k--;
        if (i == 0 && k == 0) break;
    }

    std::reverse(resultDecStr.begin(), resultDecStr.end());

    std::string resultStr;
    i = number1.length();
    k = number2.length();


    while (i > 0 || k > 0 || carry != 0) {
        int value1;
        int value2;
        if (i > 0) {
            value1 = number1[i - 1] - '0';
        } else value1 = 0;
        if (k > 0) {
            value2 = number2[k - 1] - '0';
        } else value2 = 0;

        int diff = value1 - value2 - carry;
        if (diff < 0) {
            carry = 1;
        } else carry = 0;

        if (diff < 0) {
            diff += 10;
        }

        resultStr += std::to_string(diff);

        if (i > 0) i--;
        if (k > 0) k--;
    }

    std::reverse(resultStr.begin(), resultStr.end());
    std::string checkIfDec = resultDecStr;

    // Remove leading zeros
    checkIfDec.erase(0, checkIfDec.find_first_not_of('0'));
    resultStr.erase(0, resultStr.find_first_not_of('0'));
    if (checkIfDec.empty()) {
        CIntegerNumber result = CIntegerNumber(resultStr, true);
        return result.clone();
    }
    resultStr += '.';
    resultStr += resultDecStr;
    CDecimalNumber result = CDecimalNumber(resultStr, true);
    return result.clone();
}

std::shared_ptr<CNumber> CSubtractOperator::apply(const CNumber &first, const CNumber &other) const {
    if (first.getIsPositive() != other.getIsPositive()) {
        std::shared_ptr<CNumber> result = first.add(other);

        if (!first.getIsPositive()) result->setPositive(false);
        else result->setPositive(true);
        return result;
    } else {
        std::shared_ptr<CNumber> result = first.subtract(other);
        if (isBigger(first.toString(), other.toString())) result->setPositive(other.getIsPositive());
        else {
            if (other.getIsPositive()) result->setPositive(false);
            else result->setPositive(true);
        }
        return result;
    }
}

bool CSubtractOperator::hasRemainder() const {
    return false;
}

std::shared_ptr<CNumber> CSubtractOperator::apply(const CNumber &number) const {
    throw std::logic_error("Bad Format");
}
