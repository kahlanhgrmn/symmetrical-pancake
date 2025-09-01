#include "ConcreteStates.h"
#include "PizzaOrders.h"
#include <iostream>

// ========== ORDERING STATE IMPLEMENTATIONS ==========
void OrderingState::addPizza(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    std::cout << "Pizza added to order in Ordering state" << std::endl;
    // Context can be used here to actually add pizza to the order
    // For example: context->addPizzaToList(pizza);
}

void OrderingState::removePizza(PizzaOrders* context, int index) {
    if (context->removePizza(index)) {
        std::cout << "Pizza removed from order in Ordering state" << std::endl;
    } else {
        std::cout << "Invalid pizza index - cannot remove" << std::endl;
    }
}

void OrderingState::confirmOrder(PizzaOrders* context) {
    if (context->getPizzaCount() > 0) {
        std::cout << "Order confirmed! Moving to Confirmed state." << std::endl;
        changeState(context, new ConfirmedState());
    } else {
        std::cout << "Cannot confirm empty order. Please add pizzas first." << std::endl;
    }
}

void OrderingState::cancelOrder(PizzaOrders* context) {
    std::cout << "Order cancelled from Ordering state." << std::endl;
    changeState(context, new CancelledState());
}

void OrderingState::payOrder(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    displayInvalidAction("pay order", "Ordering - please confirm order first");
}

void OrderingState::prepareOrder(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    displayInvalidAction("prepare order", "Ordering - please confirm and pay first");
}

void OrderingState::deliverOrder(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    displayInvalidAction("deliver order", "Ordering - order not ready for delivery");
}

void OrderingState::completeOrder(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    displayInvalidAction("complete order", "Ordering - order not ready for completion");
}

// ========== CONFIRMED STATE IMPLEMENTATIONS ==========
void ConfirmedState::addPizza(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    displayInvalidAction("add pizza", "Confirmed - order is locked for modifications");
}

void ConfirmedState::removePizza(PizzaOrders* context, int index) {
    (void)context; // Suppress unused parameter warning
    (void)index;   // Suppress unused parameter warning
    displayInvalidAction("remove pizza", "Confirmed - order is locked for modifications");
}

void ConfirmedState::confirmOrder(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    std::cout << "Order is already confirmed." << std::endl;
}

void ConfirmedState::cancelOrder(PizzaOrders* context) {
    std::cout << "Order cancelled from Confirmed state." << std::endl;
    changeState(context, new CancelledState());
}

void ConfirmedState::payOrder(PizzaOrders* context) {
    std::cout << "Payment processed! Order total: R" << context->getDiscountedTotal() << std::endl;
    std::cout << "Moving to Paid state." << std::endl;
    changeState(context, new PaidState());
}

void ConfirmedState::prepareOrder(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    displayInvalidAction("prepare order", "Confirmed - payment required first");
}

void ConfirmedState::deliverOrder(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    displayInvalidAction("deliver order", "Confirmed - payment and preparation required first");
}

void ConfirmedState::completeOrder(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    displayInvalidAction("complete order", "Confirmed - payment and preparation required first");
}

// ========== PAID STATE IMPLEMENTATIONS ==========
void PaidState::addPizza(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    displayInvalidAction("add pizza", "Paid - order is locked for modifications");
}

void PaidState::removePizza(PizzaOrders* context, int index) {
    (void)context; // Suppress unused parameter warning
    (void)index;   // Suppress unused parameter warning
    displayInvalidAction("remove pizza", "Paid - order is locked for modifications");
}

void PaidState::confirmOrder(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    std::cout << "Order is already confirmed and paid." << std::endl;
}

void PaidState::cancelOrder(PizzaOrders* context) {
    std::cout << "Order cancelled from Paid state. Refund processed: R" << context->getDiscountedTotal() << std::endl;
    changeState(context, new CancelledState());
}

void PaidState::payOrder(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    std::cout << "Order is already paid for." << std::endl;
}

void PaidState::prepareOrder(PizzaOrders* context) {
    std::cout << "Starting pizza preparation..." << std::endl;
    std::cout << "Moving to Preparing state." << std::endl;
    changeState(context, new PreparingState());
}

void PaidState::deliverOrder(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    displayInvalidAction("deliver order", "Paid - preparation required first");
}

void PaidState::completeOrder(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    displayInvalidAction("complete order", "Paid - preparation and delivery required first");
}

// ========== PREPARING STATE IMPLEMENTATIONS ==========
void PreparingState::addPizza(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    displayInvalidAction("add pizza", "Preparing - order is being prepared");
}

