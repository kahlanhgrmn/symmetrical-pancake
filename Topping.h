#ifndef TOPPING_H
#define TOPPING_H

#include "PizzaComponent.h"
#include <string>
#include <map>

class Topping : public PizzaComponent {
private:
    // Static map to store predefined topping prices
    static std::map<std::string, double> toppingPrices;
    
    // Static method to initialize the price map
    static std::map<std::string, double> initializeToppingPrices();

public:
    // Constructor with topping name (price is looked up automatically)
    Topping(const std::string& toppingName);
    
    // Override virtual methods
    std::string getName() const override;
    double getPrice() const override;
    
    // Static method to check if a topping exists
    static bool isValidTopping(const std::string& toppingName);
    
    // Static method to get all available toppings
    static std::map<std::string, double> getAllToppings();
};

#endif