#include "PizzaComponent.h"
#include "Topping.h"
#include "ToppingGroup.h"
#include "Pizza.h"
#include "BasePizza.h"
#include "PizzaDecorator.h"
#include "ExtraCheese.h"
#include "StuffedCrust.h"
#include "PizzaOrders.h"
#include "Observer.h"
#include "Menus.h"
#include "PizzaMenu.h"
#include "SpecialsMenu.h"
#include "Customer.h"
#include "Website.h"
#include "ConcreteStates.h"
#include "DiscountStrategy.h"
#include "ConcreteStrategy.h"
#include <iostream>
#include <vector>

using namespace std;

void testBasicDecorators() {
    cout << "=== Testing Basic Decorators ===" << endl;
    
    // Create a basic pizza using composite pattern
    ToppingGroup* pepperoniToppings = ToppingGroup::createPepperoniPizza();
    Pizza* basePizza = new BasePizza(pepperoniToppings);
    
    cout << "Base Pizza:" << endl;
    basePizza->printPizza();
    cout << endl;
    
    // Test Extra Cheese decorator
    Pizza* cheeseDecorated = new ExtraCheese(basePizza);
    cout << "With Extra Cheese:" << endl;
    cheeseDecorated->printPizza();
    cout << endl;
    
    // Test Stuffed Crust decorator
    ToppingGroup* vegetarianToppings = ToppingGroup::createVegetarianPizza();
    Pizza* vegPizza = new BasePizza(vegetarianToppings);
    Pizza* crustDecorated = new StuffedCrust(vegPizza);
    cout << "Vegetarian with Stuffed Crust:" << endl;
    crustDecorated->printPizza();
    cout << endl;
    
    // Cleanup
    delete cheeseDecorated; // This will clean up basePizza as well
    delete crustDecorated;  // This will clean up vegPizza as well
    cout << endl;
}

void testDecoratorChaining() {
    cout << "=== Testing Decorator Chaining ===" << endl;
    
    // Create a complex pizza using composite pattern
    ToppingGroup* meatLoversToppings = ToppingGroup::createMeatLoversPizza();
    Pizza* basePizza = new BasePizza(meatLoversToppings);
    
    cout << "Starting with Meat Lovers:" << endl;
    basePizza->printPizza();
    cout << endl;
    
    // Add Extra Cheese
    Pizza* step1 = new ExtraCheese(basePizza);
    cout << "Step 1 - Added Extra Cheese:" << endl;
    step1->printPizza();
    cout << endl;
    
    // Add Stuffed Crust
    Pizza* step2 = new StuffedCrust(step1);
    cout << "Step 2 - Added Stuffed Crust:" << endl;
    step2->printPizza();
    cout << endl;
    
    // Test different order
    ToppingGroup* vegDeluxeToppings = ToppingGroup::createVegetarianDeluxePizza();
    Pizza* vegDeluxeBase = new BasePizza(vegDeluxeToppings);
    
    // Chain in different order: Stuffed Crust first, then Extra Cheese
    Pizza* altStep1 = new StuffedCrust(vegDeluxeBase);
    Pizza* altStep2 = new ExtraCheese(altStep1);
    
    cout << "Alternative chaining (Crust then Cheese):" << endl;
    altStep2->printPizza();
    cout << endl;
    
    // Cleanup
    delete step2;    // Cleans up the entire chain: step2 -> step1 -> basePizza
    delete altStep2; // Cleans up: altStep2 -> altStep1 -> vegDeluxeBase
    cout << endl;
}

void testAllPizzasWithDecorators() {
    cout << "=== Testing All Pizza Types with Decorators ===" << endl;
    
    vector<ToppingGroup*> pizzaToppings = {
        ToppingGroup::createPepperoniPizza(),
        ToppingGroup::createVegetarianPizza(),
        ToppingGroup::createMeatLoversPizza(),
        ToppingGroup::createVegetarianDeluxePizza()
    };
    
    for (size_t i = 0; i < pizzaToppings.size(); ++i) {
        cout << "Pizza " << (i + 1) << ":" << endl;
        
        // Create base pizza
        Pizza* base = new BasePizza(pizzaToppings[i]);
        cout << "  Base: " << base->getName() << " - R" << base->getPrice() << endl;
        
        // Add extra cheese
        Pizza* withCheese = new ExtraCheese(base);
        cout << "  + Extra Cheese: R" << withCheese->getPrice() << endl;
        
        // Add both decorators
        Pizza* fullyDecorated = new StuffedCrust(withCheese);
        cout << "  + Stuffed Crust: R" << fullyDecorated->getPrice() << endl;
        cout << "  Final: " << fullyDecorated->getName() << endl;
        
        delete fullyDecorated; // Cleans up the entire chain
        cout << endl;
    }
}

void testDecoratorPricing() {
    cout << "=== Testing Decorator Pricing ===" << endl;
    
    // Test pricing calculations
    cout << "Decorator Prices:" << endl;
    cout << "Extra Cheese: R" << ExtraCheese::getExtraCheesePrice() << endl;
    cout << "Stuffed Crust: R" << StuffedCrust::getStuffedCrustPrice() << endl;
    cout << endl;
    
    // Create a simple base pizza
    ToppingGroup* simpleToppings = new ToppingGroup("Simple");
    simpleToppings->addComponent(new Topping("Dough"));
    simpleToppings->addComponent(new Topping("Tomato Sauce"));
    simpleToppings->addComponent(new Topping("Cheese"));
    
    Pizza* simplePizza = new BasePizza(simpleToppings);
    double basePrice = simplePizza->getPrice();
    
    cout << "Base Pizza Price: R" << basePrice << endl;
    
    // Test individual decorators
    Pizza* withCheese = new ExtraCheese(simplePizza);
    double cheesePrice = withCheese->getPrice();
    cout << "With Extra Cheese: R" << cheesePrice << endl;
    cout << "Price increase: R" << (cheesePrice - basePrice) << endl;
    
    Pizza* withBoth = new StuffedCrust(withCheese);
    double fullPrice = withBoth->getPrice();
    cout << "With Both Decorators: R" << fullPrice << endl;
    cout << "Total price increase: R" << (fullPrice - basePrice) << endl;
    
    delete withBoth; // Cleans up the entire chain
    cout << endl;
}

void testDecoratorEdgeCases() {
    cout << "=== Testing Decorator Edge Cases ===" << endl;
    
    // Test decorating an empty pizza
    ToppingGroup* emptyGroup = new ToppingGroup("Empty");
    Pizza* emptyPizza = new BasePizza(emptyGroup);
    
    cout << "Empty Pizza:" << endl;
    cout << "Name: " << emptyPizza->getName() << endl;
    cout << "Price: R" << emptyPizza->getPrice() << endl;
    
    Pizza* decoratedEmpty = new ExtraCheese(emptyPizza);
    cout << "Empty + Extra Cheese:" << endl;
    cout << "Name: " << decoratedEmpty->getName() << endl;
    cout << "Price: R" << decoratedEmpty->getPrice() << endl;
    
    delete decoratedEmpty;
    cout << endl;
    
    // Test multiple layers of same decorator (hypothetical)
    ToppingGroup* basicToppings = ToppingGroup::createPepperoniPizza();
    Pizza* basicPizza = new BasePizza(basicToppings);
    
    Pizza* extraCheese1 = new ExtraCheese(basicPizza);
    Pizza* extraCheese2 = new ExtraCheese(extraCheese1);
    
    cout << "Double Extra Cheese:" << endl;
    cout << "Name: " << extraCheese2->getName() << endl;
    cout << "Price: R" << extraCheese2->getPrice() << endl;
    
    delete extraCheese2;
    cout << endl;
}

void testCompositeDecoratorIntegration() {
    cout << "=== Testing Composite-Decorator Integration ===" << endl;
    
    // Create a complex composite pizza
    ToppingGroup* customPizza = new ToppingGroup("Ultimate Pizza");
    
    // Add base
    ToppingGroup* base = new ToppingGroup("Base");
    base->addComponent(new Topping("Dough"));
    base->addComponent(new Topping("Tomato Sauce"));
    base->addComponent(new Topping("Cheese"));
    customPizza->addComponent(base);
    
    // Add all meat toppings
    ToppingGroup* meats = new ToppingGroup("All Meats");
    meats->addComponent(new Topping("Pepperoni"));
    meats->addComponent(new Topping("Beef Sausage"));
    meats->addComponent(new Topping("Salami"));
    customPizza->addComponent(meats);
    
    // Add all veggie toppings
    ToppingGroup* veggies = new ToppingGroup("All Vegetables");
    veggies->addComponent(new Topping("Mushrooms"));
    veggies->addComponent(new Topping("Green Peppers"));
    veggies->addComponent(new Topping("Onions"));
    veggies->addComponent(new Topping("Olives"));
    customPizza->addComponent(veggies);
    
    // Add premium toppings
    customPizza->addComponent(new Topping("Feta Cheese"));
    
    cout << "Complex Composite Pizza:" << endl;
    cout << "Components: " << customPizza->getComponentCount() << endl;
    cout << "Name: " << customPizza->getName() << endl;
    cout << "Base Price: R" << customPizza->getPrice() << endl;
    cout << endl;
    
    // Now decorate this complex pizza
    Pizza* ultimatePizza = new BasePizza(customPizza);
    Pizza* withExtraCheese = new ExtraCheese(ultimatePizza);
    Pizza* fullyLoaded = new StuffedCrust(withExtraCheese);
    
    cout << "Fully Decorated Ultimate Pizza:" << endl;
    fullyLoaded->printPizza();
    cout << endl;
    
    delete fullyLoaded;
    cout << endl;
}

