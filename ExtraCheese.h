#ifndef EXTRACHEESE_H
#define EXTRACHEESE_H

#include "PizzaDecorator.h"
#include <string>

// Concrete decorator for adding extra cheese to a pizza
class ExtraCheese : public PizzaDecorator {
private:
    static const double EXTRA_CHEESE_PRICE;

public:
    ExtraCheese(Pizza* pizzaToDecorate);
    virtual ~ExtraCheese() = default;
    
    virtual double getPrice() override;
    virtual std::string getName() override;
    virtual void printPizza() override;
    
    // Static method to get the extra cheese price
    static double getExtraCheesePrice();

    virtual Pizza* clone() const override;
};

#endif