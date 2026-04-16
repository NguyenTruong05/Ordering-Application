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
   //Thêm vào giỏ
    void addItem(Product p, int q) {
        if (q <= 0) {
            std::cout << "So luong khong hop le!\n";
            return;
        }
        // kiểm tra đã tồn tại chưa
        for (auto& i : items) {
            if (i.product.getId() == p.getId()) {
                i.quantity += q;
                std::cout << "Da cap nhat so luong!\n";
                return;
            }
        }
        // chưa có -> thêm mới
        items.push_back({ p, q });
        std::cout << "Da them vao gio hang!\n";
    }

    // Tính tổng tiền
    double calculateTotal() {
        double total = 0;
        for (auto& i : items) {
            total += i.product.getPrice() * i.quantity;
        }
        return total;
    }

    // Hiển thị giỏ hàng
    void displayCart() {
        std::cout << "\n===== GIO HANG =====\n";
        for (auto& i : items) {
            std::cout << i.product.getName()
                      << " | SL: " << i.quantity
                      << " | Gia: " << i.product.getPrice()
                      << " | Thanh tien: "
                      << i.product.getPrice() * i.quantity
                      << std::endl;
        }
        std::cout << "---------------------\n";
        std::cout << "Tong tien: " << calculateTotal() << std::endl;
    }

    // Xóa 1 sản phẩm
    void removeItem(std::string productId) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it->product.getId() == productId) {
                items.erase(it);
                std::cout << "Da xoa san pham khoi gio hang!\n";
                return;
            }
        }
        std::cout << "Khong tim thay san pham!\n";
    }

    // Xóa toàn bộ giỏ
    void clearCart() {
        items.clear();
        std::cout << "Da xoa toan bo gio hang!\n";
    }

    // đặt hàng
    void checkout() {
        if (items.empty()) {
            std::cout << "Gio hang rong!\n";
            return;
        }
        std::cout << "\n===== HOA DON =====\n";
        displayCart();
        std::cout << "Dat hang thanh cong!\n";
        clearCart();
    }
    const std::vector<CartItem>& getItems() const {
        return items;
    }
};