void testIndividualToppings() {
    cout << "=== Testing Individual Toppings ===" << endl;
    
    // Test creating individual toppings
    Topping pepperoni("Pepperoni");
    Topping mushrooms("Mushrooms");
    Topping cheese("Cheese");
    Topping invalidTopping("Invalid Topping"); //this will cerr an error because its invalid 
    
    cout << "Pepperoni: " << pepperoni.getName() << " - R" << pepperoni.getPrice() << endl;
    cout << "Mushrooms: " << mushrooms.getName() << " - R" << mushrooms.getPrice() << endl;
    cout << "Cheese: " << cheese.getName() << " - R" << cheese.getPrice() << endl;
    cout << "Invalid Topping: " << invalidTopping.getName() << " - R" << invalidTopping.getPrice() << endl;
    
    // Test static methods
    cout << "\nValid topping check:" << endl;
    cout << "Is 'Pepperoni' valid? " << (Topping::isValidTopping("Pepperoni") ? "Yes" : "No") << endl;
    cout << "Is 'Pizza Sauce' valid? " << (Topping::isValidTopping("Pizza Sauce") ? "Yes" : "No") << endl;
    
    cout << endl;
    // Note: Stack objects are automatically cleaned up when they go out of scope
}

void testToppingGroups() {
    cout << "=== Testing Topping Groups ===" << endl;
    
    // Create a custom topping group
    ToppingGroup* customPizza = new ToppingGroup("Custom Pizza");
    customPizza->addComponent(new Topping("Dough"));
    customPizza->addComponent(new Topping("Tomato Sauce"));
    customPizza->addComponent(new Topping("Cheese"));
    customPizza->addComponent(new Topping("Pepperoni"));
    customPizza->addComponent(new Topping("Mushrooms"));
    
    cout << "Custom Pizza:" << endl;
    cout << "Name: " << customPizza->getName() << endl;
    cout << "Price: R" << customPizza->getPrice() << endl;
    cout << "Component count: " << customPizza->getComponentCount() << endl;
    cout << "Is empty? " << (customPizza->isEmpty() ? "Yes" : "No") << endl;
    
    delete customPizza;
    cout << endl;
}

void testPredefinedPizzas() {
    cout << "=== Testing Predefined Pizzas ===" << endl;
    
    // Test Pepperoni Pizza
    ToppingGroup* pepperoni = ToppingGroup::createPepperoniPizza();
    cout << "Pepperoni Pizza:" << endl;
    cout << "Name: " << pepperoni->getName() << endl;
    cout << "Price: R" << pepperoni->getPrice() << endl;
    cout << endl;
    
    // Test Vegetarian Pizza
    ToppingGroup* vegetarian = ToppingGroup::createVegetarianPizza();
    cout << "Vegetarian Pizza:" << endl;
    cout << "Name: " << vegetarian->getName() << endl;
    cout << "Price: R" << vegetarian->getPrice() << endl;
    cout << endl;
    
    // Test Meat Lovers Pizza
    ToppingGroup* meatLovers = ToppingGroup::createMeatLoversPizza();
    cout << "Meat Lovers Pizza:" << endl;
    cout << "Name: " << meatLovers->getName() << endl;
    cout << "Price: R" << meatLovers->getPrice() << endl;
    cout << endl;
    
    // Test Vegetarian Deluxe Pizza
    ToppingGroup* vegDeluxe = ToppingGroup::createVegetarianDeluxePizza();
    cout << "Vegetarian Deluxe Pizza:" << endl;
    cout << "Name: " << vegDeluxe->getName() << endl;
    cout << "Price: R" << vegDeluxe->getPrice() << endl;
    cout << endl;
    
    // Cleanup - FIXED: All pointers now properly deleted
    delete pepperoni;
    delete vegetarian;
    delete meatLovers;
    delete vegDeluxe;
}

void testComposition() {
    cout << "=== Testing Advanced Composition ===" << endl;
    
    // Create nested composition
    ToppingGroup* specialPizza = new ToppingGroup("Special Pizza");
    
    // Add base ingredients
    ToppingGroup* base = new ToppingGroup("Base");
    base->addComponent(new Topping("Dough"));
    base->addComponent(new Topping("Tomato Sauce"));
    base->addComponent(new Topping("Cheese"));
    
    // Add meat group
    ToppingGroup* meats = new ToppingGroup("Meats");
    meats->addComponent(new Topping("Pepperoni"));
    meats->addComponent(new Topping("Beef Sausage"));
    
    // Add veggie group
    ToppingGroup* veggies = new ToppingGroup("Vegetables");
    veggies->addComponent(new Topping("Mushrooms"));
    veggies->addComponent(new Topping("Onions"));
    
    // Compose the special pizza
    specialPizza->addComponent(base);
    specialPizza->addComponent(meats);
    specialPizza->addComponent(veggies);
    
    cout << "Special Pizza with nested groups:" << endl;
    cout << "Name: " << specialPizza->getName() << endl;
    cout << "Price: R" << specialPizza->getPrice() << endl;
    
    delete specialPizza;
    cout << endl;
}

void testCopyConstructor() {
    cout << "=== Testing Copy Constructor ===" << endl;
    
    ToppingGroup* original = ToppingGroup::createPepperoniPizza();
    cout << "Original Pizza Price: R" << original->getPrice() << endl;
    
    // Test copy constructor
    ToppingGroup copy(*original);
    cout << "Copied Pizza Price: R" << copy.getPrice() << endl;
    cout << "Copy Name: " << copy.getName() << endl;
    
    delete original;
    
    // Copy should still be valid after original is deleted
    cout << "Copy after original deletion: R" << copy.getPrice() << endl;
    cout << endl;
    // Note: copy object is automatically cleaned up when it goes out of scope
}

void testGroupModification() {
    cout << "=== Testing Group Modification ===" << endl;
    
    ToppingGroup* pizza = new ToppingGroup("Modifiable Pizza");
    
    // Add some initial toppings
    Topping* cheese = new Topping("Cheese");
    Topping* pepperoni = new Topping("Pepperoni");
    
    pizza->addComponent(cheese);
    pizza->addComponent(pepperoni);
    
    cout << "Before modification:" << endl;
    cout << "Price: R" << pizza->getPrice() << endl;
    cout << "Components: " << pizza->getComponentCount() << endl;
    
    // Remove pepperoni
    pizza->removeComponent(pepperoni);
    delete pepperoni; // Clean up removed component
    
    cout << "\nAfter removing pepperoni:" << endl;
    cout << "Price: R" << pizza->getPrice() << endl;
    cout << "Components: " << pizza->getComponentCount() << endl;
    
    // Add new topping
    pizza->addComponent(new Topping("Mushrooms"));
    
    cout << "\nAfter adding mushrooms:" << endl;
    cout << "Price: R" << pizza->getPrice() << endl;
    cout << "Components: " << pizza->getComponentCount() << endl;
    
    delete pizza;
    cout << endl;
}

void displayAllToppings() {
    cout << "=== All Available Toppings ===" << endl;
    
    auto allToppings = Topping::getAllToppings();
    for (const auto& topping : allToppings) {
        cout << topping.first << ": R" << topping.second << endl;
    }
    cout << endl;
    // Note: This function uses static data, no cleanup needed
}

// PizzaOrders tests - FIXED: Added proper cleanup for all dynamically allocated pizzas

void testPizzaOrdersBasic() {
    cout << "=== Testing Basic PizzaOrders Functionality ===" << endl;
    
    // Test default constructor
    PizzaOrders defaultOrder;
    defaultOrder.setOrderNumber(1001);
    defaultOrder.setOrderName("John Doe");
    
    cout << "Default Order Created:" << endl;
    cout << "Order Number: " << defaultOrder.getOrderNumber() << endl;
    cout << "Customer Name: " << defaultOrder.getOrderName() << endl;
    cout << "Pizza Count: " << defaultOrder.getPizzaCount() << endl;
    cout << "Total Price: R" << defaultOrder.getTotalPrice() << endl;
    cout << endl;
    
    // Test parameterized constructor
    PizzaOrders order2(1002, "Jane Smith");
    cout << "Parameterized Order Created:" << endl;
    cout << "Order Number: " << order2.getOrderNumber() << endl;
    cout << "Customer Name: " << order2.getOrderName() << endl;
    cout << endl;
    
    // Note: PizzaOrders destructor should handle cleanup of internal pizzas
}

void testPizzaCreationMethods() {
    cout << "=== Testing Pizza Creation Methods ===" << endl;
    
    PizzaOrders order(1003, "Pizza Test Customer");
    
    // Test creating different types of pizzas
    Pizza* pepperoni = order.createPepperoniPizza();
    Pizza* vegetarian = order.createVegetarianPizza(true); // with extra cheese
    Pizza* meatLovers = order.createMeatLoversPizza(false, true); // with stuffed crust
    Pizza* vegDeluxe = order.createVegetarianDeluxePizza(true, true); // with both decorators
    
    // Add pizzas to order
    order.addPizza(pepperoni);
    order.addPizza(vegetarian);
    order.addPizza(meatLovers);
    order.addPizza(vegDeluxe);
    
    cout << "Created and added 4 pizzas:" << endl;
    cout << "Pizza Count: " << order.getPizzaCount() << endl;
    cout << "Total Price: R" << order.getTotalPrice() << endl;
    cout << endl;
    
    order.displayOrder();
    cout << endl;
    
    // Note: PizzaOrders destructor will handle cleanup of pizzas
}

