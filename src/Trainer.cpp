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
    salary = 0;
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
    }
    for(int i = 0; i < orderList.size(); i++){
        if(orderList.at(i).first == id) {
            orderList.erase(orderList.begin()+i);
        }
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
    customersList.clear();
    orderList.clear();
}

int Trainer::getSalary() {
    return salary;
}

bool Trainer::isOpen() {
    return open;
}

void
Trainer::order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout> &workout_options) {
    for(auto workout_id : workout_ids){
        orderList.push_back(std::make_pair(customer_id, workout_options.at(workout_id)));
        salary += workout_options.at(workout_id).getPrice();
    }
}

void Trainer::reduceSalary(int customer_id) {
    for(auto wrk: orderList) {
        if(wrk.first == customer_id){
            salary -= wrk.second.getPrice();
        }
    }
}


