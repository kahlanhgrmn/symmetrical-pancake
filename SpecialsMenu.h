#ifndef SPECIALSMENU_H
#define SPECIALSMENU_H
#include "Menus.h"
#include <string>
#include <map>

class SpecialsMenu: public Menus{
private:
    std::string menuName;
    std::map<Pizza*, std::string> specialOffers;
public:
    SpecialsMenu(const std::string& name = "Specials Menu");
    virtual ~SpecialsMenu() = default;
    
    void notifyObservers(const std::string& message) override;
    void addSpecialOffer(Pizza* pizza, const std::string& specialDescription);
    void removeSpecialOffer(Pizza* pizza);
    void addPizza(Pizza* pizza) override;
    void removePizza(Pizza* pizza) override;
    
    std::string getMenuName() const;
    std::string getSpecialOffer(Pizza* pizza) const;
    void displaySpecialsMenu() const;
};

#endif