void testCustomPizzaCreation() {
    cout << "=== Testing Custom Pizza Creation ===" << endl;
    
    PizzaOrders order(1004, "Custom Pizza Lover");
    
    // Create custom pizzas with different toppings
    vector<string> toppings1 = {"Pepperoni", "Mushrooms", "Olives"};
    vector<string> toppings2 = {"Beef Sausage", "Green Peppers", "Onions", "Feta Cheese"};
    vector<string> invalidToppings = {"Invalid Topping", "Pepperoni", "Another Invalid"}; // Mix of valid and invalid
    
    Pizza* custom1 = order.createCustomPizza(toppings1);
    Pizza* custom2 = order.createCustomPizza(toppings2, true, false); // with extra cheese
    Pizza* custom3 = order.createCustomPizza(invalidToppings, false, true);
    
    order.addPizza(custom1);
    order.addPizza(custom2);
    order.addPizza(custom3);
    
    cout << "Created custom pizzas with different toppings:" << endl;
    order.displayOrder();
    cout << endl;
    
    // Note: PizzaOrders destructor will handle cleanup
}

void testOrderManagement() {
    cout << "=== Testing Order Management ===" << endl;
    
    PizzaOrders order(1005, "Order Manager");
    
    // Add several pizzas
    order.addPizza(order.createPepperoniPizza());
    order.addPizza(order.createVegetarianPizza(true));
    order.addPizza(order.createMeatLoversPizza(false, true));
    
    cout << "After adding 3 pizzas:" << endl;
    order.displayOrderSummary();
    
    // Remove a pizza
    cout << "\nRemoving pizza at index 1:" << endl;
    bool removed = order.removePizza(1);
    cout << "Removal " << (removed ? "successful" : "failed") << endl;
    order.displayOrderSummary();
    
    // Try to remove invalid index
    cout << "\nTrying to remove pizza at invalid index 10:" << endl;
    removed = order.removePizza(10);
    cout << "Removal " << (removed ? "successful" : "failed") << endl;
    
    // Clear entire order
    cout << "\nClearing entire order:" << endl;
    order.clearOrder();
    order.displayOrderSummary();
    cout << endl;
    
    // Note: PizzaOrders methods should handle proper cleanup
}

void testCopyConstructorAndAssignment() {
    cout << "=== Testing Copy Constructor and Assignment (With Deep Cloning) ===" << endl;
    
    // Create original order
    PizzaOrders original(1006, "Original Customer");
    original.addPizza(original.createPepperoniPizza(true));
    original.addPizza(original.createVegetarianPizza(false, true));
    
    cout << "Original order:" << endl;
    original.displayOrderSummary();
    
    // Test copy constructor
    PizzaOrders copied(original);
    copied.setOrderNumber(1007);
    copied.setOrderName("Copied Customer");
    
    cout << "\nCopied order (with deep cloned pizzas):" << endl;
    copied.displayOrderSummary();
    
    // Test assignment operator
    PizzaOrders assigned;
    assigned = original;
    assigned.setOrderNumber(1008);
    assigned.setOrderName("Assigned Customer");
    
    cout << "\nAssigned order (with deep cloned pizzas):" << endl;
    assigned.displayOrderSummary();
    
    // Add pizzas to copies to demonstrate independence
    copied.addPizza(copied.createMeatLoversPizza(true, true));
    assigned.addPizza(assigned.createVegetarianDeluxePizza());
    
    cout << "\nAfter adding pizzas to copies (demonstrating independence):" << endl;
    cout << "Original: " << original.getPizzaCount() << " pizzas, R" << original.getTotalPrice() << endl;
    cout << "Copied: " << copied.getPizzaCount() << " pizzas, R" << copied.getTotalPrice() << endl;
    cout << "Assigned: " << assigned.getPizzaCount() << " pizzas, R" << assigned.getTotalPrice() << endl;
    cout << "All orders are now independent with proper deep copying!" << endl;
    cout << endl;
    
    // Note: PizzaOrders destructors will handle cleanup when objects go out of scope
}

void testComplexOrders() {
    cout << "=== Testing Complex Orders ===" << endl;
    
    PizzaOrders complexOrder(1009, "Complex Order Customer");
    
    // Create a variety of pizzas with different decorators
    complexOrder.addPizza(complexOrder.createPepperoniPizza(true, true)); // Both decorators
    
    vector<string> customToppings = {"Pepperoni", "Beef Sausage", "Mushrooms", "Olives", "Feta Cheese"};
    complexOrder.addPizza(complexOrder.createCustomPizza(customToppings, true, false)); // Extra cheese only
    
    complexOrder.addPizza(complexOrder.createMeatLoversPizza(false, true)); // Stuffed crust only
    complexOrder.addPizza(complexOrder.createVegetarianDeluxePizza()); // No decorators
    
    // Add multiple custom pizzas
    vector<string> veggieToppings = {"Mushrooms", "Green Peppers", "Onions", "Olives"};
    complexOrder.addPizza(complexOrder.createCustomPizza(veggieToppings, true, true));
    
    cout << "Complex order with " << complexOrder.getPizzaCount() << " pizzas:" << endl;
    complexOrder.displayOrder();
    cout << endl;
    
    // Note: PizzaOrders destructor will handle cleanup
}

void testOrderDisplayMethods() {
    cout << "=== Testing Order Display Methods ===" << endl;
    
    PizzaOrders order(1010, "Display Test Customer");
    
    // Empty order display
    cout << "Empty order display:" << endl;
    order.displayOrder();
    order.displayOrderSummary();
    
    // Add some pizzas
    order.addPizza(order.createPepperoniPizza(true));
    order.addPizza(order.createVegetarianPizza(false, true));
    
    cout << "\nOrder with pizzas:" << endl;
    order.displayOrder();
    order.displayOrderSummary();
    cout << endl;
    
    // Note: PizzaOrders destructor will handle cleanup
}

void testPizzaOrdersIntegration() {
    cout << "=== Testing PizzaOrders Integration with Patterns ===" << endl;
    
    PizzaOrders masterOrder(2000, "Pattern Integration Test");
    
    // Test all predefined pizzas with all decorator combinations
    cout << "Testing all predefined pizzas with decorator combinations:" << endl;
    
    // Pepperoni variations
    masterOrder.addPizza(masterOrder.createPepperoniPizza(false, false)); // Plain
    masterOrder.addPizza(masterOrder.createPepperoniPizza(true, false));  // Extra cheese
    masterOrder.addPizza(masterOrder.createPepperoniPizza(false, true));  // Stuffed crust
    masterOrder.addPizza(masterOrder.createPepperoniPizza(true, true));   // Both decorators
    
    // Vegetarian variations
    masterOrder.addPizza(masterOrder.createVegetarianPizza(false, false));
    masterOrder.addPizza(masterOrder.createVegetarianPizza(true, true));
    
    // Meat Lovers variations
    masterOrder.addPizza(masterOrder.createMeatLoversPizza(true, false));
    masterOrder.addPizza(masterOrder.createMeatLoversPizza(false, true));
    
    // Vegetarian Deluxe
    masterOrder.addPizza(masterOrder.createVegetarianDeluxePizza(true, true));
    
    // Custom pizzas
    vector<string> ultimateToppings = {"Pepperoni", "Beef Sausage", "Salami", "Mushrooms", "Green Peppers", "Onions", "Olives", "Feta Cheese"};
    masterOrder.addPizza(masterOrder.createCustomPizza(ultimateToppings, true, true));
    
    cout << "Master order created with " << masterOrder.getPizzaCount() << " pizzas" << endl;
    cout << "Total order value: R" << masterOrder.getTotalPrice() << endl;
    cout << endl;
    
    // Display full order
    masterOrder.displayOrder();
    cout << endl;
    
    // Note: PizzaOrders destructor will handle cleanup
}



void testBasicObserverPattern() {
    std::cout << "\n=== Testing Basic Observer Pattern ===" << std::endl;
    
    // creating subjects (menus)
    PizzaMenu* mainMenu = new PizzaMenu("Romeo's Main Menu");
    SpecialsMenu* specials = new SpecialsMenu("Weekly Specials");
    
    // creating observers
    Customer* customer1 = new Customer("Mario Rossi", "082-555-1234");
    Customer* customer2 = new Customer("Lucia Ferrari", "083-555-5678");
    Website* website = new Website();
    
    // register observers with menus
    mainMenu->addObserver(customer1);
    mainMenu->addObserver(customer2);
    mainMenu->addObserver(website);
    
    specials->addObserver(customer1);
    specials->addObserver(customer2);
    specials->addObserver(website);
    
    std::cout << "\n--- Adding pizzas to main menu ---" << std::endl;
    Pizza* newPizza1 = new BasePizza(ToppingGroup::createPepperoniPizza());
    Pizza* newPizza2 = new BasePizza(ToppingGroup::createVegetarianPizza());
    
    mainMenu->addPizza(newPizza1);
    mainMenu->addPizza(newPizza2);
    
    std::cout << "\n--- Adding special offers ---" << std::endl;
    Pizza* specialPizza1 = new BasePizza(ToppingGroup::createMeatLoversPizza());
    Pizza* specialPizza2 = new BasePizza(ToppingGroup::createVegetarianDeluxePizza());
    
    specials->addSpecialOffer(specialPizza1, "20% off today!");
    specials->addSpecialOffer(specialPizza2, "Buy one, get one half price!");
    
    std::cout << "\n--- Displaying notifications ---" << std::endl;
    customer1->displayNotifications();
    customer2->displayNotifications();
    website->displayUpdates();
    
    // Cleanup - the first two will cleanup pizzas automatically
    delete mainMenu;
    delete specials;
    delete customer1;
    delete customer2;
    delete website;
    
    std::cout << "Basic Observer Pattern test complete" << std::endl;
}

