#ifndef TOPPINGGROUP_H
#define TOPPINGGROUP_H

#include "PizzaComponent.h"
#include "Topping.h"
#include <vector>
#include <string>

class ToppingGroup : public PizzaComponent {
private:
    std::vector<PizzaComponent*> components;

public:
    // Constructor
    ToppingGroup(const std::string& groupName);
    
    // Destructor to clean up components
    virtual ~ToppingGroup();
    
    // Copy constructor
    ToppingGroup(const ToppingGroup& other);
    
    // Assignment operator
    ToppingGroup& operator=(const ToppingGroup& other);
    
    // Add a component (topping or another group)
    void addComponent(PizzaComponent* component);
    
    // Remove a component
    bool removeComponent(PizzaComponent* component);
    
    // Override virtual methods
    std::string getName() const override;
    double getPrice() const override;
    
    // Get all components
    const std::vector<PizzaComponent*>& getComponents() const;
    
    // Clear all components
    void clearComponents();
    
    // Check if group is empty
    bool isEmpty() const;
    
    // Get component count
    size_t getComponentCount() const;
    
    // Static factory methods for predefined pizzas
    static ToppingGroup* createPepperoniPizza();
    static ToppingGroup* createVegetarianPizza();
    static ToppingGroup* createMeatLoversPizza();
    static ToppingGroup* createVegetarianDeluxePizza();
    
private:
    // Helper method for deep copying
    void deepCopy(const ToppingGroup& other);
    
    // Helper method to clean up components
    void cleanup();
    
    // Helper method to create base pizza components (dough, sauce, cheese)
    static ToppingGroup* createBasePizza();
};

#endif