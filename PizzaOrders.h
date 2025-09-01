#ifndef PIZZAORDERS_H
#define PIZZAORDERS_H

#include "Pizza.h"
#include "ToppingGroup.h"
#include "BasePizza.h"
#include "ExtraCheese.h"
#include "StuffedCrust.h"
#include <vector>
#include "DiscountStrategy.h"

// Forward declarations for State and Strategy patterns
class OrderState;
class DiscountStrategy;

class PizzaOrders {
private:
    std::vector<Pizza*> pizzas;
    OrderState* currentState;
    DiscountStrategy* discountStrat;
    int orderNum;
    std::string orderName;

public:
    // Constructors and Destructor
    PizzaOrders();
    PizzaOrders(int orderNumber, const std::string& customerName);
    ~PizzaOrders();
    
    // Copy constructor and assignment operator
    PizzaOrders(const PizzaOrders& other);
    PizzaOrders& operator=(const PizzaOrders& other);
    Pizza* clonePizza(Pizza* original);
    
    // Basic order management
    void addPizza(Pizza* pizza);
    bool removePizza(int index);
    void clearOrder();
    
    // Pizza creation methods (non-interactive, parameter-driven)
    Pizza* createPepperoniPizza(bool extraCheese = false, bool stuffedCrust = false);
    Pizza* createVegetarianPizza(bool extraCheese = false, bool stuffedCrust = false);
    Pizza* createMeatLoversPizza(bool extraCheese = false, bool stuffedCrust = false);
    Pizza* createVegetarianDeluxePizza(bool extraCheese = false, bool stuffedCrust = false);
    Pizza* createCustomPizza(const std::vector<std::string>& toppings, bool extraCheese = false, bool stuffedCrust = false);
    
    // Order information getters
    int getPizzaCount() const;
    double getTotalPrice() const;
    std::vector<Pizza*> getPizzas() const;
    int getOrderNumber() const;
    std::string getOrderName() const;
    
    // Display methods for order information
    void displayOrder() const;
    void displayOrderSummary() const;
    
    // Setters for order details
    void setOrderNumber(int orderNumber);
    void setOrderName(const std::string& customerName);
    
    // Strategy pattern methods for discount handling
    void setDiscountStrategy(DiscountStrategy* strategy);
    DiscountStrategy* getDiscountStrategy() const;
    double getDiscountAmount() const;
    double getDiscountedTotal() const;
    void displayDiscountInfo() const;
    
    // State pattern methods
    void setState(OrderState* state);
    OrderState* getCurrentState() const;
    std::string getCurrentStateName() const;
    std::string getAvailableActions() const;
    bool canModifyOrder() const;
    void displayStateInfo() const;
    
    // State-delegated operations
    void performAddPizza();
    void performRemovePizza(int index);
    void performConfirmOrder();
    void performCancelOrder();
    void performPayOrder();
    void performPrepareOrder();
    void performDeliverOrder();
    void performCompleteOrder();
};

#endif // PIZZAORDERS_H