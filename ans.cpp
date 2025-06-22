#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

// Constants
const int MAX_PRODUCTS = 30;
const string ADMIN_USERNAME = "admin";
const string ADMIN_PASSWORD = "password123";

// Product class
class Product {
private:
    string id;
    string name;
    double price;
    int quantity;
    int reorderLevel;

public:
    // Constructor
    Product(string id = "", string name = "", double price = 0.0, int quantity = 0, int reorderLevel = 0) 
        : id(id), name(name), price(price), quantity(quantity), reorderLevel(reorderLevel) {}

    // Getter methods
    string getId() const { return id; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    int getReorderLevel() const { return reorderLevel; }

    // Setter methods
    void setId(string newId) { id = newId; }
    void setName(string newName) { name = newName; }
    void setPrice(double newPrice) { price = newPrice; }
    void setQuantity(int newQuantity) { quantity = newQuantity; }
    void setReorderLevel(int newLevel) { reorderLevel = newLevel; }

    // Display product details
    void display() const {
        cout << left << setw(10) << id << setw(20) << name << setw(10) << fixed << setprecision(2) << price 
             << setw(10) << quantity << setw(10) << reorderLevel << endl;
    }
};

// Inventory Management System class
class InventorySystem {
private:
    vector<Product> products;
    bool loadData();
    void saveData();

public:
    InventorySystem() { loadData(); }
    ~InventorySystem() { saveData(); }

    void addProduct();
    void updateProduct();
    void deleteProduct();
    void displayAllProducts();
    void searchProduct();
    void checkLowStock();
    bool authenticateUser();
};

// Load data from file
bool InventorySystem::loadData() {
    ifstream inFile("inventory.txt");
    if (!inFile) return false;
    products.clear();
    string id, name;
    double price;
    int quantity, reorderLevel;
    while (inFile >> id >> name >> price >> quantity >> reorderLevel) {
        products.emplace_back(id, name, price, quantity, reorderLevel);
    }
    inFile.close();
    return true;
}

// Save data to file
void InventorySystem::saveData() {
    ofstream outFile("inventory.txt");
    for (const auto& product : products) {
        outFile << product.getId() << " " << product.getName() << " " << product.getPrice() << " "
                << product.getQuantity() << " " << product.getReorderLevel() << endl;
    }
    outFile.close();
}

// Add a new product with input validation
void InventorySystem::addProduct() {
    if (products.size() >= MAX_PRODUCTS) {
        cout << "Error: Maximum product limit reached!\n";
        return;
    }
    string id, name;
    double price;
    int quantity, reorderLevel;

    cout << "Enter Product ID: ";
    cin >> id;
    for (const auto& p : products) if (p.getId() == id) {
        cout << "Error: ID already exists!\n";
        return;
    }

    cout << "Enter Product Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Price: ";
    cin >> price;
    if (price < 0) {
        cout << "Error: Price cannot be negative!\n";
        return;
    }
    cout << "Enter Quantity: ";
    cin >> quantity;
    if (quantity < 0) {
        cout << "Error: Quantity cannot be negative!\n";
        return;
    }
    cout << "Enter Reorder Level: ";
    cin >> reorderLevel;
    if (reorderLevel < 0) {
        cout << "Error: Reorder level cannot be negative!\n";
        return;
    }

    products.emplace_back(id, name, price, quantity, reorderLevel);
    cout << "Product added successfully!\n";
}

// Update product details
void InventorySystem::updateProduct() {
    string id;
    cout << "Enter Product ID to update: ";
    cin >> id;
    for (auto& p : products) {
        if (p.getId() == id) {
            cout << "Enter new Price: ";
            double price; cin >> price;
            if (price >= 0) p.setPrice(price);
            else cout << "Error: Price cannot be negative!\n";
            cout << "Enter new Quantity: ";
            int qty; cin >> qty;
            if (qty >= 0) p.setQuantity(qty);
            else cout << "Error: Quantity cannot be negative!\n";
            cout << "Product updated!\n";
            return;
        }
    }
    cout << "Product not found!\n";
}

// Delete a product
void InventorySystem::deleteProduct() {
    string id;
    cout << "Enter Product ID to delete: ";
    cin >> id;
    for (auto it = products.begin(); it != products.end(); ++it) {
        if (it->getId() == id) {
            products.erase(it);
            cout << "Product deleted!\n";
            return;
        }
    }
    cout << "Product not found!\n";
}

// Display all products
void InventorySystem::displayAllProducts() {
    if (products.empty()) {
        cout << "No products in inventory!\n";
        return;
    }
    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Price" 
         << setw(10) << "Qty" << setw(10) << "Reorder" << endl;
    for (const auto& p : products) p.display();
    checkLowStock();
}

// Search product by ID or name
void InventorySystem::searchProduct() {
    string searchTerm;
    cout << "Enter Product ID or Name to search: ";
    cin.ignore();
    getline(cin, searchTerm);
    bool found = false;
    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Price" 
         << setw(10) << "Qty" << setw(10) << "Reorder" << endl;
    for (const auto& p : products) {
        if (p.getId() == searchTerm || p.getName() == searchTerm) {
            p.display();
            found = true;
        }
    }
    if (!found) cout << "Product not found!\n";
}

// Check low stock levels
void InventorySystem::checkLowStock() {
    bool alert = false;
    for (const auto& p : products) {
        if (p.getQuantity() < p.getReorderLevel()) {
            if (!alert) cout << "\n** Low Stock Alerts **\n";
            cout << "Product: " << p.getName() << " (Qty: " << p.getQuantity() 
                 << " < Reorder Level: " << p.getReorderLevel() << ")\n";
            alert = true;
        }
    }
    if (alert) cout << "-------------------\n";
}

// User authentication
bool InventorySystem::authenticateUser() {
    string username, password;
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;
    return (username == ADMIN_USERNAME && password == ADMIN_PASSWORD);
}

// Main function with menu
int main() {
    InventorySystem inventory;
    if (!inventory.authenticateUser()) {
        cout << "Authentication failed! Access denied.\n";
        return 1;
    }
 int choice;
    do {
        cout << "\nSTOCK INVENTORY MANAGEMENT SYSTEM\n"
             << "1. List all products\n"
             << "2. View a particular product\n"
             << "3. Add a product\n"
             << "4. Delete product(s)\n"
             << "5. Search product(s)\n"
             << "6. Update a product\n"
             << "7. Save and Exit\n"
             << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: inventory.displayAllProducts(); break;
            case 2: inventory.searchProduct(); break;
            case 3: inventory.addProduct(); break;
            case 4: inventory.deleteProduct(); break;
            case 5: inventory.searchProduct(); break;
            case 6: inventory.updateProduct(); break;
            case 7: cout << "Saving and exiting...\n"; return 0;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (true);

    return 0;
}