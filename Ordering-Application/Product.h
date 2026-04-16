#pragma once
#include <string>
#include <iostream>
#include <iomanip>

class Product {
private:
    std::string id, name;
    double price;
    int stock;
public:
    // VÙNG CODE CỦA TV1: Constructor, Getters, Setters (Encapsulation)
    Product(std::string i = "", std::string n = "", double p = 0, int s = 0)
        : id(i), name(n), price(p), stock(s) {
    }

    std::string getId() const { return id; }
    double getPrice() const { return price; }
    int getStock() const { return stock; }

    // VÙNG CODE CỦA TV4: Nạp chồng toán tử <<, >> và ==
    friend std::ostream& operator<<(std::ostream& out, const Product& p) {
        out << std::left
            << std::setw(10) << p.id
            << std::setw(25) << p.name
            << std::setw(12) << p.price
            << std::setw(8) << p.stock;
        return out;
    }

    bool operator==(const Product& other) const {
        return id == other.id;
    }
};