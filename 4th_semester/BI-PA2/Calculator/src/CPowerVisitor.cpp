//
// Created by Denis Olshevskiy on 10.06.2023.
//

#include "CPowerVisitor.h"

std::shared_ptr<CNumber> CPowerVisitor::accept(const CDecimalNumber &first, const CNumber &other) const {
    return other.powerFloat(first);
}

std::shared_ptr<CNumber> CPowerVisitor::accept(const CIntegerNumber &first, const CNumber &other) const {
    return other.powerInt(first);
}