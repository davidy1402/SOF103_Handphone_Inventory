#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cctype>
using namespace std;

/*------------------------------------------ Constant definitions-------------------------------------------*/
const int MAX_PRODUCTS = 100; // Maximum number of products allowed in the inventory
const int MAX_ACCOUNTS = 10; // Maximum number of accounts allowed in system
const string ADMIN_EMAIL = "admin@gmail.com";//setting up the admin email
//----------------------------------------------------------------------------------------------------------//


/*---------------------------------------- String variable definition------------------------------------*/
string loggedInEmail = "";//declaring variable to identify the current email with which the user is logged in 
//-------------------------------------------------------------------------------------------------------//


/*------------------------------------------ Class definitions----------------------------------------------*/
class Product{
private:
    string id, name;
    int qty, reorderlvl;
    float price;
public:
    // Constructor to initialize product with default values
    Product(string prod_id = "", string prod_name = "", float prod_price = 0.0,
            int prod_qty = 0, int prod_reorderlvl = 0) {
        id = prod_id;
        name = prod_name;
        price = prod_price;
        qty = prod_qty;
        reorderlvl = prod_reorderlvl;
    }

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
    // Constructor to initialize account with default values
    Account(string acc_id = "", string mail = "", string password = "") {
        id = acc_id; // Set account ID
        email = mail; // Set email
        pass = password; // Set password
    }

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
//----------------------------------------------------------------------------------------------------------//

/*------------------------------------Function to authenticate users-------------------------------------*/
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
//-------------------------------------------------------------------------------------------------------//

/*------------------------------Function to load & save account data from a file---------------------------*/ 

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
    file.close(); //Closes file to save memory
}
//----------------------------------------------------------------------------------------------------------//

/*----------------------------Function to load & save product data from a file--------------------------*/ 
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
//-------------------------------------------------------------------------------------------------------//


/*----------------------------Function to edit product data from array class--------------------------------*/
void saveData(Product products[],int count){//This is a function that save the data input from user.
    ofstream file("inventory.txt");//Open the file to save.
    for(int i=0;i<count;i++){//Save all the data that come from users through array. 
        file<<products[i].getId()<<" "//Get products Id.
        <<products[i].getName()<<" "//Get products name.
        <<products[i].getPrice()<<" "//Get product's prices.
        <<products[i].getQty()<<" "//Get product's quantity.
        <<products[i].getReorderLevel()<<endl;//Get product's reorder level.
    }
    file.close();//Close the file
}
//----------------------------------------------------------------------------------------------------------//

/*--------------------------------------------Function for identifying-----------------------------------*/
bool isValidName(const string& name){
     if(name.empty())return false;//Return false if it is empty.
     for (char c : name) {
        if (!isalnum(c) && c != ' ' && c != '_' && c != '+' && c != '-') return false;
    }
     return true;
}

bool isValidEmail(const string& email) {
    // Basic email validation: check for '@' and '.' in the email
    size_t atPos = email.find('@');
    size_t dotPos = email.find('.', atPos);

    return (atPos != string::npos && dotPos != string::npos && dotPos > atPos);
}

string replaceSpacesWithUnderscores(const string& input) {
    string result = input;
    replace(result.begin(), result.end(), ' ', '_');
    return result;
}

bool getValidInput(float& value, const string& prompt) {
    cout << prompt;
    if (!(cin >> value) || value < 0) {
        cout << "Invalid input. Value must be non-negative.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return false;
    }
    return true;
}

bool getValidInput(int& value, const string& prompt) {
    cout << prompt;
    if (!(cin >> value) || value < 0) {
        cout << "Invalid input. Value must be non-negative and integer.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return false;
    }

    return true;
}

