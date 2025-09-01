#include "PizzaOrders.h"
#include "Topping.h"
#include "ConcreteStrategy.h"
#include <iostream>
#include <string>
#include <vector>

// Interactive menu display functions
void displayMainMenu() {
    std::cout << "\n=========================================" << std::endl;
    std::cout << "    Welcome to Romeo's Pizza!" << std::endl;
    std::cout << "=========================================" << std::endl;
    std::cout << "1. Pepperoni Pizza" << std::endl;
    std::cout << "2. Vegetarian Pizza" << std::endl;
    std::cout << "3. Meat Lovers Pizza" << std::endl;
    std::cout << "4. Vegetarian Deluxe Pizza" << std::endl;
    std::cout << "5. Create Custom Pizza" << std::endl;
    std::cout << "6. View Available Toppings" << std::endl;
    std::cout << "7. View Current Order" << std::endl;
    std::cout << "8. Select Discount Strategy" << std::endl;
    std::cout << "9. Checkout" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "=========================================" << std::endl;
    std::cout << "Please select an option (0-9): ";
}

void displayAvailableToppings() {
    std::cout << "\n=== Available Toppings ===" << std::endl;
    auto allToppings = Topping::getAllToppings();
    int counter = 1;
    for (const auto& topping : allToppings) {
        std::cout << counter++ << ". " << topping.first << " - R" << topping.second << std::endl;
    }
    std::cout << std::endl;
}

void displayFinalPizza(Pizza* pizza) {
    if (pizza == nullptr) {
        std::cout << "No pizza to display." << std::endl;
        return;
    }
    
    std::cout << "\n=========================================" << std::endl;
    std::cout << "           PIZZA ADDED TO ORDER" << std::endl;
    std::cout << "=========================================" << std::endl;
    pizza->printPizza();
    std::cout << "=========================================" << std::endl;
}

void waitForEnter() {
    std::cout << "Press Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

void displayDiscountMenu() {
    std::cout << "\n=== Available Discount Strategies ===" << std::endl;
    std::cout << "1. Regular Price (No Discount)" << std::endl;
    std::cout << "2. Family Discount" << std::endl;
    std::cout << "3. Bulk Discount" << std::endl;
    std::cout << "4. Student Discount" << std::endl;
    std::cout << "5. Senior Discount" << std::endl;
    std::cout << "6. Loyalty Discount" << std::endl;
    std::cout << "0. Back to Main Menu" << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << "Select a discount strategy: ";
}

void selectDiscountStrategy(PizzaOrders& order) {
    int choice;
    
    while (true) {
        displayDiscountMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 0:
                return;
                
            case 1: {
                order.setDiscountStrategy(new RegularPrice());
                std::cout << "\nRegular pricing selected - no discount applied." << std::endl;
                break;
            }
            
            case 2: {
                order.setDiscountStrategy(new FamilyDiscount());
                FamilyDiscount temp;
                std::cout << "\nFamily Discount selected!" << std::endl;
                std::cout << "Details: " << temp.getDescription() << std::endl;
                break;
            }
            
            case 3: {
                order.setDiscountStrategy(new BulkDiscount());
                BulkDiscount temp;
                std::cout << "\nBulk Discount selected!" << std::endl;
                std::cout << "Details: " << temp.getDescription() << std::endl;
                break;
            }
            
            case 4: {
                order.setDiscountStrategy(new StudentDiscount());
                StudentDiscount temp;
                std::cout << "\nStudent Discount selected!" << std::endl;
                std::cout << "Details: " << temp.getDescription() << std::endl;
                break;
            }
            
            case 5: {
                order.setDiscountStrategy(new SeniorDiscount());
                SeniorDiscount temp;
                std::cout << "\nSenior Discount selected!" << std::endl;
                std::cout << "Details: " << temp.getDescription() << std::endl;
                break;
            }
            
            case 6: {
                std::cout << "\nEnter your loyalty tier (1-5): ";
                int tier;
                std::cin >> tier;
                
                order.setDiscountStrategy(new LoyaltyDiscount(tier));
                LoyaltyDiscount temp(tier);
                std::cout << "\nLoyalty Discount selected!" << std::endl;
                std::cout << "Details: " << temp.getDescription() << std::endl;
                break;
            }
            
            default:
                std::cout << "\nInvalid option! Please select 0-6." << std::endl;
                waitForEnter();
                continue;
        }
        
        // Show current discount info after selection
        if (order.getPizzaCount() > 0) {
            order.displayDiscountInfo();
        } else {
            std::cout << "Add some pizzas to see the discount in action!" << std::endl;
        }
        
        waitForEnter();
        return;
    }
}

