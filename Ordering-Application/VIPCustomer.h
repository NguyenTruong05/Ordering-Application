#pragma once
#include "Customer.h"

class VIPCustomer : public Customer {
public:
    VIPCustomer(std::string n = "", std::string p = "", std::string a = "")
        : Customer(n, p, a) {
    }

    double getDiscount() const override {
        return 0.10;
    }

    std::string getType() const override {
        return "VIP Customer";
    }

    friend std::ostream& operator<<(std::ostream& out, const VIPCustomer& c) {
        out << "Loai: " << c.getType() << "\n";
        out << "Ten: " << c.name << "\n";
        out << "So dien thoai: " << c.phone << "\n";
        out << "Dia chi: " << c.address << "\n";
        out << "Giam gia: " << c.getDiscount() * 100 << "%\n";
        return out;
    }
};