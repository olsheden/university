//
// Created by Denis Olshevskiy on 11.06.2023.
//

#include "cassert"
#include "memory"
#include "../src/CNumber.h"
#include "../src/CIntegerNumber.h"
#include "../src/CDecimalNumber.h"

int main()
{
    std::shared_ptr<CNumber> number1 = CIntegerNumber("12432975887921498218964192412864216467812124", true).clone();
    std::shared_ptr<CNumber> number2 = CDecimalNumber("91248918921892478124789174218412874781245681.3", true).clone();

    assert(number1->add(*number2)->toString() == "103681894809813976343753366631277091249057805.3");

    assert(number1->multiply(*number2)->toString() == "1134495608754792933201110695102317315723687476635504664952829713530946173670938334780081.2");

    assert(number1->subtract(*number2)->toString() == "-7881594333970979905824981805548658313433557.3");

    number2 = CIntegerNumber("9999999999999999999999999999999999999999", true).clone();

    assert(number1->divide(*number2)->toString() == "1243.2975887921498218964192412864216467813367"); //remainder is 2975887921498218964192412864216467813367

    number1 = CIntegerNumber("31",true).clone();

    assert(number1->factorial()->toString() == "8222838654177922817725562880000000");

    number1 = CDecimalNumber("28410972094719024.592478124781", true).clone();

    assert(number1->round()->toString() == "28410972094719025");

    assert(number1->multiply(*number2)->toString() == "284109720947190245924781247809999999999971589027905280975.407521875219");

    
}
