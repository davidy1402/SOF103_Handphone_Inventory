#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std;

/*---------------------------------------------- Constant definitions---------------------------------------------*/
const int MAX_PRODUCTS = 100; // Maximum number of products allowed in the inventory
const int MAX_ACCOUNTS = 10; // Maximum number of accounts allowed in system
const string ADMIN_EMAIL = "admin@gmail.com";//setting up the admin email
//-----------------------------------------------------------------------------------------------------------------//

/*---------------------------------------------- String variable definition---------------------------------------*/
string loggedInEmail = "";//declaring variable to identify the current email with which the user is logged in 
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
    void setAcc(string acc_id, string mail, string password){
        email = mail; // Set Mail
        pass = password; // Set Pass
        id = acc_id; // Set ID
    }

   void displayAcc() const {
    cout << setw(10) << id //display ID
         << setw(30) << email //display EMAIL
         << setw(20) << pass //display PASS
         << endl;
}

//Getters ~each individually allows main access to private
    string getId() const{return id;}
    string getEmail() const{return email;}
    string getPass() const{return pass;}

};
//-----------------------------------------------------------------------------------------------------------------//

/*---------------------------------Function to authenticate users----------------------------------------------*/
bool userAuthentication(const Account accounts[], int accountcount, string& loggedInEmail){
    string email, password;
        cout << "Enter email: ";
        cin >> email;
        cout << "Enter password: ";
        cin >> password;// asks the users to key-in their email and password to log in

        for (int i = 0; i < accountcount; i++) {
            if (accounts[i].getEmail() == email && accounts[i].getPass() == password) {
                loggedInEmail = email; // Store the logged-in user's email
                cout << "Login successful.\n";//displayed if user enters the correct email and password
                return true;
            } 
                
        } 
                cout << "Could not login. Try again.\n";//if log in is unsuccessful
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
    if(accountcount>=MAX_ACCOUNTS){//to check whether maximum capacity of account has been reached
        cout<<"Error! Maximum capacity (10) reached!\n";
        return;
    }
    cout<<"Enter email: ";
    cin.ignore();
    getline(cin, email);
    for(int i = 0; i < accountcount; i++) {//to check whether the account to be registered is overlapping with any other registered email 
        if(accounts[i].getEmail() == email) {
            cout << "Error! Email already exists!\n";
            return;
        }
    }
    if (email.empty()) {//if the user does not input any email
        cout << "Email cannot be empty.\n";
        return;
    }
    cout<<"Enter the password: ";//for setting up the password
    getline(cin, pass);
    if (pass.empty()) {
        cout << "Password cannot be empty.\n";
        return;
    }
    
    do {
        cout << "Confirm the password: ";//confirming the password
        getline(cin, confirmPass);
        if(confirmPass != pass) {
            cout << "Password does not match. Enter again.\n";
        }
    } while(confirmPass != pass);//the user can infinitely try setting up password until the password matches with the confirm password



    id = "A" + to_string(accountcount + 1);//generate id
    accounts[accountcount].setAcc(id, email, pass);
    accountcount++;//add the number of accounts in the list
    saveAcc(accounts,accountcount);
    cout << "Account registered successfully.\n";
}
/*-----------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------Function to delete account--------------------------------------------*/
void deleteAcc(Account accounts[], int& accountcount,const string& loggedInEmail) {
    string email, pass;
    cout << "Enter email of account to delete: ";
    cin.ignore();
    getline(cin, email);//getting the account the user wants to delete
    
    if(email == ADMIN_EMAIL) {
        cout << "Cannot delete admin account!\n";
        return;
    }//admin cannot delete his account so the code ensures it is not an admin's account which the user wants to delete
    
    if(email == loggedInEmail) {
        cout << "You are currently logged in with this email. It cannot be deleted!\n";
        return;
    }//user also cannot delete the account if he is logged in with that account
    
    cout << "Enter password to verify: ";//verification with password before deleting account 
    getline(cin, pass);
    
    bool answer = false;
    for(int i = 0; i < accountcount; i++) {
        if(accounts[i].getEmail() == email && accounts[i].getPass() == pass) {//verifying the account
            for(int j = i; j < accountcount - 1; j++) {
                accounts[j] = accounts[j + 1];
            }
            accountcount--;//deleting account from the list
            saveAcc(accounts, accountcount);
            cout << "Account has been deleted!\n";
            answer = true;
            break;
        }
    }
    
    if(!answer) {
        cout << "Account does not exist or password incorrect!\n";//diplayed if the entered email is not found or the password is incorrect
    }
}

