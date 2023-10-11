#include <iostream>
#include <vector>
#include <string>
#include <functions.cpp>
#include <iomanip>

int main()
{
    std::string stringInput;
    std::vector <float> numbsFromString;
    enterEquation (stringInput);

    std::vector <int> operationsFromString; /* 0 - nothing,
                                               1 - "*",
                                               2 - "/" */

    for (unsigned i = 0; i < stringInput.size(); i++){
        if (stringInput[i] >= '0' && stringInput[i] <= '9'){
            numbsFromString.emplace_back(fromStrToFloat(stringInput, i));
            operationsFromString.emplace_back(0);
            i--;
        }
        else {
            switch (stringInput[i]) {
            case '+':
                break;

            case '-':
                if (stringInput[i+1] == '-'){
                    i += 2;
                    numbsFromString.emplace_back(fromStrToFloat(stringInput, i) * (-1));
                    operationsFromString.emplace_back(0);
                    i--;
                }
                break;

            case '*':
                if ((stringInput[i+1] >= '0' && stringInput[i+1] <= '9') || (stringInput[i+1] == '-' && stringInput[i+2] >= '0' && stringInput[i+2] <= '9') ){
                    operationsFromString.emplace_back(1);
                    numbsFromString.emplace_back(0);
                }
                break;

            case '/':
                if ((stringInput[i+1] >= '0' && stringInput[i+1] <= '9') || (stringInput[i+1] == '-' && stringInput[i+2] >= '0' && stringInput[i+2] <= '9') ){
                    operationsFromString.emplace_back(2);
                    numbsFromString.emplace_back(0);
                }
                break;

            case '.' | ',':
                numbsFromString.emplace_back(fromStrToFloat(stringInput, i));
                operationsFromString.emplace_back(0);
                break;

            default:
                std::cout << "Error with: " << stringInput[i] << std::endl;
                break;
            }
        }
    }

    for (unsigned i = 1; i < operationsFromString.size(); i++){
        if (operationsFromString[i] == 1){
            numbsFromString[i-1] =  numbsFromString[i-1] * numbsFromString[i+1];
            eraseCurrentAndNext2Blocks(numbsFromString, i);
            eraseCurrentAndNext2Blocks(operationsFromString, i);
        }
        else if (operationsFromString[i] == 2){
            float epsilon = 1e-5;
            if (std::abs(numbsFromString[i+1] - 0) > epsilon) {
                numbsFromString[i-1] = numbsFromString[i-1] / numbsFromString[i+1];}
            else{
                std::cout<< "You cant divide by zero."; return 0;}
            eraseCurrentAndNext2Blocks(numbsFromString, i);
            eraseCurrentAndNext2Blocks(operationsFromString, i);
        }
    }

    float result = 0;
    for (auto numb : numbsFromString)
        result += numb;

    std::cout << "Result is " << result << std::endl;
    return 0;
}
