//
// Created by omri on 09/11/2021.
//
#include "../include/Action.h"
#include <iostream>
#include "../include/Trainer.h"
using namespace std;


BaseAction::BaseAction() {

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
}

void OpenTrainer::act(Studio &studio) {
    Trainer* trainer = studio.getTrainer(trainerId);
    if(trainer == nullptr || trainer->isOpen() == false || trainer->getCapacity() < customers.size() ){
        cout << getErrorMsg() << endl;
    } else {
        trainer->openTrainer();
        for(auto customer: customers){
            trainer->addCustomer(customer);
        }
        complete();
    }
}

Order::Order(int id): trainerId(id) {
    error("Trainer does not exist or is not open");
}

void Order::act(Studio &studio) {
    Trainer* trainer = studio.getTrainer(trainerId);
    if(trainer == nullptr || trainer->isOpen() == false){
        cout << getErrorMsg() << endl;
    } else {
        for(auto customer : trainer->getCustomers()){
            trainer->order(customer->getId(), customer->order(studio.getWorkoutOptions()), studio.getWorkoutOptions());
        }
        for(auto order : trainer->getOrders()){
            cout << trainer->getCustomer(order.first)->getName() + " Is Doing " + order.second.getName() << endl;
        }
    }
}
