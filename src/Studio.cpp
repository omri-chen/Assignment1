//
// Created by omri on 08/11/2021.
// trying to edit
#include <iostream>
#include "../include/Studio.h"
#include <string>
#include <fstream>
#include <istream>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <vector>
using namespace std;
using std::cout; using std::cin;
using std::endl; using std::string;
using std::vector; using std::istringstream;
using std::stringstream;
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
    std::cout << "Studio is now open!" << endl;
    open = true;
    std::string input;
    std::getline(cin, input);
    vector<string> words = splitInput(input);
    string command = words.at(0);
    while(command != "closeall"){
        //case 1:
        if(command == "open"){
            //OpenTrainer
            cout << "Open function called." << endl;
        } else if(command == "order"){
            //Order
            cout << "Order function called." << endl;
        } else if(command == "move"){
            //Move Customer
            cout << "Move customer called" << endl;
        } else if(command == "close"){
            //Closes a Trainer
            cout << "Close trainer called" << endl;
        } else if(command == "workout_options"){
            //Prints workout options
            cout << "Called workout options" << endl;
        } else if(command == "status"){
            //Status of trainer
            cout << "Status of Trainer" << endl;
        } else if(command == "log"){
            //Print actions log
            cout << "Actions log" << endl;
        } else if(command == "backup"){
            //Backup the studio
            cout << "Backup function called" << endl;
        } else if(command == "restore"){
            //Restore from backup
            cout << "Restore from backup" << endl;
        }
        getline(cin, input);
        words = splitInput(input);
        command = words.at(0);
    }
    if(command == "closeall"){
        //call closeall function
        cout << "CloseAll called" << endl;
    }
}

std::vector<std::string> Studio::splitInput(std::string input) {
    string word;
    vector<string> splittedInput{};
    istringstream ss(input);
    while(getline(ss, word, ' ')){
        splittedInput.push_back(word);
    }
    return splittedInput;
}

