#include "PizzaMenu.h"
#include <iostream>

PizzaMenu::PizzaMenu(const std::string& name): menuName(name){
}

void PizzaMenu::notifyObservers(const std::string& message){
    std::cout << "\n[PIZZA MENU NOTIFICATION]" << std::endl;
    std::cout << "Broadcasting from " << menuName << ": " << message << std::endl;
    
    for(Observer* observer : observers){

        if(observer != nullptr){
            observer->update(message);
        }
    }

    std::cout << "Notification sent to " << observers.size() << " observers." << std::endl;
}

void PizzaMenu::addPizza(Pizza* pizza){

    if(pizza != nullptr){
        Menus::addPizza(pizza);

        std::string message = "New pizza flavour added: " + pizza->getName() + 
                              " is now available on our menu. Price: R" + 
                              std::to_string(pizza->getPrice());

        notifyObservers(message);
    }
}

void PizzaMenu::removePizza(Pizza* pizza){

    if(pizza != nullptr){
        std::string pizzaName = pizza->getName();
        Menus::removePizza(pizza);

        std::string message = "Pizza flavour removed: " + pizzaName + 
                              " is no longer available on our menu.";

        notifyObservers(message);
    }
}

std::string PizzaMenu::getMenuName() const{
    return menuName;
}

void PizzaMenu::displayMenu() const{
    std::cout << "\n=== " << menuName << " ===" << std::endl;

    if (pizzas.empty()){
        std::cout << "No pizzas currently available." << std::endl;
    } 
    
    else{
        for(size_t i = 0; i < pizzas.size(); ++i){
            
            std::cout << (i + 1) << ". " << pizzas[i]->getName() 
                      << " - R" << pizzas[i]->getPrice() << std::endl;
        }
    }
    std::cout << "=========================" << std::endl;
}