void PreparingState::removePizza(PizzaOrders* context, int index) {
    (void)context; // Suppress unused parameter warning
    (void)index;   // Suppress unused parameter warning
    displayInvalidAction("remove pizza", "Preparing - order is being prepared");
}

void PreparingState::confirmOrder(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    std::cout << "Order is confirmed and being prepared." << std::endl;
}

void PreparingState::cancelOrder(PizzaOrders* context) {
    std::cout << "Order cancelled during preparation. Partial refund processed." << std::endl;
    changeState(context, new CancelledState());
}

void PreparingState::payOrder(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    std::cout << "Order is already paid for and being prepared." << std::endl;
}

void PreparingState::prepareOrder(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    std::cout << "Order is already being prepared." << std::endl;
}

void PreparingState::deliverOrder(PizzaOrders* context) {
    std::cout << "Pizzas ready! Starting delivery..." << std::endl;
    std::cout << "Moving to Delivering state." << std::endl;
    changeState(context, new DeliveringState());
}

void PreparingState::completeOrder(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    displayInvalidAction("complete order", "Preparing - delivery required first");
}

// ========== DELIVERING STATE IMPLEMENTATIONS ==========
void DeliveringState::addPizza(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    displayInvalidAction("add pizza", "Delivering - order is out for delivery");
}

void DeliveringState::removePizza(PizzaOrders* context, int index) {
    (void)context; // Suppress unused parameter warning
    (void)index;   // Suppress unused parameter warning
    displayInvalidAction("remove pizza", "Delivering - order is out for delivery");
}

void DeliveringState::confirmOrder(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    std::cout << "Order is confirmed and out for delivery." << std::endl;
}

void DeliveringState::cancelOrder(PizzaOrders* context) {
    std::cout << "Order cancelled during delivery. Driver returning to store." << std::endl;
    changeState(context, new CancelledState());
}

void DeliveringState::payOrder(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    std::cout << "Order is already paid for and being delivered." << std::endl;
}

void DeliveringState::prepareOrder(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    std::cout << "Order is already prepared and being delivered." << std::endl;
}

void DeliveringState::deliverOrder(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    std::cout << "Order is already out for delivery." << std::endl;
}

void DeliveringState::completeOrder(PizzaOrders* context) {
    std::cout << "Order delivered successfully!" << std::endl;
    std::cout << "Moving to Completed state." << std::endl;
    changeState(context, new CompletedState());
}

// ========== COMPLETED STATE IMPLEMENTATIONS ==========
void CompletedState::addPizza(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    displayInvalidAction("add pizza", "Completed - order is finished");
}

void CompletedState::removePizza(PizzaOrders* context, int index) {
    (void)context; // Suppress unused parameter warning
    (void)index;   // Suppress unused parameter warning
    displayInvalidAction("remove pizza", "Completed - order is finished");
}

void CompletedState::confirmOrder(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    std::cout << "Order is already completed." << std::endl;
}

void CompletedState::cancelOrder(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    displayInvalidAction("cancel order", "Completed - order is already finished");
}

void CompletedState::payOrder(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    std::cout << "Order was already paid for and completed." << std::endl;
}

void CompletedState::prepareOrder(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    std::cout << "Order was already prepared and completed." << std::endl;
}

void CompletedState::deliverOrder(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    std::cout << "Order was already delivered and completed." << std::endl;
}

void CompletedState::completeOrder(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    std::cout << "Order is already completed." << std::endl;
}

// ========== CANCELLED STATE IMPLEMENTATIONS ==========
void CancelledState::addPizza(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    displayInvalidAction("add pizza", "Cancelled - order was cancelled");
}

void CancelledState::removePizza(PizzaOrders* context, int index) {
    (void)context; // Suppress unused parameter warning
    (void)index;   // Suppress unused parameter warning
    displayInvalidAction("remove pizza", "Cancelled - order was cancelled");
}

void CancelledState::confirmOrder(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    displayInvalidAction("confirm order", "Cancelled - order was cancelled");
}

void CancelledState::cancelOrder(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    std::cout << "Order is already cancelled." << std::endl;
}

void CancelledState::payOrder(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    displayInvalidAction("pay order", "Cancelled - order was cancelled");
}

void CancelledState::prepareOrder(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    displayInvalidAction("prepare order", "Cancelled - order was cancelled");
}

void CancelledState::deliverOrder(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    displayInvalidAction("deliver order", "Cancelled - order was cancelled");
}

void CancelledState::completeOrder(PizzaOrders* context) {
    (void)context; // Suppress unused parameter warning
    displayInvalidAction("complete order", "Cancelled - order was cancelled");
}