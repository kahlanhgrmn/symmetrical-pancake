#include "ToppingGroup.h"
#include <iostream>

ToppingGroup::ToppingGroup(const std::string& groupName) {
    this->name = groupName;
    this->price = 0.0; // Will be calculated dynamically
}

ToppingGroup::~ToppingGroup() {
    cleanup();
}

ToppingGroup::ToppingGroup(const ToppingGroup& other) : PizzaComponent(other.price, other.name) {
    deepCopy(other);
}

ToppingGroup& ToppingGroup::operator=(const ToppingGroup& other) {
    if (this != &other) {
        cleanup();
        deepCopy(other);
    }
    return *this;
}

void ToppingGroup::addComponent(PizzaComponent* component) {
    if (component != nullptr) {
        components.push_back(component);
    }
}

bool ToppingGroup::removeComponent(PizzaComponent* component) {
    for (auto it = components.begin(); it != components.end(); ++it) {
        if (*it == component) {
            components.erase(it);
            return true;
        }
    }
    return false;
}

std::string ToppingGroup::getName() const {
    if (components.empty()) {
        return name;
    }
    
    std::string result = name + " (";
    
    for (size_t i = 0; i < components.size(); ++i) {
        result += components[i]->getName();
        if (i < components.size() - 1) {
            result += ", ";
        }
    }
    
    result += ")";
    return result;
}

double ToppingGroup::getPrice() const {
    double totalPrice = 0.0;
    
    for (const auto& component : components) {
        totalPrice += component->getPrice();
    }
    
    return totalPrice;
}

const std::vector<PizzaComponent*>& ToppingGroup::getComponents() const {
    return components;
}

void ToppingGroup::clearComponents() {
    cleanup();
    components.clear();
}

bool ToppingGroup::isEmpty() const {
    return components.empty();
}

size_t ToppingGroup::getComponentCount() const {
    return components.size();
}

void ToppingGroup::deepCopy(const ToppingGroup& other) {
    this->name = other.name;
    this->price = other.price;
    
    // Deep copy all components
    for (const auto& component : other.components) {
        // Check if it's a Topping or ToppingGroup
        Topping* topping = dynamic_cast<Topping*>(component);
        if (topping) {
            // Create a new Topping
            this->components.push_back(new Topping(topping->getName()));
        } else {
            ToppingGroup* group = dynamic_cast<ToppingGroup*>(component);
            if (group) {
                // Create a new ToppingGroup
                this->components.push_back(new ToppingGroup(*group));
            }
        }
    }
}

void ToppingGroup::cleanup() {
    for (auto& component : components) {
        if (component != nullptr) {
            delete component;  // This will call the proper destructor
            component = nullptr;
        }
    }
    components.clear();  // Clear the vector
}

// Helper method to create base pizza components
ToppingGroup* ToppingGroup::createBasePizza() {
    ToppingGroup* base = new ToppingGroup("Base");
    base->addComponent(new Topping("Dough"));
    base->addComponent(new Topping("Tomato Sauce"));
    base->addComponent(new Topping("Cheese"));
    return base;
}

// Static factory methods for predefined pizzas
ToppingGroup* ToppingGroup::createPepperoniPizza() {
    ToppingGroup* pizza = new ToppingGroup("Pepperoni");
    
    // Add base components
    ToppingGroup* base = createBasePizza();
    pizza->addComponent(base);
    
    // Add pepperoni topping
    pizza->addComponent(new Topping("Pepperoni"));
    
    return pizza;
}

ToppingGroup* ToppingGroup::createVegetarianPizza() {
    ToppingGroup* pizza = new ToppingGroup("Vegetarian");
    
    // Add base components
    ToppingGroup* base = createBasePizza();
    pizza->addComponent(base);
    
    // Add vegetarian toppings
    pizza->addComponent(new Topping("Mushrooms"));
    pizza->addComponent(new Topping("Green Peppers"));
    pizza->addComponent(new Topping("Onions"));
    
    return pizza;
}

ToppingGroup* ToppingGroup::createMeatLoversPizza() {
    ToppingGroup* pizza = new ToppingGroup("Meat Lovers");
    
    // Start with a Pepperoni pizza (composition)
    ToppingGroup* pepperoniBase = createPepperoniPizza();
    pizza->addComponent(pepperoniBase);
    
    // Add additional meat toppings
    pizza->addComponent(new Topping("Beef Sausage"));
    pizza->addComponent(new Topping("Salami"));
    
    return pizza;
}

ToppingGroup* ToppingGroup::createVegetarianDeluxePizza() {
    ToppingGroup* pizza = new ToppingGroup("Vegetarian Deluxe");
    
    // Start with a Vegetarian pizza (composition)
    ToppingGroup* vegetarianBase = createVegetarianPizza();
    pizza->addComponent(vegetarianBase);
    
    // Add additional vegetarian toppings
    pizza->addComponent(new Topping("Feta Cheese"));
    pizza->addComponent(new Topping("Olives"));
    
    return pizza;
}