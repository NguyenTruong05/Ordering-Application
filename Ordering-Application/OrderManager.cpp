#include "OrderManager.h"

int main() {
    OrderManager order;

    order.loadProducts();
    order.checkout();

    return 0;
}