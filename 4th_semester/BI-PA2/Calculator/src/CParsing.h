/**
 * @author Denis Olshevskiy <olsheden@fit.cvut.cz>
 * @date 12.05.2021
 */
#pragma once

#include "./CNumber.h"
#include "./COperator.h"
#include "./CVariables.h"
#include "./CQueue.h"
#include <vector>
#include <memory>

class CParsing {
private:
    CQueue m_queue;

    bool lastOperator;
public:
    CParsing();

    ~CParsing();

    // function to parse an input
    CParsing &parseTheString(const std::string &input, CVariables &variables);

    bool isOperator(const char &c) const;

    void badExpressionError(const char &last_symb) const;

    long long my_pow(const int &x, const int &power) const;

    // function to save a variable
    CParsing &saveVariable(const std::string &var, const CNumber &number);

    void reform(const std::string &input, std::vector<long long> &intPart, int &exponent) const;

    void reformDec(const std::string &input, std::vector<long long> &decPart) const;

    std::shared_ptr<COperator> determTheOperator(const char &c) const;

    std::string splitString(std::string &input) const;

    void operatorExecute(CIntegerNumber &remainder);

    bool ifNegative(const std::string &input, size_t i) const;

    void readNumber(const std::string &input, size_t &i, const bool &isPositive);
};