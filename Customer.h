#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "Observer.h"
#include <string>
#include <vector>

class Customer: public Observer{
private:
    std::string customerName;
    std::string phoneNumber;
    std::vector<std::string> notifications;

public:
    Customer(const std::string& name, const std::string& phone = "");
    virtual ~Customer() = default;
    
    void update(const std::string& message) override;
    std::string getName() const;
    std::string getPhoneNumber() const;
    void setPhoneNumber(const std::string& phone);
    
    std::vector<std::string> getNotifications() const;
    void clearNotifications();
    void displayNotifications() const;
};

#endif