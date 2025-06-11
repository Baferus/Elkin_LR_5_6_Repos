#include "Elkin_LR5_6_HelperFunctions.h"
#include "Elkin_LR5_6_HelperFunctions.h"
#include "Elkin_LR5_6_ChildSmartphone.h"
#include "Elkin_LR5_6_ChildLaptop.h"
#include "Elkin_LR5_6_MultiAccessory.h"
#include <iostream>

char getYesNoInput(const std::string& message) {
    char input;
    while (true) {
        std::cout << message;
        std::cin >> input;
        if (input == 'y' || input == 'Y' || input == 'n' || input == 'N')
            return input;

        std::cout << "Invalid input! Please enter y or n." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int getIntInRange(const std::string& message, int minVal, int maxVal) {
    int value;
    while (true) {
        std::cout << message;
        std::cin >> value;
        if (!std::cin.fail() && value >= minVal && value <= maxVal)
            return value;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input! Enter a number between " << minVal << " and " << maxVal << "." << std::endl;
    }
}

int getValidInt(const std::string& message) {
    int value;
    while (true) {
        std::cout << message;
        std::cin >> value;
        if (!std::cin.fail())
            return value;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number." << std::endl;
    }
}

void addSmartphone(std::map<int, std::unique_ptr<Product>>& inventory, int& currentId) {
    auto sm = std::make_unique<Smartphone>();
    std::cin >> *sm;

    try {
        if (!sm->validate()) {
            throw std::runtime_error("Validation failed: Invalid smartphone data");
        }

        inventory[currentId++] = std::move(sm);
        std::cout << "Smartphone added successfully!\n";

        
        inventory[currentId - 1]->polymorphicCheck();
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}


void addLaptop(std::map<int, std::unique_ptr<Product>>& inventory, int& currentId) {
    auto lap = std::make_unique<Laptop>();
    std::cin >> *lap;

    try {
        if (!lap->validate()) {
            throw std::runtime_error("Validation failed: Invalid laptop data");
        }

        inventory[currentId++] = std::move(lap);
        std::cout << "Laptop added successfully!\n";

        
        inventory[currentId - 1]->polymorphicCheck();
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}


void addAccessory(std::map<int, std::unique_ptr<Product>>& inventory, int& currentId) {
    auto acc = std::make_unique<Accessory>();
    std::cin >> *acc;

    try {
        if (!acc->validate()) {
            throw std::runtime_error("Validation failed: Invalid accessory data");
        }

        inventory[currentId++] = std::move(acc);
        std::cout << "Accessory added successfully!\n";

     
        inventory[currentId - 1]->polymorphicCheck();
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void showInventory(const std::map<int, std::unique_ptr<Product>>& inventory) {
    if (inventory.empty()) {
        std::cout << "Inventory is empty." << std::endl;
        return;
    }

    for (const auto& pair : inventory) {
        std::cout << "[" << pair.first << "] " << *pair.second
            << "\nDescription: " << pair.second->getDescription() << "\n\n";
    }
}

void copyItem(std::map<int, std::unique_ptr<Product>>& inventory, int& currentId) {
    int id = getValidInt("Enter ID of item to copy: ");
    auto it = inventory.find(id);
    if (it == inventory.end()) {
        std::cout << "Invalid ID." << std::endl;
        return;
    }

    Product* original = it->second.get();
    if (auto sp = dynamic_cast<Smartphone*>(original)) {
        inventory[currentId++] = std::make_unique<Smartphone>(*sp);
        std::cout << "Smartphone copied." << std::endl;
    }
    else if (auto lp = dynamic_cast<Laptop*>(original)) {
        inventory[currentId++] = std::make_unique<Laptop>(*lp);
        std::cout << "Laptop copied." << std::endl;
    }
    else if (auto ac = dynamic_cast<Accessory*>(original)) {
        inventory[currentId++] = std::make_unique<Accessory>(*ac);
        std::cout << "Accessory copied." << std::endl;
    }
}


void demonstratePolymorphism(const std::map<int, std::unique_ptr<Product>>& inventory) {
    if (inventory.empty()) {
        std::cout << "Inventory is empty. Add some products first." << std::endl;
        return;
    }

    std::cout << "\n=== POLYMORPHISM DEMONSTRATION ===" << std::endl;
    for (const auto& pair : inventory) {
        std::cout << "\n[ID: " << pair.first << "]";
        pair.second->polymorphicCheck();
    }
}