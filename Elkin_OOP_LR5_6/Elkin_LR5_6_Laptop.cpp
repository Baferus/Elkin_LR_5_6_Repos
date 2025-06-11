#include "Elkin_LR5_6_ChildLaptop.h"
#include "Elkin_LR5_6_AbstractProduct.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <stdexcept>
using namespace std;

Laptop::Laptop() : Product(), processor("Intel"), weight(2.5), isGaming(false) {}

Laptop::Laptop(const string& id, const string& cpu)
    : Product(id), processor(cpu), weight(2.5), isGaming(false) {}

void Laptop::applyDiscount() {
    if (isGaming) setPrice(getPrice() * 0.85);
}

string Laptop::getDescription() const {
    return "Laptop with processor " + processor + ", weight: " + to_string(weight) + " kg" +
        (isGaming ? ", gaming model" : ", non-gaming model");
}

void Laptop::upgradeRAM() {
    cout << "Upgrading RAM... Price increased." << endl;
    setPrice(getPrice() + 1000);
}

void Laptop::input(istream& in) {
    Product::input(in);
    in.ignore();

    cout << "Enter processor: ";
    getline(in, processor);

    while (true) {
        cout << "Enter weight (in kg, <= 5.0): ";
        in >> weight;
        if (!in.fail() && weight > 0 && weight <= 5.0) break;
        in.clear();
        in.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid weight! Please enter a value between 0 and 5 kg.\n";
    }

    while (true) {
        cout << "Is this a gaming laptop? (1 = Yes, 0 = No): ";
        in >> isGaming;
        if (!in.fail() && (isGaming == 0 || isGaming == 1)) break;
        in.clear();
        in.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Please enter 1 or 0.\n";
    }
}

void Laptop::output(ostream& out) const {
    Product::output(out);
    out << ", Processor: " << processor
        << ", Weight: " << weight << " kg"
        << ", Gaming: " << (isGaming ? "Yes" : "No");
}

void Laptop::polymorphicCheck() const {
    cout << "\n=== Laptop Polymorphic Check ===" << endl;
    cout << "Description: " << getDescription() << endl;
    cout << "Validation: " << (validate() ? "PASSED" : "FAILED") << endl;
    cout << "Original price: $" << fixed << setprecision(2) << getPrice() << endl;
    Laptop temp = *this;
    temp.applyDiscount();
    cout << "Price after discount: $" << fixed << setprecision(2) << temp.getPrice() << endl;
    cout << "Demonstrating RAM upgrade..." << endl;
    temp.upgradeRAM();
    cout << "Price after RAM upgrade: $" << fixed << setprecision(2) << temp.getPrice() << endl;

    cout << "Current stock: " << getStock() << endl;
    if (getStock() >= 1) {
        temp -= 1;
        cout << "After removing 1 unit (operator-=): " << temp.getStock() << endl;
    }
    else {
        cout << "Not enough stock to demonstrate operator-=" << endl;
    }
    cout << "================================" << endl;
}

bool Laptop::validate() const {
    return Product::validate() &&
        !processor.empty() &&
        (weight > 0 && weight <= 5.0);
}


Laptop& Laptop::operator-=(int qty) {
    if (qty < 0) {
        throw invalid_argument("Cannot reduce stock by negative amount");
    }
    if (getStock() < qty) {
        throw runtime_error("Insufficient stock: trying to reduce " + to_string(qty) +
            " units, but only have " + to_string(getStock()));
    }
    setStock(getStock() - qty);
    return *this;
}