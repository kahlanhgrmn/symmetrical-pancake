#ifndef PIZZA_H
#define PIZZA_H

#include <string>

// Abstract base class for all pizzas
class Pizza {
public:
    virtual ~Pizza() = default;
    virtual double getPrice() = 0;
    virtual std::string getName() = 0;
    virtual void printPizza();
    virtual Pizza* clone() const = 0;
};

#endif