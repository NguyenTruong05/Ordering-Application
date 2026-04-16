#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Product {
private:
    string name;
    double price;

public:
    Product(string n = "", double p = 0) {
        name = n;
        price = p;
    }

    double getPrice() const {
        return price;
    }
};

class OrderManager {
private:
    vector<Product> products;

    void readFile() {
        ifstream file("products.txt");

        if (!file) {
            cout << "Cannot open file!\n";
            return;
        }

        string name;
        double price;

        while (file >> name >> price) {
            products.push_back(Product(name, price));
        }

        file.close();
    }

 
    double calculateTotal() {
        double total = 0;
        for (int i = 0; i < products.size(); i++) {
            total += products[i].getPrice();
        }

        double tax = total * 0.1;
        double shipping = 5;

        return total + tax + shipping;
    }

public:
  
    void loadProducts() {
        products.clear();
        readFile();
        cout << "Loaded products!\n";
    }

    void checkout() {
        if (products.empty()) {
            cout << "No products!\n";
            return;
        }

        cout << "Total: " << calculateTotal() << endl;
    }
};
