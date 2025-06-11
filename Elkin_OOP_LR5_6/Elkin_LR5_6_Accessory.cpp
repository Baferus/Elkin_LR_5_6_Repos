#include "Elkin_LR5_6_MultiAccessory.h"
#include "Elkin_LR5_6_AbstractProduct.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <algorithm>
#include <vector>
#include <memory>
#include <stdexcept>

using namespace std;

Accessory::Accessory() : Product(), warrantyMonths(12), category("case") {}

Accessory::Accessory(const string& id, const string& cat) : Product(id), warrantyMonths(12), category(cat) {}

void Accessory::applyDiscount() {
    if (warrantyMonths >= 12) {
        
        double discountRate = 0.95;
        if (warrantyMonths >= 18) {
            discountRate = 0.92;
        }
        if (warrantyMonths >= 24) {
            discountRate = 0.90;
        }
        setPrice(getPrice() * discountRate);
    }
}

string Accessory::getDescription() const {
    return "Accessory (" + category + "), warranty: " + to_string(warrantyMonths) + " months.";
}

void Accessory::extendWarranty(int months) {
    warrantyMonths += months;
    cout << "Warranty extended by " << months << " months." << endl;

    double warrantyPrice = months * 50.0;
    setPrice(getPrice() + warrantyPrice);
    cout << "Price increased by $" << fixed << setprecision(2) << warrantyPrice << " for extended warranty." << endl;
}

void Accessory::input(istream& in) {
    Product::input(in);
    in.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter accessory category: ";
    getline(in, category);

    cout << "Enter warranty period (in months, default is 12): ";
    in >> warrantyMonths;

    if (in.fail() || warrantyMonths < 0) {
        in.clear();
        in.ignore(numeric_limits<streamsize>::max(), '\n');
        warrantyMonths = 12;
        cout << "Invalid input. Default warranty set to: 12 months." << endl;
    }
}

void Accessory::output(ostream& out) const {
    Product::output(out);
    out << ", Category: " << category << ", Warranty: " << warrantyMonths << " months.";
}

int Accessory::getWarrantyMonths() const {
    return warrantyMonths;
}

void Accessory::polymorphicCheck() const {
    cout << "\n=== Accessory Polymorphic Check ===" << endl;
    cout << "Description: " << getDescription() << endl;
    cout << "Validation: " << (validate() ? "PASSED" : "FAILED") << endl;
    cout << "Current warranty: " << getWarrantyMonths() << " months" << endl;
    cout << "Original price: $" << fixed << setprecision(2) << getPrice() << endl;


    Accessory temp = *this;


    temp.applyDiscount();
    cout << "Price after base discount: $" << fixed << setprecision(2) << temp.getPrice() << endl;


    cout << "Extending warranty by 6 months..." << endl;
    temp.extendWarranty(6);
    cout << "New warranty period: " << temp.getWarrantyMonths() << " months" << endl;
    cout << "Price after warranty extension: $" << fixed << setprecision(2) << temp.getPrice() << endl;


    temp.applyDiscount();
    cout << "Final price after extended warranty discount: $" << fixed << setprecision(2) << temp.getPrice() << endl;
    cout << "===================================" << endl;
}

bool Accessory::validate() const {
    return Product::validate() &&
        !category.empty() &&
        (warrantyMonths >= 0 && warrantyMonths <= 36);
}