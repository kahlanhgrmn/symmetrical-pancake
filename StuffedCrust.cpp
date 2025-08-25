#include "StuffedCrust.h"
#include <iostream>

const double StuffedCrust::STUFFED_CRUST_PRICE = 20.00;

StuffedCrust::StuffedCrust(Pizza* pizzaToDecorate) : PizzaDecorator(pizzaToDecorate) {
}

double StuffedCrust::getPrice() {
    return PizzaDecorator::getPrice() + STUFFED_CRUST_PRICE;
}

std::string StuffedCrust::getName() {
    return PizzaDecorator::getName() + " + Stuffed Crust";
}

void StuffedCrust::printPizza() {
    std::cout << "Pizza with Stuffed Crust: " << getName() << std::endl;
    std::cout << "Price: R" << getPrice() << std::endl;
}

double StuffedCrust::getStuffedCrustPrice() {
    return STUFFED_CRUST_PRICE;
}

Pizza* StuffedCrust::clone() const {
    Pizza* clonedWrappedPizza = pizza->clone();
    return new StuffedCrust(clonedWrappedPizza);
}