// Interactive pizza creation functions
std::vector<std::string> createCustomPizzaInteractive() {
    std::cout << "\n=== Create Your Custom Pizza ===" << std::endl;
    std::cout << "Your pizza will automatically include: Dough, Tomato Sauce, and Cheese" << std::endl;
    
    displayAvailableToppings();
    
    std::cout << "Enter the names of toppings you want to add (one per line)." << std::endl;
    std::cout << "Press Enter on an empty line when you're done:" << std::endl;
    
    std::vector<std::string> selectedToppings;
    std::string toppingName;
    bool addedToppings = false;
    
    // Clear the input buffer
    std::cin.ignore();
    
    while (true) {
        std::cout << "Add topping: ";
        getline(std::cin, toppingName);
        
        if (toppingName.empty()) {
            break;
        }
        
        if (Topping::isValidTopping(toppingName)) {
            selectedToppings.push_back(toppingName);
            std::cout << "Added " << toppingName << " to your pizza!" << std::endl;
            addedToppings = true;
        } else {
            std::cout << "Sorry, '" << toppingName << "' is not available. Please choose from the list above." << std::endl;
        }
    }
    
    if (!addedToppings) {
        std::cout << "No additional toppings added. Your pizza has just the base ingredients." << std::endl;
    }
    
    return selectedToppings;
}

Pizza* selectPredefinedPizza(PizzaOrders& order, int choice) {
    switch (choice) {
        case 1:
            return order.createPepperoniPizza();
        case 2:
            return order.createVegetarianPizza();
        case 3:
            return order.createMeatLoversPizza();
        case 4:
            return order.createVegetarianDeluxePizza();
        default:
            return nullptr;
    }
}

Pizza* customizeWithDecorators(Pizza* basePizza) {
    if (basePizza == nullptr) {
        return nullptr;
    }
    
    std::cout << "\n=== Customize Your Pizza ===" << std::endl;
    std::cout << "Current Pizza: " << basePizza->getName() << std::endl;
    std::cout << "Current Price: R" << basePizza->getPrice() << std::endl;
    
    Pizza* currentPizza = basePizza;
    
    // Extra Cheese option
    std::cout << "\nWould you like Extra Cheese? (+R" << ExtraCheese::getExtraCheesePrice() << ") (y/n): ";
    char choice;
    std::cin >> choice;
    
    if (choice == 'y' || choice == 'Y') {
        currentPizza = new ExtraCheese(currentPizza);
        std::cout << "Extra Cheese added!" << std::endl;
        std::cout << "New Price: R" << currentPizza->getPrice() << std::endl;
    }
    
    // Stuffed Crust option
    std::cout << "\nWould you like Stuffed Crust? (+R" << StuffedCrust::getStuffedCrustPrice() << ") (y/n): ";
    std::cin >> choice;
    
    if (choice == 'y' || choice == 'Y') {
        currentPizza = new StuffedCrust(currentPizza);
        std::cout << "Stuffed Crust added!" << std::endl;
        std::cout << "New Price: R" << currentPizza->getPrice() << std::endl;
    }
    
    return currentPizza;
}

void interactivePizzaMenu(PizzaOrders& order) {
    int choice;
    
    while (true) {
        displayMainMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 0:
                std::cout << "\nThank you for visiting Romeo's Pizza! Arrivederci!" << std::endl;
                return;
                
            case 1:
            case 2:
            case 3:
            case 4: {
                Pizza* basePizza = selectPredefinedPizza(order, choice);
                if (basePizza != nullptr) {
                    Pizza* finalPizza = customizeWithDecorators(basePizza);
                    order.addPizza(finalPizza);
                    displayFinalPizza(finalPizza);
                }
                break;
            }
            
            case 5: {
                std::vector<std::string> customToppings = createCustomPizzaInteractive();
                Pizza* customBasePizza = order.createCustomPizza(customToppings);
                Pizza* finalPizza = customizeWithDecorators(customBasePizza);
                order.addPizza(finalPizza);
                displayFinalPizza(finalPizza);
                break;
            }
            
            case 6:
                displayAvailableToppings();
                waitForEnter();
                break;
                
            case 7:
                order.displayOrder();
                waitForEnter();
                break;
                
            case 8:
                selectDiscountStrategy(order);
                break;
                
            case 9:
                order.displayOrder();
                std::cout << "\nProceeding to checkout..." << std::endl;
                return;
                
            default:
                std::cout << "\nInvalid option! Please select a number between 0-9." << std::endl;
                waitForEnter();
                break;
        }
    }
}

void runInteractiveSession(PizzaOrders& order) {
    std::cout << "\n=========================================" << std::endl;
    std::cout << "    Starting Interactive Pizza Session" << std::endl;
    std::cout << "    Order #" << order.getOrderNumber() << " - " << order.getOrderName() << std::endl;
    std::cout << "=========================================" << std::endl;
    
    interactivePizzaMenu(order);
    
    if (order.getPizzaCount() > 0) {
        std::cout << "\n=========================================" << std::endl;
        std::cout << "           FINAL ORDER" << std::endl;
        std::cout << "=========================================" << std::endl;
        order.displayOrder();
        std::cout << "Thank you for choosing Romeo's Pizza!" << std::endl;
        std::cout << "Your delicious pizzas will be ready soon!" << std::endl;
    }
}

