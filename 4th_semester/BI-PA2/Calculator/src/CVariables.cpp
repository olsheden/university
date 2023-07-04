/**
 * @author Denis Olshevskiy <olsheden@fit.cvut.cz>
 * @date 12.05.2021
 */
#include "./CVariables.h"

CVariables::CVariables() {}

CVariables::~CVariables() {}

const std::unordered_map<std::string, std::shared_ptr<CNumber>> &CVariables::getMap() const {
    return m_mapVariables;
}


std::unordered_map<std::string, std::shared_ptr<CNumber>> &CVariables::getMap() {
    return m_mapVariables;
}

const std::shared_ptr<CNumber> &CVariables::getValue(const std::string &variable) {
    if (m_mapVariables.find(variable) == m_mapVariables.end()) throw std::logic_error("The variable doesnt exist");
    return m_mapVariables.find(variable)->second;
}

void CVariables::setValue(const std::string &variable, const std::shared_ptr<CNumber> &value) {
    auto it = m_mapVariables.find(variable);
    if (it == m_mapVariables.end()) m_mapVariables.insert(std::make_pair(variable, value));
    else {
        it->second = value;
    }
}