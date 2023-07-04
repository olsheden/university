/**
 * @author Denis Olshevskiy <olsheden@fit.cvut.cz>
 * @date 12.05.2021
 */
#include "./CParsing.h"
#include "./CDecimalNumber.h"
#include "./CIntegerNumber.h"
#include "CParrenOperator.h"
#include "CPowerOperator.h"
#include "CSubtractOperator.h"
#include "CMultiplyOperator.h"
#include "CDivideOperator.h"
#include "CAddOperator.h"
#include "CFactOperator.h"
#include "CRoundOperator.h"
#include "CModOperator.h"

void CParsing::readNumber(const std::string &input, size_t &i, const bool &isPositive) {
    std::vector<long long> intPart;
    std::string intPartStr;
    bool begin = true;
    while (isdigit(input[i])) {
        if (input[i] == '0' && begin) {
            i++;
        } else {
            begin = false;
            intPartStr.push_back(input[i++]);
        }
    }
    int exponent = 0;
    reform(intPartStr, intPart, exponent);
    if (intPart.empty()) intPart.push_back(0);
    if (input[i] == '.') {
        i++;
        std::vector<long long> decPart;
        std::string decPartStr;
        int zeroes = 0;
        begin = true;
        while (isdigit(input[i])) {
            if (input[i] == '0' && begin) {
                i++;
                zeroes++;
            } else {
                begin = false;
                decPartStr.push_back(input[i++]);
            }
        }
        reformDec(decPartStr, decPart);
        badExpressionError(input[i]);
        if (decPart.empty()) {
            CIntegerNumber tmp(intPart, exponent, isPositive);
            m_queue.addNumber(tmp.clone());
        } else {
            CDecimalNumber tmp(intPart, decPart, zeroes, exponent, isPositive);
            m_queue.addNumber(tmp.clone());
        }
        return;
    }
    while (isspace(input[i])) {
        i++;
    }
    CIntegerNumber tmp(intPart, exponent, isPositive);
    badExpressionError(input[i]);
    m_queue.addNumber(tmp.clone());
}

bool CParsing::ifNegative(const std::string &input, size_t i) const {
    if (input[i] == '-') i++;
    while (isspace(input[i]))i++;
    if (!isdigit(input[i])) return false;
    return true;
}

std::shared_ptr<COperator> CParsing::determTheOperator(const char &c) const {
    if (c == '(') {
        CParrenOperator op;
        return op.clone();
    } else if (c == '+') {
        CAddOperator op;
        return op.clone();
    } else if (c == '-') {
        CSubtractOperator op;
        return op.clone();
    } else if (c == '/') {
        CDivideOperator op;
        return op.clone();
    } else if (c == '*') {
        CMultiplyOperator op;
        return op.clone();
    } else if (c == '!') {
        CFactOperator op;
        return op.clone();
    } else if (c == '#') {
        CRoundOperator op;
        return op.clone();
    } else if (c == '%') {
        CModOperator op;
        return op.clone();
    } else {
        CPowerOperator op;
        return op.clone();
    }
}

void CParsing::operatorExecute(CIntegerNumber &remainder) {
    std::shared_ptr<CNumber> result;
    std::shared_ptr<COperator> op_tmp = m_queue.m_operators_queue[m_queue.m_operators_queue.size() - 1];
    m_queue.m_operators_queue.pop_back();

    if (op_tmp->getNeeded() > m_queue.m_output_queue.size()) throw std::logic_error("Bad syntax");
    if (op_tmp->getNeeded() == 1) {
        std::shared_ptr<CNumber> number1 = m_queue.m_output_queue[m_queue.m_output_queue.size() - 1];
        result = op_tmp->apply(*number1);
        m_queue.m_output_queue.pop_back();
    } else {
        std::shared_ptr<CNumber> number1 = m_queue.m_output_queue[m_queue.m_output_queue.size() - 2];
        std::shared_ptr<CNumber> number2 = m_queue.m_output_queue[m_queue.m_output_queue.size() - 1];
        result = op_tmp->apply(*number1, *number2);
        m_queue.m_output_queue.pop_back();
        m_queue.m_output_queue.pop_back();
    }
    if (op_tmp->hasRemainder()) {
        std::string quotient = result->toString();
        std::string remainderDec = splitString(quotient);
        remainder = CIntegerNumber(remainderDec, result->getIsPositive());
        result = CIntegerNumber(quotient, true).clone();
    }
    m_queue.m_output_queue.push_back(result);
}

