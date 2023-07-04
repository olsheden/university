/**
 * @author Denis Olshevskiy <olsheden@fit.cvut.cz>
 * @date 12.05.2021
 */
#include "./CCalculator.h"
#include <fstream>

CCalculator::CCalculator() {}

CCalculator::~CCalculator() {}

void CCalculator::writeVariables() const {
    std::ofstream dataFile("./assets/variables.txt");
    if (!dataFile) {
        return;
    }
    dataFile.clear();
    for (const auto &pair: m_variables.getMap()) {
        dataFile << pair.first << " : " << pair.second->toString() << std::endl;
    }
    dataFile.close();
}

void CCalculator::readVariables() {
    std::ifstream dataFile("./assets/variables.txt");
    if (!dataFile) {
        std::cerr << "Error opening the file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(dataFile, line)) {
        std::string variable;
        std::string value;
        size_t i = 0;
        bool isName = true;
        bool isDecimal = false;
        bool isPositive = true;
        while (i < line.size()) {
            if (isspace(line[i])) {
                i++;
                continue;
            } else if (line[i] == ':') {
                isName = false;
                while (isspace(line[i]))i++;
                if (line[i] == '-') isPositive = false;
                else {
                    value += line[i];
                }
            } else if (line[i] == '.' && !isName) {
                isDecimal = true;
                variable += line[i];
            } else if (isName) {
                variable += line[i];
            } else {
                value += line[i];
            }
            i++;
        }
        if (variable.empty() || value.empty()) continue;
        if (isDecimal) m_variables.getMap().insert(std::make_pair(variable, CDecimalNumber(value, isPositive).clone()));
        else m_variables.getMap().insert(std::make_pair(variable, CIntegerNumber(value, isPositive).clone()));
    }

    dataFile.close();
}

void CCalculator::run() {
    std::cout << "The application is running..\nFor more information use command '/help' " << std::endl;
    readVariables();
    while (true) {
        if (!takeValue()) {
            writeVariables();
            std::cout << "Exitting the application..." << std::endl;
            return;
        }
    }
}

bool CCalculator::takeValue() {
    std::string input;
    std::getline(std::cin, input);
    if (input.empty()) {
        return false;
    } else if (input == "/help") {
        std::ifstream helpFile("./assets/help.txt", std::ios::in);
        if (helpFile.is_open()) {
            std::string line;
            while (std::getline(helpFile, line)) {
                //reads line by line
                std::cout << line << std::endl;
            }
            std::cout << std::endl;
            helpFile.close();
        } else {
            std::cout << "Failed to open the file." << std::endl;
        }
    } else if (input == "/variables") {
        for (const auto &pair: m_variables.getMap()) {
            std::cout << pair.first << " : " << pair.second->toString() << std::endl;
        }
    } else if (input.substr(0, 10) == "/variable ") {
        std::string variable = input.substr(10, input.size() - 1);
        if (m_variables.getMap().find(variable) == m_variables.getMap().end()) {
            std::cout << "Variable doesnt exist" << std::endl;
        } else {
            std::cout << m_variables.getMap().find(variable)->first << " = "
                      << m_variables.getMap().find(variable)->second->toString() << std::endl;
        }
    } else if (input == "/clear all") {
        m_variables.getMap().clear();
        std::cout << "Cleared successfully" << std::endl;
    } else if (input.substr(0, 7) == "/clear ") {
        std::string variable = input.substr(7, input.size() - 1);
        if (m_variables.getMap().find(variable) == m_variables.getMap().end()) {
            std::cout << "Variable doesnt exist" << std::endl;
        } else {
            m_variables.getMap().erase(variable);
            std::cout << "Cleared successfully" << std::endl;
        }
    } else if (input == "/exit") return false;
    else m_parser.parseTheString(input, m_variables);
    return true;
}