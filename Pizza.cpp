#include "Pizza.h"
#include <iostream>

void Pizza::printPizza() {
    std::cout << getName() << " - R" << getPrice() << std::endl;
}