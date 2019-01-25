#include <iostream>

#include "LongInt.h"

int main() {
    std::string number1, number2, operation;

    while (std::cin >> number1 >> number2 >> operation) {
        LongInt num1(number1);
        LongInt num2(number2);
        LongInt res;

        if (operation == "+") {
            res = num1 + num2;
        }
        else if (operation == "-") {
            if (num1 < num2) {
                std::cout << "Error" << std::endl;
                continue;
            }
            res = num1 - num2;
        }
        else if (operation == "*") {
            res = num1 * num2;
        }
        else if (operation == "/") {
            if (num2 == 0) {
                std::cout << "Error" << std::endl;
                continue;
            }
            res = num1 / num2;
        }
        else if (operation == "^") {
            if (num1 == 0 && num2 == 0) {
                std::cout << "Error" << std::endl;
                continue;
            }
            res = num1.Pow(num2);
        }
        else if (operation == "<") {
            std::cout << ((num1 < num2) ? "true" : "false") << std::endl;
        }
        else if (operation == ">") {
            std::cout << ((num1 > num2) ? "true" : "false") << std::endl;
        }
        else if (operation == "=") {
            std::cout << ((num1 == num2) ? "true" : "false") << std::endl;
        }

        if (!res.Empty()) {
            std::cout << res << std::endl;
        }
    }

    return 0;
}