#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

class Product{
private:
    string id, name;
    int qty, reorderlvl;
    float price;
public:
    Product(string prod_id, string prod_name, float prod_price, int prod_qty, int prod_reorderlvl){
        id = prod_id;
        price = prod_price;
        qty = prod_qty;
        reorderlvl = prod_reorderlvl;
        name = prod_name;
    }
    string getId() const { return id; }
    string getName() const { return name; }
    float getPrice() const { return price; }
    int getQty() const { return qty; }
    int getReorderLevel() const { return reorderlvl; }
};

int main(){
Product samsung("s01","glxy dev", 123.4,100,21);
cout << "Product ID: " << samsung.getId() << endl;
cout << "Product Name: " << samsung.getName() << endl;
cout << "Price: $" << samsung.getPrice() << endl;
cout << "Quantity: " << samsung.getQty() << endl;
cout << "Reorder Level: " << samsung.getReorderLevel() << endl; 

    return 0;
}
