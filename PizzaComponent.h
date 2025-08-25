#ifndef PIZZACOMPONENT_H
#define PIZZACOMPONENT_H

#include <string>

class PizzaComponent {
protected:
    double price;
    std::string name;

public:
    // Constructor
    PizzaComponent(double price = 0.0, const std::string& name = "");
    
    // Virtual destructor
    virtual ~PizzaComponent() = default;
    
    // Pure virtual methods
    virtual std::string getName() const = 0;
    virtual double getPrice() const = 0;
};

#endif