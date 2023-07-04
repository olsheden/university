//
// Created by Denis Olshevskiy on 04.06.2023.
//
#pragma once

#include "CIntegerNumber.h"
#include "CDecimalNumber.h"
#include <memory>


//Abstract visitor class for making an action with different numbers despite their type
class CVisitor {
public:

    /**
    Accepts an object of type CIntegerNumber and another number,
    and performs operation between them.
    @param[in] first The CIntegerNumber object to be visited.
    @param[in] other The other number to perform operation with.
    @returns A shared pointer to the result of the operation.
    **/
    virtual std::shared_ptr<CNumber> accept(const CIntegerNumber &first, const CNumber &other) const = 0;

    /**
    Accepts an object of type CDecimalNumber and another number,
    and performs operation between them.
    @param[in] first The CDecimalNumber object to be visited.
    @param[in] other The other number to perform operation with.
    @returns A shared pointer to the result of the operation.
    **/
    virtual std::shared_ptr<CNumber> accept(const CDecimalNumber &first, const CNumber &other) const = 0;
};
