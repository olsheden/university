/**
 * @author Denis Olshevskiy <olsheden@fit.cvut.cz>
 * @date 12.05.2021
 */
#pragma once

#include "./CNumber.h"
#include <string>
#include <unordered_map>

class CVariables {
private:

    //database of saved variables
    std::unordered_map<std::string, std::shared_ptr<CNumber>> m_mapVariables;
public:
    CVariables();

    ~CVariables();

    const std::unordered_map<std::string, std::shared_ptr<CNumber>> &getMap() const;

    std::unordered_map<std::string, std::shared_ptr<CNumber>> &getMap();

    // function to get a value from db by variable
    const std::shared_ptr<CNumber> &getValue(const std::string &variable);

    // function to set a value from db by variable
    void setValue(const std::string &variable, const std::shared_ptr<CNumber> &value);
};