void testObserverRegistrationAndRemoval() {
    std::cout << "\n=== Testing Observer Registration and Removal ===" << std::endl;
    
    PizzaMenu* menu = new PizzaMenu("Test Menu");
    
    Customer* customer1 = new Customer("Test Customer 1");
    Customer* customer2 = new Customer("Test Customer 2");
    Customer* customer3 = new Customer("Test Customer 3");
    
    // registering observers
    menu->addObserver(customer1);
    menu->addObserver(customer2);
    menu->addObserver(customer3);
    
    std::cout << "--- Registered 3 observers ---" << std::endl;
    
    // adding a pizza (notify all 3 observers)
    Pizza* pizza = new BasePizza(ToppingGroup::createPepperoniPizza());
    menu->addPizza(pizza);
    
    std::cout << "\n--- Removing one observer ---" << std::endl;
    menu->removeObserver(customer2);
    
    // adding another pizza (notify the two left)
    Pizza* pizza2 = new BasePizza(ToppingGroup::createVegetarianPizza());
    menu->addPizza(pizza2);
    
    std::cout << "\nFinal notification counts: " << std::endl;
    std::cout << "Customer 1 notifications: " << customer1->getNotifications().size() << std::endl;
    std::cout << "Customer 2 notifications: " << customer2->getNotifications().size() << std::endl;
    std::cout << "Customer 3 notifications: " << customer3->getNotifications().size() << std::endl;
    
    // Cleanup
    delete menu;
    delete customer1;
    delete customer2;
    delete customer3;
    
    std::cout << "Observer registration and removal test completed" << std::endl;
}

void testPizzaMenuOperations() {
    std::cout << "\n=== Testing Pizza Menu Operations ===" << std::endl;
    
    PizzaMenu* menu = new PizzaMenu("Test Pizza Menu");
    Customer* customer = new Customer("Test Customer");
    Website* website = new Website();
    
    menu->addObserver(customer);
    menu->addObserver(website);
    
    // create various pizzas
    Pizza* pepperoni = new BasePizza(ToppingGroup::createPepperoniPizza());
    Pizza* decorated = new ExtraCheese(new BasePizza(ToppingGroup::createVegetarianPizza()));
    
    std::cout << "\nAdding pizzas to menu" << std::endl;
    menu->addPizza(pepperoni);
    menu->addPizza(decorated);
    
    std::cout << "\n--- Displaying menu ---" << std::endl;
    menu->displayMenu();
    
    std::cout << "\n--- Removing a pizza ---" << std::endl;
    menu->removePizza(pepperoni);
    // FIXED: Delete the pizza after removing it from menu since menu no longer owns it
    delete pepperoni;
    
    std::cout << "\n--- Final menu state ---" << std::endl;
    menu->displayMenu();
    
    // Cleanup
    delete menu;  // This will delete remaining pizzas (decorated)
    delete customer;
    delete website;
    
    std::cout << "Pizza Menu operations test completed" << std::endl;
}

void testSpecialsMenuOperations() {
    std::cout << "\n=== Testing Specials Menu Operations ===" << std::endl;
    
    SpecialsMenu* specials = new SpecialsMenu("Tuesday Specials");
    Customer* loyalCustomer = new Customer("Loyal Customer", "084-123-4567");
    Website* website = new Website();
    
    specials->addObserver(loyalCustomer);
    specials->addObserver(website);
    
    // creating special offers pizza
    Pizza* meatLovers = new BasePizza(ToppingGroup::createMeatLoversPizza());
    Pizza* vegDeluxe = new ExtraCheese(new StuffedCrust(
        new BasePizza(ToppingGroup::createVegetarianDeluxePizza())
    ));
    
    std::cout << "\n--- Adding special offers ---" << std::endl;
    specials->addSpecialOffer(meatLovers, "30% off for Meat Lovers Tuesday");
    specials->addSpecialOffer(vegDeluxe, "Free delivery on fully loaded veggie pizza");
    
    std::cout << "\n--- Displaying specials menu ---" << std::endl;
    specials->displaySpecialsMenu();
    
    std::cout << "\n--- Ending a special offer ---" << std::endl;
    specials->removeSpecialOffer(meatLovers);
    // FIXED: Delete the pizza after removing it from specials since specials no longer owns it
    delete meatLovers;
    
    std::cout << "\n--- Final specials menu ---" << std::endl;
    specials->displaySpecialsMenu();
    
    // check notifications
    std::cout << "\n--- Customer notifications ---" << std::endl;
    loyalCustomer->displayNotifications();
    
    // Cleanup
    delete specials;  // This will delete remaining pizzas (vegDeluxe)
    delete loyalCustomer;
    delete website;
    
    std::cout << "Specials Menu operations test completed!" << std::endl;
}

void testMultipleMenusAndObservers() {
    std::cout << "\n=== Testing Multiple Menus and Observers ===" << std::endl;
    
    // multiple menus
    PizzaMenu* mainMenu = new PizzaMenu("Main Menu");
    PizzaMenu* kidsMenu = new PizzaMenu("Kids Menu");
    SpecialsMenu* weeklySpecials = new SpecialsMenu("Weekly Specials");
    SpecialsMenu* holidaySpecials = new SpecialsMenu("Holiday Specials");
    
    // multiple observers
    Customer* family = new Customer("The Rossi Family", "082-111-2222");
    Customer* student = new Customer("University Student", "083-333-4444");
    Website* mainWebsite = new Website("Romeo's Main Site");
    Website* mobileApp = new Website("Romeo's Mobile App", "app.romeospizza.co.za");
    
    // complex observer registration
    mainMenu->addObserver(family);
    mainMenu->addObserver(student);
    mainMenu->addObserver(mainWebsite);
    
    kidsMenu->addObserver(family); // Only family that wants kids menu
    kidsMenu->addObserver(mainWebsite);
    
    weeklySpecials->addObserver(family);
    weeklySpecials->addObserver(student);
    weeklySpecials->addObserver(mainWebsite);
    weeklySpecials->addObserver(mobileApp);
    
    holidaySpecials->addObserver(family);
    holidaySpecials->addObserver(mobileApp);
    
    std::cout << "\n--- Adding items to different menus ---" << std::endl;
    
    // Main menu updates
    mainMenu->addPizza(new BasePizza(ToppingGroup::createPepperoniPizza()));
    
    // Kids menu updates
    Pizza* kidsPizza = new BasePizza(new ToppingGroup("Mini Margherita"));
    kidsMenu->addPizza(kidsPizza);
    
    // Weekly specials
    weeklySpecials->addSpecialOffer(
        new BasePizza(ToppingGroup::createMeatLoversPizza()), 
        "Monday Meat Madness - 25% off!"
    );
    
    // Holiday specials
    holidaySpecials->addSpecialOffer(
        new ExtraCheese(new StuffedCrust(new BasePizza(ToppingGroup::createVegetarianDeluxePizza()))),
        "Heritage Day Special. R50 off family size"
    );
    
    std::cout << "\n--- Notification Summary ---" << std::endl;
    std::cout << "Family notifications: " << family->getNotifications().size() << std::endl;
    std::cout << "Student notifications: " << student->getNotifications().size() << std::endl;
    std::cout << "Main website updates: " << mainWebsite->getUpdates().size() << std::endl;
    std::cout << "Mobile app updates: " << mobileApp->getUpdates().size() << std::endl;
    
    // Cleanup
    delete mainMenu;
    delete kidsMenu;
    delete weeklySpecials;
    delete holidaySpecials;
    delete family;
    delete student;
    delete mainWebsite;
    delete mobileApp;
    
    std::cout << "Multiple Menus and Observers test completed!" << std::endl;
}

// MISSING TEST COVERAGE ANALYSIS
// ================================

// 1. DISCOUNT STRATEGY PATTERN - COMPLETELY UNTESTED
// Your PizzaOrders class has extensive discount strategy functionality but no tests

void testDiscountStrategies() {
    cout << "\n=== Testing Discount Strategies ===" << endl;
    
    PizzaOrders order(5001, "Discount Test Customer");
    order.addPizza(order.createPepperoniPizza());
    order.addPizza(order.createVegetarianPizza());
    order.addPizza(order.createMeatLoversPizza());
    
    cout << "Base order total: R" << order.getTotalPrice() << endl;
    
    // Test RegularPrice (no discount)
    order.setDiscountStrategy(new RegularPrice());
    cout << "Regular Price - Discount: R" << order.getDiscountAmount() 
         << ", Final: R" << order.getDiscountedTotal() << endl;
    
    // Test FamilyDiscount
    order.setDiscountStrategy(new FamilyDiscount());
    cout << "Family Discount - Discount: R" << order.getDiscountAmount() 
         << ", Final: R" << order.getDiscountedTotal() << endl;
    
    // Test BulkDiscount
    order.setDiscountStrategy(new BulkDiscount());
    cout << "Bulk Discount - Discount: R" << order.getDiscountAmount() 
         << ", Final: R" << order.getDiscountedTotal() << endl;
    
    // Test StudentDiscount
    order.setDiscountStrategy(new StudentDiscount());
    cout << "Student Discount - Discount: R" << order.getDiscountAmount() 
         << ", Final: R" << order.getDiscountedTotal() << endl;
    
    // Test SeniorDiscount
    order.setDiscountStrategy(new SeniorDiscount());
    cout << "Senior Discount - Discount: R" << order.getDiscountAmount() 
         << ", Final: R" << order.getDiscountedTotal() << endl;
    
    // Test LoyaltyDiscount with different tiers
    for (int tier = 1; tier <= 5; ++tier) {
        order.setDiscountStrategy(new LoyaltyDiscount(tier));
        cout << "Loyalty Tier " << tier << " - Discount: R" << order.getDiscountAmount() 
             << ", Final: R" << order.getDiscountedTotal() << endl;
    }
    
    // Test displayDiscountInfo
    order.displayDiscountInfo();
}

