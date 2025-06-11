#pragma once
#include "Elkin_LR5_6_AbstractProduct.h"
#include <iostream>
#include <limits>
#include <iomanip>
using namespace std;
class Smartphone : public Product {
private:
    string model;
    int storage;
    bool is5G;

protected:
    void input(istream& in) override;
    void output(ostream& out) const override;

public:
    Smartphone();
    Smartphone(const string& id, const string& m);
    void applyDiscount() override;
    string getDescription() const override;
    bool validate() const override;
    void checkCompatibility() const;
    
    void polymorphicCheck() const override;
    Smartphone operator+(const Smartphone& other) const;
};

