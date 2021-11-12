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
        for(auto customer : trainer->getCustomers()){
            trainer->order(customer->getId(), customer->order(studio.getWorkoutOptions()), studio.getWorkoutOptions());
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
        for(auto order : trainer->getOrders()){
            cout << trainer->getCustomer(order.first)->getName() + " Is Doing " + order.second.getName() << endl;
        }
    }
}

MoveCustomer::MoveCustomer(int src, int dst, int customerId): srcTrainer(src), dstTrainer(dst), id(customerId){
    error("Cannot move customer");
}

void MoveCustomer::act(Studio &studio) {
    Trainer* srcTrainer = studio.getTrainer(srcTrainer);
    Trainer* dstTrainer = studio.getTrainer(dstTrainer);
    if(srcTrainer == nullptr || dstTrainer == nullptr || !srcTrainer->isOpen() || !dstTrainer->isOpen() || srcTrainer->getCustomer(id) == nullptr || dstTrainer->getCapacity() <= dstTrainer->getCustomers().size()){
        cout << getErrorMsg() << endl;
    } else {
        Customer* customer = srcTrainer->getCustomer(id);
        srcTrainer->reduceSalary(id);
        srcTrainer->removeCustomer(id);
        dstTrainer->addCustomer(customer);
        dstTrainer->order(id, customer->order(studio.getWorkoutOptions()), studio.getWorkoutOptions());
    }
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
    }
}

CloseAll::CloseAll() {
}

void CloseAll::act(Studio &studio) {
    for(int i = 0; i< studio.getNumOfTrainers(); i++) {
        if(studio.getTrainer(i).isOpen()) {
            Close closeCurr = Close(i);
            closeCurr.act(studio);
        } else {
            cout << "Trainer " + to_string(i) + " closed. Salary " + to_string(studio.getTrainer(i)->getSalary()) + "NIS" << endl;
        }
    }

}
