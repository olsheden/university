//
// Created by Denis Olshevskiy on 05.06.2023.
//
#pragma once

#include "CVisitor.h"

class CAddVisitor : public CVisitor {
public:

    /**
    Accepts an object of type CIntegerNumber and another number,
    and performs addition operation between them.
    @param[in] first The CIntegerNumber object to be visited.
    @param[in] other The other number to perform addition with.
    @returns A shared pointer to the result of the addition operation.
    **/
    std::shared_ptr<CNumber> accept(const CIntegerNumber &first, const CNumber &other) const override;

    /**
    Accepts an object of type CDecimalNumber and another number,
    and performs addition operation between them.
    @param[in] first The CDecimalNumber object to be visited.
    @param[in] other The other number to perform addition with.
    @returns A shared pointer to the result of the addition operation.
    **/
    std::shared_ptr<CNumber> accept(const CDecimalNumber &first, const CNumber &other) const override;
};

