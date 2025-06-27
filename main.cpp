#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

/*---------------------------------------------- Constant definitions---------------------------------------------*/
const int MAX_PRODUCTS = 100; // Maximum number of products allowed in the inventory
const int MAX_ACCOUNTS = 10; // Maximum number of accounts allowed in system
const string ADMIN_EMAIL = "admin@gmail.com";
//-----------------------------------------------------------------------------------------------------------------//

/*---------------------------------------------- String variable definition---------------------------------------*/
string loggedInEmail = "";
/*----------------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------- Class definitions------------------------------------------------*/
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
    string getName() const { return name; } // Return product name
    float getPrice() const { return price; } // Return product price
    int getQty() const { return qty; } // Return product quantity
    int getReorderLevel() const { return reorderlvl; } // Return product reorder level
};
class Account{
    private: 
    string email, pass, id; 
    public:
    void setAcc(string mail, string password, string acc_id){
        email = mail; // Set Mail
        pass = password; // Set Pass
        id = acc_id; // Set ID
    }

    void displayAcc()const {
        cout << setw(10) << id      // display account ID
         << setw(30) << email       // display email
         << setw(20) << pass        // display password
         << endl;
    }

//Getters ~each individually allows main access to private
    string getId() const{return id;}
    string getEmail() const{return email;}
    string getPass() const{return pass;}

};
//-----------------------------------------------------------------------------------------------------------------//

/*---------------------------------Function to authenticate users----------------------------------------------*/
bool userAuthentication(const Account accounts[], int accountcount, string& loggedInEmail)
{string email, password;
        cin.ignore();
        cout << "Enter email: ";
        getline(cin, email);
        cout << "Enter password: ";
        getline(cin, password);

        for (int i = 0; i < accountcount; i++) {
            if (accounts[i].getEmail() == email && accounts[i].getPass() == password) {
                loggedInEmail = email; // Store the logged-in user's email
                return true;
            }
        }
        cout << "Could not login. Try again.\n";
        return false;
    }
//-----------------------------------------------------------------------------------------------------------------//

/*---------------------------------Function to load & save product data from a file-------------------------------*/ 
int loadData(Product products[]) {

    ifstream file("inventory.txt"); // Open the file for reading
    if (!file) { // Check if the file opened successfully
        cout << "Error: Unable to open product file.\n"; // Display error message if file cannot be opened
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
        cout << "Warning: Maximum product capacity (100) reached. Some data may be ignored.\n";
    }
    file.close();
    return count;
}

void saveData(Product products[],int count){
    ofstream file("inventory.txt"); //Opens inventory to write
    for(int i=0;i<count;i++){   //Writes into new file
        file<<products[i].getId()<<" "
        <<products[i].getName()<<" "
        <<products[i].getPrice()<<" "
        <<products[i].getQty()<<" "
        <<products[i].getReorderLevel()<<endl;
    }
    file.close(); //Closed file to save memory
}

//-----------------------------------------------------------------------------------------------------------------//

/*---------------------------------Function to load & save account data from a file-------------------------------*/ 

int loadAcc(Account accounts[]){

    ifstream file1("acc_management.txt"); // Open the file for reading
    if (!file1) { // Check if the file opened successfully
        cout << "Error: Unable to open account file.\n"; // Display error message if file cannot be opened
        return 0;}

    string acc_id, email, pass;
    int count = 0; // Initialize count of accounts loaded
    while ((file1 >> acc_id >> email >> pass) && count < MAX_ACCOUNTS) {
        accounts[count].setAcc(acc_id,email,pass); // Set account details
        count++; // Increment the count of accounts loaded
    }

    if (count == MAX_ACCOUNTS) {// Check if maximum capacity is reached
        // If maximum capacity is reached, display a warning message
        cout << "Warning: Maximum account capacity (10) reached. Some data may be ignored.\n";
    }

    file1.close();
    return count;
}
void saveAcc(Account accounts[],int count){
    ofstream file("acc_management.txt"); //Opens acc_management for writting
    for(int i=0;i<count;i++){            //Loops and writes into file
        file<<accounts[i].getId()<<" "
        <<accounts[i].getEmail()<<" "
        <<accounts[i].getPass()<<" "
        <<endl;
    }
    file.close();                         //Closes file to save memory
}
//-----------------------------------------------------------------------------------------------------------------//

