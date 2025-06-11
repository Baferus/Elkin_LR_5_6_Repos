#pragma once
#include "Elkin_LR5_6_AbstractProduct.h"
#include <iomanip>
class Laptop final : public Product {
private:
    string processor;
    double weight;
    bool isGaming;

protected:
    void input(istream& in) override;
    void output(ostream& out) const override;

public:
    Laptop();
    Laptop(const string& id, const string& cpu);
    void applyDiscount() override;
    string getDescription() const override;
    bool validate() const override;
    void upgradeRAM();
    
    void polymorphicCheck() const override;
    Laptop& operator-=(int qty);
};