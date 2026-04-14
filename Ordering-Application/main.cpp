#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>

using namespace std;

// ==============================================================================
// 1. TEMPLATE & STL (Khuôn mẫu và Cấu trúc dữ liệu)
// ==============================================================================
template <typename T>
class InventoryManager {
private:
    vector<T> items;
public:
    void add(const T& item) { items.push_back(item); }

    vector<T>& getAll() { return items; }

    T* findById(string id) {
        for (auto& item : items) {
            if (item.getId() == id) return &item;
        }
        return nullptr;
    }

    void displayAll() const {
        for (const auto& item : items) {
            cout << item << endl;
        }
    }
};

// ==============================================================================
// 2. CLASSES, ENCAPSULATION & 3. OPERATOR OVERLOADING
// ==============================================================================
class Product {
private:
    string id;
    string name;
    double price;
    int stock;

public:
    Product(string _id = "", string _name = "", double _price = 0, int _stock = 0)
        : id(_id), name(_name), price(_price), stock(_stock) {
    }

    string getId() const { return id; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getStock() const { return stock; }

    bool decreaseStock(int amount) {
        if (amount > 0 && stock >= amount) {
            stock -= amount;
            return true;
        }
        return false;
    }

    // Nạp chồng toán tử in ra màn hình
    friend ostream& operator<<(ostream& out, const Product& p) {
        out << left << setw(10) << p.id
            << setw(25) << p.name
            << setw(10) << p.price
            << "Kho: " << p.stock;
        return out;
    }

    // Nạp chồng toán tử nhập từ file txt
    friend istream& operator>>(istream& in, Product& p) {
        string line;
        if (getline(in, line)) {
            stringstream ss(line);
            string priceStr, stockStr;
            getline(ss, p.id, ',');
            getline(ss, p.name, ',');
            getline(ss, priceStr, ',');
            getline(ss, stockStr, ',');
            if (!priceStr.empty() && !stockStr.empty()) {
                p.price = stod(priceStr);
                p.stock = stoi(stockStr);
            }
        }
        return in;
    }

    bool operator==(const Product& other) const {
        return this->id == other.id;
    }
};

// ==============================================================================
// 4. INHERITANCE & 5. POLYMORPHISM (Kế thừa và Đa hình)
// ==============================================================================
class User {
protected:
    string name;
    string phone;
public:
    User(string n = "", string p = "") : name(n), phone(p) {}
    virtual ~User() {}

    string getName() const { return name; }
    string getPhone() const { return phone; }

    virtual double getDiscountRate() const = 0;
    virtual string getCustomerType() const = 0;
};

class Customer : public User {
protected:
    string address;
public:
    Customer(string n = "", string p = "", string addr = "") : User(n, p), address(addr) {}
    string getAddress() const { return address; }

    double getDiscountRate() const override { return 0.0; }
    string getCustomerType() const override { return "Khach Hang Thuong (Giam 0%)"; }
};

class VIPCustomer : public Customer {
public:
    VIPCustomer(string n = "", string p = "", string addr = "") : Customer(n, p, addr) {}

    double getDiscountRate() const override { return 0.10; }
    string getCustomerType() const override { return "Khach VIP (Giam 10%)"; }
};

// ==============================================================================
// CẤU TRÚC GIỎ HÀNG
// ==============================================================================
struct CartItem {
    Product product;
    int quantity;
};

class ShoppingCart {
private:
    vector<CartItem> items;
public:
    void addItem(Product& p, int qty) {
        for (auto& item : items) {
            if (item.product == p) {
                item.quantity += qty;
                return;
            }
        }
        items.push_back({ p, qty });
    }

    bool isEmpty() const { return items.empty(); }
    void clearCart() { items.clear(); }

    double getSubtotal() const {
        double total = 0;
        for (const auto& item : items) {
            total += item.product.getPrice() * item.quantity;
        }
        return total;
    }

    void displayCart() const {
        if (isEmpty()) {
            cout << "Gio hang dang trong!" << endl;
            return;
        }
        cout << left << setw(25) << "Ten San Pham" << setw(10) << "So Luong" << "Thanh Tien" << endl;
        cout << string(50, '-') << endl;
        for (const auto& item : items) {
            double cost = item.product.getPrice() * item.quantity;
            cout << left << setw(25) << item.product.getName()
                << setw(10) << item.quantity
                << cost << " VND" << endl;
        }
        cout << string(50, '-') << endl;
        cout << "Tam tinh: " << getSubtotal() << " VND" << endl;
    }
};

// ==============================================================================
// 6. ABSTRACTION (Trừu tượng hóa hệ thống)
// ==============================================================================
class OrderingSystem {
private:
    InventoryManager<Product> inventory;
    ShoppingCart cart;

