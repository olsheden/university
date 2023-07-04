//
// Created by Denis Olshevskiy on 05.06.2023.
//

#pragma once

#include "CVisitor.h"

class CDivideVisitor : public CVisitor {
public:
    /**
     * Accepts a division operation on an integer number and another number.
     * @param first The integer number.
     * @param other The other number.
     * @returns A shared pointer to the result of the division operation.
     */
    std::shared_ptr<CNumber> accept(const CIntegerNumber &first, const CNumber &other) const override;

    /**
     * Accepts a division operation on a decimal number and another number.
     *
     * @param first The decimal number.
     * @param other The other number.
     * @returns A shared pointer to the result of the division operation.
     */
    std::shared_ptr<CNumber> accept(const CDecimalNumber &first, const CNumber &other) const override;
};