void testDiscountEdgeCases() {
    cout << "\n=== Testing Discount Edge Cases ===" << endl;
    
    // Test with empty order
    PizzaOrders emptyOrder(5002, "Empty Order");
    emptyOrder.setDiscountStrategy(new FamilyDiscount());
    cout << "Empty order discount: R" << emptyOrder.getDiscountAmount() << endl;
    
    // Test with single pizza (should not qualify for family discount)
    PizzaOrders singleOrder(5003, "Single Pizza");
    singleOrder.addPizza(singleOrder.createPepperoniPizza());
    singleOrder.setDiscountStrategy(new FamilyDiscount());
    cout << "Single pizza family discount: R" << singleOrder.getDiscountAmount() << endl;
    
    // Test loyalty tier bounds
    LoyaltyDiscount* loyalty = new LoyaltyDiscount(10); // Should cap at 5
    cout << "Loyalty tier with input 10: " << loyalty->getTier() << endl;
    
    loyalty->setTier(-5); // Should set to 1
    cout << "Loyalty tier with input -5: " << loyalty->getTier() << endl;
    
    delete loyalty;
}

void testDiscountStrategyPolymorphism() {
    cout << "\n=== Testing Discount Strategy Polymorphism ===" << endl;
    
    PizzaOrders order(5004, "Polymorphism Test");
    order.addPizza(order.createMeatLoversPizza(true, true)); // Expensive pizza
    order.addPizza(order.createVegetarianDeluxePizza(true, true));
    
    // Array of different strategies
    DiscountStrategy* strategies[] = {
        new RegularPrice(),
        new FamilyDiscount(),
        new BulkDiscount(),
        new StudentDiscount(),
        new SeniorDiscount(),
        new LoyaltyDiscount(3)
    };
    
    for (int i = 0; i < 6; ++i) {
        order.setDiscountStrategy(strategies[i]);
        cout << "Strategy: " << strategies[i]->getStrategyName() 
             << " - Description: " << strategies[i]->getDescription() << endl;
        cout << "Discount: R" << order.getDiscountAmount() << endl;
        strategies[i] = nullptr; // Strategy now owned by order
    }
}

// 2. STATE PATTERN EDGE CASES - Some missing scenarios

void testStatePatternEdgeCases() {
    cout << "\n=== Testing State Pattern Edge Cases ===" << endl;
    
    // Test state without pizzas
    PizzaOrders order(6001, "State Edge Case");
    order.setState(new OrderingState());
    
    // Test getAvailableActions and canModifyOrder in all states
    OrderState* states[] = {
        new OrderingState(),
        new ConfirmedState(),
        new PaidState(),
        new PreparingState(),
        new DeliveringState(),
        new CompletedState(),
        new CancelledState()
    };
    
    for (int i = 0; i < 7; ++i) {
        order.setState(states[i]);
        cout << "State: " << order.getCurrentStateName() << endl;
        cout << "Can modify: " << order.canModifyOrder() << endl;
        cout << "Actions: " << order.getAvailableActions() << endl;
        states[i] = nullptr; // State now owned by order
    }
}

// 3. PIZZAORDERS FUNCTIONALITY - Missing tests

void testPizzaOrdersGetters() {
    cout << "\n=== Testing PizzaOrders Getters ===" << endl;
    
    PizzaOrders order(7001, "Getter Test");
    Pizza* pizza1 = order.createPepperoniPizza();
    Pizza* pizza2 = order.createVegetarianPizza();
    
    order.addPizza(pizza1);
    order.addPizza(pizza2);
    
    // Test getPizzas() method
    auto pizzaVector = order.getPizzas();
    cout << "getPizzas() returned " << pizzaVector.size() << " pizzas" << endl;
    
    // Test getDiscountStrategy() when null
    cout << "Discount strategy when null: " << (order.getDiscountStrategy() == nullptr ? "nullptr" : "not null") << endl;
    
    // Test getDiscountStrategy() when set
    order.setDiscountStrategy(new FamilyDiscount());
    cout << "Discount strategy when set: " << (order.getDiscountStrategy() != nullptr ? "not null" : "nullptr") << endl;
}

// 4. COMPOSITE PATTERN - Missing deep nesting tests

void testDeepComposition() {
    cout << "\n=== Testing Deep Composition Nesting ===" << endl;
    
    // Create deeply nested structure
    ToppingGroup* level1 = new ToppingGroup("Level 1");
    ToppingGroup* level2 = new ToppingGroup("Level 2");
    ToppingGroup* level3 = new ToppingGroup("Level 3");
    ToppingGroup* level4 = new ToppingGroup("Level 4");
    
    level4->addComponent(new Topping("Deep Topping"));
    level3->addComponent(level4);
    level2->addComponent(level3);
    level1->addComponent(level2);
    level1->addComponent(new Topping("Surface Topping"));
    
    cout << "Deep composition price: R" << level1->getPrice() << endl;
    cout << "Deep composition component count: " << level1->getComponentCount() << endl;
    
    delete level1; // Should cascade delete all levels
}

// 5. MEMORY MANAGEMENT - Missing destructor behavior tests

void testMemoryManagement() {
    cout << "\n=== Testing Memory Management ===" << endl;
    
    // Test PizzaOrders destructor with strategies
    {
        PizzaOrders order(8001, "Memory Test");
        order.addPizza(order.createPepperoniPizza());
        order.setDiscountStrategy(new BulkDiscount());
        // Order should clean up pizza and strategy when destroyed
    }
    cout << "PizzaOrders with strategy destroyed" << endl;
    
    // Test assignment operator with strategies
    {
        PizzaOrders order1(8002, "Original");
        order1.addPizza(order1.createVegetarianPizza());
        order1.setDiscountStrategy(new StudentDiscount());
        
        PizzaOrders order2(8003, "Copy");
        order2.addPizza(order2.createMeatLoversPizza());
        order2.setDiscountStrategy(new FamilyDiscount());
        
        order2 = order1; // Should clean up order2's original strategy and pizzas
        cout << "Assignment with strategies completed" << endl;
    }
}

// 6. DECORATOR PATTERN - Missing null pointer tests

void testDecoratorNullHandling() {
    cout << "\n=== Testing Decorator Null Handling ===" << endl;
    
    // Test decorators with null pizza (should not crash)
    try {
        ExtraCheese* decorator1 = new ExtraCheese(nullptr);
        cout << "ExtraCheese with null: " << decorator1->getName() << endl;
        delete decorator1;
        
        StuffedCrust* decorator2 = new StuffedCrust(nullptr);
        cout << "StuffedCrust with null: " << decorator2->getName() << endl;
        delete decorator2;
    } catch (const std::exception& e) {
        cout << "Exception caught: " << e.what() << endl;
    }
}

// 7. OBSERVER PATTERN - Missing notification content tests

void testObserverNotificationContent() {
    cout << "\n=== Testing Observer Notification Content ===" << endl;
    
    PizzaMenu* menu = new PizzaMenu("Content Test Menu");
    Customer* customer = new Customer("Content Test Customer");
    
    menu->addObserver(customer);
    
    Pizza* pizza = new BasePizza(ToppingGroup::createPepperoniPizza());
    menu->addPizza(pizza);
    
    // Test notification content
    auto notifications = customer->getNotifications();
    cout << "Number of notifications: " << notifications.size() << endl;
    
    if (!notifications.empty()) {
        cout << "First notification: " << notifications[0] << endl;
    }
    
    delete menu;
    delete customer;
}

// 8. STATIC METHODS - Missing comprehensive static method tests

void testStaticMethods() {
    cout << "\n=== Testing Static Methods ===" << endl;
    
    // Test ExtraCheese and StuffedCrust static price methods
    cout << "ExtraCheese static price: R" << ExtraCheese::getExtraCheesePrice() << endl;
    cout << "StuffedCrust static price: R" << StuffedCrust::getStuffedCrustPrice() << endl;
    
    // Test Topping static methods more thoroughly
    cout << "All toppings count: " << Topping::getAllToppings().size() << endl;
    
    // Test edge cases for isValidTopping
    cout << "Empty string valid: " << Topping::isValidTopping("") << endl;
    cout << "Null check (spaces): " << Topping::isValidTopping("   ") << endl;
    cout << "Case sensitive: " << Topping::isValidTopping("pepperoni") << endl; // lowercase
}

// Main function to run all missing tests
void runMissingTests() {
    cout << "\n" << string(60, '=') << endl;
    cout << "        RUNNING MISSING TEST COVERAGE" << endl;
    cout << string(60, '=') << endl;
    
    testDiscountStrategies();
    testDiscountEdgeCases();
    testDiscountStrategyPolymorphism();
    testStatePatternEdgeCases();
    testPizzaOrdersGetters();
    testDeepComposition();
    testMemoryManagement();
    testDecoratorNullHandling();
    testObserverNotificationContent();
    testStaticMethods();
    
    cout << "\n" << string(60, '=') << endl;
    cout << "        MISSING TESTS COMPLETED" << endl;
    cout << string(60, '=') << endl;
}

void testObserverPatternWithPizzaOrders() {
    std::cout << "\n=== Testing Observer Pattern Integration with PizzaOrders ===" << std::endl;
    
    // create menus
    PizzaMenu* menu = new PizzaMenu("Romeo's Complete Menu");
    SpecialsMenu* specials = new SpecialsMenu("Daily Specials");
    
    // create observers
    Customer* customer = new Customer("Integration Test Customer");
    Website* website = new Website();
    
    menu->addObserver(customer);
    menu->addObserver(website);
    specials->addObserver(customer);
    specials->addObserver(website);
    
    // create pizzas using PizzaOrders class
    PizzaOrders orderSystem(3001, "Menu Management System");
    
    // create pizzas and add to menus
    Pizza* pepperoni = orderSystem.createPepperoniPizza(true, false);
    Pizza* vegDeluxe = orderSystem.createVegetarianDeluxePizza(false, true);
    Pizza* custom = orderSystem.createCustomPizza({"Mushrooms", "Olives", "Feta Cheese"});
    
    std::cout << "\n--- Adding PizzaOrders-created pizzas to menus ---" << std::endl;
    menu->addPizza(pepperoni);
    menu->addPizza(vegDeluxe);
    
    specials->addSpecialOffer(custom, "Chef's Special - Limited time only!");
    
    std::cout << "\n--- Displaying final state ---" << std::endl;
    menu->displayMenu();
    specials->displaySpecialsMenu();
    
    // don't add these pizzas to the order system since they're now owned by the menus
    // menus will handle cleanup
    
    // Cleanup - these will cleanup the pizzas
    delete menu;
    delete specials;
    delete customer;  // FIXED: Added missing cleanup
    delete website;   // FIXED: Added missing cleanup
    
    std::cout << "Observer Pattern with PizzaOrders test completed!" << std::endl;
}
// Add these functions to your PizzaOrders.cpp file or create a separate test file

