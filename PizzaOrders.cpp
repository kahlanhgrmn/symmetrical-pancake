#include "PizzaOrders.h"
#include "Topping.h"
#include "ConcreteStates.h"
#include <iostream>

// Constructors and Destructor
PizzaOrders::PizzaOrders() : currentState(nullptr), discountStrat(nullptr), orderNum(0), orderName("Guest") {
    currentState = new OrderingState();
}

PizzaOrders::PizzaOrders(int orderNumber, const std::string& customerName) 
    : currentState(nullptr), discountStrat(nullptr), orderNum(orderNumber), orderName(customerName) {
        currentState = new OrderingState();
}

PizzaOrders::~PizzaOrders() {
    clearOrder();
    // Clean up strategy if it exists
    delete discountStrat;
    delete currentState;
    // Note: currentState will be managed when State pattern is implemented
}

PizzaOrders::PizzaOrders(const PizzaOrders& other) 
    : currentState(nullptr), discountStrat(nullptr), orderNum(other.orderNum), orderName(other.orderName) {
    // Deep copy pizzas using clone method
    for (const auto& pizza : other.pizzas) {
        Pizza* clonedPizza = clonePizza(pizza);
        if (clonedPizza != nullptr) {
            pizzas.push_back(clonedPizza);
        }
    }
}

PizzaOrders& PizzaOrders::operator=(const PizzaOrders& other) {
    if (this != &other) {
        clearOrder();
        // Clean up existing strategy
        delete discountStrat;
        discountStrat = nullptr;
        
        orderNum = other.orderNum;
        orderName = other.orderName;
        
        // Deep copy pizzas using clone method
        for (const auto& pizza : other.pizzas) {
            Pizza* clonedPizza = clonePizza(pizza);
            if (clonedPizza != nullptr) {
                pizzas.push_back(clonedPizza);
            }
        }
        
        // Note: Strategy patterns are not copied - they should be set explicitly
        // This is intentional as discount strategies may be context-specific
    }
    return *this;
}

// Basic order management
void PizzaOrders::addPizza(Pizza* pizza) {
    if (pizza != nullptr) {
        pizzas.push_back(pizza);
    }
}

bool PizzaOrders::removePizza(int index) {
    if (index >= 0 && index < static_cast<int>(pizzas.size())) {
        delete pizzas[index];
        pizzas.erase(pizzas.begin() + index);
        return true;
    }
    return false;
}

void PizzaOrders::clearOrder() {
    for (auto& pizza : pizzas) {
        delete pizza;
    }
    pizzas.clear();
}

// Pizza creation methods (non-interactive)
Pizza* PizzaOrders::createPepperoniPizza(bool extraCheese, bool stuffedCrust) {
    ToppingGroup* toppings = ToppingGroup::createPepperoniPizza();
    Pizza* pizza = new BasePizza(toppings);
    
    if (extraCheese) {
        pizza = new ExtraCheese(pizza);
    }
    if (stuffedCrust) {
        pizza = new StuffedCrust(pizza);
    }
    
    return pizza;
}

Pizza* PizzaOrders::createVegetarianPizza(bool extraCheese, bool stuffedCrust) {
    ToppingGroup* toppings = ToppingGroup::createVegetarianPizza();
    Pizza* pizza = new BasePizza(toppings);
    
    if (extraCheese) {
        pizza = new ExtraCheese(pizza);
    }
    if (stuffedCrust) {
        pizza = new StuffedCrust(pizza);
    }
    
    return pizza;
}

Pizza* PizzaOrders::createMeatLoversPizza(bool extraCheese, bool stuffedCrust) {
    ToppingGroup* toppings = ToppingGroup::createMeatLoversPizza();
    Pizza* pizza = new BasePizza(toppings);
    
    if (extraCheese) {
        pizza = new ExtraCheese(pizza);
    }
    if (stuffedCrust) {
        pizza = new StuffedCrust(pizza);
    }
    
    return pizza;
}

