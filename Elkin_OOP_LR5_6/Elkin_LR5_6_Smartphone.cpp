#include "Elkin_LR5_6_ChildSmartphone.h"
#include "Elkin_LR5_6_AbstractProduct.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <algorithm>
#include <stdexcept>

using namespace std;

Smartphone::Smartphone() : Product(), model("Model"), storage(64), is5G(false) {}

Smartphone::Smartphone(const string& id, const string& m)
    : Product(id), model(m), storage(64), is5G(false) {}

void Smartphone::applyDiscount() {
    if (!is5G) setPrice(getPrice() * 0.9);
}

string Smartphone::getDescription() const {
    return "Smartphone " + model + " with " + to_string(storage) + "GB, " + (is5G ? "5G-enabled" : "no 5G");
}

bool Smartphone::validate() const {
    return Product::validate() &&
        storage >= 32 &&
        !model.empty();
}

void Smartphone::checkCompatibility() const {
    cout << "5G check: " << (is5G ? "supported" : "not supported") << endl;
}

void Smartphone::input(istream& in) {
    Product::input(in);
    in.ignore();
    cout << "Enter model: ";
    getline(in, model);

    while (true) {
        cout << "Enter storage (GB, >= 32): ";
        in >> storage;
        if (!in.fail() && storage >= 32) break;
        in.clear();
        in.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid storage! Must be >= 32." << endl;
    }

    while (true) {
        cout << "Supports 5G? (1 = Yes, 0 = No): ";
        in >> is5G;
        if (!in.fail() && (is5G == 0 || is5G == 1)) break;
        in.clear();
        in.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Enter 1 or 0." << endl;
    }
}

void Smartphone::output(ostream& out) const {
    Product::output(out);
    out << ", Model: " << model << ", Storage: " << storage << "GB, 5G: " << (is5G ? "Yes" : "No");
}

void Smartphone::polymorphicCheck() const {
    cout << "\n=== Smartphone Polymorphic Check ===" << endl;
    cout << "Description: " << getDescription() << endl;
    cout << "Validation: " << (validate() ? "PASSED" : "FAILED") << endl;
    checkCompatibility();
    cout << "Original price: $" << fixed << setprecision(2) << getPrice() << endl;


    Smartphone tempForDiscount = *this;
    tempForDiscount.applyDiscount();
    cout << "Price after discount: $" << fixed << setprecision(2) << tempForDiscount.getPrice() << endl;


    cout << "Current stock: " << getStock() << endl;

    
    Smartphone batch = *this;
    batch.setStock(5);
    batch.setPrice(getPrice() + 100);
    cout << "Creating batch with 5 units (price: $" << fixed << setprecision(2) << batch.getPrice() << ")..." << endl;

    
    Smartphone combined = *this + batch;
    cout << "After combining batches (operator+): " << combined.getStock() << " units" << endl;
    cout << "Combined average price: $" << fixed << setprecision(2) << combined.getPrice() << endl;
    cout << "===================================" << endl;
}


Smartphone Smartphone::operator+(const Smartphone& other) const {
    
    if (model != other.model || storage != other.storage || is5G != other.is5G) {
        throw invalid_argument("Cannot combine different smartphone models/specifications");
    }

    
    Smartphone result = *this;

    result.setStock(getStock() + other.getStock());


    double avgPrice = (getPrice() * getStock() + other.getPrice() * other.getStock()) /
        (getStock() + other.getStock());
    result.setPrice(avgPrice);

    return result;
}