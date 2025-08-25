#ifndef PIZZADECORATOR_H
#define PIZZADECORATOR_H

#include "Pizza.h"
#include <string>

// Abstract decorator class that wraps a Pizza
class PizzaDecorator : public Pizza {
protected:
    Pizza* pizza;

public:
    PizzaDecorator(Pizza* pizzaToDecorate);
    virtual ~PizzaDecorator();
    
    // Copy constructor and assignment operator
    PizzaDecorator(const PizzaDecorator& other);
    PizzaDecorator& operator=(const PizzaDecorator& other);
    
    virtual double getPrice() override;
    virtual std::string getName() override;
    
    // Getter for the wrapped pizza
    Pizza* getWrappedPizza() const;

    virtual Pizza* clone() const override = 0;
};

#endif