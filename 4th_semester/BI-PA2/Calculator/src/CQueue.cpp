//
// Created by Denis Olshevskiy on 03.06.2023.
//
#include "./CQueue.h"
#include "CParrenOperator.h"
#include "CPowerOperator.h"
#include "CSubtractOperator.h"
#include "CMultiplyOperator.h"
#include "CDivideOperator.h"
#include "CAddOperator.h"
#include "CFactOperator.h"
#include "CModOperator.h"
#include "CRoundOperator.h"

CQueue::CQueue() {}

CQueue::~CQueue() {}

CQueue &CQueue::addNumber(const std::shared_ptr<CNumber> &number) {
    m_output_queue.push_back(number);
    return *this;
}

CQueue &CQueue::addOperator(const char &c) {
    if (c == '(') {
        CParrenOperator op;
        m_operators_queue.push_back(op.clone());
    } else if (c == '+') {
        CAddOperator op;
        m_operators_queue.push_back(op.clone());
    } else if (c == '-') {
        CSubtractOperator op;
        m_operators_queue.push_back(op.clone());
    } else if (c == '/') {
        CDivideOperator op;
        m_operators_queue.push_back(op.clone());
    } else if (c == '*') {
        CMultiplyOperator op;
        m_operators_queue.push_back(op.clone());
    } else if (c == '!') {
        CFactOperator op;
        m_operators_queue.push_back(op.clone());
    } else if (c == '#') {
        CRoundOperator op;
        m_operators_queue.push_back(op.clone());
    } else if (c == '%') {
        CModOperator op;
        m_operators_queue.push_back(op.clone());
    } else {
        CPowerOperator op;
        m_operators_queue.push_back(op.clone());
    }
    return *this;
}

CQueue &CQueue::clear() {
    m_output_queue.clear();
    m_operators_queue.clear();
    return *this;
}
