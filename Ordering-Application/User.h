#pragma once
#include <string>

class User {
protected:
    std::string name, phone, address;
public:
    User(std::string n, std::string p, std::string a) : name(n), phone(p), address(a) {}
    virtual ~User() {}

    // VÙNG CODE CỦA TV3: Hàm ảo để tính giảm giá (Polymorphism)
    virtual double getDiscount() const = 0;
    virtual std::string getType() const = 0;

    std::string getName() const { return name; }
    std::string getAddr() const { return address; }
};

class VIPCustomer : public User {
public:
    VIPCustomer(std::string n, std::string p, std::string a) : User(n, p, a) {}
    double getDiscount() const override { return 0.1; } // Giảm 10%
    std::string getType() const override { return "VIP"; }
};