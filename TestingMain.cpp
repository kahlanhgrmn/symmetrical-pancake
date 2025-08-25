#include "PizzaComponent.h"
#include "Topping.h"
#include "ToppingGroup.h"
#include "Pizza.h"
#include "BasePizza.h"
#include "PizzaDecorator.h"
#include "ExtraCheese.h"
#include "StuffedCrust.h"
#include "PizzaOrders.h"
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
        
        // === DECORATOR PATTERN TESTS ===
        testBasicDecorators();
        testDecoratorChaining();
        testAllPizzasWithDecorators();
        testDecoratorPricing();
        testDecoratorEdgeCases();
        
        cout << endl << "PIZZAORDERS CLASS TESTS" << endl;
        cout << "======================" << endl;
        
        // === PIZZAORDERS PATTERN TESTS ===
        testPizzaOrdersBasic();
        testPizzaCreationMethods();
        testCustomPizzaCreation();
        testOrderManagement();
        testCopyConstructorAndAssignment();
        testComplexOrders();
        testOrderDisplayMethods();
        
        cout << endl << "INTEGRATION TESTS" << endl;
        cout << "=================" << endl;
        
        // === INTEGRATION TESTS ===
        testCompositeDecoratorIntegration();
        testPizzaOrdersIntegration();
        
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

    //valgrind();
    
    return 0;
}