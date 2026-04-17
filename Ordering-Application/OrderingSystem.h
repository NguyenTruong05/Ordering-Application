#pragma once
#include "InventoryManager.h"
#include "Product.h"
#include "User.h"
#include "ShoppingCart.h"
#include <fstream>
#include <iostream> 

class OrderingSystem {
private:
    InventoryManager<Product> store;
    ShoppingCart cart;

public:
    void loadFile(std::string path) {

    }

    void displayMenu() {
        int choice;
        do {
            std::cout << "\n===== UNG DUNG DAT HANG =====" << std::endl;
            std::cout << "1. Xem danh sach san pham" << std::endl;
            std::cout << "2. Them vao gio hang" << std::endl;
            std::cout << "3. Thanh toan" << std::endl;
            std::cout << "0. Thoat" << std::endl;
            std::cout << "Moi ban chon chuc nang: ";
            std::cin >> choice;

            // Thành viên 2 sẽ dùng switch-case để xử lý choice ở đây
            switch (choice) {
            case 1: std::cout << "Dang hien thi san pham...\n";
                    store.displayAll();
                    break;
            case 2: {
                int id;
                std::cout << "Nhap ID san pham: ";
                std::cin >> id;
                Product p = store.getProductById(id);
                cart.addProduct(p);
                std::cout << "Da them vao gio hang!\n";
                break;
            }
            case 3: std::cout << "Gio hang cua ban:\n";
                    cart.showCart();
                    std::cout << "Dang thanh toan...\n";
                    cart.checkout();
                    break;  
            case 0: std::cout << "Tam biet!\n"; break;
            default: std::cout << "Chua code chuc nang nay!\n";
            }
        } while (choice != 0);
    }

    // 3. In hóa đơn
    void showInvoice(User* u) {
        std::cout << "KH: " << u->getName() << " | Giam gia: " << u->getDiscount() * 100 << "%";
    }
};
