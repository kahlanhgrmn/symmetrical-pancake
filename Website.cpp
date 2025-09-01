#include "Website.h"
#include <iostream>

Website::Website(const std::string& name, const std::string& url): websiteName(name), websiteUrl(url){
}

void Website::update(const std::string& message){
    updates.push_back(message);
    
    std::cout << "\nWebsite Update: " << websiteName << std::endl;
    std::cout << "Website automatically updated with: " << message << std::endl;
    std::cout << "Update published at: " << websiteUrl << std::endl;
    
    if(message.find("NEW PIZZA") != std::string::npos){
        std::cout << "- Added to online menu with photos and descriptions" << std::endl;
        std::cout << "- Updated homepage banner" << std::endl;
    } 
    
    else if(message.find("SPECIAL OFFER") != std::string::npos){
        std::cout << "- Featured on specials page" << std::endl;
        std::cout << "- Added popup notification for visitors" << std::endl;
        std::cout << "- Social media posts scheduled" << std::endl;
    } 
    
    else if(message.find("REMOVED") != std::string::npos || message.find("ENDED") != std::string::npos){
        std::cout << "- Removed from online menu" << std::endl;
        std::cout << "- Updated availability status" << std::endl;
    }
    
    publishUpdate(message);
}

std::string Website::getWebsiteName() const{
    return websiteName;
}

std::string Website::getWebsiteUrl() const{
    return websiteUrl;
}

std::vector<std::string> Website::getUpdates() const{
    return updates;
}

void Website::clearUpdates(){
    updates.clear();
}

void Website::displayUpdates() const{
    std::cout << "\n=== Website Updates for " << websiteName << " ===" << std::endl;

    if(updates.empty()){
        std::cout << "No recent updates." << std::endl;
    } 
    
    else{
        for(size_t i = 0; i < updates.size(); ++i){
            std::cout << (i + 1) << ". " << updates[i] << std::endl;
        }
    }

    std::cout << "==========================================" << std::endl;
}

void Website::publishUpdate(const std::string& update){
    (void)update;
    std::cout << "Published to website backend database" << std::endl;
    std::cout << "Cache cleared for updated pages" << std::endl;
}