//
// Created by omri on 08/11/2021.
//

#include <vector>
#include "Customer.h"
#include "Workout.h"
#include "Trainer.h"

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
    std::vector<Customer *>::iterator it = customersList.begin();
 //   while (it != customersList.end()) {
 //       if (*it.id == id) { //we dont know
//            customersList.erase(it);
//            break;
//        }
 //   }
}