/*---------------------------------Function to edit product data from array class---------------------------------*/
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
    cin >>price;
    if (price<0) {
        cout << "Invalid! Please enter it again.\n";
        return;
    }
    cout<<"Enter the quantity: ";
    cin>> quantity;
    if (quantity<0) {
        cout << "Invalid! Please enter it again.\n";
        return;
    }
    cout<< "Enter the re-order level: ";
    cin>>reorder;
    if (reorder<0) {
        cout << "Invalid! Please enter it again.\n";
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
        if (products[i].getId() == id) { //HERE NEED TO FIND EVERY PRODUCT CONTAINING THE INPUT,eg. cin>>13 will show P013, P213, P313 etc.
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
            cin>>price;
            if (price < 0) {
                cout << "Invalid! Please enter it again.\n";
                return;
            }

            cout<<"Enter the new quantity: ";
            cin>>quantity;
            if (quantity < 0) {
                cout << "Invalid! Please enter it again.\n";
                return;
            }

            cout<<"Enter the new reorder level: ";
            cin>>reorder;
            if (reorder < 0) {
                cout << "Invalid! Please enter it again.\n";
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
//-----------------------------------------------------------------------------------------------------------------//
/*-----------------------------------------Function to register new account--------------------------------------------*/
void registerAccount(Account accounts[],int& accountcount){
string id, email,pass, confirmPass;
    if(accountcount>=MAX_ACCOUNTS){
        cout<<"Error! Maximum capacity (10) reached!\n";
        return;
    }
    cout<<"Enter email: ";
    cin.ignore();
    getline(cin, email);
    for(int i = 0; i < accountcount; i++) {
        if(accounts[i].getEmail() == email) {
            cout << "Error! Email already exists!\n";
            return;
        }
    }
    if (email.empty()) {
        cout << "Email cannot be empty.\n";
        return;
    }
    cout<<"Enter the password: ";
    getline(cin, pass);
    if (pass.empty()) {
        cout << "Password cannot be empty.\n";
        return;
    }
    
    do {
        cout << "Confirm the password: ";
        getline(cin, confirmPass);
        if(confirmPass != pass) {
            cout << "Password does not match. Enter again.\n";
        }
    } while(confirmPass != pass);



    id = "A" + to_string(accountcount + 1);//generate id
    accounts[accountcount].setAcc(id, email, pass);
    accountcount++;
    saveAcc(accounts,accountcount);
    cout << "Account registered successfully.\n";
}
/*-----------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------Function to delete account--------------------------------------------*/
void deleteAcc(Account accounts[], int& accountcount,const string& loggedInEmail) {
    string email, pass;
    cout << "Enter email of account to delete: ";
    cin.ignore();
    getline(cin, email);
    
    if(email == ADMIN_EMAIL) {
        cout << "Cannot delete admin account!\n";
        return;
    }
    
    if(email == loggedInEmail) {
        cout << "You are currently logged in with this email. It cannot be deleted!\n";
        return;
    }
    
    cout << "Enter password to verify: ";
    getline(cin, pass);
    
    bool answer = false;
    for(int i = 0; i < accountcount; i++) {
        if(accounts[i].getEmail() == email && accounts[i].getPass() == pass) {
            for(int j = i; j < accountcount - 1; j++) {
                accounts[j] = accounts[j + 1];
            }
            accountcount--;
            saveAcc(accounts, accountcount);
            cout << "Account has been deleted!\n";
            answer = true;
            break;
        }
    }
    
    if(!answer) {
        cout << "Account does not exist or password incorrect!\n";
    }
}

/*-----------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------Function to manage accounts--------------------------------------------*/
void accManagement(Account accounts[], int& accountcount, const string& loggedInEmail) {
    int choice;
    do {
        cout << "\n Account Management:\n";
        cout << "1. Register\n";
        cout << "2. Delete Account\n";
        cout << "3. Back to Main Menu\n";
        cout << " Enter choice: ";
        cin >> choice;
         if (cin.fail()) { // Check for invalid input
            cin.clear(); // Clear the error flag
             cin.ignore(10000, '\n');// Ignore the invalid input
            choice = 0; // Set choice to an invalid value
        }
        switch (choice) {
            case 1:registerAccount(accounts, accountcount);
                   break;
            case 2:deleteAcc(accounts, accountcount, loggedInEmail); // Pass loggedInEmail
                   break;
            case 3:cout<<"Exited from Account Management\n";
                   break; 
            default: cout<<"Invalid choice. Try again.\n";
        }
    } while (choice!=3);
}
/*-----------------------------------------------------------------------------------------------------------------*/

/*---------------------------------Function to check-stock product data from array class---------------------------*/
void checkLowStock(Product products[], int count) {
    bool okStock = true; //Check if any products are low
    int lowDataCount = 0; // Track low products
    for (int i = 0; i < count; i++) {
        if (products[i].getQty() <= products[i].getReorderLevel()) { //Compares reorder level and qty
            cout << endl << "Low stock found at: \n";
            products[i].displayProduct();   //displays
            okStock = false;   
            lowDataCount++;      
        }
    }
    if (okStock) //Notifies how many products require restock
    {
        cout << "All products are not low stocked!\n";
    } else {
        cout << lowDataCount << " products require urgent restock!\n";
    }
    
}
//-----------------------------------------------------------------------------------------------------------------//


/*------------------------------------------Main Function----------------------------------------------------------*/
int main(){
    Product products[MAX_PRODUCTS]; //Set Product class
    Account accounts[MAX_ACCOUNTS]; //Set Account class
    int accountcount = loadAcc(accounts); // Load accounts data from file
    int productcount = loadData(products);// Load product data from file

    string loggedInEmail; // Store who is logged in
    while (!userAuthentication(accounts, accountcount, loggedInEmail)) {
    }
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
        cout << "5. Check Low Stock\n";
        cout << "6. Account Management\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        if (cin.fail()) { // Check for invalid input
            cin.clear(); // Clear the error flag
             cin.ignore(10000, '\n');// Ignore the invalid input
            choice = 0; // Set choice to an invalid value
        }

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
            case 5: checkLowStock(products,productcount);break;
            case 6: accManagement(accounts, accountcount, loggedInEmail); break;
            case 7: cout << "Exiting...\n"; break;
            
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
/*-----------------------------------------------------------------------------------------------------------------*/
