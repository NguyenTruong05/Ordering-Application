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
    // ===== THÊM SẢN PHẨM =====
    void addItem(Product p, int q) {
        // Kiểm tra nếu sản phẩm đã tồn tại thì cộng số lượng
        for (auto& item : items) {
            if (item.product == p) {
                item.quantity += q;
                return;
            }
        }
        // Nếu chưa có thì thêm mới
        items.push_back({ p, q });
    }

    // ===== TÍNH TỔNG TIỀN =====
    double calculateTotal() {
        double total = 0;
        for (const auto& i : items) {
            total += i.product.getPrice() * i.quantity;
        }
        return total;
    }

    // ===== LẤY DANH SÁCH =====
    const std::vector<CartItem>& getItems() const {
        return items;
    }
    //======HIỂN THỊ GIỎ HÀNG====
    void displayCart() {
    for (const auto& i : items) {
        std::cout << i.product << " | SL: " << i.quantity << std::endl;
    }
    std::cout << "Total: " << calculateTotal() << std::endl;
}
};