// Additional test functions to improve coverage for Topping and ToppingGroup classes

void testToppingAssignmentOperator() {
    cout << "\n=== Testing Topping Assignment Operator ===" << endl;
    
    // Create two toppings
    Topping topping1("Pepperoni");
    Topping topping2("Mushrooms");
    
    cout << "Before assignment:" << endl;
    cout << "Topping1: " << topping1.getName() << " - R" << topping1.getPrice() << endl;
    cout << "Topping2: " << topping2.getName() << " - R" << topping2.getPrice() << endl;
    
    // Test assignment operator (if it exists)
    topping2 = topping1;
    
    cout << "After assignment:" << endl;
    cout << "Topping1: " << topping1.getName() << " - R" << topping1.getPrice() << endl;
    cout << "Topping2: " << topping2.getName() << " - R" << topping2.getPrice() << endl;
    
    cout << endl;
}

void testToppingGroupAssignmentOperator() {
    cout << "\n=== Testing ToppingGroup Assignment Operator ===" << endl;
    
    // Create two topping groups
    ToppingGroup group1("First Group");
    group1.addComponent(new Topping("Pepperoni"));
    group1.addComponent(new Topping("Mushrooms"));
    
    ToppingGroup group2("Second Group");
    group2.addComponent(new Topping("Cheese"));
    
    cout << "Before assignment:" << endl;
    cout << "Group1: " << group1.getName() << " - R" << group1.getPrice() << endl;
    cout << "Group2: " << group2.getName() << " - R" << group2.getPrice() << endl;
    
    // Test assignment operator
    group2 = group1;
    
    cout << "After assignment:" << endl;
    cout << "Group1: " << group1.getName() << " - R" << group1.getPrice() << endl;
    cout << "Group2: " << group2.getName() << " - R" << group2.getPrice() << endl;
    
    // Test independence after assignment
    group1.addComponent(new Topping("Olives"));
    cout << "After adding to group1:" << endl;
    cout << "Group1 components: " << group1.getComponentCount() << endl;
    cout << "Group2 components: " << group2.getComponentCount() << endl;
    
    cout << endl;
}

void testToppingGroupSelfAssignment() {
    cout << "\n=== Testing ToppingGroup Self-Assignment ===" << endl;
    
    ToppingGroup group("Self Assignment Test");
    group.addComponent(new Topping("Pepperoni"));
    group.addComponent(new Topping("Mushrooms"));
    
    cout << "Before self-assignment:" << endl;
    cout << "Components: " << group.getComponentCount() << endl;
    cout << "Price: R" << group.getPrice() << endl;
    
    // Test self-assignment
    group = group;
    
    cout << "After self-assignment:" << endl;
    cout << "Components: " << group.getComponentCount() << endl;
    cout << "Price: R" << group.getPrice() << endl;
    cout << "Name: " << group.getName() << endl;
    
    cout << endl;
}

void testToppingGroupClearComponents() {
    cout << "\n=== Testing ToppingGroup clearComponents ===" << endl;
    
    ToppingGroup group("Clear Test");
    group.addComponent(new Topping("Pepperoni"));
    group.addComponent(new Topping("Mushrooms"));
    group.addComponent(new Topping("Cheese"));
    
    cout << "Before clearing:" << endl;
    cout << "Components: " << group.getComponentCount() << endl;
    cout << "Price: R" << group.getPrice() << endl;
    cout << "Is empty? " << (group.isEmpty() ? "Yes" : "No") << endl;
    
    // Clear all components
    group.clearComponents();
    
    cout << "After clearing:" << endl;
    cout << "Components: " << group.getComponentCount() << endl;
    cout << "Price: R" << group.getPrice() << endl;
    cout << "Is empty? " << (group.isEmpty() ? "Yes" : "No") << endl;
    cout << "Name: " << group.getName() << endl;
    
    cout << endl;
}

void testToppingGroupRemoveComponent() {
    cout << "\n=== Testing ToppingGroup removeComponent ===" << endl;
    
    ToppingGroup group("Remove Test");
    Topping* pepperoni = new Topping("Pepperoni");
    Topping* mushrooms = new Topping("Mushrooms");
    Topping* cheese = new Topping("Cheese");
    
    group.addComponent(pepperoni);
    group.addComponent(mushrooms);
    group.addComponent(cheese);
    
    cout << "Initial state:" << endl;
    cout << "Components: " << group.getComponentCount() << endl;
    cout << "Price: R" << group.getPrice() << endl;
    
    // Remove existing component
    bool removed = group.removeComponent(mushrooms);
    cout << "Removing mushrooms: " << (removed ? "Success" : "Failed") << endl;
    cout << "Components after removal: " << group.getComponentCount() << endl;
    cout << "Price after removal: R" << group.getPrice() << endl;
    delete mushrooms; // Clean up removed component
    
    // Try to remove non-existent component
    Topping* nonExistent = new Topping("Olives");
    removed = group.removeComponent(nonExistent);
    cout << "Removing non-existent component: " << (removed ? "Success" : "Failed") << endl;
    delete nonExistent;
    
    // Try to remove nullptr
    removed = group.removeComponent(nullptr);
    cout << "Removing nullptr: " << (removed ? "Success" : "Failed") << endl;
    
    cout << endl;
}

void testToppingGroupAddNullComponent() {
    cout << "\n=== Testing ToppingGroup addComponent with nullptr ===" << endl;
    
    ToppingGroup group("Null Test");
    
    cout << "Initial components: " << group.getComponentCount() << endl;
    
    // Try to add nullptr
    group.addComponent(nullptr);
    
    cout << "After adding nullptr: " << group.getComponentCount() << endl;
    cout << "Price: R" << group.getPrice() << endl;
    cout << "Is empty? " << (group.isEmpty() ? "Yes" : "No") << endl;
    
    // Add valid component
    group.addComponent(new Topping("Cheese"));
    cout << "After adding valid component: " << group.getComponentCount() << endl;
    
    cout << endl;
}

void testToppingGroupGetComponents() {
    cout << "\n=== Testing ToppingGroup getComponents ===" << endl;
    
    ToppingGroup group("Components Test");
    group.addComponent(new Topping("Pepperoni"));
    group.addComponent(new Topping("Mushrooms"));
    group.addComponent(new Topping("Cheese"));
    
    // Get components vector
    const std::vector<PizzaComponent*>& components = group.getComponents();
    
    cout << "Components via getComponents():" << endl;
    for (size_t i = 0; i < components.size(); ++i) {
        cout << "Component " << i << ": " << components[i]->getName() 
             << " - R" << components[i]->getPrice() << endl;
    }
    
    cout << "Vector size: " << components.size() << endl;
    cout << "Group component count: " << group.getComponentCount() << endl;
    
    cout << endl;
}

void testNestedToppingGroupCopy() {
    cout << "\n=== Testing Nested ToppingGroup Copy Constructor ===" << endl;
    
    // Create complex nested structure
    ToppingGroup* outerGroup = new ToppingGroup("Outer Group");
    
    ToppingGroup* innerGroup1 = new ToppingGroup("Inner Group 1");
    innerGroup1->addComponent(new Topping("Pepperoni"));
    innerGroup1->addComponent(new Topping("Mushrooms"));
    
    ToppingGroup* innerGroup2 = new ToppingGroup("Inner Group 2");
    innerGroup2->addComponent(new Topping("Cheese"));
    innerGroup2->addComponent(new Topping("Olives"));
    
    outerGroup->addComponent(innerGroup1);
    outerGroup->addComponent(innerGroup2);
    outerGroup->addComponent(new Topping("Extra Topping"));
    
    cout << "Original nested group:" << endl;
    cout << "Name: " << outerGroup->getName() << endl;
    cout << "Components: " << outerGroup->getComponentCount() << endl;
    cout << "Price: R" << outerGroup->getPrice() << endl;
    
    // Test copy constructor with nested structure
    ToppingGroup copiedGroup(*outerGroup);
    
    cout << "Copied nested group:" << endl;
    cout << "Name: " << copiedGroup.getName() << endl;
    cout << "Components: " << copiedGroup.getComponentCount() << endl;
    cout << "Price: R" << copiedGroup.getPrice() << endl;
    
    // Delete original and test if copy is still valid
    delete outerGroup;
    
    cout << "After deleting original:" << endl;
    cout << "Copied group name: " << copiedGroup.getName() << endl;
    cout << "Copied group price: R" << copiedGroup.getPrice() << endl;
    
    cout << endl;
}

void testToppingStaticMethods() {
    cout << "\n=== Testing Topping Static Methods Thoroughly ===" << endl;
    
    // Test isValidTopping with various inputs
    vector<string> testToppings = {
        "Pepperoni", "Mushrooms", "Cheese", "Dough",
        "InvalidTopping", "", "PEPPERONI", "pepperoni",
        "Tomato Sauce", "Green Peppers", "Beef Sausage"
    };
    
    cout << "Testing isValidTopping:" << endl;
    for (const string& topping : testToppings) {
        bool isValid = Topping::isValidTopping(topping);
        cout << "'" << topping << "': " << (isValid ? "Valid" : "Invalid") << endl;
    }
    
    cout << "\nTesting getAllToppings:" << endl;
    auto allToppings = Topping::getAllToppings();
    cout << "Total available toppings: " << allToppings.size() << endl;
    
    // Verify the map is not empty and contains expected toppings
    cout << "Sample toppings from map:" << endl;
    int count = 0;
    for (const auto& pair : allToppings) {
        cout << pair.first << ": R" << pair.second << endl;
        if (++count >= 5) break; // Show first 5 only
    }
    
    cout << endl;
}