string generateNextId(Product products[], int count) {
    if (count == 0) return "P001"; // If no products exist, start with P001
    int maxnum = 0;
    for (int i = 0; i < count; i++) {
        string id = products[i].getId();
        if (!id.empty() && id[0] == 'P') {
            try {
                int num = stoi(id.substr(1));
                maxnum = max(maxnum, num);
            } catch (...) {
                continue; 
            }
        }
    }
    string result = "P";
    int nextnum = maxnum + 1;
    if (nextnum < 10) result += "00";
    else if (nextnum < 100) result += "0";
    result += to_string(nextnum);
    return result;
}

string generateNextAccId(Account accounts[], int count) {   //This function will generate the next account ID based on existing IDs.
    int maxnum = 0;
    for (int i = 0; i < count; i++) {
        string id = accounts[i].getId();
        if (!id.empty() && id[0] == 'A') {
            try {
                int num = stoi(id.substr(1));
                maxnum = max(maxnum, num);
            } catch (...) {
                continue;
            }
        }
    }
    return "A" + to_string(maxnum + 1);
}

int findProductsId(Product products[], int count, const string& searchId, int matches[]) {
    int matchCount=0;
    string findid=searchId;//Define a string type findid which get searchId.
    if (findid[0] != 'P') {//Confirm that the first one is P, or execulte otherwise.
           int len =findid.length();
           if (len == 1)      findid= "P00" +findid;//findid will automatically add two 0 in front of it.
           else if (len == 2) findid= "P0" +findid;//findid will automaticcally add 0 in front of it.
           else               findid= "P" +findid;//Add P in front of it.
}
    for (int i = 0; i < count; i++) {
        string id = products[i].getId();
        bool found = false;
        for (int j=0;j<=id.length()-findid.length();j++) {//Ensure that j won't be higher than search area.
            bool match = true;
            for (int k=0;k<findid.length();k++) {
                if (id[j+k]!=findid[k]) {/*If id isn't same as findid, execute false.
                                           It will write as j+k so that it can find it correctly. */
                    match=false;
                    break;
                }
            }

            if (match) {
                found=true;
                break;
            }
        }
        if (!found) {//Execute if it isn't found.
            for (int j=0;j<=id.length()-searchId.length(); j++) {//Find it in original which is searchId.
                bool match = true;
                for (int k=0;k< searchId.length();k++) {
                    if (id[j+k]!=searchId[k]) {
                        match=false;
                        break;
                    }
                }
                if (match) {
                    found=true;
                    break;
                }
            }
        }
        if (found) {
            matches[matchCount++] = i;//Save it in i if it successfully match id.
        }
    }
    return matchCount;//Return how much is in searchId or findid.
}
//-------------------------------------------------------------------------------------------------------//

/*-----------------------------------------Product Operation------------------------------------------------*/

void addProduct(Product products[],int& productcount){
 if (productcount>=MAX_PRODUCTS) {
        cout << "Error! Maximum capacity (100) reached!\n";
        return;
    }

    string id=generateNextId(products, productcount);
    string name;
    float price;
    int quantity, reorder;

    cout << "Enter product name (only letters, numbers, spaces, +, - are allowed): ";
    cin.ignore();//Empty the buffer area in cin.
    getline(cin, name);
    name = replaceSpacesWithUnderscores(name);
    if (!isValidName(name)) {
        cout <<"Invalid name. Only letters, numbers, spaces, +, - are allowed.\n";
        return;
    }

    if (!getValidInput(price, "Enter the price: ")) return;
    if (!getValidInput(quantity, "Enter the quantity: ")) return;
    if (!getValidInput(reorder, "Enter the re-order level: ")) return;

    cout <<"\nPlease check the following details:\n";
    cout <<setw(10)<<"ID"
         <<setw(30)<<"Name"
         <<setw(15)<<"Price"
         <<setw(15)<<"Quantity"
         <<setw(15)<<"Reorder level\n";
    cout <<setw(10)<<id
         <<setw(30)<<name
         <<setw(15)<<fixed<<setprecision(2)<<price
         <<setw(15)<<quantity
         <<setw(15)<<reorder
         <<endl;

    char confirm;
    cout << "Do you want to save it (y/n)? ";
    cin >> confirm;
    if (confirm=='Y'||confirm=='y') {//Execute if user cin y or Y.
        products[productcount].setProduct(id, name, price, quantity, reorder);
        productcount++;//It successfully add a product.
        saveData(products, productcount);
        cout << "Product added successfully.\n";
    }else{
        cout << "Product addition cancelled.\n";
    }
}

