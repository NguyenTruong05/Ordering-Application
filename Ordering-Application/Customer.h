#pragma once
#include "User.h"
#include <iostream>
#include <string>

class Customer : public User {
public:
    Customer(std::string n = "", std::string p = "", std::string a = "")
        : User(n, p, a) {
    }

    double getDiscount() const override {
        return 0.05;
    }

    std::string getType() const override {
        return "Customer";
    }

    friend std::istream& operator>>(std::istream& in, Customer& c) {

        if (&in == &std::cin) std::cout << "Nhap ten khach hang: ";
        std::getline(in >> std::ws, c.name);

        if (&in == &std::cin) std::cout << "Nhap so dien thoai: ";
        std::getline(in, c.phone);

        if (&in == &std::cin) std::cout << "Nhap dia chi: ";
        std::getline(in, c.address);

        return in;
    }

    friend std::ostream& operator<<(std::ostream& out, const Customer& c) {
        out << "Loai: " << c.getType() << "\n";
        out << "Ten: " << c.name << "\n";
        out << "So dien thoai: " << c.phone << "\n";
        out << "Dia chi: " << c.address << "\n";
        out << "Giam gia: " << c.getDiscount() * 100 << "%\n";
        return out;
    }
};