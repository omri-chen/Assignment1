//
// Created by omri on 08/11/2021.
//
#include <iostream>
#include "Studio.h"
#include <string>
#include <fstream>
#include <istream>
#include <algorithm>
using namespace std;
Studio::Studio() {

}

Studio::Studio(const std::string &configFilePath){
    std::ifstream myFile;
    myFile.open(configFilePath);
    std::string myString;
    std::string myLine;
    if(myFile.is_open()){
        while(myFile){
            std::getline(myFile, myLine);
            if(not myLine.empty() && myLine.substr(0,1)!="#"){
                std:: cout << myLine << '\n';
            }
        }
    }
    else {
        std::cout << "Coudl'nt open file." << '\n';
    }
}

void Studio::start() {
    std::cout << "Studio is now open!";
    open = true;
    std::string input;
    int id;
    std::cin >> input >> id;
    while(input != "closeall"){
        cout << input;
        cout << id;
        std::cin >> input >> id;
    }

}

