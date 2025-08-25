#ifndef STUFFEDCRUST_H
#define STUFFEDCRUST_H

#include "PizzaDecorator.h"
#include <string>

// Concrete decorator for adding stuffed crust to a pizza
class StuffedCrust : public PizzaDecorator {
private:
    static const double STUFFED_CRUST_PRICE;

public:
    StuffedCrust(Pizza* pizzaToDecorate);
    virtual ~StuffedCrust() = default;
    
    virtual double getPrice() override;
    virtual std::string getName() override;
    virtual void printPizza() override;
    
    // Static method to get the stuffed crust price
    static double getStuffedCrustPrice();

    Pizza* clone() const override;
};

#endif