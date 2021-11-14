//
// Created by omri on 09/11/2021.
//
#include "../include/Action.h"
#include <iostream>
#include "../include/Trainer.h"
#include "../include/Studio.h"
using namespace std;


BaseAction::BaseAction() {
    status = ERROR;
}

ActionStatus BaseAction::getStatus() const {
    return status;
}

void BaseAction::complete() {
    status = COMPLETED;
}

void BaseAction::error(std::string errorMsg) {
    this->errorMsg = errorMsg;
}

std::string BaseAction::getErrorMsg() const {
    return errorMsg;
}

OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList) : trainerId(id), customers(customersList){
    error("Workout session does not exist or is already open");
    cout << "FUCKING OPENED TRAINER" << endl;
}

void OpenTrainer::act(Studio &studio) {
    Trainer* trainer = studio.getTrainer(trainerId);
    if(trainer == nullptr || trainer->isOpen() || trainer->getCapacity() <= customers.size() ){
        cout << getErrorMsg() << endl;
    } else {
        cout << "else else else" << endl;
        trainer->openTrainer();
        for(auto customer: customers){
            trainer->addCustomer(customer);
            cout << "ACT: Added " + customer->getName() << endl;
        }
        for(auto customer : trainer->getCustomers()){
            cout << "ORDER OF OPEN TRAINER" << endl;
            trainer->order(customer->getId(), customer->order(studio.getWorkoutOptions()), studio.getWorkoutOptions());
        }
        complete();
    }
}

std::string OpenTrainer::toString() const {
    string str;
    str = "open " + to_string(trainerId);
    for(auto customer: customers){
        str +=" " + customer->getName() + "," + customer->toString();
    }
    if(getStatus() == COMPLETED) {
        str += " Completed";
    } else {
        str += " Error: " + getErrorMsg();
    }
    return str;
}

Order::Order(int id): trainerId(id) {
    error("Trainer does not exist or is not open");
}

void Order::act(Studio &studio) {
    Trainer* trainer = studio.getTrainer(trainerId);
    if(trainer == nullptr || trainer->isOpen() == false){
        cout << getErrorMsg() << endl;

    } else {
        cout << trainer->getOrders().size() << endl; //PRINTING SIZE OF ORDER LIST
        for(auto order : trainer->getOrders()){
            cout << trainer->getCustomer(order.first)->getName() + " Is Doing " + order.second.getName() << endl;
        }
        complete();
    }
}

std::string Order::toString() const {
    string str;
    str = "order " + to_string(trainerId);
    if(getStatus() == COMPLETED) {
        str += " Completed";
    } else {
        str += " Error: " + getErrorMsg();
    }
    return str;
}

MoveCustomer::MoveCustomer(int src, int dst, int customerId): srcTrainer(src), dstTrainer(dst), id(customerId){
    error("Cannot move customer");
}

void MoveCustomer::act(Studio &studio) {
    Trainer* sourceTrainer = studio.getTrainer(srcTrainer);
    Trainer* destTrainer = studio.getTrainer(dstTrainer);
    if(sourceTrainer == nullptr || destTrainer == nullptr || !sourceTrainer->isOpen() || !destTrainer->isOpen() || sourceTrainer->getCustomer(id) == nullptr || destTrainer->getCapacity() <= destTrainer->getCustomers().size()){
        cout << getErrorMsg() << endl;
    } else {
        Customer* customer = sourceTrainer->getCustomer(id);
        sourceTrainer->reduceSalary(id);
        sourceTrainer->removeCustomer(id);
        sourceTrainer->addCustomer(customer);
        sourceTrainer->order(id, customer->order(studio.getWorkoutOptions()), studio.getWorkoutOptions());
        complete();
    }
}

std::string MoveCustomer::toString() const {
    string str;
    str = "move " + to_string(srcTrainer) + " " + to_string(dstTrainer) + " " + to_string(id);
    if(getStatus() == COMPLETED) {
        str += " Completed";
    } else {
        str += " Error: " + getErrorMsg();
    }
    return str;
}

Close::Close(int id): trainerId(id){
    error("Trainer does not exist or is not open");
}

void Close::act(Studio &studio) {
    Trainer* trainer = studio.getTrainer(trainerId);
    if(trainer == nullptr || !trainer->isOpen()) {
        cout << getErrorMsg() << endl;
    } else{
        trainer->getCustomers().clear();
        trainer->getOrders().clear();
        cout << "Trainer " + to_string(trainerId) + " closed. Salary " + to_string(trainer->getSalary()) + "NIS" << endl;
        complete();
    }
}

std::string Close::toString() const {
    string str = "close " + to_string(trainerId);
    if(getStatus() == COMPLETED) {
        str += " Completed";
    } else {
        str += " Error: " + getErrorMsg();
    }
    return str;
}

CloseAll::CloseAll() {
}

void CloseAll::act(Studio &studio) {
    for(int i = 0; i< studio.getNumOfTrainers(); i++) {
        if(studio.getTrainer(i)->isOpen()) {
            Close closeCurr = Close(i);
            closeCurr.act(studio);
        } else {
            cout << "Trainer " + to_string(i) + " closed. Salary " + to_string(studio.getTrainer(i)->getSalary()) + "NIS" << endl;
            complete();
        }
    }

}

std::string CloseAll::toString() const {
    return "closeall Completed";
}

PrintWorkoutOptions::PrintWorkoutOptions() {

}

void PrintWorkoutOptions::act(Studio &studio) {
    vector<Workout> workouts = studio.getWorkoutOptions();
    for(auto workout : workouts){
        cout << workout.getName() + ", " + to_string(workout.getType()) + ", " + to_string(workout.getPrice()) << endl;
    }
    complete();
}

std::string PrintWorkoutOptions::toString() const {
    return "workout_options Completed";
}

PrintTrainerStatus::PrintTrainerStatus(int id): trainerId(id) {

}

void PrintTrainerStatus::act(Studio &studio) {
    Trainer* trainer = studio.getTrainer(trainerId);
    if(!trainer->isOpen()){
        cout << "Trainer " + to_string(trainerId) + " status: closed" << endl;
    } else {
        cout << "Trainer " + to_string(trainerId) + " status: open" << endl;
        cout << "Customers:" << endl;
        for(auto customer : trainer->getCustomers()){
            cout << to_string(customer->getId()) + " " + customer->getName() << endl;
        }
        cout << "Orders:" << endl;
        for(auto workout: trainer->getOrders()){
            cout << workout.second.getName() + " " + to_string(workout.second.getPrice()) + "NIS " + to_string(workout.first) << endl;
        }
        cout << "Current Trainer's Salary: " + to_string(trainer->getSalary()) + "NIS" << endl;
        complete();
    }
}

std::string PrintTrainerStatus::toString() const {
    return "status " + to_string(trainerId) + " Completed";
}

PrintActionsLog::PrintActionsLog() {

}

void PrintActionsLog::act(Studio &studio) {
    vector<BaseAction*> actions = studio.getActionsLog();
    for(auto action : actions){
        cout << action->toString() << endl;
    }
}

std::string PrintActionsLog::toString() const {
    return "log";
}
