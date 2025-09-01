#include "Menus.h"
#include <algorithm>
#include <iostream>

Menus::~Menus(){
    clearPizzas();
}

void Menus::addObserver(Observer* observer){
    if(observer != nullptr){
        auto it = std::find(observers.begin(), observers.end(), observer);

        if(it == observers.end()){
            observers.push_back(observer);
        }
    }
}

void Menus::removeObserver(Observer* observer){
    if(observer != nullptr){
        auto it = std::find(observers.begin(), observers.end(), observer);

        if(it != observers.end()){
            observers.erase(it);
        }
    }
}

void Menus::addPizza(Pizza* pizza){
    if(pizza != nullptr){
        pizzas.push_back(pizza);
    }
}

void Menus::removePizza(Pizza* pizza){
    if(pizza != nullptr){
        auto it = std::find(pizzas.begin(), pizzas.end(), pizza);

        if(it != pizzas.end()){
            pizzas.erase(it);
        }
    }
}

std::vector<Pizza*> Menus::getPizzas() const{
    return pizzas;
}

int Menus::getPizzaCount() const{
    return static_cast<int>(pizzas.size());
}

void Menus::clearPizzas(){
    for(auto* pizza : pizzas){
        delete pizza;
    }
    
    pizzas.clear();
}