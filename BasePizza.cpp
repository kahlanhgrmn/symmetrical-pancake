#include "BasePizza.h"
#include "ToppingGroup.h"
#include "Topping.h"
#include <iostream>

BasePizza::BasePizza(PizzaComponent* toppingComponent) 
    : toppings(toppingComponent), ownsComponent(true) {
}

BasePizza::~BasePizza() {
    if (ownsComponent && toppings != nullptr) {
        delete toppings;
    }
}

BasePizza::BasePizza(const BasePizza& other) : ownsComponent(true) {
    if (other.toppings != nullptr) {
        // Deep copy the component
        Topping* topping = dynamic_cast<Topping*>(other.toppings);
        if (topping) {
            this->toppings = new Topping(topping->getName());
        } else {
            ToppingGroup* group = dynamic_cast<ToppingGroup*>(other.toppings);
            if (group) {
                this->toppings = new ToppingGroup(*group);
            } else {
                this->toppings = nullptr;
            }
        }
    } else {
        this->toppings = nullptr;
    }
}

BasePizza& BasePizza::operator=(const BasePizza& other) {
    if (this != &other) {
        // Clean up existing resource
        if (ownsComponent && toppings != nullptr) {
            delete toppings;
        }
        
        // Deep copy from other
        if (other.toppings != nullptr) {
            Topping* topping = dynamic_cast<Topping*>(other.toppings);
            if (topping) {
                this->toppings = new Topping(topping->getName());
            } else {
                ToppingGroup* group = dynamic_cast<ToppingGroup*>(other.toppings);
                if (group) {
                    this->toppings = new ToppingGroup(*group);
                } else {
                    this->toppings = nullptr;
                }
            }
        } else {
            this->toppings = nullptr;
        }
        
        this->ownsComponent = true;
    }
    return *this;
}

Pizza* BasePizza::clone() const {
    if (toppings != nullptr) {
        // Deep copy the component
        Topping* topping = dynamic_cast<Topping*>(toppings);
        if (topping) {
            return new BasePizza(new Topping(topping->getName()));
        } else {
            ToppingGroup* group = dynamic_cast<ToppingGroup*>(toppings);
            if (group) {
                return new BasePizza(new ToppingGroup(*group));
            }
        }
    }
    return new BasePizza(nullptr);
}

double BasePizza::getPrice() {
    if (toppings != nullptr) {
        return toppings->getPrice();
    }
    return 0.0;
}

std::string BasePizza::getName() {
    if (toppings != nullptr) {
        return toppings->getName();
    }
    return "Empty Pizza";
}

void BasePizza::printPizza() {
    std::cout << "Pizza: " << getName() << std::endl;
    std::cout << "Price: R" << getPrice() << std::endl;
}

PizzaComponent* BasePizza::getToppings() const {
    return toppings;
}