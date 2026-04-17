#pragma once
#include "InventoryManager.h"
#include "Product.h"
#include "User.h"
#include "ShoppingCart.h"
#include <fstream>
#include <iostream> 
#include "Customer.h"
#include "VIPCustomer.h"
#include "Admin.h"
#include <sstream> 
#include <string>   

class OrderingSystem {
private:
    InventoryManager<Product> store;
    ShoppingCart cart;

public:
    void loadFile(std::string path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cout << "[Loi] Khong mo duoc file!\n";
            return;
        }
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            Product p;

            if (ss >> p) {
                store.add(p);
            }
        }
        file.close();
        std::cout << "[He thong] Da tai du lieu thanh cong!\n";
    }

    void displayMenu() {
        int choice;
        do {
            std::cout << "\n===== UNG DUNG DAT HANG =====" << std::endl;
            std::cout << "1. Xem danh sach san pham" << std::endl;
            std::cout << "2. Them vao gio hang" << std::endl;
            std::cout << "3. Xem gio hang" << std::endl;
            std::cout << "4. Thanh toan (Dat hang)" << std::endl;
            std::cout << "0. Thoat" << std::endl;
            std::cout << "Moi ban chon chuc nang: ";
            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                choice = -1; 
            }

            // Thành viên 2 sẽ dùng switch-case để xử lý choice ở đây
            switch (choice) {
            case 1: 
                std::cout << "\n--- DANH SACH SAN PHAM ---\n";
                store.displayAll(); 
                break;
            case 2: {
                std::string id;
                int q;
                std::cout << "Nhap ID san pham: ";
                std::cin >> id;
                std::cout << "Nhap so luong: ";
                if (!(std::cin >> q)) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "So luong phai la so!\n";
                    break;
                }
                Product* p = store.findById(id);
                if (p != nullptr) {
                    cart.addItem(p, q);
                } else {
                    std::cout << "Khong tim thay san pham mang ID nay!\n";
                }
                break;
            }
            case 3:
                cart.displayCart();
                break;
            case 4: {
                if (cart.getItems().empty()) {
                    std::cout << "Gio hang hien dang rong, hay them san pham truoc!\n";
                    break;
                }
                Customer c;
                std::cout << "\n--- YEU CAU NHAP THONG TIN GIAO HANG ---\n";
                std::cin >> c; 
                cart.checkout(c);
                break;
            }
            case 0: 
                std::cout << "Tam biet!\n"; 
                break;
            default: 
                if (choice != -1) std::cout << "Lua chon khong hop le!\n";
            }
        } while (choice != 0);
    }

    // 3. In hóa đơn
    void showInvoice(User* u) {
        std::cout << "KH: " << u->getName() << " | Giam gia: " << u->getDiscount() * 100 << "%";
    }
};