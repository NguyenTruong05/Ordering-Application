#define _CRT_SECURE_NO_WARNINGS
#include "OrderingSystem.h"

int main() {
    OrderingSystem app;
    app.loadFile("products.txt");
    app.displayMenu(); // Thành viên 2 hoàn thiện hàm này
    return 0;
}
