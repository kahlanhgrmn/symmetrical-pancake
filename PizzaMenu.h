#ifndef PIZZAMENU_H
#define PIZZAMENU_
#include "Menus.h"
#include <string>

class PizzaMenu: public Menus{
private:
    std::string menuName;

public:
    PizzaMenu(const std::string& name = "Main Menu");
    virtual ~PizzaMenu() = default;
    
    void notifyObservers(const std::string& message) override;
    void addPizza(Pizza* pizza) override;
    void removePizza(Pizza* pizza) override;
    
    std::string getMenuName() const;
    void displayMenu() const;
};

#endif