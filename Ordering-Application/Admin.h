#pragma once
#include "User.h"
#include <string>

class Admin : public User {
public:
    Admin(std::string n = "", std::string p = "", std::string a = "")
        : User(n, p, a) {
    }

    double getDiscount() const override {
        return 0.0;
    }

    std::string getType() const override {
        return "Admin";
    }
};