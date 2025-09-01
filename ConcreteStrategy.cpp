#include "ConcreteStrategy.h"
#include "PizzaOrders.h"
#include <algorithm>

// ==================== RegularPrice Strategy ====================
double RegularPrice::applyDiscount(const PizzaOrders& order) const {
    (void)order;
    // No discount applied - return 0
    return 0.0;
}

std::string RegularPrice::getStrategyName() const {
    return "Regular Price";
}

std::string RegularPrice::getDescription() const {
    return "No discount applied - pay full price";
}

// ==================== FamilyDiscount Strategy ====================
double FamilyDiscount::applyDiscount(const PizzaOrders& order) const {
    double totalPrice = order.getTotalPrice();
    int pizzaCount = order.getPizzaCount();
    
    // Family discount: 15% off if ordering 3+ pizzas, 10% off if ordering 2+ pizzas
    if (pizzaCount >= 3) {
        return totalPrice * 0.15; // 15% discount
    } else if (pizzaCount >= 2) {
        return totalPrice * 0.10; // 10% discount
    }
    
    return 0.0; // No discount for single pizza
}

std::string FamilyDiscount::getStrategyName() const {
    return "Family Discount";
}

std::string FamilyDiscount::getDescription() const {
    return "10% off for 2+ pizzas, 15% off for 3+ pizzas";
}

// ==================== BulkDiscount Strategy ====================
double BulkDiscount::applyDiscount(const PizzaOrders& order) const {
    double totalPrice = order.getTotalPrice();
    
    // Bulk discount based on total price
    if (totalPrice >= 500.0) {
        return totalPrice * 0.20; // 20% discount for orders R500+
    } else if (totalPrice >= 300.0) {
        return totalPrice * 0.15; // 15% discount for orders R300+
    } else if (totalPrice >= 150.0) {
        return totalPrice * 0.10; // 10% discount for orders R150+
    }
    
    return 0.0; // No discount for orders under R150
}

std::string BulkDiscount::getStrategyName() const {
    return "Bulk Discount";
}

std::string BulkDiscount::getDescription() const {
    return "10% off R150+, 15% off R300+, 20% off R500+";
}

// ==================== StudentDiscount Strategy ====================
double StudentDiscount::applyDiscount(const PizzaOrders& order) const {
    double totalPrice = order.getTotalPrice();
    
    // Student discount: flat 12% off entire order
    return totalPrice * 0.12;
}

std::string StudentDiscount::getStrategyName() const {
    return "Student Discount";
}

std::string StudentDiscount::getDescription() const {
    return "12% off entire order with valid student ID";
}

// ==================== SeniorDiscount Strategy ====================
double SeniorDiscount::applyDiscount(const PizzaOrders& order) const {
    double totalPrice = order.getTotalPrice();
    int pizzaCount = order.getPizzaCount();
    
    // Senior discount: 15% off, plus additional 5% if ordering 2+ pizzas
    double discount = totalPrice * 0.15; // Base 15% discount
    
    if (pizzaCount >= 2) {
        discount += totalPrice * 0.05; // Additional 5% for multiple pizzas
    }
    
    return discount;
}

std::string SeniorDiscount::getStrategyName() const {
    return "Senior Discount";
}

std::string SeniorDiscount::getDescription() const {
    return "15% off entire order, +5% extra for 2+ pizzas (ages 65+)";
}

// ==================== LoyaltyDiscount Strategy ====================
LoyaltyDiscount::LoyaltyDiscount(int customerTier) : tier(customerTier) {
    // Ensure tier is within valid range (1-5)
    this->tier = std::max(1, std::min(5, customerTier));
}

double LoyaltyDiscount::applyDiscount(const PizzaOrders& order) const {
    double totalPrice = order.getTotalPrice();
    
    // Loyalty discount based on customer tier (1-5)
    // Tier 1: 5%, Tier 2: 8%, Tier 3: 12%, Tier 4: 16%, Tier 5: 20%
    double discountRate = 0.04 + (tier * 0.04); // 4% base + 4% per tier
    
    return totalPrice * discountRate;
}

std::string LoyaltyDiscount::getStrategyName() const {
    return "Loyalty Discount (Tier " + std::to_string(tier) + ")";
}

std::string LoyaltyDiscount::getDescription() const {
    double percentage = (0.04 + (tier * 0.04)) * 100;
    return std::to_string(static_cast<int>(percentage)) + "% off for loyal customers (Tier " + std::to_string(tier) + ")";
}

int LoyaltyDiscount::getTier() const {
    return tier;
}

void LoyaltyDiscount::setTier(int newTier) {
    this->tier = std::max(1, std::min(5, newTier));
}