    string getCurrentDate() {
        time_t now = time(0);
        string dt = ctime(&now);
        dt.pop_back();
        return dt;
    }

    string getDeliveryDate() {
        time_t now = time(0);
        time_t delivery = now + (3 * 24 * 60 * 60); // Giao hàng sau 3 ngày
        string dt = ctime(&delivery);
        dt.pop_back();
        return dt;
    }

public:
    void loadProducts(string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Loi: Khong the mo file " << filename << endl;
            cout << "Vui long tao file products.txt cung thu muc voi file code!" << endl;
            return;
        }
        Product p;
        while (file >> p) {
            inventory.add(p);
        }
        file.close();
        cout << "[He thong] Da tai du lieu san pham thanh cong!" << endl;
    }

    void displayMenu() {
        int choice;
        do {
            cout << "\n===== UNG DUNG DAT HANG =====" << endl;
            cout << "1. Xem danh sach san pham" << endl;
            cout << "2. Them san pham vao gio hang" << endl;
            cout << "3. Xem gio hang" << endl;
            cout << "4. Tien hanh dat hang (Checkout)" << endl;
            cout << "0. Thoat chuong trinh" << endl;
            cout << "Chon chuc nang: ";
            cin >> choice;

            switch (choice) {
            case 1: showProducts(); break;
            case 2: addToCart(); break;
            case 3: cart.displayCart(); break;
            case 4: processCheckout(); break;
            case 0: cout << "Tam biet!" << endl; break;
            default: cout << "Lua chon khong hop le!" << endl;
            }
        } while (choice != 0);
    }

private:
    void showProducts() {
        cout << "\n--- DANH SACH SAN PHAM ---" << endl;
        inventory.displayAll();
    }

    void addToCart() {
        string id;
        int qty;
        cout << "Nhap Ma San Pham (ID): ";
        cin >> id;
        Product* p = inventory.findById(id);

        if (p == nullptr) {
            cout << "Khong tim thay san pham!" << endl;
            return;
        }

        cout << "Nhap so luong: ";
        cin >> qty;

        if (p->decreaseStock(qty)) {
            cart.addItem(*p, qty);
            cout << "Da them " << qty << " " << p->getName() << " vao gio hang!" << endl;
        }
        else {
            cout << "Loi: Kho khong du hang (Chi con " << p->getStock() << " san pham)." << endl;
        }
    }

    void processCheckout() {
        if (cart.isEmpty()) {
            cout << "Gio hang trong. Khong the dat hang!" << endl;
            return;
        }

        cin.ignore();
        string name, phone, address;
        int isVip;

        cout << "\n--- NHAP THONG TIN GIAO HANG ---" << endl;
        cout << "Ten khach hang: "; getline(cin, name);
        cout << "So dien thoai: "; getline(cin, phone);
        cout << "Dia chi: "; getline(cin, address);
        cout << "Ban co phai khach VIP khong? (1. Co / 0. Khong): ";
        cin >> isVip;

        Customer* customer;
        if (isVip == 1) customer = new VIPCustomer(name, phone, address);
        else customer = new Customer(name, phone, address);

        printInvoice(customer);

        delete customer;
        cart.clearCart();
    }

    void printInvoice(Customer* customer) {
        cout << "\n================ HOÁ ĐƠN MUA HÀNG ================" << endl;
        cout << "Ngay dat hang    : " << getCurrentDate() << endl;
        cout << "Khach hang       : " << customer->getName() << " - SĐT: " << customer->getPhone() << endl;
        cout << "Dia chi giao hang: " << customer->getAddress() << endl;
        cout << "Ngay giao du kien: " << getDeliveryDate() << endl;
        cout << "Loai khach       : " << customer->getCustomerType() << endl;
        cout << "--------------------------------------------------" << endl;

        cart.displayCart();

        double subtotal = cart.getSubtotal();
        double discount = subtotal * customer->getDiscountRate();
        double shippingFee = (subtotal > 100000) ? 0 : 15000;
        double total = subtotal - discount + shippingFee;

        cout << "--------------------------------------------------" << endl;
        cout << left << setw(35) << "Phi van chuyen:" << shippingFee << " VND" << endl;
        cout << left << setw(35) << "Giam gia:" << "-" << discount << " VND" << endl;
        cout << left << setw(35) << "TONG THANH TOAN:" << total << " VND" << endl;
        cout << "==================================================" << endl;
        cout << "Cam on quy khach da mua hang!" << endl;
    }
};

// ==============================================================================
// HÀM MAIN
// ==============================================================================
int main() {
    OrderingSystem app;
    app.loadProducts("products.txt");
    app.displayMenu();
    return 0;
}