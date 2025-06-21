#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;


const int MAX_PRODUCTS = 100; // Maximum number of products allowed in the inventory

/*----------------------------------------------Product class definition-----------------------------------*/
class Product{
private:
    string id, name;
    int qty, reorderlvl;
    float price;
public:
    void setProduct(string prod_id, string prod_name, float prod_price, int prod_qty, int prod_reorderlvl){
        id = prod_id;  //set product ID
        price = prod_price; //set product price
        qty = prod_qty; //set product quantity
        reorderlvl = prod_reorderlvl; //set product reorder level
        name = prod_name; // set product name
    }
    void displayProduct() const {
        cout << setw(10) << id  // display product ID, set width to 10 for ID
            << setw(30) << name // display product name, set width to 30 for name
            << setw(15) << fixed  << setprecision(2) << price // display product price, set width to 15 for price
            << setw(15) << qty  // display product quantity, set width to 15 for quantity
            << setw(15) << reorderlvl // display product reorder level, set width to 15 for reorder level
            << endl;
    }

    string getId() const { return id; } // Return product ID
    string getName() const { return name; } // Returnproduct name
    float getPrice() const { return price; } // Return product price
    int getQty() const { return qty; } // Return product quantity
    int getReorderLevel() const { return reorderlvl; } // Return product reorder level
};
//--------------------------------------------------------------------------------------------------------//



/*---------------------------------Function to load product data from a file-------------------------------*/ 
int loadData(Product products[]) {
    ifstream file("inventory.txt"); // Open the file for reading
    if (!file) { // Check if the file opened successfully
        cout << "Error: Unable to open file.\n"; // Display error message if file cannot be opened
        return 0;
    }

    string id, name;
    float price;
    int qty, reorder;

    int count = 0; // Initialize count of products loaded
    while ((file >> id >> name >> price >> qty >> reorder) && count < MAX_PRODUCTS) {
        products[count].setProduct(id, name, price, qty, reorder); // Set product details
        count++; // Increment the count of products loaded
    }

    if (count == MAX_PRODUCTS) {// Check if maximum capacity is reached
        // If maximum capacity is reached, display a warning message
        cout << "Warning: Maximum capacity (100) reached. Some data may be ignored.\n";
    }

    file.close();
    return count;
}

void saveData(Product products[],int count){
    ofstream file("inventory.txt");
    for(int i=0;i<count;i++){
        file<<products[i].getId()<<" "
        <<products[i].getName()<<" "
        <<products[i].getPrice()<<" "
        <<products[i].getQty()<<" "
        <<products[i].getReorderLevel()<<endl;
    }
    file.close();
}
void addProduct(Product products[],int& productcount){
string id, name;
    float price;
    int quantity, reorder;
    
    if(productcount>=MAX_PRODUCTS){
        cout<<"Error! Maximum capacity(100)reached!\n";
        return;
    }
    cout<<"Enter product ID: ";
    cin>>id;

    for(int i=0;i<productcount;i++){
        if(products[i].getId()==id){
            cout<<"Error! Product Id already exist!\n";
            return;
        }
    }

    cout<< "Enter product name: ";
    cin.ignore();
    getline(cin, name);
    if (name.empty()) {
        cout << "Product name cannot be empty.\n";
        return;
    }

    cout<<"Enter the prices: ";
    if (!(cin >> price) || price < 0) {
    cout << "Invalid input. Please enter it again.\n";
    cin.clear();
    cin.ignore(1000, '\n');
    return;
    }

    cout<<"Enter the quantity: ";
    if (!(cin >> quantity) || quantity < 0) {
    cout << "Invalid input. Please enter it again.\n";
    cin.clear();
    cin.ignore(1000, '\n');
    return;
    }

    cout<< "Enter the re-order level: ";
    if (!(cin >> reorder) || reorder < 0) {
    cout << "Invalid input. Please enter it again.\n";
    cin.clear();
    cin.ignore(1000, '\n');
    return;
    }

    products[productcount].setProduct(id, name, price, quantity, reorder);
    productcount++;
    saveData(products,productcount);
    cout << "Product added successfully.\n";
}

void updateProduct(Product products[],int productcount) {
    string id;
    cout << "Enter product ID to update: ";
    cin >> id;

     for (int i=0;i<productcount;i++) {
        if (products[i].getId() == id) {
            string name;
            float price;
            int quantity, reorder;

            cout<<"Enter new name: ";
            cin.ignore();
            getline(cin, name);
            if (name.empty()) {
                cout << "Product name cannot be empty.\n";
                return;
            }

            cout<<"Enter the new prices: ";
            if (!(cin >> price) || price < 0) {
              cout << "Invalid input. Please enter it again.\n";
              cin.clear();
              cin.ignore(1000, '\n');
              return;
              }

            cout<<"Enter the new quantity: ";
            cin>>quantity;
            if (!(cin >> quantity) || quantity < 0) {
              cout << "Invalid input. Please enter it again.\n";
              cin.clear();
              cin.ignore(1000, '\n');
              return;
              }

            cout<<"Enter the new reorder level: ";
             if (!(cin >> reorder) || reorder < 0) {
               cout << "Invalid input. Please enter it again.\n";
               cin.clear();
               cin.ignore(1000, '\n');
               return;
               }

            products[i].setProduct(id,name, price, quantity, reorder);
            saveData(products,productcount);
            cout<<"Product updated successfully.\n";
            return;
        }
    }
    cout <<"Product ID not found.\n";
}

void deleteProduct(Product products[],int& productcount) {
    string id;
    cout<<"Enter Product ID to delete: ";
    cin>>id;

    bool answer=false;
    for(int i=0;i<productcount;i++){
        if (products[i].getId()==id){
            for(int j=i;j<productcount-1;j++){
                products[j]=products[j+1];
            }
            productcount--;
            saveData(products,productcount);
            cout<<"Product have been deleted!\n";
            answer=true;
            break;
        }
    }
    if(!answer){
        cout<<"Not found!\n";
    }
}
//--------------------------------------------------------------------------------------------------------//



int main(){
    Product products[MAX_PRODUCTS];
    int productcount = loadData(products);// Load product data from file

    // Display the loaded products
    if (productcount > 0) {
        cout << "Loaded " << productcount << " products:\n";
        cout << setw(10) << "ID" 
            << setw(30) << "Name" 
            << setw(15) << "Price" 
            << setw(15) << "Qty" 
            << setw(15) << "Reorder\n"; 

        for (int i = 0; i < productcount; i++) {
            products[i].displayProduct();
        }
        
    }else{
        cout << "No products loaded.\n";
    }

    int choice;
    do {
        cout << "\n===== Product Management Menu =====\n";
        cout << "1. Add a product\n";
        cout << "2. Delete product(s)\n";
        cout << "3. Update a product\n";
        cout << "4. Display product\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addProduct(products,productcount); 
                    break;
            case 2: deleteProduct(products,productcount); 
                    break;
            case 3: updateProduct(products,productcount); 
                    break;
            case 4:  if (productcount > 0) {
                            cout << "Loaded " << productcount << " products:\n";
                            cout << setw(10) << "ID" 
                                 << setw(30) << "Name" 
                                 << setw(15) << "Price" 
                                 << setw(15) << "Qty" 
                                 << setw(15) << "Reorder\n"; 

                            for (int i = 0; i < productcount; i++) {
                                      products[i].displayProduct();
                                }   
                     }else{
                            cout << "No products loaded.\n";
                     } 
                     break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}


