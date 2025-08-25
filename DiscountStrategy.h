#ifndef DISCOUNTSTRATEGY_H
#define DISCOUNTSTRATEGY_H

class PizzaOrders;
#include <string>

class DiscountStrategy {
public:
    virtual ~DiscountStrategy() = default;
    virtual double applyDiscount(const PizzaOrders& order) const = 0;
    virtual std::string getStrategyName() const = 0;
    virtual std::string getDescription() const = 0;
};

#endif