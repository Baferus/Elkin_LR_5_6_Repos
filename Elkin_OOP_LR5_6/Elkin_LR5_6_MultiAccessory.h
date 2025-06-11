#pragma once
#include "Elkin_LR5_6_AbstractProduct.h"
#include "Elkin_LR5_6_ParentWarrantyProvider.h"
#include <string>
#include <iomanip>
using namespace std;

class Accessory : public Product, public WarrantyProvider {
private:
    int warrantyMonths;
    string category;

protected:
    void input(istream& in) override;
    void output(ostream& out) const override;

public:
    Accessory();
    Accessory(const string& id, const string& cat);

    void applyDiscount() override;
    string getDescription() const override;
    bool validate() const override;

    void extendWarranty(int months) override; // реализация из WarrantyProvider
    int getWarrantyMonths() const override;   // реализация из WarrantyProvider

    void polymorphicCheck() const override;
};
