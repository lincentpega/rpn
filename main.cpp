#include <iostream>
#include <vector>
#include <string>
#include "stack.h"
#include "binary_number.h"

const int bitness = 8;

bool isNumber(const std::string& str) {
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}

void split(std::string &str, char del, std::vector<std::string>& vect) {
    std::string temp;

    for (char i : str) {
        if(i != del) {
            temp += i;
        }
        else if (!temp.empty()) {
            vect.push_back(temp);
            temp = "";
        }
    }

    vect.push_back(temp);
}

int processing(std::vector<std::string> &expr) {
    Stack stack;

    for (std::string &i: expr) {
        if (isNumber(i)){
            if (i.size() > pow(2, bitness - 1)){
                std::cerr << "Owerflow" << std::endl;
                exit(1);
            }
            else
                try{
                    stack.push(BinaryNumber(std::stoi(i), bitness));
                }
                catch(std::out_of_range &e){
                    std::cerr << "Owerflow" << std::endl;
                    exit(1);
                }
        }
        else if (i == "+" || i == "-" || i == "*" || i == "/") {
            BinaryNumber n1 = stack.pop();
            BinaryNumber n2 = stack.pop();

            switch (static_cast<char>(i[0])) {
                case '+': {
                    BinaryNumber result{n1 + n2};
                    stack.push(result);
                    break;
                }
                case '-': {
                    BinaryNumber result{n2 - n1};
                    stack.push(result);
                    break;
                }
                case '*': {
                    BinaryNumber result{n1 * n2};
                    stack.push(result);
                    break;
                }
            }
        }
        else {
            std::cerr << "Incorrect input" << std::endl;
            exit(1);
        }
    }
    if (stack.size() > 1) {
        std::cerr << "Incorrect input" << std::endl;
        exit(1);
    }
    else
        return stack.pop().to_decimal();
}


int main() {
    std::string input;
    char delimiter;

    std::cout << "Enter expression" << std::endl;
    std::getline(std::cin, input);

    std::vector<std::string> expression;
    split(input, ' ', expression);

    int result = processing(expression);
    BinaryNumber bin_res{result, bitness};
    std::cout << result << ' ' << bin_res;
}