// Example usage and demo functions
void demonstrateStrategyPattern() {
    std::cout << "\n=========================================" << std::endl;
    std::cout << "    Strategy Pattern Demo" << std::endl;
    std::cout << "=========================================" << std::endl;
    
    PizzaOrders order(2001, "Strategy Demo Customer");
    
    // Create a sample order
    Pizza* pepperoni = order.createPepperoniPizza(true, false);
    Pizza* vegetarian = order.createVegetarianPizza(false, true);
    Pizza* meatLovers = order.createMeatLoversPizza(true, true);
    
    order.addPizza(pepperoni);
    order.addPizza(vegetarian);
    order.addPizza(meatLovers);
    
    std::cout << "\nSample order created with 3 pizzas:" << std::endl;
    order.displayOrder();
    
    // Test all strategies
    std::vector<DiscountStrategy*> strategies = {
        new RegularPrice(),
        new FamilyDiscount(),
        new BulkDiscount(),
        new StudentDiscount(),
        new SeniorDiscount(),
        new LoyaltyDiscount(3) // Tier 3 loyalty
    };
    
    std::cout << "\n=== Testing All Discount Strategies ===" << std::endl;
    
    for (auto* strategy : strategies) {
        order.setDiscountStrategy(strategy);
        
        std::cout << "\n--- " << strategy->getStrategyName() << " ---" << std::endl;
        std::cout << "Description: " << strategy->getDescription() << std::endl;
        order.displayDiscountInfo();
    }
    
    // Clean up - the order destructor will delete the last strategy
    // but we need to clean up the others
    for (size_t i = 0; i < strategies.size() - 1; ++i) {
        // Don't delete the last one as it's still set in the order
        if (i < strategies.size() - 1) {
            // We'll let the order handle the cleanup
        }
    }
    
    std::cout << "\nStrategy pattern demonstration complete!" << std::endl;
}

void demonstrateNonInteractiveOrdering() {
    std::cout << "\n=========================================" << std::endl;
    std::cout << "    Non-Interactive Ordering Demo" << std::endl;
    std::cout << "=========================================" << std::endl;
    
    PizzaOrders order(1001, "Demo Customer");
    
    // Create some pizzas programmatically
    Pizza* pepperoni = order.createPepperoniPizza(true, false); // With extra cheese
    Pizza* vegetarian = order.createVegetarianPizza(false, true); // With stuffed crust
    Pizza* custom = order.createCustomPizza({"Mushrooms", "Bell Peppers", "Olives"}, true, true);
    
    order.addPizza(pepperoni);
    order.addPizza(vegetarian);
    order.addPizza(custom);
    
    // Apply a discount strategy
    order.setDiscountStrategy(new BulkDiscount());
    
    order.displayOrder();
}

void demonstrateInteractiveOrdering() {
    std::cout << "\n=========================================" << std::endl;
    std::cout << "    Interactive Ordering Demo" << std::endl;
    std::cout << "=========================================" << std::endl;
    
    std::string customerName;
    int orderNumber;
    
    std::cout << "Enter customer name: ";
    std::cin.ignore();
    getline(std::cin, customerName);
    
    std::cout << "Enter order number: ";
    std::cin >> orderNumber;
    
    PizzaOrders order(orderNumber, customerName);
    runInteractiveSession(order);
}

void displayDemoMenu() {
    std::cout << "\n=========================================" << std::endl;
    std::cout << "           PIZZA ORDERING DEMO" << std::endl;
    std::cout << "=========================================" << std::endl;
    std::cout << "1. Run Interactive Ordering System" << std::endl;
    std::cout << "2. Show Non-Interactive Demo" << std::endl;
    std::cout << "3. Demonstrate Strategy Pattern" << std::endl;
    std::cout << "4. Show Available Toppings" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "=========================================" << std::endl;
    std::cout << "Please select an option: ";
}

int main() {
    int choice;
    
    while (true) {
        displayDemoMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 0:
                std::cout << "\nGoodbye! Thanks for trying Romeo's Pizza System!" << std::endl;
                return 0;
                
            case 1:
                demonstrateInteractiveOrdering();
                break;
                
            case 2:
                demonstrateNonInteractiveOrdering();
                break;
                
            case 3:
                demonstrateStrategyPattern();
                break;
                
            case 4:
                displayAvailableToppings();
                waitForEnter();
                break;
                
            default:
                std::cout << "\nInvalid option! Please select 0-4." << std::endl;
                waitForEnter();
                break;
        }
    }
    
    return 0;
}