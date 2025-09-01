#ifndef ORDERSTATE_H
#define ORDERSTATE_H

#include <string>
#include <iostream>

// Forward declaration
class PizzaOrders;

/**
 * Abstract base class for the State pattern
 * Defines the interface for all concrete states
 */
class OrderState {
public:
    virtual ~OrderState() = default;
    
    // Core state operations
    virtual void addPizza(PizzaOrders* context) = 0;
    virtual void removePizza(PizzaOrders* context, int index) = 0;
    virtual void confirmOrder(PizzaOrders* context) = 0;
    virtual void cancelOrder(PizzaOrders* context) = 0;
    virtual void payOrder(PizzaOrders* context) = 0;
    virtual void prepareOrder(PizzaOrders* context) = 0;
    virtual void deliverOrder(PizzaOrders* context) = 0;
    virtual void completeOrder(PizzaOrders* context) = 0;
    
    // Information methods
    virtual std::string getStateName() const = 0;
    virtual bool canModifyOrder() const = 0;
    virtual std::string getAvailableActions() const = 0;
    
protected:
    // Helper method for state transitions
    void changeState(PizzaOrders* context, OrderState* newState);
    
    // Helper method for invalid operations
    void displayInvalidAction(const std::string& action, const std::string& reason) const {
        std::cout << "Cannot " << action << " - " << reason << std::endl;
    }
};

#endif // ORDERSTATE_H