void testToppingEdgeCases() {
    cout << "\n=== Testing Topping Edge Cases ===" << endl;
    
    // Test empty string topping
    Topping emptyTopping("");
    cout << "Empty string topping:" << endl;
    cout << "Name: '" << emptyTopping.getName() << "'" << endl;
    cout << "Price: R" << emptyTopping.getPrice() << endl;
    
    // Test whitespace topping
    Topping whitespaceTopping("   ");
    cout << "Whitespace topping:" << endl;
    cout << "Name: '" << whitespaceTopping.getName() << "'" << endl;
    cout << "Price: R" << whitespaceTopping.getPrice() << endl;
    
    // Test very long topping name
    string longName(1000, 'A');
    Topping longTopping(longName);
    cout << "Long name topping (length " << longName.length() << "):" << endl;
    cout << "Name length: " << longTopping.getName().length() << endl;
    cout << "Price: R" << longTopping.getPrice() << endl;
    
    cout << endl;
}

void testEmptyToppingGroupOperations() {
    cout << "\n=== Testing Empty ToppingGroup Operations ===" << endl;
    
    ToppingGroup emptyGroup("Empty Group");
    
    cout << "Empty group operations:" << endl;
    cout << "Name: " << emptyGroup.getName() << endl;
    cout << "Price: R" << emptyGroup.getPrice() << endl;
    cout << "Component count: " << emptyGroup.getComponentCount() << endl;
    cout << "Is empty: " << (emptyGroup.isEmpty() ? "Yes" : "No") << endl;
    
    // Test operations on empty group
    const vector<PizzaComponent*>& components = emptyGroup.getComponents();
    cout << "Components vector size: " << components.size() << endl;
    
    // Try to remove from empty group
    bool removed = emptyGroup.removeComponent(nullptr);
    cout << "Remove from empty group: " << (removed ? "Success" : "Failed") << endl;
    
    // Clear empty group
    emptyGroup.clearComponents();
    cout << "After clearing empty group - still empty: " << (emptyGroup.isEmpty() ? "Yes" : "No") << endl;
    
    cout << endl;
}

void testFactoryMethodsDetailedOutput() {
    cout << "\n=== Testing Factory Methods with Detailed Output ===" << endl;
    
    vector<ToppingGroup*> factoryPizzas = {
        ToppingGroup::createPepperoniPizza(),
        ToppingGroup::createVegetarianPizza(),
        ToppingGroup::createMeatLoversPizza(),
        ToppingGroup::createVegetarianDeluxePizza()
    };
    
    vector<string> pizzaNames = {
        "Pepperoni", "Vegetarian", "Meat Lovers", "Vegetarian Deluxe"
    };
    
    for (size_t i = 0; i < factoryPizzas.size(); ++i) {
        cout << pizzaNames[i] << " Pizza Details:" << endl;
        cout << "  Full Name: " << factoryPizzas[i]->getName() << endl;
        cout << "  Total Price: R" << factoryPizzas[i]->getPrice() << endl;
        cout << "  Component Count: " << factoryPizzas[i]->getComponentCount() << endl;
        cout << "  Is Empty: " << (factoryPizzas[i]->isEmpty() ? "Yes" : "No") << endl;
        
        // Show components breakdown
        const auto& components = factoryPizzas[i]->getComponents();
        cout << "  Components:" << endl;
        for (size_t j = 0; j < components.size(); ++j) {
            cout << "    " << j+1 << ". " << components[j]->getName() 
                 << " (R" << components[j]->getPrice() << ")" << endl;
        }
        cout << endl;
        
        delete factoryPizzas[i];
    }
}

// Main function to run all additional tests
void runAdditionalCoverageTests() {
    cout << "\n" << string(60, '=') << endl;
    cout << "    ADDITIONAL COVERAGE TESTS FOR TOPPING & TOPPINGGROUP" << endl;
    cout << string(60, '=') << endl;
    
    try {
        testToppingAssignmentOperator();
        testToppingGroupAssignmentOperator();
        testToppingGroupSelfAssignment();
        testToppingGroupClearComponents();
        testToppingGroupRemoveComponent();
        testToppingGroupAddNullComponent();
        testToppingGroupGetComponents();
        testNestedToppingGroupCopy();
        testToppingStaticMethods();
        testToppingEdgeCases();
        testEmptyToppingGroupOperations();
        testFactoryMethodsDetailedOutput();
        
        cout << "\n" << string(60, '=') << endl;
        cout << "    ALL ADDITIONAL COVERAGE TESTS COMPLETED SUCCESSFULLY" << endl;
        cout << string(60, '=') << endl;
    } catch (const exception& e) {
        cerr << "Error during additional testing: " << e.what() << endl;
    }
}


// Test function 1: Complete order workflow
void testCompleteOrderWorkflow() {
    std::cout << "\n=== TESTING COMPLETE ORDER WORKFLOW ===" << std::endl;
    
    PizzaOrders order(12345, "John Doe");
    order.setState(new OrderingState()); // Initialize state
    
    std::cout << "\n1. Starting in Ordering State:" << std::endl;
    order.displayStateInfo();
    
    // Add some pizzas
    std::cout << "\n2. Adding pizzas to order:" << std::endl;
    Pizza* pizza1 = order.createPepperoniPizza(true, false);
    Pizza* pizza2 = order.createVegetarianPizza(false, true);
    order.addPizza(pizza1);
    order.addPizza(pizza2);
    order.performAddPizza(); // Test state-aware add
    
    // Try to pay before confirming (should fail)
    std::cout << "\n3. Trying to pay before confirming:" << std::endl;
    order.performPayOrder();
    
    // Confirm order
    std::cout << "\n4. Confirming order:" << std::endl;
    order.performConfirmOrder();
    order.displayStateInfo();
    
    // Try to add pizza after confirming (should fail)
    std::cout << "\n5. Trying to add pizza after confirming:" << std::endl;
    order.performAddPizza();
    
    // Pay for order
    std::cout << "\n6. Paying for order:" << std::endl;
    order.performPayOrder();
    order.displayStateInfo();
    
    // Prepare order
    std::cout << "\n7. Preparing order:" << std::endl;
    order.performPrepareOrder();
    order.displayStateInfo();
    
    // Deliver order
    std::cout << "\n8. Delivering order:" << std::endl;
    order.performDeliverOrder();
    order.displayStateInfo();
    
    // Complete order
    std::cout << "\n9. Completing order:" << std::endl;
    order.performCompleteOrder();
    order.displayStateInfo();
    
    // Try to modify completed order (should fail)
    std::cout << "\n10. Trying to modify completed order:" << std::endl;
    order.performAddPizza();
    order.performCancelOrder();
    
    std::cout << "\n=== COMPLETE WORKFLOW TEST FINISHED ===" << std::endl;
}

// Test function 2: Order cancellation at different stages
void testOrderCancellation() {
    std::cout << "\n=== TESTING ORDER CANCELLATION ===" << std::endl;
    
    // Test 1: Cancel during ordering
    std::cout << "\n1. Cancel during Ordering state:" << std::endl;
    PizzaOrders order1(12346, "Jane Smith");
    order1.setState(new OrderingState());
    Pizza* pizza = order1.createMeatLoversPizza();
    order1.addPizza(pizza);
    order1.displayStateInfo();
    order1.performCancelOrder();
    order1.displayStateInfo();
    
    // Test 2: Cancel after payment
    std::cout << "\n2. Cancel after payment:" << std::endl;
    PizzaOrders order2(12347, "Bob Johnson");
    order2.setState(new OrderingState());
    Pizza* pizza2 = order2.createVegetarianDeluxePizza();
    order2.addPizza(pizza2);
    order2.performConfirmOrder();
    order2.performPayOrder();
    order2.displayStateInfo();
    order2.performCancelOrder();
    order2.displayStateInfo();
    
    // Test 3: Cancel during delivery
    std::cout << "\n3. Cancel during delivery:" << std::endl;
    PizzaOrders order3(12348, "Alice Brown");
    order3.setState(new DeliveringState()); // Simulate order in delivery
    order3.displayStateInfo();
    order3.performCancelOrder();
    order3.displayStateInfo();
    
    std::cout << "\n=== CANCELLATION TEST FINISHED ===" << std::endl;
}

// Test function 3: Invalid operations
void testInvalidOperations() {
    std::cout << "\n=== TESTING INVALID OPERATIONS ===" << std::endl;
    
    PizzaOrders order(12349, "Test Customer");
    
    // Test operations in different states
    std::cout << "\n1. Testing operations in Confirmed state:" << std::endl;
    order.setState(new ConfirmedState());
    order.displayStateInfo();
    order.performAddPizza();        // Should fail
    order.performRemovePizza(0);    // Should fail
    order.performPrepareOrder();    // Should fail
    order.performDeliverOrder();    // Should fail
    
    std::cout << "\n2. Testing operations in Preparing state:" << std::endl;
    order.setState(new PreparingState());
    order.displayStateInfo();
    order.performAddPizza();        // Should fail
    order.performPayOrder();        // Should show already paid
    order.performCompleteOrder();   // Should fail
    
    std::cout << "\n3. Testing operations in Completed state:" << std::endl;
    order.setState(new CompletedState());
    order.displayStateInfo();
    order.performAddPizza();        // Should fail
    order.performConfirmOrder();    // Should show already completed
    order.performCancelOrder();     // Should fail
    
    std::cout << "\n=== INVALID OPERATIONS TEST FINISHED ===" << std::endl;
}

