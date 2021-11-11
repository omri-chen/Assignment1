//
// Created by omri on 08/11/2021.
//
#include <vector>
#include <string>
#include <algorithm>
#include "../include/Workout.h"
#include "../include/Customer.h"


Customer::Customer(std::string c_name, int c_id): name(c_name), id(c_id) {

}

std::string Customer::getName() const {
    return name;
}

int Customer::getId() const {
    return id;
}

SweatyCustomer::SweatyCustomer(std::string name, int id) : Customer(name, id) {

}

std::vector<int> SweatyCustomer::order(const std::vector<Workout> &workout_options) {
    std::vector<int> orders{};
    for(int i = 0; i < workout_options.size(); i++){
        if(workout_options.at(i).getType() == CARDIO){
            orders.push_back(workout_options.at(i).getId());
        }
    }
    return orders;
}


CheapCustomer::CheapCustomer(std::string name, int id) : Customer(name, id) {

}

std::vector<int> CheapCustomer::order(const std::vector<Workout> &workout_options) {
    std::vector<int> orders{};
    int cheapest_id = 0;
    for(int i = 1; i < workout_options.size(); i++){
        if(workout_options.at(i).getPrice() < workout_options.at(cheapest_id).getPrice()){
            cheapest_id = i;
        }
    }
    orders.push_back(cheapest_id);
    return orders;
}

HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id) : Customer(name, id) {

}

std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout> &workout_options) {
    std::vector<std::pair<int, int>> priceAndId{};
    for(int i = 0; i < workout_options.size(); i++){
        if(workout_options.at(i).getType() == ANAEROBIC){
            int price = workout_options.at(i).getPrice();
            int workout_id = workout_options.at(i).getId();
            priceAndId.push_back(std::make_pair(price,workout_id));
        }
    }
    std::sort(priceAndId.begin(), priceAndId.end());
    std::vector<int> orders{};
    for(int i = priceAndId.size()-1; i>=0; i--){
        orders.push_back(priceAndId.at(i).second);
    }
    return orders;
}

FullBodyCustomer::FullBodyCustomer(std::string name, int id) : Customer(name, id) {

}

std::vector<int> FullBodyCustomer::order(const std::vector<Workout> &workout_options) {
    std::pair<int, int> cardio(INTMAX_MAX,0);
    std::pair<int,int> mixed(0,0);
    std::pair<int, int> anaerobic(INTMAX_MAX, 0);
    for(int i = 0; i < workout_options.size(); i++){
        Workout temp = workout_options.at(i);
        if(temp.getType() == CARDIO) {
            if (temp.getPrice() < cardio.first) {
                cardio.first = temp.getPrice();
                cardio.second = temp.getId();
            }
        } else if(temp.getType() == MIXED) {
            if (temp.getPrice() > mixed.first) {
                mixed.first = temp.getPrice();
                mixed.second = temp.getId();
            }
        } else if(temp.getType() == ANAEROBIC){
            if(temp.getPrice() < anaerobic.first){
                anaerobic.first = temp.getPrice();
                anaerobic.second = temp.getId();
            }
        }
    }
    std::vector<int> orders{};
    orders.push_back(cardio.second);
    orders.push_back(mixed.second);
    orders.push_back(anaerobic.second);
    return orders;

}
