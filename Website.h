#ifndef WEBSITE_H
#define WEBSITE_H
#include "Observer.h"
#include <string>
#include <vector>

class Website: public Observer{
private:
    std::string websiteName;
    std::string websiteUrl;
    std::vector<std::string> updates;

public:
    Website(const std::string& name = "Romeo's Pizza Website", const std::string& url = "www.romeospizza.co.za");
    virtual ~Website() = default;
    
    void update(const std::string& message) override;
    std::string getWebsiteName() const;
    std::string getWebsiteUrl() const;
    
    std::vector<std::string> getUpdates() const;
    void clearUpdates();
    void displayUpdates() const;
    void publishUpdate(const std::string& update);
};

#endif