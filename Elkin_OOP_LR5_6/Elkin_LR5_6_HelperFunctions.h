#pragma once
#include <iostream>
#include <string>
#include <limits>
#include "Elkin_LR5_6_AbstractProduct.h"
#include <map>
#include <memory>
#include <functional>
char getYesNoInput(const std::string& message);
int getIntInRange(const std::string& message, int minVal, int maxVal);
int getValidInt(const std::string& message);
void addSmartphone(std::map<int, std::unique_ptr<Product>>& inventory, int& currentId);
void addLaptop(std::map<int, std::unique_ptr<Product>>& inventory, int& currentId);
void addAccessory(std::map<int, std::unique_ptr<Product>>& inventory, int& currentId);
void showInventory(const std::map<int, std::unique_ptr<Product>>& inventory);
void copyItem(std::map<int, std::unique_ptr<Product>>& inventory, int& currentId);
void demonstratePolymorphism(const std::map<int, std::unique_ptr<Product>>& inventory);