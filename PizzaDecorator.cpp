#include "PizzaDecorator.h"
#include "BasePizza.h"

PizzaDecorator::PizzaDecorator(Pizza* pizzaToDecorate) 
    : pizza(pizzaToDecorate) {
}

PizzaDecorator::~PizzaDecorator() {
    delete pizza;  // Always delete the wrapped pizza
}

PizzaDecorator::PizzaDecorator(const PizzaDecorator& other) {
    if (other.pizza != nullptr) {
        this->pizza = other.pizza->clone(); // Use clone method for proper deep copy
    } else {
        this->pizza = nullptr;
    }
}

PizzaDecorator& PizzaDecorator::operator=(const PizzaDecorator& other) {
    if (this != &other) {
        delete pizza;  // Clean up existing pizza
        
        if (other.pizza != nullptr) {
            this->pizza = other.pizza->clone(); // Use clone method
        } else {
            this->pizza = nullptr;
        }
    }
    return *this;
}

double PizzaDecorator::getPrice() {
    if (pizza != nullptr) {
        return pizza->getPrice();
    }
    return 0.0;
}

Pizza* PizzaDecorator::getWrappedPizza() const {
    return pizza;
}

std::string PizzaDecorator::getName() {
    if (pizza != nullptr) {
        return pizza->getName();
    }
    return "Unknown Pizza";
}
