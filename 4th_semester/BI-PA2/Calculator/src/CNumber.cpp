/**
 * @author Denis Olshevskiy <olsheden@fit.cvut.cz>
 * @date 12.05.2021
 */
#include "CNumber.h"

bool CNumber::getIsPositive() const {
    return m_isPositive;
}

bool &CNumber::getIsPositive() {
    return m_isPositive;
}

void CNumber::setPositive(const bool &isPositive) {
    m_isPositive = isPositive;
}