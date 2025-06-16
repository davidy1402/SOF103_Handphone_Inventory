#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;
const int MAX_PRODUCTS = 100;

class Product{
private:
    string id, name;
    int qty, reorderlvl;
    float price;
public:
    void setProduct(string prod_id, string prod_name, float prod_price, int prod_qty, int prod_reorderlvl){
        id = prod_id;
        price = prod_price;
        qty = prod_qty;
        reorderlvl = prod_reorderlvl;
        name = prod_name;
    }
    void display() const {
        cout << setw(10) << id << setw(15) << name << setw(10)
             << fixed << setprecision(2) << price << setw(10)
             << qty << setw(10) << reorderlvl << endl;
    }

    string getId() const { return id; }
    string getName() const { return name; }
    float getPrice() const { return price; }
    int getQty() const { return qty; }
    int getReorderLevel() const { return reorderlvl; }
};

int loadData(Product products[]) {
    ifstream file("inventory.txt");
    if (!file) {
        cout << "Error opening file.\n";
        return 0;
    }

    string id, name;
    float price;
    int qty, reorder;
    int count = 0;

    while (file >> id >> name >> price >> qty >> reorder && count < MAX_PRODUCTS) {
        products[count].setProduct(id, name, price, qty, reorder);
        count++;
    }

    file.close();
    return count;
}



int main(){
    Product products[MAX_PRODUCTS];
    int total = loadData(products);

    cout << "Loaded " << total << " products:\n";
    cout << setw(10) << "ID" << setw(15) << "Name" << setw(10)
         << "Price" << setw(10) << "Qty" << setw(10) << "Reorder\n";
    for (int i = 0; i < total; i++) {
        products[i].display();
    }

    return 0;
}