// Test function 4: Order state transitions with order display
void testOrderStateTransitionsWithDisplay() {
    std::cout << "\n=== TESTING STATE TRANSITIONS WITH ORDER DISPLAY ===" << std::endl;
    
    PizzaOrders order(12350, "Demo Customer");
    order.setState(new OrderingState());
    
    // Add pizzas and show order
    std::cout << "\n1. Adding pizzas in Ordering state:" << std::endl;
    Pizza* pizza1 = order.createPepperoniPizza(true, true);
    Pizza* pizza2 = order.createVegetarianPizza(false, false);
    order.addPizza(pizza1);
    order.addPizza(pizza2);
    order.displayOrder();
    order.displayStateInfo();
    
    // Confirm and show state change
    std::cout << "\n2. Confirming order:" << std::endl;
    order.performConfirmOrder();
    order.displayStateInfo();
    
    // Pay and show state change
    std::cout << "\n3. Processing payment:" << std::endl;
    order.performPayOrder();
    order.displayStateInfo();
    order.displayDiscountInfo();
    
    // Prepare
    std::cout << "\n4. Starting preparation:" << std::endl;
    order.performPrepareOrder();
    order.displayStateInfo();
    
    // Deliver
    std::cout << "\n5. Starting delivery:" << std::endl;
    order.performDeliverOrder();
    order.displayStateInfo();
    
    // Complete
    std::cout << "\n6. Completing order:" << std::endl;
    order.performCompleteOrder();
    order.displayStateInfo();
    order.displayOrderSummary();
    
    std::cout << "\n=== STATE TRANSITIONS WITH DISPLAY TEST FINISHED ===" << std::endl;
}

// Test function 5: Edge cases and error handling
void testEdgeCases() {
    std::cout << "\n=== TESTING EDGE CASES ===" << std::endl;
    
    PizzaOrders order(12351, "Edge Case Customer");
    order.setState(new OrderingState());
    
    // Try to confirm empty order
    std::cout << "\n1. Trying to confirm empty order:" << std::endl;
    order.displayStateInfo();
    order.performConfirmOrder(); // Should fail
    order.displayStateInfo();    // Should still be in Ordering
    
    // Add pizza then confirm
    std::cout << "\n2. Adding pizza then confirming:" << std::endl;
    Pizza* pizza = order.createCustomPizza({"Pepperoni", "Mushrooms", "Olives"}, true, false);
    order.addPizza(pizza);
    order.performConfirmOrder(); // Should succeed
    order.displayStateInfo();
    
    // Try multiple payments
    std::cout << "\n3. Trying multiple payments:" << std::endl;
    order.performPayOrder();     // First payment - should work
    order.performPayOrder();     // Second payment - should show already paid
    
    // Try invalid removePizza index
    std::cout << "\n4. Testing invalid remove operations:" << std::endl;
    order.performRemovePizza(99); // Invalid index in wrong state
    
    std::cout << "\n=== EDGE CASES TEST FINISHED ===" << std::endl;
}

// Main test function that calls all the others
void statePattern() {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "           PIZZA ORDER STATE PATTERN TESTING" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    // Run all test functions
    testCompleteOrderWorkflow();
    testOrderCancellation();
    testInvalidOperations();
    testOrderStateTransitionsWithDisplay();
    testEdgeCases();
    
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "           ALL STATE PATTERN TESTS COMPLETED" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
}

void observerPatterns(){
        // === OBSERVER PATTERN TESTS ===
        testBasicObserverPattern();
        testObserverRegistrationAndRemoval();
        testPizzaMenuOperations();
        testSpecialsMenuOperations();
        testMultipleMenusAndObservers();
         testObserverPatternWithPizzaOrders();
}

void pizzaOrderFunctions(){
        // === PIZZAORDERS PATTERN TESTS ===
        testPizzaOrdersBasic();
        testPizzaCreationMethods();
        testCustomPizzaCreation();
        testOrderManagement();
        testCopyConstructorAndAssignment();
        testComplexOrders();
        testOrderDisplayMethods();
}

void decoratorPattern(){
        // === DECORATOR PATTERN TESTS ===
        testBasicDecorators();
        testDecoratorChaining();
        testAllPizzasWithDecorators();
        testDecoratorPricing();
        testDecoratorEdgeCases();
}


void functions(){
cout << "Romeo's Pizza - Complete System Testing" << endl;
    cout << "=======================================" << endl << endl;
    
    try {
        // === COMPOSITE PATTERN TESTS ===
        cout << "COMPOSITE PATTERN TESTS" << endl;
        cout << "======================" << endl;
        displayAllToppings();
        testIndividualToppings();
        testToppingGroups();
        testPredefinedPizzas();
        testComposition();
        testCopyConstructor();
        testGroupModification();
        
        cout << endl << "DECORATOR PATTERN TESTS" << endl;
        cout << "======================" << endl;
        
        decoratorPattern();
        
        cout << endl << "PIZZAORDERS CLASS TESTS" << endl;
        cout << "======================" << endl;
        
        pizzaOrderFunctions();

        
        cout << endl << "OBSERVER PATTERN TESTS" << endl;
        cout << "======================" << endl;

        observerPatterns();

        statePattern();
        

        
        cout << endl << "INTEGRATION TESTS" << endl;
        cout << "=================" << endl;
        
        // === INTEGRATION TESTS ===
        testCompositeDecoratorIntegration();
        testPizzaOrdersIntegration();
        

         runAdditionalCoverageTests();
         runMissingTests();

        
        cout << "=========================================" << endl;
        cout << "All automated tests completed successfully!" << endl;
        cout << "Composite, Decorator, and PizzaOrders patterns working together!" << endl;
        cout << "=========================================" << endl;
        
        
    } catch (const exception& e) {
        cerr << "Error during testing: " << e.what() << endl;
        return ;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void testCopyConstructor2() {
    cout << "\n=== Testing Copy Constructor ===" << endl;
    
    // Test 9: Copy constructor
    cout << "Test 9: BasePizza copy constructor" << endl;
    BasePizza* original = new BasePizza(nullptr);
    BasePizza* copied = new BasePizza(*original);
    cout << "Created original and copied pizza" << endl;
    cout << "Original name: " << original->getName() << endl;
    cout << "Copied name: " << copied->getName() << endl;
    delete original;
    cout << "Deleted original" << endl;
    delete copied;
    cout << "Deleted copied" << endl;
}

void testBasePizzaOnly() {
    cout << "\n=== Testing BasePizza Only ===" << endl;
    
    // Test 2: Create BasePizza with nullptr - should not leak
    cout << "Test 2: BasePizza with nullptr" << endl;
    BasePizza* pizza1 = new BasePizza(nullptr);
    cout << "Created BasePizza with nullptr" << endl;
    cout << "Pizza name: " << pizza1->getName() << endl;
    cout << "Pizza price: " << pizza1->getPrice() << endl;
    delete pizza1;
    cout << "Deleted BasePizza" << endl;
}

void testToppingOnly() {
    cout << "\n=== Testing Topping Only ===" << endl;
    
    // Test 3: Create simple Topping - check if this leaks
    cout << "Test 3: Simple Topping creation" << endl;
    Topping* topping = new Topping("Cheese");
    cout << "Created topping: " << topping->getName() << endl;
    cout << "Topping price: " << topping->getPrice() << endl;
    delete topping;
    cout << "Deleted topping" << endl;
}

void testBasePizzaWithTopping() {
    cout << "\n=== Testing BasePizza with Topping ===" << endl;
    
    // Test 4: BasePizza with a simple Topping
    cout << "Test 4: BasePizza with Topping" << endl;
    Topping* topping = new Topping("Pepperoni");
    BasePizza* pizza = new BasePizza(topping);
    cout << "Created BasePizza with topping" << endl;
    cout << "Pizza name: " << pizza->getName() << endl;
    cout << "Pizza price: " << pizza->getPrice() << endl;
    delete pizza; // This should delete the topping too due to ownsComponent=true
    cout << "Deleted BasePizza (topping should be auto-deleted)" << endl;
}


void testSimpleDecorator() {
    cout << "\n=== Testing Simple Decorator ===" << endl;
    
    // Test 7: Simple decorator pattern
    cout << "Test 7: BasePizza with ExtraCheese decorator" << endl;
    BasePizza* basePizza = new BasePizza(nullptr);
    ExtraCheese* decoratedPizza = new ExtraCheese(basePizza);
    cout << "Created decorated pizza" << endl;
    cout << "Decorated pizza name: " << decoratedPizza->getName() << endl;
    cout << "Decorated pizza price: " << decoratedPizza->getPrice() << endl;
    delete decoratedPizza; // This should delete basePizza if ownsPizza=true
    cout << "Deleted decorated pizza" << endl;
}

void testCloneBasePizza() {
    cout << "\n=== Testing BasePizza Clone ===" << endl;
    
    // Test 8: Test cloning
    cout << "Test 8: BasePizza clone" << endl;
    BasePizza* original = new BasePizza(nullptr);
    Pizza* cloned = original->clone();
    cout << "Created original and cloned pizza" << endl;
    cout << "Original name: " << original->getName() << endl;
    cout << "Cloned name: " << cloned->getName() << endl;
    delete original;
    cout << "Deleted original" << endl;
    delete cloned;
    cout << "Deleted cloned" << endl;
}



void valgrind(){
    //testCopyConstructor2();
    testSimpleDecorator();
    //testBasePizzaWithTopping();
}

// Updated main function
int main() {
    
    functions();
    //statePattern();

    //valgrind();
    
    return 0;
}