/**
 * @author Denis Olshevskiy <olsheden@fit.cvut.cz>
 * @date 12.05.2021
 */
#include "./CDecimalNumber.h"
#include "CAddVisitor.h"
#include "CDivideVisitor.h"
#include "CMultiplyVisitor.h"
#include "CSubtractVisitor.h"
#include "CAddOperator.h"
#include "CDivideOperator.h"
#include "CMultiplyOperator.h"
#include "CSubtractOperator.h"
#include "CPowerVisitor.h"
#include "CPowerOperator.h"

CDecimalNumber::CDecimalNumber() {
    decZeroes = 0;
    m_exponent = 0;
    m_isPositive = true;
}

CDecimalNumber::CDecimalNumber(const std::vector<long long> &intValue, const std::vector<long long> &decValue,
                               const int &zeroes, const int &exponent, const bool &isPositive) {
    m_intValue = intValue;
    m_decValue = decValue;
    decZeroes = zeroes;
    m_exponent = exponent;
    m_isPositive = isPositive;
}

std::string CDecimalNumber::splitString(std::string &input) const {
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

CDecimalNumber::CDecimalNumber(const std::string &input, const bool &isPositive) {
    std::string inputInt = input;
    std::string inputDec = splitString(inputInt);
    size_t i = inputInt.size();
    m_exponent = 0;
    m_isPositive = isPositive;
    bool begin = true;
    while (i > 0) {
        long long converter = 0;
        for (int k = 0; k < 18; k++) {
            if (inputInt[i - 1] == '0' && begin) {
                m_exponent++;
                i--;
                k--;
                if (i == 0) break;
                continue;
            } else begin = false;
            converter += (inputInt[i - 1] - '0') * my_pow(10, k);
            i--;
            if (i == 0) break;
        }
        m_intValue.insert(m_intValue.begin(), converter);
    }
    if (m_intValue.empty()) m_intValue.push_back(0);
    if (m_intValue.size() == 1 && m_intValue[0] == 0) m_exponent = 0;
    i = inputDec.size();
    begin = true;
    decZeroes = 0;
    while (i > 0) {
        long long converter = 0;
        for (int k = 0; k < 18; k++) {
            if (inputDec[i - 1] == '0' && begin) {
                k--;
                i--;
                if (i == 0) break;
                continue;
            } else if (inputDec[i - 1] == '0') {
                decZeroes++;
            } else {
                decZeroes = 0;
                begin = false;
            }
            converter += (inputDec[i - 1] - '0') * my_pow(10, k);
            i--;
            if (i == 0) break;
        }
        if (converter == 0 && i == 0) return;
        m_decValue.insert(m_decValue.begin(), converter);
    }
}

CDecimalNumber::~CDecimalNumber() {}

std::shared_ptr<CNumber> CDecimalNumber::power(const CNumber &other) const {
    CPowerVisitor tmp;
    return tmp.accept(*this, other);
}

std::shared_ptr<CNumber> CDecimalNumber::powerInt(const CIntegerNumber &other) const {
    throw std::logic_error("Not supported yet");
}

std::shared_ptr<CNumber> CDecimalNumber::powerFloat(const CDecimalNumber &other) const {
    throw std::logic_error("Not supported yet");
}

std::shared_ptr<CNumber> CDecimalNumber::clone() const {
    std::shared_ptr<CDecimalNumber> tmp = std::make_shared<CDecimalNumber>(*this);
    return tmp;
}

std::vector<long long> &CDecimalNumber::getIntValue() {
    return m_intValue;
}

std::vector<long long> &CDecimalNumber::getDecValue() {
    return m_decValue;
}

const std::vector<long long> &CDecimalNumber::getDecValue() const {
    return m_decValue;
}

const std::vector<long long> &CDecimalNumber::getIntValue() const {
    return m_intValue;
}

size_t CDecimalNumber::determTheSize(long long num) const {
    size_t size = 0;
    if (num == 0) return 1;
    while (num != 0) {
        num /= 10;
        size++;
    }
    return size;
}

long long CDecimalNumber::my_pow(const int &x, const int &power) const {
    int i = 0;
    long long result = 1;
    while (i < power) {
        result *= x;
        i++;
    }
    return result;
}

std::shared_ptr<CNumber> CDecimalNumber::add(const CNumber &other) const {
    CAddVisitor tmp;
    return tmp.accept(*this, other);
}

std::shared_ptr<CNumber> CDecimalNumber::subtract(const CNumber &other) const {
    CSubtractVisitor tmp;
    return tmp.accept(*this, other);
}

std::shared_ptr<CNumber> CDecimalNumber::multiply(const CNumber &other) const {
    CMultiplyVisitor tmp;
    return tmp.accept(*this, other);
}

std::shared_ptr<CNumber> CDecimalNumber::divide(const CNumber &other) const {
    CDivideVisitor tmp;
    return tmp.accept(*this, other);
}

std::shared_ptr<CNumber> CDecimalNumber::addIntOrFl(const CIntegerNumber &other) const {
    CAddOperator addFunc;
    return addFunc.execute(*this, other);
}

std::shared_ptr<CNumber> CDecimalNumber::subtractIntOrFl(const CIntegerNumber &other) const {
    CSubtractOperator subFunc;
    return subFunc.execute(*this, other);
}

std::shared_ptr<CNumber> CDecimalNumber::multiplyIntOrFl(const CIntegerNumber &other) const {
    CMultiplyOperator mulFunc;
    return mulFunc.execute(*this, other);
}

std::shared_ptr<CNumber> CDecimalNumber::divideIntOrFl(const CIntegerNumber &other) const {
    CDivideOperator divFunc;
    return divFunc.execute(*this, other);
}

std::shared_ptr<CNumber> CDecimalNumber::addIntOrFl(const CDecimalNumber &other) const {
    CAddOperator addFunc;
    return addFunc.execute(*this, other);
}

std::shared_ptr<CNumber> CDecimalNumber::subtractIntOrFl(const CDecimalNumber &other) const {
    CSubtractOperator subFunc;
    return subFunc.execute(*this, other);
}

std::shared_ptr<CNumber> CDecimalNumber::multiplyIntOrFl(const CDecimalNumber &other) const {
    CMultiplyOperator mulFunc;
    return mulFunc.execute(*this, other);
}

std::shared_ptr<CNumber> CDecimalNumber::divideIntOrFl(const CDecimalNumber &other) const {
    CDivideOperator divFunc;
    return divFunc.execute(*this, other);
}


void CDecimalNumber::print() const {
    if (m_intValue.empty() && m_decValue.empty()) std::cout << 0;
    else if (!(m_intValue[0] == 0 && m_intValue.size() == 1 && decZeroes != 0)) {
        if (!m_isPositive) std::cout << '-';
        for (size_t i = 0; i < m_intValue.size(); i++) {
            std::cout << m_intValue[i];
        }
        for (int i = 0; i < m_exponent; i++) std::cout << 0;
        std::cout << ".";
        for (int i = 0; i < decZeroes; i++) std::cout << 0;
        for (size_t i = 0; i < m_decValue.size(); i++) {
            std::cout << m_decValue[i];
        }
    } else {
        if (!m_isPositive) std::cout << '-';
        for (size_t i = 0; i < m_decValue.size(); i++) {
            std::cout << m_decValue[i];
        }
        if (m_intValue[0] == 0 && decZeroes != 0)std::cout << " * 10 ^ -" << decZeroes;
    }
}

std::string CDecimalNumber::toString() const {
    std::string result;
    if (!m_intValue.empty())result += std::to_string(m_intValue[0]);
    for (size_t i = 1; i < m_intValue.size(); i++) {
        for (size_t k = 0; k < 18 - determTheSize(m_intValue[i]); k++) result += '0';
        result += std::to_string(m_intValue[i]);
    }
    for (int i = 0; i < m_exponent; i++) result += '0';
    result += '.';
    for (int i = 0; i < decZeroes; i++) result += '0';
    if (!m_decValue.empty()) result += std::to_string(m_decValue[0]);
    for (size_t i = 1; i < m_decValue.size(); i++) {
        for (size_t k = 0; k < 18 - determTheSize(m_decValue[i]); k++) result += '0';
        result += std::to_string(m_decValue[i]);
    }
    return result;
}

std::shared_ptr<CNumber> CDecimalNumber::factorial() const {
    throw std::logic_error("Factorial doesnt exist for dec numbers");
}

std::shared_ptr<CNumber> CDecimalNumber::round() const {
    std::string decimalStr = this->toString();

    size_t decimalPointPos = decimalStr.find('.');


    if (decimalPointPos == std::string::npos) {
        return CIntegerNumber(decimalStr, this->getIsPositive()).clone();
    }


    std::string decimalDigits = decimalStr.substr(decimalPointPos + 1);


    if (decimalDigits.empty() || decimalDigits[0] < '5') {

        return CIntegerNumber(decimalStr.substr(0, decimalPointPos), this->getIsPositive()).clone();
    } else {
        std::shared_ptr<CNumber> tmp = CIntegerNumber(decimalStr.substr(0, decimalPointPos),
                                                      this->getIsPositive()).clone();
        tmp = tmp->add(CIntegerNumber("1", true));
        return tmp;
    }
}