void updateProduct(Product products[],int productcount) {
    string searchId;
    cout<<"Enter product ID (with or without 'P' prefix): ";
    cin>>searchId;

    int matches[MAX_PRODUCTS];
    int matchCount=findProductsId(products, productcount, searchId, matches);

    if (matchCount==0) {
        cout<<"Product ID not found.\n";
        return;
    }

    int selectedIndex;
    if (matchCount > 1) {//List all the products found.
        cout<<"\nMultiple products found:\n";
        cout<<setw(10)<<"ID"
             <<setw(30)<<"Name"
             <<setw(15)<<"Price"
             <<setw(15)<<"Qty"
             <<setw(15)<<"Reorder\n";
        for (int i =0;i<matchCount;i++) {
            cout<<setw(2)<<i + 1<<": ";
            products[matches[i]].displayProduct();
        }
        cout <<"Enter the number (1-"<<matchCount<<") of the product to update: ";
        int choice;
        cin >> choice;

        if (cin.fail()||choice<1||choice>matchCount) {//Detect if user cin text is in invalid, or out of the match area.
            cout<<"Invalid selection.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            return;
        }
        selectedIndex = matches[choice-1];//In array the first one is 0, so it can find the right one if minus 1.
    } else {
        selectedIndex = matches[0];
    }

    string name;
    float price;
    int quantity, reorder;

    cout << "Enter new name (only letters, numbers, and spaces, +, - are allowed): ";
    cin.ignore();
    getline(cin, name);
    name = replaceSpacesWithUnderscores(name);
    if (!isValidName(name)) {
        cout << "Invalid name. Only letters, numbers, and spaces, +, - are allowed.\n";
        return;
    }

    if (!getValidInput(price, "Enter the new price: ")) return;
    if (!getValidInput(quantity, "Enter the new quantity: ")) return;
    if (!getValidInput(reorder, "Enter the new reorder level: ")) return;

    cout << "\nPlease check the updated details:\n";
    cout << setw(10) << "ID" << setw(30) << "Name" << setw(15) << "Price"
         << setw(15) << "Quantity" << setw(15) << "Reorder\n";
    cout << setw(10) << products[selectedIndex].getId()
         << setw(30) << name << setw(15) << fixed << setprecision(2) << price
         << setw(15) << quantity << setw(15) << reorder << endl;

    char confirm;
    cout << "Do you want to save changes (y/n)? ";
    cin >> confirm;

    if (tolower(confirm) == 'y') {
        products[selectedIndex].setProduct(products[selectedIndex].getId(), name, price, quantity, reorder);
        saveData(products, productcount);
        cout << "Product updated successfully.\n";
    } else {
        cout << "Product update cancelled.\n";
    }
}

