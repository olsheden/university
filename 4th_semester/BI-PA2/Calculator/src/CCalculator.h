/**
 * @author Denis Olshevskiy <olsheden@fit.cvut.cz>
 * @date 12.05.2021
 */
#pragma once

#include "./CNumber.h"
#include "./CParsing.h"
#include "./CIntegerNumber.h"
#include "./CDecimalNumber.h"

class CCalculator {
private:

    //database of saved variables
    CVariables m_variables;

    CParsing m_parser;
public:
    CCalculator();

    /**
     * Destructor for CCalculator.
     */
    ~CCalculator();

    /**
     * Runs the calculator application.
     */
    void run();

    /**
     * Writes the variables to a file.
     */
    void writeVariables() const;

    /**
     * Reads the variables from a file.
     */
    void readVariables();

    /**
     * Prompts the user for input and performs the necessary calculations.
     *
     * @returns True if the input is successfully taken and processed, False if user wants to stop the program.
     */
    bool takeValue();
};