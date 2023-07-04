/**
 * @author Denis Olshevskiy <olsheden@fit.cvut.cz>
 * @date 12.05.2021
 */
#include "./CIntegerNumber.h"
#include "CAddVisitor.h"
#include "CDivideVisitor.h"
#include "CSubtractVisitor.h"
#include "CMultiplyVisitor.h"
#include "CAddOperator.h"
#include "CDivideOperator.h"
#include "CMultiplyOperator.h"
#include "CSubtractOperator.h"
#include "CPowerVisitor.h"
#include "CPowerOperator.h"

CIntegerNumber::CIntegerNumber() {
    m_exponent = 0;

    m_isPositive = true;
}

CIntegerNumber::CIntegerNumber(const std::vector<long long> &value, const int &exponent, const bool &isPositive) {
    m_value = value;
    m_exponent = exponent;
    m_isPositive = isPositive;
}

CIntegerNumber::CIntegerNumber(const std::string &input, const bool &isPositive) {
    size_t i = input.size();
    bool begin = true;
    m_exponent = 0;
    m_isPositive = isPositive;
    while (i > 0) {
        long long converter = 0;
        for (int k = 0; k < 18; k++) {
            if (input[i - 1] == '0' && begin) {
                m_exponent++;
                i--;
                k--;
                if (i == 0) break;
                continue;
            } else begin = false;
            converter += (input[i - 1] - '0') * my_pow(10, k);
            i--;
            if (i == 0) break;
        }
        m_value.insert(m_value.begin(), converter);
    }
    if (m_value.size() == 1 && m_value[0] == 0) m_exponent = 0;
}

long long CIntegerNumber::my_pow(const int &x, const int &power) const {
    int i = 0;
    long long result = 1;
    while (i < power) {
        result *= x;
        i++;
    }
    return result;
}

size_t CIntegerNumber::determTheSize(long long num) const {
    size_t size = 0;
    if (num == 0) return 1;
    while (num != 0) {
        num /= 10;
        size++;
    }
    return size;
}

CIntegerNumber::~CIntegerNumber() {}

CIntegerNumber &CIntegerNumber::reform(const std::string &input) {
    size_t i = input.size();
    while (i > 0) {
        long long converter = 0;
        for (int k = 0; k < 18; k++) {
            converter += (input[i - 1] - '0') * my_pow(10, k);
            i--;
            if (i == 0) break;
        }
        m_value.insert(m_value.begin(), converter);
    }
    return *this;
}

std::shared_ptr<CNumber> CIntegerNumber::clone() const {
    std::shared_ptr<CIntegerNumber> tmp = std::make_shared<CIntegerNumber>(*this);
    return tmp;
}


std::vector<long long> &CIntegerNumber::getIntValue() {
    return m_value;
}

const std::vector<long long> &CIntegerNumber::getIntValue() const {
    return m_value;
}

std::shared_ptr<CNumber> CIntegerNumber::add(const CNumber &other) const {
    CAddVisitor tmp;
    return tmp.accept(*this, other);
}

std::shared_ptr<CNumber> CIntegerNumber::subtract(const CNumber &other) const {
    CSubtractVisitor tmp;
    return tmp.accept(*this, other);
}

std::shared_ptr<CNumber> CIntegerNumber::multiply(const CNumber &other) const {
    CMultiplyVisitor tmp;
    return tmp.accept(*this, other);
}

std::shared_ptr<CNumber> CIntegerNumber::divide(const CNumber &other) const {
    CDivideVisitor tmp;
    return tmp.accept(*this, other);
}

std::shared_ptr<CNumber> CIntegerNumber::power(const CNumber &other) const {
    CPowerVisitor tmp;
    return tmp.accept(*this, other);
}

std::shared_ptr<CNumber> CIntegerNumber::addIntOrFl(const CIntegerNumber &other) const {
    CAddOperator addfunc;
    return addfunc.execute(*this, other);
}

std::shared_ptr<CNumber> CIntegerNumber::subtractIntOrFl(const CIntegerNumber &other) const {
    CSubtractOperator subFunc;
    return subFunc.execute(*this, other);
}

std::shared_ptr<CNumber> CIntegerNumber::multiplyIntOrFl(const CIntegerNumber &other) const {
    CMultiplyOperator mulFunc;
    return mulFunc.execute(*this, other);
}

std::shared_ptr<CNumber> CIntegerNumber::divideIntOrFl(const CIntegerNumber &other) const {
    CDivideOperator divFunc;
    return divFunc.execute(*this, other);
}

std::shared_ptr<CNumber> CIntegerNumber::addIntOrFl(const CDecimalNumber &other) const {
    CAddOperator addFunc;
    return addFunc.execute(*this, other);
}

std::shared_ptr<CNumber> CIntegerNumber::subtractIntOrFl(const CDecimalNumber &other) const {
    CSubtractOperator subFunc;
    return subFunc.execute(*this, other);
}

std::shared_ptr<CNumber> CIntegerNumber::multiplyIntOrFl(const CDecimalNumber &other) const {
    CMultiplyOperator mulFunc;
    return mulFunc.execute(*this, other);
}

std::shared_ptr<CNumber> CIntegerNumber::divideIntOrFl(const CDecimalNumber &other) const {
    CDivideOperator divFunc;
    return divFunc.execute(*this, other);
}

std::shared_ptr<CNumber> CIntegerNumber::powerInt(const CIntegerNumber &other) const {
    CPowerOperator powFunc;
    return powFunc.execute(*this, other);
}

std::shared_ptr<CNumber> CIntegerNumber::powerFloat(const CDecimalNumber &other) const {
    CPowerOperator powFunc;
    return powFunc.execute(*this, other);
}

void CIntegerNumber::print() const {
    if (m_value.empty()) {
        std::cout << "0";
        return;
    }
    if (!m_isPositive) std::cout << '-';
    for (size_t i = 0; i < m_value.size(); i++) {
        std::cout << m_value[i];
    }
    if (m_exponent != 0)std::cout << " * 10 ^ " << m_exponent;
}

std::shared_ptr<CNumber> CIntegerNumber::factorial() const {
    std::shared_ptr<CNumber> count = CIntegerNumber("1", true).clone();
    CIntegerNumber iter = CIntegerNumber("1", true);
    std::shared_ptr<CNumber> result = CIntegerNumber("1", true).clone();
    while (count->toString() != this->toString()) {
        count = count->add(iter);
        result = result->multiply(*count);
    }
    return result;
}

std::string CIntegerNumber::toString() const {
    std::string result;
    if (!m_value.empty())result += std::to_string(m_value[0]);
    for (size_t i = 1; i < m_value.size(); i++) {
        for (size_t k = 0; k < 18 - determTheSize(m_value[i]); k++) result += '0';
        result += std::to_string(m_value[i]);
    }
    for (int i = 0; i < m_exponent; i++) result += '0';
    return result;
}

std::shared_ptr<CNumber> CIntegerNumber::round() const {
    return this->clone();
}