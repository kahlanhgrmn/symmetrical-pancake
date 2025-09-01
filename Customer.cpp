#include "Customer.h"
#include <iostream>

Customer::Customer(const std::string& name, const std::string& phone): customerName(name), phoneNumber(phone){
}

void Customer::update(const std::string& message){
    notifications.push_back(message);
    
    std::cout << "\nCustomer Notification: " << customerName << std::endl;
    std::cout << "Received: " << message << std::endl;
    
    if(!phoneNumber.empty()){
        std::cout << "SMS sent to " << phoneNumber << std::endl;
    }
    
    if(message.find("NEW PIZZA") != std::string::npos){
        std::cout << customerName << " says: 'Exciting!'" << std::endl;
    } 
    
    else if(message.find("SPECIAL OFFER") != std::string::npos){
        std::cout << customerName << " says: 'I should order soon!'" << std::endl;
    } 
    
    else if(message.find("REMOVED") != std::string::npos || message.find("ENDED") != std::string::npos){
        std::cout << customerName << " says: 'Oh no!'" << std::endl;
    }
}

std::string Customer::getName() const{
    return customerName;
}

std::string Customer::getPhoneNumber() const{
    return phoneNumber;
}

void Customer::setPhoneNumber(const std::string& phone){
    phoneNumber = phone;
}

std::vector<std::string> Customer::getNotifications() const{
    return notifications;
}

void Customer::clearNotifications(){
    notifications.clear();
}

void Customer::displayNotifications() const{
    std::cout << "\n=== Notifications for " << customerName << " ===" << std::endl;

    if(notifications.empty()){
        std::cout << "No notifications." << std::endl;
    } 
    
    else{
        for(size_t i = 0; i < notifications.size(); ++i){
            std::cout << (i + 1) << ". " << notifications[i] << std::endl;
        }
    }
    std::cout << "=====================================" << std::endl;
}