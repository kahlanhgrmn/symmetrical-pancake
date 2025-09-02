#ifndef MENUS_H
#define MENUS_H
#include "Observer.h"
#include "Pizza.h"
#include <vector>
#include <string>

class Menus{
protected:
    std::vector<Observer*> observers;
    std::vector<Pizza*> pizzas;

public:
    virtual ~Menus();
    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);
    
    virtual void addPizza(Pizza* pizza);
    virtual void removePizza(Pizza* pizza);
    
    virtual void notifyObservers(const std::string& message) = 0;
    
    std::vector<Pizza*> getPizzas() const;
    int getPizzaCount() const;
    
protected:
    void clearPizzas();
};

#endif