//
// Created by Denis Olshevskiy on 05.06.2023.
//

#include "CMultiplyVisitor.h"


std::shared_ptr<CNumber> CMultiplyVisitor::accept(const CIntegerNumber &first, const CNumber &other) const {
    return other.multiplyIntOrFl(first);
}

std::shared_ptr<CNumber> CMultiplyVisitor::accept(const CDecimalNumber &first, const CNumber &other) const {
    return other.multiplyIntOrFl(first);
}