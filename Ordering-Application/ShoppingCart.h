#pragma once
#include "Product.h"
#include "Customer.h"
#include <vector>
#include <iostream>
#include <ctime>    
#include <iomanip>

struct CartItem {
    Product* product; 
    int quantity;
};

class ShoppingCart {
private:
    std::vector<CartItem> items;
public:
    // TV1: Viết logic thêm vào giỏ, tính tổng tiền (Subtotal)
    //Thêm vào giỏ
    void addItem(Product* p, int q) { 
        if (p == nullptr || q <= 0 || q > p->getStock()) {
            std::cout << "So luong khong hop le hoac kho khong du!\n";
            return;
        }
        // kiểm tra đã tồn tại chưa
        for (auto& i : items) {
            if (i.product->getId() == p->getId()) {
                i.quantity += q;
                p->decreaseStock(q); 
                std::cout << "Da cap nhat so luong!\n";
                return;
            }
        }
        // chưa có -> thêm mới
        p->decreaseStock(q); 
        items.push_back({ p, q });
        std::cout << "Da them vao gio hang!\n";
    }

    // Tính tổng tiền
    double calculateTotal() {
        double total = 0;
        for (auto& i : items) {
            total += i.product->getPrice() * i.quantity; 
        }
        return total;
    }

    // Hiển thị giỏ hàng
    void displayCart() {
        std::cout << "\n===== GIO HANG =====\n";
        for (auto& i : items) {
            std::cout << i.product->getName()
                      << " | SL: " << i.quantity
                      << " | Gia: " << i.product->getPrice()
                      << " | Thanh tien: "
                      << i.product->getPrice() * i.quantity
                      << std::endl;
        }
        std::cout << "---------------------\n";
        std::cout << "Tong tien: " << calculateTotal() << std::endl;
    }

    // Xóa 1 sản phẩm
    void removeItem(std::string productId) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it->product->getId() == productId) {
                // Sửa: Hoàn lại kho trước khi xóa
                it->product->setStock(it->product->getStock() + it->quantity);
                items.erase(it);
                std::cout << "Da xoa san pham khoi gio hang!\n";
                return;
            }
        }
        std::cout << "Khong tim thay san pham!\n";
    }

    // Xóa toàn bộ giỏ (Hủy đơn)
    void clearCart() {
        // Sửa: Hoàn toàn bộ kho trước khi xóa
        for (auto& i : items) {
            i.product->setStock(i.product->getStock() + i.quantity);
        }
        items.clear();
        std::cout << "Da xoa toan bo gio hang!\n";
    }

    // đặt hàng
    void checkout(const Customer& c) {
        if (items.empty()) {
            std::cout << "Gio hang rong!\n";
            return;
        }

        // Xử lý ngày tháng hệ thống
        time_t now = time(0);
        tm t_now;
        localtime_s(&t_now, &now);

        // Cộng thêm 3 ngày = 3 * 24 * 60 * 60 giây
        time_t expected = now + (3 * 24 * 60 * 60); 
        tm t_expected;
        localtime_s(&t_expected, &expected);

        double shippingFee = 30000;
        double subtotal = calculateTotal();
        double discountAmount = subtotal * c.getDiscount();
        double total = subtotal - discountAmount + shippingFee;

        std::cout << "\n========== HOA DON THANH TOAN ==========\n";
        std::cout << "Ngay dat hang: " << t_now.tm_mday << "/" << t_now.tm_mon + 1 << "/" << t_now.tm_year + 1900 << "\n";
        std::cout << "Ngay giao du kien: " << t_expected.tm_mday << "/" << t_expected.tm_mon + 1 << "/" << t_expected.tm_year + 1900 << "\n";
        std::cout << "----------------------------------------\n";
        std::cout << "THONG TIN KHACH HANG:\n" << c;
        std::cout << "----------------------------------------\n";
        
        displayCart();

        std::cout << "Phu phi Shipping: " << shippingFee << "\n";
        std::cout << "Giam gia khach hang (" << c.getDiscount() * 100 << "%): -" << discountAmount << "\n";
        std::cout << "----------------------------------------\n";
        // Ép kiểu long long cho số tiền lớn tránh in exponent (e+)
        std::cout << "TONG CAN THANH TOAN: " << (long long)total << " VND\n";
        std::cout << "========================================\n";
        std::cout << "Dat hang thanh cong!\n";

        items.clear(); 
    }
    const std::vector<CartItem>& getItems() const {
        return items;
    }
};