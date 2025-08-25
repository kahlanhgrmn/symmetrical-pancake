#ifndef CONCRETESTRATEGY_H
#define CONCRETESTRATEGY_H

#include "DiscountStrategy.h"
#include <string>

class RegularPrice : public DiscountStrategy {
public:
    double applyDiscount(const PizzaOrders& order) const override;
    std::string getStrategyName() const override;
    std::string getDescription() const override;
};

class FamilyDiscount : public DiscountStrategy {
public:
    double applyDiscount(const PizzaOrders& order) const override;
    std::string getStrategyName() const override;
    std::string getDescription() const override;
};

class BulkDiscount : public DiscountStrategy {
public:
    double applyDiscount(const PizzaOrders& order) const override;
    std::string getStrategyName() const override;
    std::string getDescription() const override;
};

class StudentDiscount : public DiscountStrategy {
public:
    double applyDiscount(const PizzaOrders& order) const override;
    std::string getStrategyName() const override;
    std::string getDescription() const override;
};

class SeniorDiscount : public DiscountStrategy {
public:
    double applyDiscount(const PizzaOrders& order) const override;
    std::string getStrategyName() const override;
    std::string getDescription() const override;
};

class LoyaltyDiscount : public DiscountStrategy {
private:
    int tier; // Customer loyalty tier (1-5)
    
public:
    explicit LoyaltyDiscount(int customerTier = 1);
    
    double applyDiscount(const PizzaOrders& order) const override;
    std::string getStrategyName() const override;
    std::string getDescription() const override;
    
    // Tier management
    int getTier() const;
    void setTier(int newTier);
};

#endif