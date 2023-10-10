#include <iostream>
#include <vector>
#include <string>

int main()
{
    std::string stringInput;
    std::vector <float> numbsFromString;
    bool canSolve = false;

    do{
        std::cout << "Enter your equation: ";
        std::getline(std::cin, stringInput);
        for (unsigned i = 0; i < stringInput.size(); i++){
            if (stringInput[i] <= ')' || stringInput[i] >= ':'){
                std::cout << "I dont know what is " << stringInput[i] << ".\nTry again.\n";
                break;
            }
            if (stringInput[i] == '/' && stringInput[i+1] == '0'){
                std::cout << "You cant divide by zero.\nTry again.\n";
                break;
            }

            if ( stringInput[i] == stringInput.back())
                canSolve = true;
        }
    }while (!canSolve);

    std::vector <int> operationsFromString;
    /* 0 - nothing,
      1 - "*",
      2 - "/" */
    for (unsigned i = 0; i < stringInput.size(); i++){
        if (stringInput[i] >= '0' && stringInput[i] <= '9'){
            float numb = 0.f;
            while (stringInput[i] >= '0' && stringInput[i] <= '9'){
                numb = numb * 10.f + (stringInput[i] - '0');
                i++;
            }
            numbsFromString.emplace_back(numb);
            operationsFromString.emplace_back(0);
            i--;
        }
        else {
            switch (stringInput[i]) {
            case '+':
                break;

            case '-':
                i++;
                {float numb = 0.f;
                while (stringInput[i] >= '0' && stringInput[i] <= '9'){
                    numb = numb * 10.f + (stringInput[i] - '0');
                    i++;
                }
                numbsFromString.emplace_back(-numb);}
                operationsFromString.emplace_back(0);
                i--;
                break;

            case '*':
                operationsFromString.emplace_back(1);
                numbsFromString.emplace_back(0);
                break;

            case '/':
                operationsFromString.emplace_back(2);
                numbsFromString.emplace_back(0);
                break;

            default:
                std::cout << "Error with: " << stringInput[i] << std::endl;
                break;
            }
        }
    }

    for (unsigned i = 0; i < operationsFromString.size(); i++){
        if (operationsFromString[i] == 1){
            numbsFromString[i-1] =  numbsFromString[i-1] * numbsFromString[i+1];
            numbsFromString.erase(numbsFromString.begin() + i, numbsFromString.begin() + i + 2);
            operationsFromString.erase(operationsFromString.begin() + i, operationsFromString.begin() + i + 2);
            i--;
        }
    }
    for (unsigned i = 0; i < operationsFromString.size(); i++){
        if (operationsFromString[i] == 2){
            numbsFromString[i-1] = numbsFromString[i-1] / numbsFromString[i+1];
            numbsFromString.erase(numbsFromString.begin() + i, numbsFromString.begin() + i + 2);
            operationsFromString.erase(operationsFromString.begin() + i, operationsFromString.begin() + i + 2);
            i--;
        }
    }

    float result = 0;
    for (unsigned i = 0; i < numbsFromString.size(); i++)
        result += numbsFromString[i];

    std::cout << "Result is " << result << std::endl;
    return 0;
}
