#include "Elkin_LR5_6_AbstractProduct.h"
#include "Elkin_LR5_6_ChildSmartphone.h"
#include "Elkin_LR5_6_ChildLaptop.h"
#include "Elkin_LR5_6_MultiAccessory.h"

#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <algorithm>
#include <vector>
#include <memory>

using namespace std;



Product::Product() : productID("UNKNOWN"), price(0.0), stock(0) {}
Product::Product(const string& id) : productID(id), price(0.0), stock(0) {}
Product::Product(const Product& other) : productID(other.productID), price(other.price), stock(other.stock) {}
Product::~Product() {}

void Product::setProductID(const string& id) { productID = id; }
void Product::setPrice(double p) { price = p; }
void Product::setStock(int s) { stock = s; }

string Product::getProductID() const { return productID; }
double Product::getPrice() const { return price; }
int Product::getStock() const { return stock; }

bool Product::validate() const {
    return price > 0 && stock >= 0;
}

Product& Product::operator+=(int qty) {
    stock += qty;
    return *this;
}

bool Product::operator==(const Product& other) const {
    return productID == other.productID;
}

void Product::input(istream& in) {
    while (true) {
        cout << "Enter product ID (numeric > 0): ";
        in >> productID;
        if (!in.fail() && all_of(productID.begin(), productID.end(), ::isdigit) && stoi(productID) > 0) break;
        in.clear();
        in.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid ID! Must be a positive number." << endl;
    }

    while (true) {
        cout << "Enter price (> 0): ";
        in >> price;
        if (!in.fail() && price > 0) break;
        in.clear();
        in.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid price! Must be a positive number." << endl;
    }

    while (true) {
        cout << "Enter stock quantity (>= 0): ";
        in >> stock;
        if (!in.fail() && stock >= 0) break;
        in.clear();
        in.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid stock! Must be zero or positive." << endl;
    }
}

void Product::output(ostream& out) const {
    out << "ID: " << productID
        << ", Price: " << fixed << setprecision(2) << price
        << ", Stock: " << stock;
}

istream& operator>>(istream& in, Product& obj) {
    obj.input(in);
    return in;
}

ostream& operator<<(ostream& out, const Product& obj) {
    obj.output(out);
    return out;
}
