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
    std::string getName() const { return name; }
    double getPrice() const { return price; }
    int getStock() const { return stock; }
    void setId(std::string i) {
        if (!i.empty())
            id = i;
        else
            std::cout << "ID khong hop le!";
    }
    void setName(std::string n) {
        if (!n.empty())
            name = n;
        else
            std::cout << "Ten khong hop le!";
    }
    void setPrice(double p) {
        if (p >= 0 && p <= 1e9)
            price = p;
        else
            std::cout << "Gia khong hop le!";
    }
  void setStock(int s) {
        if (s >= 0 && s <= 10000)
            stock = s;
        else
            std::cout << "So luong khong hop le!";
    }
    void decreaseStock(int quantity) {
    if (quantity > 0 && quantity <= stock) {
        stock -= quantity;
    } else {
        std::cout << "So luong khong hop le hoac khong du hang!\n";
    }
}
    // VÙNG CODE CỦA TV4: Nạp chồng toán tử <<, >> và ==
    friend std::ostream& operator<<(std::ostream& out, const Product& p) {
        out << std::left << std::setw(10) << p.id << std::setw(20) << p.name << p.price;
        return out;
    }
    bool operator==(const Product& other) const { return this->id == other.id; }
};