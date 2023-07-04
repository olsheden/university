//
// Created by Denis Olshevskiy on 10.06.2023.
//

#pragma once

#include "CVisitor.h"

class CPowerVisitor : CVisitor {
public:
    std::shared_ptr<CNumber> accept(const CDecimalNumber &first, const CNumber &other) const override;

    std::shared_ptr<CNumber> accept(const CIntegerNumber &first, const CNumber &other) const override;
};
