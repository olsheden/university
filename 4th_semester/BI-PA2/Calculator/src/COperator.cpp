//
// Created by Denis Olshevskiy on 10.06.2023.
//

#include "COperator.h"

int COperator::getPriority() const {
    return m_priority;
}

size_t COperator::getNeeded() const {
    return m_needed;
}