void deleteProduct(Product products[],int& productcount) {
   string searchId;
    cout<<"Enter product ID (with or without 'P' prefix): ";
    cin>>searchId;

    int matches[MAX_PRODUCTS];
    int matchCount = findProductsId(products, productcount, searchId, matches);

    if(matchCount==0){
        cout<<"Product ID not found.\n";
        return;
    }

    int selectedIndex;
    if(matchCount>1){
        cout<<"\nMultiple products found:\n";
        cout<<setw(10)<<"ID"
             <<setw(30)<<"Name"
             <<setw(15)<<"Price"
             <<setw(15)<<"Qty"
             <<setw(15)<<"Reorder\n";
        for(int i=0;i<matchCount;i++) {
            cout<<setw(2)<<i + 1<<": ";
            products[matches[i]].displayProduct();
        }
        cout<<"Enter the number (1-"<<matchCount<<") of the product to delete: ";
        int choice;
        cin >> choice;
        if (cin.fail()||choice<1||choice>matchCount) {
            cout<<"Invalid selection.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            return;
        }

        selectedIndex = matches[choice - 1];
        cout << "\nYou have selected:\n";
        cout << setw(10) << "ID" << setw(30) << "Name" << setw(15) << "Price"
             << setw(15) << "Qty" << setw(15) << "Reorder\n";
        products[selectedIndex].displayProduct();
    } else {
        selectedIndex = matches[0];
        cout << "\nYou have selected:\n";
        cout << setw(10) << "ID" << setw(30) << "Name" << setw(15) << "Price"
             << setw(15) << "Qty" << setw(15) << "Reorder\n";
        products[selectedIndex].displayProduct();
    }

    char confirm;
    cout << "Are you sure you want to delete this product? (y/n): ";
    cin >> confirm;
    if (tolower(confirm) != 'y') {
        cout << "Product deletion cancelled.\n";
        return;
    }

    for(int j=selectedIndex;j<productcount-1;j++) {//Start from selectedIndex, and use productcount-1 to make sure it will not over the area.
        products[j]=products[j+1];//Take content in product[j] which come from [j+1] to overwrite it.
    }
    productcount--;//Delete a product successfully.
    saveData(products, productcount);
    cout<<"Product deleted successfully.\n";
}

//------------------------------------------------------------------------------------------------------------//

/*---------------------------------Function to register new account-------------------------------------*/
void registerAccount(Account accounts[],int& accountcount){
string id, email,pass, confirmPass;
    if(accountcount>=MAX_ACCOUNTS){//to check whether maximum capacity of account has been reached
        cout<<"Error! Maximum capacity (10) reached!\n";
        return;
    }
    cout<<"Enter email: ";
    cin.ignore();
    getline(cin, email);

    if (!isValidEmail(email)) {
    cout << "Invalid email format. Please enter a valid email address (must contain '@' and '.').\n";
    return;
    }
    
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



    id = generateNextAccId(accounts, accountcount); //generate the next account ID based on existing accounts

    accounts[accountcount].setAcc(id, email, pass);
    accountcount++;//add the number of accounts in the list
    saveAcc(accounts,accountcount);
    cout << "Account registered successfully.\n";
}
//-------------------------------------------------------------------------------------------------------//

/*-------------------------------------Function to delete account-------------------------------------------*/
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

//----------------------------------------------------------------------------------------------------------//

/*-------------------------------------Function to manage accounts---------------------------------------*/
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
//-------------------------------------------------------------------------------------------------------//

/*-----------------------------Function to check-stock product data from array class------------------------*/
void checkLowStock(Product products[], int count) {
    int lowDataCount = 0; // Track low products
    Product lowStockProducts[MAX_PRODUCTS];

    for (int i = 0; i < count; i++) {
        if (products[i].getQty() <= products[i].getReorderLevel()) { //Compares reorder level and qty
            lowStockProducts[lowDataCount++] = products[i]; //Store low stock products     
        }
    }
    if (lowDataCount == 0) //Notifies how many products require restock
    {
        cout << "All products are sufficiently stocked!\n";
    } else {
        cout << endl << "\nLow stock found at: \n";
        cout << setw(10) << "ID"
             << setw(30) << "Name"
             << setw(15) << "Price"
             << setw(15) << "Qty"
             << setw(15) << "Reorder\n";
        for (int i = 0; i < lowDataCount; i++) {//Displays low stock
            lowStockProducts[i].displayProduct();
        }        cout << endl;
        cout << "Total " << lowDataCount << " product(s) require urgent restock!\n";
    }
    
}
//----------------------------------------------------------------------------------------------------------//

