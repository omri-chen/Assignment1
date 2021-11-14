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
    open = false;
    std::ifstream myFile;
    myFile.open(configFilePath);
    vector<string> configString;
    std::string myLine;
    if(myFile.is_open()){
        while(myFile){
            std::getline(myFile, myLine);
            if(not myLine.empty() && myLine.substr(0,1)!="#"){
                configString.push_back(myLine);
                std:: cout << myLine << '\n';
            }
        }
    }
    else {
        std::cout << "Couldn't open file." << '\n';
    }
    int numOfTrainers = stoi(configString.at(0));
    string cap;
    istringstream ss(configString.at(1));
    trainers = vector<Trainer*>{};
    while(getline(ss, cap, ',')){
        Trainer* trainer = new Trainer(stoi(cap));
        trainers.push_back(trainer);
        cout << "pushed trainer " + cap << endl;
    }
    workout_options = vector<Workout>{};
    for(int i = 2, j = 0 ; i < configString.size(); i++){
        vector<string> split;
        string word;
        istringstream ss(configString.at(i));
        while(getline(ss, word, ',')){
            split.push_back(word);
        }
        WorkoutType type;
        if(split.at(1) == "Anaerobic") {
            type = ANAEROBIC;
        } else if ( split.at(1) == "Mixed") {
            type = MIXED;
        } else {
            type = CARDIO;
        }
        Workout wrk = Workout(j, split.at(0), stoi(split.at(2)), type);
        workout_options.push_back(wrk);
    }
    actionsLog = vector<BaseAction*>{};

}

void Studio::start() {
    int id_counter = 0;
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
            vector<Customer*> customers{};
            int id = stoi(words.at(1));
            for(int i = 2; i < words.size(); i++){
                vector<string> cus = splitComma(words.at(i));
                string cus_name = cus.at(0);
                Customer* customer;
                if(cus.at(1) == "swt"){
                    customer = new SweatyCustomer(cus_name, id_counter);
                } else if(cus.at(1) == "chp"){
                    customer = new CheapCustomer(cus_name, id_counter);
                } else if(cus.at(1) == "msc"){
                    customer = new HeavyMuscleCustomer(cus_name, id_counter);
                } else {
                    customer = new FullBodyCustomer(cus_name, id_counter);
                }
                customers.push_back(customer);
                cout << cus_name + " " + customer->toString() + " added" << endl;
                id_counter++;
            }
            BaseAction* openTrainer = new OpenTrainer(id, customers);
            openTrainer->act(*this);
            actionsLog.push_back(openTrainer);
            cout << "Open function called." << endl;
        } else if(command == "order"){
            //Order
            int id = stoi(words.at(1));
            BaseAction* order = new Order(id);
            order->act(*this);
            actionsLog.push_back(order);
            cout << "Order function called." << endl;
        } else if(command == "move"){
            //Move Customer
            int src = stoi(words.at(1));
            int dst = stoi(words.at(2));
            int id = stoi(words.at(3));
            BaseAction* move = new MoveCustomer(src,dst,id);
            move->act(*this);
            actionsLog.push_back(move);
            cout << "Move customer called" << endl;
        } else if(command == "close"){
            //Closes a Trainer
            int id = stoi(words.at(1));
            BaseAction* closeTrainer = new Close(id);
            closeTrainer->act(*this);
            actionsLog.push_back(closeTrainer);
            cout << "Close trainer called" << endl;
        } else if(command == "workout_options"){
            //Prints workout options
            BaseAction* printWorkouts = new PrintWorkoutOptions();
            printWorkouts->act(*this);
            actionsLog.push_back(printWorkouts);
            cout << "Called workout options" << endl;
        } else if(command == "status"){
            //Status of trainer
            int id = stoi(words.at(1));
            BaseAction* printTrainer = new PrintTrainerStatus(id);
            printTrainer->act(*this);
            actionsLog.push_back(printTrainer);
            cout << "Status of Trainer" << endl;
        } else if(command == "log"){
            //Print actions log
            BaseAction* printLog = new PrintActionsLog();
            printLog->act(*this);
            actionsLog.push_back(printLog);
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
        BaseAction* closeAll = new CloseAll();
        closeAll->act(*this);
        actionsLog.push_back(closeAll);
        cout << "CloseAll called" << endl;
    }
}

int Studio::getNumOfTrainers() const {
    return trainers.size();
}

Trainer *Studio::getTrainer(int tid) {
    return trainers.at(tid);
}

const std::vector<BaseAction *> &Studio::getActionsLog() const {
    return actionsLog;
}

std::vector<Workout> &Studio::getWorkoutOptions() {
    return workout_options;
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

std::vector<std::string> Studio::splitComma(std::string input) {
    string word;
    vector<string> splittedInput{};
    istringstream ss(input);
    while(getline(ss, word, ',')){
        splittedInput.push_back(word);
    }
    return splittedInput;
}


