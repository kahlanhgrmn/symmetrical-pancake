#include "SpecialsMenu.h"
#include <iostream>

SpecialsMenu::SpecialsMenu(const std::string& name): menuName(name){
}

void SpecialsMenu::notifyObservers(const std::string& message){
    std::cout << "\nSpecials Menu Notification" << std::endl;
    std::cout << "Broadcasting from " << menuName << ": " << message << std::endl;
    
    for(Observer* observer : observers){

        if(observer != nullptr){
            observer->update(message);
        }
    }

    std::cout << "Special notification sent to " << observers.size() << " observers." << std::endl;
}

void SpecialsMenu::addSpecialOffer(Pizza* pizza, const std::string& specialDescription){
    if(pizza != nullptr){
        addPizza(pizza);

        specialOffers[pizza] = specialDescription;
        
        std::string message = "New special offer: " + pizza->getName() + 
                              " - " + specialDescription + 
                              " (R" + std::to_string(pizza->getPrice()) + ")";

        notifyObservers(message);
    }
}

void SpecialsMenu::removeSpecialOffer(Pizza* pizza){
    if(pizza != nullptr){
        std::string pizzaName = pizza->getName();
        std::string offer = getSpecialOffer(pizza);
        
        specialOffers.erase(pizza);
        removePizza(pizza);
        
        std::string message = "Special has ended: " + pizzaName + 
                              " special offer (" + offer + ") has ended.";

        notifyObservers(message);
    }
}

void SpecialsMenu::addPizza(Pizza* pizza){
    if(pizza != nullptr){
        Menus::addPizza(pizza);
    }
}

void SpecialsMenu::removePizza(Pizza* pizza){
    if(pizza != nullptr){
        Menus::removePizza(pizza);
    }
}

std::string SpecialsMenu::getMenuName() const{
    return menuName;
}

std::string SpecialsMenu::getSpecialOffer(Pizza* pizza) const{
    auto it = specialOffers.find(pizza);

    if(it != specialOffers.end()){
        return it->second;
    }

    return "No special offer";
}

void SpecialsMenu::displaySpecialsMenu() const{
    std::cout << "\n=== " << menuName << " ===" << std::endl;

    if(pizzas.empty()){
        std::cout << "No special offers currently available." << std::endl;
    } 
    
    else{
        for (size_t i = 0; i < pizzas.size(); ++i) {
            std::string offer = getSpecialOffer(pizzas[i]);
            std::cout << (i + 1) << ". " << pizzas[i]->getName() 
                      << " - R" << pizzas[i]->getPrice() 
                      << " [" << offer << "]" << std::endl;
        }
    }
    std::cout << "==========================" << std::endl;
}