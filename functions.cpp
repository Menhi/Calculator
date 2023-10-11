#include <iostream>
#include <vector>
#include <string>

void enterEquation (std::string &stringInput){
    bool canSolve = false;
    do{
        std::cout << "Enter your equation: ";
        std::getline(std::cin, stringInput);
        for (unsigned i = 0; i < stringInput.size(); i++){
            if (stringInput[i] <= ')' || stringInput[i] >= ':'){
                std::cout << R"(I dont know what is ")" << stringInput[i] << R"(")" <<".\nTry again.\n\n";
                break;
            }
            if (stringInput[i] == '/' && stringInput[i+1] == '0' && stringInput[i+2] != '.'){
                std::cout << "You cant divide by zero.\nTry again.\n\n";
                break;
            }
            if (stringInput[i] == '*' && (stringInput[i+1] == '*' || stringInput[i+1] == '+' || stringInput[i+1] == '/')){
                std::cout << "You cant do this operations: " << stringInput[i] << stringInput[i+1] << std::endl;
                break;
            }
            if (stringInput[i] == '/' && (stringInput[i+1] == '*' || stringInput[i+1] == '+' || stringInput[i+1] == '/')){
                std::cout << "You cant do this operations: " << stringInput[i] << stringInput[i+1] << std::endl;
                break;
            }
            if ( i == stringInput.size() - 1)
                canSolve = true;
        }
    }while (!canSolve);
}

template <typename T>
void eraseCurrentAndNext2Blocks (std::vector<T> &vector, unsigned &i){
    vector.erase(vector.begin() + i, vector.begin() + i + 2);
    i--;
}

float fromStrToFloat (std::string str, unsigned &i){
    float intNumb = 0.f;
    int k;
    i == 0 ? k = 1 : (str[i-1] == '-'? k = (-1) : k = 1);
    while (str[i] >= '0' && str[i] <= '9'){
        intNumb = intNumb * 10.f + (str[i] - '0');
        i++;
    }

    if (str[i] == '.' || str[i] == ','){
        i++;
        int j = 1;
        float fractionalNumb = 0.f;
        while (str[i] >= '0' && str[i] <= '9'){
            j*=10;
            fractionalNumb += float(str[i] - '0')/j;
            i++;
        }
        intNumb += fractionalNumb;
    }
    return intNumb*k;
}
