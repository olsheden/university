//
// Created by Denis Olshevskiy on 05.06.2023.
//

#include "CSubtractVisitor.h"

std::shared_ptr<CNumber> CSubtractVisitor::accept(const CIntegerNumber &first, const CNumber &other) const {
    return other.subtractIntOrFl(first);
}

std::shared_ptr<CNumber> CSubtractVisitor::accept(const CDecimalNumber &first, const CNumber &other) const {
    return other.subtractIntOrFl(first);
}
