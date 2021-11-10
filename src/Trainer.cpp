//
// Created by omri on 08/11/2021.
//

#include <vector>
#include "../include/Customer.h"
#include "../include/Workout.h"
#include "../include/Trainer.h"

Trainer::Trainer(int t_capacity){
    capacity = t_capacity;
    open = false;
    customersList = std::vector<Customer*>();
    orderList = std::vector<OrderPair>();
}

int Trainer::getCapacity() const {
    return capacity;
}

void Trainer::addCustomer(Customer *customer) {
    customersList.push_back(customer);
}

void Trainer::removeCustomer(int id) {
    for(int i = 0; i < customersList.size(); i++){
        if(customersList.at(i)->getId() == id){
            customersList.erase(customersList.begin()+i);
            break;
        }
        //Need to update trainer's salary and order.
    }
}

Customer* Trainer::getCustomer(int id) {
    for(int i = 0; i < customersList.size(); i++){
        if(customersList.at(i)->getId() == id){
            return customersList.at(i);
        }
    }
    return nullptr;
}

std::vector<Customer *> &Trainer::getCustomers() {
    return customersList;
}

std::vector<OrderPair> &Trainer::getOrders() {
    return orderList;
}

void Trainer::openTrainer() {
    open = true;
}

void Trainer::closeTrainer() {
    open = false;
}

int Trainer::getSalary() {
    int salary = 0;
    for(int i = 0; i < orderList.size(); i++){
        salary += orderList.at(i).second.getPrice();
    }
    return salary;
}

bool Trainer::isOpen() {
    return open;
}


