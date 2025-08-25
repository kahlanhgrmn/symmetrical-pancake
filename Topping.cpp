#include "Topping.h"
#include <iostream>

// Initialize the static map with predefined topping prices
std::map<std::string, double> Topping::toppingPrices = Topping::initializeToppingPrices();

std::map<std::string, double> Topping::initializeToppingPrices() {
    std::map<std::string, double> prices;
    
    // Base ingredients
    prices["Dough"] = 10.00;
    prices["Tomato Sauce"] = 5.00;
    prices["Cheese"] = 15.00;
    
    // Toppings
    prices["Pepperoni"] = 20.00;
    prices["Mushrooms"] = 12.00;
    prices["Green Peppers"] = 10.00;
    prices["Onions"] = 8.00;
    prices["Beef Sausage"] = 25.00;
    prices["Salami"] = 22.00;
    prices["Feta Cheese"] = 18.00;
    prices["Olives"] = 15.00;
    
    return prices;
}

Topping::Topping(const std::string& toppingName) {
    auto it = toppingPrices.find(toppingName);
    if (it != toppingPrices.end()) {
        this->name = toppingName;
        this->price = it->second;
    } else {
        std::cerr << "Warning: Unknown topping '" << toppingName << "'. Using default values." << std::endl;
        this->name = toppingName;
        this->price = 0.0;
    }
}

std::string Topping::getName() const {
    return name;
}

double Topping::getPrice() const {
    return price;
}

bool Topping::isValidTopping(const std::string& toppingName) {
    return toppingPrices.find(toppingName) != toppingPrices.end();
}

std::map<std::string, double> Topping::getAllToppings() {
    return toppingPrices;
}