Pizza* PizzaOrders::createVegetarianDeluxePizza(bool extraCheese, bool stuffedCrust) {
    ToppingGroup* toppings = ToppingGroup::createVegetarianDeluxePizza();
    Pizza* pizza = new BasePizza(toppings);
    
    if (extraCheese) {
        pizza = new ExtraCheese(pizza);
    }
    if (stuffedCrust) {
        pizza = new StuffedCrust(pizza);
    }
    
    return pizza;
}

Pizza* PizzaOrders::createCustomPizza(const std::vector<std::string>& toppings, bool extraCheese, bool stuffedCrust) {
    ToppingGroup* customToppings = new ToppingGroup("Custom Pizza");
    
    // Add base ingredients
    ToppingGroup* base = new ToppingGroup("Base");
    base->addComponent(new Topping("Dough"));
    base->addComponent(new Topping("Tomato Sauce"));
    base->addComponent(new Topping("Cheese"));
    customToppings->addComponent(base);
    
    // Add custom toppings
    for (const std::string& topping : toppings) {
        if (Topping::isValidTopping(topping)) {
            customToppings->addComponent(new Topping(topping));
        }
    }
    
    Pizza* pizza = new BasePizza(customToppings);
    
    if (extraCheese) {
        pizza = new ExtraCheese(pizza);
    }
    if (stuffedCrust) {
        pizza = new StuffedCrust(pizza);
    }
    
    return pizza;
}

// Order information
int PizzaOrders::getPizzaCount() const {
    return static_cast<int>(pizzas.size());
}

double PizzaOrders::getTotalPrice() const {
    double total = 0.0;
    for (const auto& pizza : pizzas) {
        total += pizza->getPrice();
    }
    return total;
}

Pizza* PizzaOrders::clonePizza(Pizza* original) {
    if (original == nullptr) {
        return nullptr;
    }
    
    // Use the clone method - much simpler!
    return original->clone();
}

std::vector<Pizza*> PizzaOrders::getPizzas() const {
    return pizzas;
}

int PizzaOrders::getOrderNumber() const {
    return orderNum;
}

std::string PizzaOrders::getOrderName() const {
    return orderName;
}

// Display methods
void PizzaOrders::displayOrder() const {
    std::cout << "\n=========================================" << std::endl;
    std::cout << "           ORDER #" << orderNum << std::endl;
    std::cout << "           Customer: " << orderName << std::endl;
    std::cout << "=========================================" << std::endl;
    
    if (pizzas.empty()) {
        std::cout << "No pizzas in order." << std::endl;
    } else {
        for (size_t i = 0; i < pizzas.size(); ++i) {
            std::cout << "Pizza " << (i + 1) << ":" << std::endl;
            pizzas[i]->printPizza();
            std::cout << std::endl;
        }
    }
    
    std::cout << "Total Pizzas: " << getPizzaCount() << std::endl;
    std::cout << "Subtotal: R" << getTotalPrice() << std::endl;
    
    // Display discount information if strategy is set
    if (discountStrat != nullptr) {
        double discount = getDiscountAmount();
        if (discount > 0.0) {
            std::cout << "Discount (" << discountStrat->getStrategyName() << "): -R" << discount << std::endl;
            std::cout << "Final Total: R" << getDiscountedTotal() << std::endl;
        } else {
            std::cout << "Final Total: R" << getTotalPrice() << " (no discount qualified)" << std::endl;
        }
    } else {
        std::cout << "Final Total: R" << getTotalPrice() << std::endl;
    }
    std::cout << "=========================================" << std::endl;
}

void PizzaOrders::displayOrderSummary() const {
    std::cout << "\n--- Order Summary ---" << std::endl;
    std::cout << "Order #" << orderNum << " - " << orderName << std::endl;
    std::cout << "Pizzas: " << getPizzaCount() << std::endl;
    std::cout << "Total: R" << (discountStrat != nullptr ? getDiscountedTotal() : getTotalPrice()) << std::endl;
}