/*--------Leo : " First part, need the user to choice first, want to choose ID, name, or Price range-----*/
void searchProducts(Product products[], int productcount) {
    int searchType;
    cout << "How do you want to search by?" << endl;
    cout << "Search by:"<< endl;
    cout << "1. Product ID"<< endl;
    cout << "2. Product Name"<< endl;
    cout << "3. Price Range"<< endl;
    cout << "Please Enter Your choice: ";    
    if (!getValidInput(searchType, "") || searchType < 1 || searchType > 3) {
        cout << "Invalid choice.\n";
        return;
    }

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
        searchName = replaceSpacesWithUnderscores(searchName);

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

        if (cin.fail() || minPrice < 0 || maxPrice < 0 || minPrice > maxPrice) { // check if the user input is valid
            cout << "Invalid input. Please enter valid price range.\n"; // if the user input is invalid, it will print out this message
            cin.clear(); // clear the cin buffer
            cin.ignore(1000, '\n'); // ignore the next 1000 characters until it meets a newline character
            return; // exit the function
        }

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

    cout << "\nSearch Results:\n";
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
        if (!getValidInput(sortBy, "") || sortBy < 1 || sortBy > 3) {
            cout << "Invalid sort option.\n";
            return;
        }

        cout << "Enter order (1 for Ascending, 2 for Descending): ";
        if (!getValidInput(order, "") || order < 1 || order > 2) {
            cout << "Invalid order.\n";
            return;
        }

        // ----------- Sort Results -----------
        // Using a lambda function to sort the results based on the selected criteria and order.
        sort(results, results + resultCount, [sortBy, order](const Product& a, const Product& b) {
            if (sortBy == 1) return order == 1 ? a.getId() < b.getId() : a.getId() > b.getId();
            if (sortBy == 2) return order == 1 ? a.getName() < b.getName() : a.getName() > b.getName();
            return order == 1 ? a.getPrice() < b.getPrice() : a.getPrice() > b.getPrice();
        });

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
//------------------------------------------------------------------------------------------------------//


/*------------------------------------------Main Function---------------------------------------------------*/
int main(){
    Product products[MAX_PRODUCTS]; //Set Product class
    Account accounts[MAX_ACCOUNTS]; //Set Account class
    int accountcount = loadAcc(accounts); // Load accounts data from file
    int productcount = loadData(products);// Load product data from file

    bool allowAccess = false;
    string loggedInEmail; // Store who is logged in
    
    while (!allowAccess){ //Check for userAccess
        allowAccess= userAuthentication(accounts, accountcount, loggedInEmail);}//calls the function to authenticate user

    int choice;
    do {
        cout << "\n===== Handphone Inventory Management Menu =====\n";
        cout << "1. Display All Products\n";
        cout << "2. Search Product(s)\n";
        cout << "3. Add a Product\n";
        cout << "4. Update a Product\n";
        cout << "5. Delete Product(s)\n"; 
        cout << "6. Check Low Stock\n";
        cout << "7. Account Management\n";
        cout << "8. Exit\n";
        cout << "Enter your choice (1-8): ";
        cin >> choice;
        cout << endl;
        
        if (cin.fail()) { // Check for invalid input
            cin.clear(); // Clear the error flag
             cin.ignore(10000, '\n');// Ignore the invalid input
            choice = 0; // Set choice to an invalid value
        }

        switch (choice) {
            case 1: // Display all products
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
                break; 

            case 2: searchProducts(products,productcount);break;

            case 3: addProduct(products,productcount); break;

            case 4: updateProduct(products,productcount); break;

            case 5: deleteProduct(products,productcount); break;
            
            case 6: checkLowStock(products,productcount);break;

            case 7: accManagement(accounts, accountcount, loggedInEmail); break;

            case 8: cout << "Exiting...\n"; break;
            
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 8);

    return 0;
}
//----------------------------------------------------------------------------------------------------------//
