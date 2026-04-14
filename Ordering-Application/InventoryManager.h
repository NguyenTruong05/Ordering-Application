#pragma once
#include <vector>
#include <iostream>

template <typename T>
class InventoryManager {
private:
    std::vector<T> items;
public:
    // VÙNG CODE CỦA TV5: Viết các hàm add, getAll, findById bằng Template
    void add(const T& item) { items.push_back(item); }
    std::vector<T>& getAll() { return items; }

    T* findById(std::string id) {
        for (auto& item : items) {
            if (item.getId() == id) return &item;
        }
        return nullptr;
    }
};