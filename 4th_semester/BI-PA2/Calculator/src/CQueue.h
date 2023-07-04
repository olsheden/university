//
// Created by Denis Olshevskiy on 03.06.2023.
//
#include <vector>
#include "./CNumber.h"
#include "./COperator.h"

#pragma once

class CQueue {
public:
    std::vector<std::shared_ptr<CNumber>> m_output_queue;

    std::vector<std::shared_ptr<COperator>> m_operators_queue;
public:
    CQueue();

    ~CQueue();

    CQueue &addOperator(const char &op);

    CQueue &addNumber(const std::shared_ptr<CNumber> &number);

    CQueue &clear();
};