/*-----------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------Function to manage accounts--------------------------------------------*/
void accManagement(Account accounts[], int& accountcount, const string& loggedInEmail) {
    int choice;
    do {//displays the menu infinitely until the user chooses 3(Back to main menu)
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
            case 1:registerAccount(accounts, accountcount);//calls function to register new account
                   break;
            case 2:deleteAcc(accounts, accountcount, loggedInEmail); // Pass loggedInEmail
                   break;
            case 3:cout<<"Exited from Account Management\n";
                   break; 
            default: cout<<"Invalid choice. Try again.\n";//if the user enters any number other than 1-3
        }
    } while (choice!=3);//the loop keeps on repeating until 3 is entered
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
// Leo : " First part, need the user to choice first, want to choose ID, name, or Price range "
void searchProducts(Product products[], int productcount) {
    int searchType;
    cout << "How do you want to search by?" << endl;
    cout << "Search by:"<< endl;
    cout << "1. Product ID"<< endl;
    cout << "2. Product Name"<< endl;
    cout << "3. Price Range"<< endl;
    cout << "Please Enter Your choice: "<< endl;
    cin >> searchType;

    Product results[MAX_PRODUCTS]; // all the Store matched results will be stored at this variable.
    int resultCount = 0;           // How many products matched ( amount of the produtcs that matched)


    //first one. 
    // ----------- Search by ID -----------
    if (searchType == 1) {                              //( if user enter 1 )
        string searchId;
        cout << "Please Enter product ID to search: ";  // the user will input the product ID.
        cin >> searchId;

        for (int i = 0; i < productcount; i++) {        // a forloop to check each Id in inventory
            if (products[i].getId().find(searchId) != string::npos) {
                    results[resultCount++] = products[i];
}
        }
    }

    // ----------- Search by Name (case-insensitive) -----------
    else if (searchType == 2) {                                  // if the user input 2
        string searchName;                                       // string variable to use for 
        cout << "Enter part or full product name to search: ";
        cin.ignore();                                            // Clear leftover newline
        getline(cin, searchName);

        // Convert input to lowercase so it will not be case sensitive. 
        transform(searchName.begin(), searchName.end(), searchName.begin(), ::tolower);

        for (int i = 0; i < productcount; i++) {                 // loop through all products. 
            string prodName = products[i].getName();             // get the name of the current product via getter function. 
            string lowerName = prodName;                         // set the lowercase version of prodName, and it will be stored to lowercase.
            transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

            if (lowerName.find(searchName) != string::npos) {    // checks if the lowercase  searchName es=xist anywhere inside the lowercase product name
                results[resultCount++] = products[i];            // find ( ) will return the index if found
            }                                                    //  string :: npos  ( meaning not found )
        }
    }

    // ----------- Search by Price Range -----------
    else if (searchType == 3) {                           // id the user enter 3
        float minPrice, maxPrice;                         // variable to store the maximum price range and minimu price range
        cout << " Please Enter minimum price: ";          // the maximum price user want
        cin >> minPrice;
        cout << " Please Enter maximum price: ";          // the minimum price user want
        cin >> maxPrice;

        for (int i = 0; i < productcount; i++) {          //to loop through products
            float p = products[i].getPrice();             //get the price from using getPrice()
            if (p >= minPrice && p <= maxPrice) {         //if the product's price is in the range of the minPrice and maxPrice 
                results[resultCount++] = products[i];     // the for loop will input the product in array result[] to find the match result                                                      }
            }
        }
    }

    // ----------- Invalid Option -----------
    else {
        cout << "Invalid choice.\n";                 // will print out invalid choice if the requirement do not match 
        return;
    }

    // ----------- Show Results -----------
    if (resultCount == 0) {
        cout << "No matching products found.\n";     
        return;
    }

    // Print table header
    cout << setw(10) << "ID"
         << setw(30) << "Name"
         << setw(15) << "Price"
         << setw(15) << "Qty"
         << setw(15) << "Reorder\n";

    for (int i = 0; i < resultCount; i++) {
        results[i].displayProduct();
    }

    // ----------- Ask to Sort -----------
    char sortChoice;
    cout << "Do you want to sort the results? (y/n): ";
    cin >> sortChoice;

    if (tolower(sortChoice) == 'y') {
        int sortBy, order;
        cout << "Sort by:\n";
        cout << "1. ID\n";
        cout << "2. Name\n";
        cout << "3. Price\n";
        cout << "Enter option: ";
        cin >> sortBy;
        cout << "Enter order (1 for Ascending, 2 for Descending): ";
        cin >> order;

        // Sort using simple nested loops 
        for (int i = 0; i < resultCount - 1; i++) {                
            for (int j = i + 1; j < resultCount; j++) {       // for loop to sort one by one manually
                bool swap = false;
                // Check which attribute to sort by
                if (sortBy == 1) {                            // sort y id
                    swap = (order == 1) ? (results[i].getId() > results[j].getId()) : (results[i].getId() < results[j].getId());             // Ascending: if left > right, swap; Descending: if left < right, swap;
                } else if (sortBy == 2) {                     // sort by name
                    swap = (order == 1) ? (results[i].getName() > results[j].getName()) : (results[i].getName() < results[j].getName());     // Ascending: Alphabetical order; Descending: Z to A;
                } else if (sortBy == 3) {                     // sort by price
                    swap = (order == 1) ? (results[i].getPrice() > results[j].getPrice()) : (results[i].getPrice() < results[j].getPrice()); // Ascending: Lowest price to Highest;  Descending: Highest Price to the Lowest.
                }

                if (swap) {
                    Product temp = results[i]; // Temporarily hold one product
                    results[i] = results[j];   // Assign second product to the first production 
                    results[j] = temp;         // Put the temp product into the second 
                }
            }
        }

        // ----------- Show Sorted Results -----------
        cout << "\nSorted Results:\n";
        cout << setw(10) << "ID"
             << setw(30) << "Name"
             << setw(15) << "Price"
             << setw(15) << "Qty"
             << setw(15) << "Reorder\n";

        for (int i = 0; i < resultCount; i++) {
            results[i].displayProduct();
        }        
        cout << "\nSuccessfully sorted the results.\n";
        cout << "Sorted by: "<< (sortBy == 1 ? "ID" : sortBy == 2 ? "Name" : "Price")
             << ", Order: " << (order == 1 ? "Ascending" : "Descending") << endl;
    }
}



/*------------------------------------------Main Function----------------------------------------------------------*/
int main(){
    Product products[MAX_PRODUCTS]; //Set Product class
    Account accounts[MAX_ACCOUNTS]; //Set Account class
    int accountcount = loadAcc(accounts); // Load accounts data from file
    int productcount = loadData(products);// Load product data from file

    bool allowAccess = false;
    string loggedInEmail; // Store who is logged in
    
    while (!allowAccess){ //Check for userAccess
        allowAccess= userAuthentication(accounts, accountcount, loggedInEmail);}//calls the function to authenticate user

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
        cout << "7. Search\n";

        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;
        
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

            case 7: searchProducts(products,productcount);break;

            case 8: cout << "Exiting...\n"; break;
            
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
/*-----------------------------------------------------------------------------------------------------------------*/
