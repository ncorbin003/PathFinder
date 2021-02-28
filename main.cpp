
#include <iostream>
#include <limits.h>
#include "d_except.h"
#include <list>
#include <fstream>
#include "d_matrix.h"
#include <queue>
#include <vector>

int main()
{
    std::ifstream readFile;
    std::string fileName;
    std::string input;
    char spaceIndicator;
    //int numberHolder;
    int num1;
    int num2;

    std::cout << "Enter the text file you would like to read from:\n";
    std::cin >> fileName;
    readFile.open(fileName);
    //read the first 2 numbers from the file to create matrix
    if (readFile.is_open()) {
        std::cout << fileName + " is open\n";
        for (int i = 0; i < 2; i++) {
            if (i == 0) {
                readFile >> input;
                num1 = stoi(input);
            }
            if (i == 1) {
                readFile >> input;
                num2 = stoi(input);
            }
        }
        char myArray[num1][num2];

            for (int i = 0; i < num1; i++) {
                for(int j = 0; j < num2; j++) {
                    readFile >> spaceIndicator;
                    myArray[i][j] = spaceIndicator;
                }
            }

        for(int i = 0; i < num1; i++) {
            for(int j = 0; j < num2; j++) {
                std::cout << myArray[i][j];
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
    else {
        std::cout << "File not able to be opened.\n";
    }

    

    return 0;
}
