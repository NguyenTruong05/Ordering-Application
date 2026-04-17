#pragma once
#include <vector>
#include <iostream>
#include <string>

// su dung template de tao ra 1 class quan ly kho 
template <typename T>
class InventoryManager {
private:
	// su dung vector de luu tru danh sach san pham, tu dong co gian kthuoc
    std::vector<T> items;

public:
    // dat truoc vung do lon vector de tranh tran gay doi dia ch bo nho (safe cho findById)
    InventoryManager() {
        items.reserve(200);
    }

    //  add
    void add(const T& item) {
        items.push_back(item);
    }

    // get all
	// tra ve tham chieu de cac calss co the thao tac truc tiep ds sp
    std::vector<T>& getAll() {
        return items;
    }

    // display
    void displayAll() const {
        if (items.empty()) {
            std::cout << "Danh sach hien tai dang trong!\n";
            return;
        }
        for (const auto& item : items) {
            std::cout << item << std::endl;
        }
    }

    // find
	//tra ve con tro den doi tuong tim thay, co the tru sl kho truc tiep
    T* findById(const std::string& id) {
        for (auto& item : items) {
			// yeu cau class T phai co ham getId() tra ve id de so sanh
            if (item.getId() == id) {
				return &item; // tra ve dia chi cua doi tuong tim thay
            }
        }
        return nullptr; 
    }

    // remove
    bool removeById(const std::string& id) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it->getId() == id) {
                items.erase(it);
                std::cout << "[He thong] Da xoa thanh cong ID: " << id << "\n";
                return true;
            }
        }
        std::cout << "[He thong] Khong tim thay ID: " << id << " de xoa!\n";
        return false;
    }

    // clear
    void clear() {
        items.clear();
        std::cout << "[He thong] Kho luu tru da duoc lam sach!\n";
    }
};