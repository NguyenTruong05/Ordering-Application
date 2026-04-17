#include "OrderingSystem.h"
#include <iostream>

int main() {
    std::cout << "   HE THONG QUAN LY DAT HANG    \n";

    // 1. Khởi tạo đối tượng trung tâm của hệ thống
    OrderingSystem app;

    // 2. Load dữ liệu từ kho (Test tính năng đọc File của Sơn & Quản lý kho của Trường)
    std::cout << "[He thong] Dang khoi tao du lieu...\n";
    app.loadFile("products.txt");

    // 3. Kích hoạt giao diện người dùng (Sẽ gọi Giỏ hàng của Kiệt, Tính tiền của Toàn, In ấn của Phi)
    app.displayMenu();

    std::cout << "\n[He thong] Da dong. Hen gap lai!\n";
    return 0;
}