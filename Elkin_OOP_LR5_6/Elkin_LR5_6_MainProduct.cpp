#include "Elkin_LR5_6_ChildSmartphone.h"
#include "Elkin_LR5_6_ChildLaptop.h"
#include "Elkin_LR5_6_MultiAccessory.h"
#include "Elkin_LR5_6_HelperFunctions.h"

#include <iostream>
#include <map>
#include <memory>
#include <functional>

struct MenuItem {
    std::string title;
    std::function<void()> action;
};

int main() {
    std::map<int, std::unique_ptr<Product>> inventory;
    int currentId = 0;
    int choice = 0;

    std::map<int, MenuItem> menu = {
    {1, {"Add smartphone", [&]() { addSmartphone(inventory, currentId); }}},
    {2, {"Add laptop",     [&]() { addLaptop(inventory, currentId); }}},
    {3, {"Add accessory",  [&]() { addAccessory(inventory, currentId); }}},
    {4, {"Show inventory", [&]() { showInventory(inventory); }}},
    {5, {"Copy item by ID", [&]() { copyItem(inventory, currentId); }}},
    {6, {"Demonstrate polymorphism", [&]() { demonstratePolymorphism(inventory); }}}
    };

    while (true) {
        std::cout << "\n--- MENU ---\n";
        for (const auto& item : menu) {
            std::cout << " Task " << item.first << ". " << item.second.title << std::endl;
        }
        std::cout << " 0. Exit\nChoice: ";

        choice = getValidInt("");

        if (choice == 0) break;

        auto it = menu.find(choice);
        if (it != menu.end()) {
            it->second.action();
        }
        else {
            std::cout << "Unknown menu choice." << std::endl;
        }
    }

    return 0;
}