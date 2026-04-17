#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <limits>

class Product {
private:
    std::string id, name;
    double price;
    int stock;

public:
    // TV1 (KIỆT): Constructor & Đóng gói
    Product(std::string i = "", std::string n = "", double p = 0, int s = 0)
        : id(i), name(n), price(p), stock(s) {
    }

    std::string getId() const { return id; }
    std::string getName() const { return name; }
    double getPrice() const { return price; }
    int getStock() const { return stock; }

    void setId(const std::string& i) { id = i; }
    void setName(const std::string& n) { name = n; }
    void setPrice(double p) { price = p; }
    void setStock(int s) { stock = s; }

    void decreaseStock(int quantity) {
        if (quantity > 0 && quantity <= stock) {
            stock -= quantity;
        }
        else {
            std::cout << "So luong khong hop le hoac khong du hang!\n";
        }
    }

    //TV4 (PHI): Nạp chồng toán tử
    friend std::ostream& operator<<(std::ostream& out, const Product& p) {
        out << std::left
            << std::setw(10) << p.id
            << std::setw(25) << p.name
            << std::setw(10) << p.price
            << std::setw(10) << p.stock;
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Product& p) {
        std::getline(in, p.id, ',');
        std::getline(in, p.name, ',');
        in >> p.price;
        in.ignore(1); // bỏ dấu ,
        in >> p.stock;
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return in;
    }

    bool operator==(const Product& other) const {
        return id == other.id;
    }
};