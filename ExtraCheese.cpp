#include "ExtraCheese.h"
#include <iostream>

const double ExtraCheese::EXTRA_CHEESE_PRICE = 12.00;

ExtraCheese::ExtraCheese(Pizza* pizzaToDecorate) : PizzaDecorator(pizzaToDecorate) {
}

double ExtraCheese::getPrice() {
    return PizzaDecorator::getPrice() + EXTRA_CHEESE_PRICE;
}

std::string ExtraCheese::getName() {
    return PizzaDecorator::getName() + " + Extra Cheese";
}

void ExtraCheese::printPizza() {
    std::cout << "Pizza with Extra Cheese: " << getName() << std::endl;
    std::cout << "Price: R" << getPrice() << std::endl;
}

double ExtraCheese::getExtraCheesePrice() {
    return EXTRA_CHEESE_PRICE;
}

Pizza* ExtraCheese::clone() const {
    Pizza* clonedWrappedPizza = pizza->clone();
    return new ExtraCheese(clonedWrappedPizza);
}