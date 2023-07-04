//
// Created by Denis Olshevskiy on 05.06.2023.
//

#include "CAddVisitor.h"

std::shared_ptr<CNumber> CAddVisitor::accept(const CIntegerNumber &first, const CNumber &other) const {
    return other.addIntOrFl(first);
}

std::shared_ptr<CNumber> CAddVisitor::accept(const CDecimalNumber &first, const CNumber &other) const {
    return other.addIntOrFl(first);
}