// Setters
void PizzaOrders::setOrderNumber(int orderNumber) {
    orderNum = orderNumber;
}

void PizzaOrders::setOrderName(const std::string& customerName) {
    orderName = customerName;
}

// Strategy pattern methods for discount handling
void PizzaOrders::setDiscountStrategy(DiscountStrategy* strategy) {
    // Delete existing strategy to prevent memory leaks
    delete discountStrat;
    discountStrat = strategy;
}

DiscountStrategy* PizzaOrders::getDiscountStrategy() const {
    return discountStrat;
}

double PizzaOrders::getDiscountAmount() const {
    if (discountStrat == nullptr) {
        return 0.0;
    }
    return discountStrat->applyDiscount(*this);
}

double PizzaOrders::getDiscountedTotal() const {
    double originalTotal = getTotalPrice();
    double discount = getDiscountAmount();
    return originalTotal - discount;
}

void PizzaOrders::displayDiscountInfo() const {
    double originalTotal = getTotalPrice();
    double discount = getDiscountAmount();
    double finalTotal = originalTotal - discount;
    
    std::cout << "\n--- Pricing Breakdown ---" << std::endl;
    std::cout << "Subtotal: R" << originalTotal << std::endl;
    
    if (discountStrat != nullptr && discount > 0.0) {
        std::cout << "Discount (" << discountStrat->getStrategyName() << "): -R" << discount << std::endl;
        std::cout << "Final Total: R" << finalTotal << std::endl;
        std::cout << "You saved: R" << discount << "!" << std::endl;
    } else {
        std::cout << "No discount applied" << std::endl;
        std::cout << "Final Total: R" << finalTotal << std::endl;
    }
}

// State pattern methods implementation
void PizzaOrders::setState(OrderState* state) {
    delete currentState;
    currentState = state;
}

OrderState* PizzaOrders::getCurrentState() const {
    return currentState;
}

std::string PizzaOrders::getCurrentStateName() const {
    if (currentState != nullptr) {
        return currentState->getStateName();
    }
    return "Unknown";
}

std::string PizzaOrders::getAvailableActions() const {
    if (currentState != nullptr) {
        return currentState->getAvailableActions();
    }
    return "No actions available";
}

bool PizzaOrders::canModifyOrder() const {
    if (currentState != nullptr) {
        return currentState->canModifyOrder();
    }
    return false;
}

void PizzaOrders::displayStateInfo() const {
    std::cout << "\n--- Order State Information ---" << std::endl;
    std::cout << "Current State: " << getCurrentStateName() << std::endl;
    std::cout << "Available Actions: " << getAvailableActions() << std::endl;
    std::cout << "Can Modify Order: " << (canModifyOrder() ? "Yes" : "No") << std::endl;
    std::cout << "------------------------------" << std::endl;
}

// State-delegated operations
void PizzaOrders::performAddPizza() {
    if (currentState != nullptr) {
        currentState->addPizza(this);
    }
}

void PizzaOrders::performRemovePizza(int index) {
    if (currentState != nullptr) {
        currentState->removePizza(this, index);
    }
}

void PizzaOrders::performConfirmOrder() {
    if (currentState != nullptr) {
        currentState->confirmOrder(this);
    }
}

void PizzaOrders::performCancelOrder() {
    if (currentState != nullptr) {
        currentState->cancelOrder(this);
    }
}

void PizzaOrders::performPayOrder() {
    if (currentState != nullptr) {
        currentState->payOrder(this);
    }
}

void PizzaOrders::performPrepareOrder() {
    if (currentState != nullptr) {
        currentState->prepareOrder(this);
    }
}

void PizzaOrders::performDeliverOrder() {
    if (currentState != nullptr) {
        currentState->deliverOrder(this);
    }
}

void PizzaOrders::performCompleteOrder() {
    if (currentState != nullptr) {
        currentState->completeOrder(this);
    }
}