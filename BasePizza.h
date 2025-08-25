#ifndef BASEPIZZA_H
#define BASEPIZZA_H

#include "Pizza.h"
#include "PizzaComponent.h"
#include <string>

// Concrete pizza implementation that wraps a PizzaComponent (from Composite pattern)
class BasePizza : public Pizza {
private:
    PizzaComponent* toppings;
    bool ownsComponent; // Flag to track ownership for proper cleanup

public:
    BasePizza(PizzaComponent* toppingComponent);
    virtual ~BasePizza();
    
    // Copy constructor and assignment operator
    BasePizza(const BasePizza& other);
    BasePizza& operator=(const BasePizza& other);
    
    virtual double getPrice() override;
    virtual std::string getName() override;
    virtual void printPizza() override;
    
    // Getter for the toppings component
    PizzaComponent* getToppings() const;

    Pizza* clone() const override;
};

#endif