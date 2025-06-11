#pragma once
#include "Elkin_LR5_6_defProduct.h"
// ������ ������ ����� �������� �� ����, ������� �������.
// ������� ������� � ���� (�� ��������� ��� � ���������) +
// ����������� ��������� � lAPTOP AND SMARTPHONE +
// �������� ������� ����������� + 
class Product {
private:
    string productID;
    double price;
    int stock;

protected:
    virtual void input(istream& in);
    virtual void output(ostream& out) const;

public:
    Product();
    Product(const string& id);
    Product(const Product& other);
    virtual ~Product();

    void setProductID(const string& id);
    void setPrice(double p);
    void setStock(int s);

    string getProductID() const;
    double getPrice() const;
    int getStock() const;

    virtual void applyDiscount() = 0;
    virtual string getDescription() const = 0;
    virtual bool validate() const;

    Product& operator+=(int qty);
    bool operator==(const Product& other) const;

    friend istream& operator>>(istream& in, Product& obj);
    friend ostream& operator<<(ostream& out, const Product& obj);

    virtual void polymorphicCheck() const = 0;
};