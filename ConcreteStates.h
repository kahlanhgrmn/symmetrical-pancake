#ifndef CONCRETESTATES_H
#define CONCRETESTATES_H

#include "OrderState.h"
#include "PizzaOrders.h"
#include <iostream>

// ==================== ORDERING STATE ====================
class OrderingState : public OrderState {
public:
    void addPizza(PizzaOrders* context) override;
    void removePizza(PizzaOrders* context, int index) override;
    void confirmOrder(PizzaOrders* context) override;
    void cancelOrder(PizzaOrders* context) override;
    void payOrder(PizzaOrders* context) override;
    void prepareOrder(PizzaOrders* context) override;
    void deliverOrder(PizzaOrders* context) override;
    void completeOrder(PizzaOrders* context) override;
    
    std::string getStateName() const override { return "Ordering"; }
    bool canModifyOrder() const override { return true; }
    std::string getAvailableActions() const override { 
        return "Add Pizza, Remove Pizza, Confirm Order, Cancel Order"; 
    }
};

// ==================== CONFIRMED STATE ====================
class ConfirmedState : public OrderState {
public:
    void addPizza(PizzaOrders* context) override;
    void removePizza(PizzaOrders* context, int index) override;
    void confirmOrder(PizzaOrders* context) override;
    void cancelOrder(PizzaOrders* context) override;
    void payOrder(PizzaOrders* context) override;
    void prepareOrder(PizzaOrders* context) override;
    void deliverOrder(PizzaOrders* context) override;
    void completeOrder(PizzaOrders* context) override;
    
    std::string getStateName() const override { return "Confirmed"; }
    bool canModifyOrder() const override { return false; }
    std::string getAvailableActions() const override { 
        return "Pay Order, Cancel Order"; 
    }
};

// ==================== PAID STATE ====================
class PaidState : public OrderState {
public:
    void addPizza(PizzaOrders* context) override;
    void removePizza(PizzaOrders* context, int index) override;
    void confirmOrder(PizzaOrders* context) override;
    void cancelOrder(PizzaOrders* context) override;
    void payOrder(PizzaOrders* context) override;
    void prepareOrder(PizzaOrders* context) override;
    void deliverOrder(PizzaOrders* context) override;
    void completeOrder(PizzaOrders* context) override;
    
    std::string getStateName() const override { return "Paid"; }
    bool canModifyOrder() const override { return false; }
    std::string getAvailableActions() const override { 
        return "Prepare Order, Cancel Order (with refund)"; 
    }
};

// ==================== PREPARING STATE ====================
class PreparingState : public OrderState {
public:
    void addPizza(PizzaOrders* context) override;
    void removePizza(PizzaOrders* context, int index) override;
    void confirmOrder(PizzaOrders* context) override;
    void cancelOrder(PizzaOrders* context) override;
    void payOrder(PizzaOrders* context) override;
    void prepareOrder(PizzaOrders* context) override;
    void deliverOrder(PizzaOrders* context) override;
    void completeOrder(PizzaOrders* context) override;
    
    std::string getStateName() const override { return "Preparing"; }
    bool canModifyOrder() const override { return false; }
    std::string getAvailableActions() const override { 
        return "Deliver Order"; 
    }
};

// ==================== DELIVERING STATE ====================
class DeliveringState : public OrderState {
public:
    void addPizza(PizzaOrders* context) override;
    void removePizza(PizzaOrders* context, int index) override;
    void confirmOrder(PizzaOrders* context) override;
    void cancelOrder(PizzaOrders* context) override;
    void payOrder(PizzaOrders* context) override;
    void prepareOrder(PizzaOrders* context) override;
    void deliverOrder(PizzaOrders* context) override;
    void completeOrder(PizzaOrders* context) override;
    
    std::string getStateName() const override { return "Delivering"; }
    bool canModifyOrder() const override { return false; }
    std::string getAvailableActions() const override { 
        return "Complete Order"; 
    }
};

// ==================== COMPLETED STATE ====================
class CompletedState : public OrderState {
public:
    void addPizza(PizzaOrders* context) override;
    void removePizza(PizzaOrders* context, int index) override;
    void confirmOrder(PizzaOrders* context) override;
    void cancelOrder(PizzaOrders* context) override;
    void payOrder(PizzaOrders* context) override;
    void prepareOrder(PizzaOrders* context) override;
    void deliverOrder(PizzaOrders* context) override;
    void completeOrder(PizzaOrders* context) override;
    
    std::string getStateName() const override { return "Completed"; }
    bool canModifyOrder() const override { return false; }
    std::string getAvailableActions() const override { 
        return "Order is complete - no actions available"; 
    }
};

// ==================== CANCELLED STATE ====================
class CancelledState : public OrderState {
public:
    void addPizza(PizzaOrders* context) override;
    void removePizza(PizzaOrders* context, int index) override;
    void confirmOrder(PizzaOrders* context) override;
    void cancelOrder(PizzaOrders* context) override;
    void payOrder(PizzaOrders* context) override;
    void prepareOrder(PizzaOrders* context) override;
    void deliverOrder(PizzaOrders* context) override;
    void completeOrder(PizzaOrders* context) override;
    
    std::string getStateName() const override { return "Cancelled"; }
    bool canModifyOrder() const override { return false; }
    std::string getAvailableActions() const override { 
        return "Order is cancelled - no actions available"; 
    }
};

#endif // CONCRETESTATES_H