std::string CParsing::splitString(std::string &input) const {
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

CParsing::CParsing() {}

CParsing::~CParsing() {}

bool CParsing::isOperator(const char &c) const {
    if (c == '+' || c == '/' || c == '-' || c == '*' || c == '^' || c == '!' || c == '#' || c == '(' || c == '%')
        return true;
    return false;
}

void CParsing::badExpressionError(const char &last_symb) const {
    if (!isspace(last_symb) && !isOperator(last_symb) && last_symb != '\0' && last_symb != ')')
        throw std::logic_error("Bad number");
}

long long CParsing::my_pow(const int &x, const int &power) const {
    int i = 0;
    long long result = 1;
    while (i < power) {
        result *= x;
        i++;
    }
    return result;
}

void CParsing::reform(const std::string &input, std::vector<long long> &intPart, int &exponent) const {
    size_t i = input.size();
    bool begin = true;
    while (i > 0) {
        long long converter = 0;
        for (int k = 0; k < 18; k++) {
            if (input[i - 1] == '0' && begin) {
                exponent++;
                i--;
                k--;
                if (i == 0) break;
                continue;
            } else begin = false;
            converter += (input[i - 1] - '0') * my_pow(10, k);
            i--;
            if (i == 0) break;
        }
        intPart.insert(intPart.begin(), converter);
    }
}

void CParsing::reformDec(const std::string &input, std::vector<long long> &decPart) const {
    size_t i = input.size();
    bool begin = true;
    while (i > 0) {
        long long converter = 0;
        for (int k = 0; k < 18; k++) {
            if (input[i - 1] == '0' && begin) {
                k--;
                i--;
                continue;
            } else {
                begin = false;
            }
            converter += (input[i - 1] - '0') * my_pow(10, k);
            i--;
            if (i == 0) break;
        }
        if (converter == 0 && i == 0) return;
        decPart.insert(decPart.begin(), converter);
    }
}

CParsing &CParsing::parseTheString(const std::string &input, CVariables &variables) {
    int m_num_of_parentheses = 0;
    bool isVarExpr = false;
    lastOperator = true;
    CIntegerNumber remainder = CIntegerNumber("0", true);
    std::string variableToSet;
    size_t i = 0;
    while (i < input.size()) {
        if (isspace(input[i])) {
            i++;
            continue;
        } else if (input[i] == '(') {
            try {
                if (!lastOperator) throw std::logic_error("Bad Syntax");
            }
            catch (const std::logic_error &e) {
                m_queue.clear();
                std::cout << e.what() << std::endl;
                return *this;
            }
            lastOperator = true;
            m_queue.addOperator(input[i]);
            m_num_of_parentheses++;
            i++;
        } else if (input[i] == ')') {
            try {
                if (lastOperator) throw std::logic_error("Bad Syntax");
            }
            catch (const std::logic_error &e) {
                m_queue.clear();
                std::cout << e.what() << std::endl;
                return *this;
            }
            lastOperator = false;
            m_num_of_parentheses--;
            try {
                if (m_num_of_parentheses < 0) throw std::logic_error("The fault in logic of parentheses");
            }
            catch (const std::logic_error &e) {
                m_queue.clear();
                std::cout << e.what() << std::endl;
                return *this;
            }
            while (!m_queue.m_operators_queue.empty() &&
                   m_queue.m_operators_queue[m_queue.m_operators_queue.size() - 1]->getPriority() != 0) {
                try {
                    operatorExecute(remainder);
                }
                catch (const std::logic_error &e) {
                    m_queue.clear();
                    std::cout << e.what() << std::endl;
                    return *this;
                }
            }
            m_queue.m_operators_queue.pop_back();
            i++;
        } else if (isalpha(input[i])) {
            try {
                if (!lastOperator) throw std::logic_error("Bad Syntax");
            }
            catch (const std::logic_error &e) {
                m_queue.clear();
                std::cout << e.what() << std::endl;
                return *this;
            }
            lastOperator = false;
            std::string variable;
            while (!isOperator(input[i]) && !isspace(input[i]) && input[i] != '=' && input[i] != ')') {
                variable.push_back(input[i]);
                i++;
            }
            while (isspace(input[i])) i++;
            if (input[i] == '=') {
                try {
                    if (isVarExpr) throw std::logic_error("Bad syntax");
                }
                catch (const std::logic_error &e) {
                    m_queue.clear();
                    std::cout << e.what() << std::endl;
                    return *this;
                }
                isVarExpr = true;
                variableToSet = variable;
                i++;
            } else {
                std::shared_ptr<CNumber> value;
                try {
                    value = variables.getValue(variable);
                }
                catch (const std::logic_error &e) {
                    m_queue.clear();
                    std::cout << e.what() << std::endl;
                    return *this;
                }
                m_queue.m_output_queue.push_back(value);
            }
        } else if (input[i] == '-' && lastOperator && ifNegative(input, i)) {
            lastOperator = false;
            while (isspace(input[i]) || input[i] == '-')i++;
            try {
                readNumber(input, i, false);
            }
            catch (const std::logic_error &e) {
                m_queue.clear();
                std::cout << e.what() << std::endl;
                return *this;
            }
        } else if (isOperator(input[i])) {
            try {
                if (lastOperator) throw std::logic_error("Bad Syntax");
            }
            catch (const std::logic_error &e) {
                m_queue.clear();
                std::cout << e.what() << std::endl;
                return *this;
            }
            lastOperator = true;
            if (m_queue.m_operators_queue.empty()) {
                m_queue.addOperator(input[i++]);
                continue;
            }
            std::shared_ptr<COperator> op = determTheOperator(input[i]);
            if (m_queue.m_operators_queue[m_queue.m_operators_queue.size() - 1]->getPriority() < op->getPriority()) {
                m_queue.m_operators_queue.push_back(op);
                i++;
                continue;
            }
            while (!m_queue.m_operators_queue.empty() &&
                   m_queue.m_operators_queue[m_queue.m_operators_queue.size() - 1]->getPriority() >=
                   op->getPriority()) {
                try {
                    operatorExecute(remainder);
                }
                catch (const std::logic_error &e) {
                    m_queue.clear();
                    std::cout << e.what() << std::endl;
                    return *this;
                }
            }
            m_queue.m_operators_queue.push_back(op);
            i++;
        } else if (isdigit(input[i])) {
            try {
                if (!lastOperator) throw std::logic_error("Bad Syntax");
                readNumber(input, i, true);
            }
            catch (const std::logic_error &e) {
                m_queue.clear();
                std::cout << e.what() << std::endl;
                return *this;
            }
            lastOperator = false;
        } else {
            try {
                throw std::logic_error("Bad Syntax");
            }
            catch (const std::logic_error &e) {
                m_queue.clear();
                std::cout << e.what() << std::endl;
                return *this;
            }
        }
    }
    try {
        if (m_num_of_parentheses != 0) throw std::logic_error("Bad amount of parentheses");
    }
    catch (const std::logic_error &e) {
        m_queue.clear();
        std::cout << e.what() << " " << m_num_of_parentheses << std::endl;
        return *this;
    }
    if (!m_queue.m_operators_queue.empty()) {
        for (size_t k = m_queue.m_operators_queue.size(); k > 0; k--) {
            try {
                operatorExecute(remainder);
            }
            catch (const std::logic_error &e) {
                m_queue.clear();
                std::cout << e.what() << std::endl;
                return *this;
            }
        }
    }
    if (isVarExpr) {
        variables.setValue(variableToSet, m_queue.m_output_queue[0]);
        std::cout << variableToSet << " = ";
        m_queue.m_output_queue[0]->print();
    } else {
        std::cout << "The result of counting is ";
        m_queue.m_output_queue[0]->print();
    }
    if (remainder.toString() != "0") {
        std::cout << "(the remainder is:";
        remainder.print();
        std::cout << ")";
    }
    m_queue.clear();
    std::cout << std::endl;
    return *this;
}
