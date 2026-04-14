#pragma once
#include "Product.h"
#include <vector>

struct CartItem {
    Product product;
    int quantity;
};

class ShoppingCart {
private:
    std::vector<CartItem> items;
public:
    // TV1: Viết logic thêm vào giỏ, tính tổng tiền (Subtotal)
    void addItem(Product p, int q) { items.push_back({ p, q }); }
    double calculateTotal() {
        double total = 0;
        for (auto& i : items) total += i.product.getPrice() * i.quantity;
        return total;
    }
    const std::vector<CartItem>& getItems() const { return items; }
};