#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cctype>
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

/*------------------------------------------------Function for identifying----------------------------------*/
bool isValidName(const string& name){
     if(name.empty())return false;//Return false if it is empty.
     for(int i=0;i<name.length();++i){//i cannot more than parameter length.
        char c=name[i];//Define a character to get parameter.
        if (!isalnum(c)&&c!=' ') return false;//Returns false if c is a digit or a letter, or have a space, and true otherwise.
     }
     return true;
}

string intToString(int num) {//Convert number to string type.
    if (num==0)return "0";//If a number called 0, return 0 because it is also called 0 in string type.
    string result = "";//Create a blankspace to store result.
    while (num>0){//Continue execute if parameter has not turn in 0.
        int digit =num%10;//Define an integer digit to store parameter which is already mod 10.
        char ch='0'+digit;/*Define a character call ch to store digit, and there is a 0 because in ASCII represent as 48. 
                            Integer 1 starts as 49 in ASCII. With this it can turn in character type.*/
        result=ch+result;//Blankspace will store ch and itself, and ch will be first one so it can add it in front of result.
        num=num/10;//Get parameter with last number, which is not used in mod 10 form.
    }
    return result;//Get the string type after executing while loop.
}

string generateNextId(Product products[],int count){//Auto generate next Id.
    int maxnum=0;
    for(int i=0;i<count;i++){
        string id=products[i].getId();//Define a string type id to get product id.
        if (!id.empty() && id[0] == 'P') {//If id is not in empty type and the first one is P, it continue executes.
           string numberPart = "";//Create a string numberPart to store item. 
            for (int j=1;j<id.length();j++) {
                numberPart+=id[j];//Store id in numberPart.
            }
            bool isNumber = true;
            for (int j=0;j<numberPart.length();j++) {
                if(numberPart[j]<'0'||numberPart[j]>'9') {//Detect if the number is lower than 0 or higher than 9.
                    isNumber = false;
                    break;
                }
            }
            if(isNumber) {//Execute if it is true.
                int num=0;
                for (int j=0;j<numberPart.length();j++) {
                    num=num*10+(numberPart[j]-'0');/*num will become higher because it will multiply 10 every loop,
                                                     and the numberpart will decrease the first one in array.*/
                }
                if(num>maxnum) {
                    maxnum=num;//maxnum will become num if num is bigger than maxnum.
                }
            }
        }
    }
    int nextnum=maxnum+1;//Get nextnum through plus 1 in maxnum.
    string result="P";//Define a string type result which has a P at first.
    if (nextnum<10)result+= "00";//If nextnum is lower than 10, it automatically increase two 0, so it will become hundreds.
    else if (nextnum<100)result += "0";//If nextnum is lower than 100, it automatically increase 0, so it will become two digits.
    result +=intToString(nextnum);//Put nextnum in result.
    return result;
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
/*-----------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------Product Operation---------------------------------------------------------*/
void addProduct(Product products[],int& productcount){
 if (productcount>=MAX_PRODUCTS) {
        cout << "Error! Maximum capacity (100) reached!\n";
        return;
    }

    string id=generateNextId(products, productcount);
    string name;
    float price;
    int quantity, reorder;

    cout <<"Enter product name (only letters, numbers, and spaces allowed): ";
    cin.ignore();//Empty the buffer area in cin.
    getline(cin, name);
    if (!isValidName(name)) {
        cout <<"Invalid name. Only letters, numbers, and spaces are allowed.\n";
        return;
    }

    cout<<"Enter the price: ";
    cin>>price;
    if (cin.fail()||price < 0){
        //这里可以放try catch，if 是小数点，if是character，if是负数，if是字母等。
        cout <<"Invalid input. Price must be positive.\n";
        cin.clear();//Clear all the cin and the wrong type.
        cin.ignore(1000, '\n');//Ignore next 1000 word until meet \n.
        return;
    }

    cout << "Enter the quantity: ";
    cin>>quantity;
    if (cin.fail()||quantity<0){
        //这里可以放try catch，if 是小数点，if是character，if是负数，if是字母等。
        cout << "Invalid input. Quantity must be non-negative.\n";
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    cout<<"Enter the re-order level: ";
    cin>>reorder;
    if (cin.fail()||reorder<0){
        //这里可以放try catch，if 是小数点，if是character，if是负数，if是字母等。
        cout << "Invalid input. Reorder level must be non-negative.\n";
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

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
    if (matchCount>1) {//List all the products found.
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
        if (cin.fail()||choice<1||choice>matchCount) {//Detect if user cin text is in invalid, or out of the match area.
            cout<<"Invalid selection.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            return;
        }
        selectedIndex=matches[choice-1];//In array the first one is 0, so it can find the right one if minus 1.
    } else {
        selectedIndex=matches[0];
    }

    string name;
    float price;
    int quantity, reorder;

    cout << "Enter new name (only letters, numbers, and spaces allowed): ";
    cin.ignore();
    getline(cin, name);
    if (!isValidName(name)) {
        cout << "Invalid name. Only letters, numbers, and spaces are allowed.\n";
        return;
    }

    cout<<"Enter the new price: ";
    cin>>price;
    if (cin.fail()||price<0){
        cout << "Invalid input. Price must be positive.\n";
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    cout<<"Enter the new quantity: ";
    cin>>quantity;
    if (cin.fail()||quantity<0){
        cout << "Invalid input. Quantity must be non-negative.\n";
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    cout<<"Enter the new reorder level: ";
    cin>>reorder;
    if (cin.fail()|| reorder<0){
        cout << "Invalid input. Reorder level must be non-negative.\n";
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    products[selectedIndex].setProduct(products[selectedIndex].getId(), name, price, quantity, reorder);
    saveData(products, productcount);
    cout << "Product updated successfully.\n";
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
        if (cin.fail()||choice<1||choice>matchCount) {
            cout<<"Invalid selection.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            return;
        }
        selectedIndex=matches[choice-1];
    } else {
        selectedIndex=matches[0];
    }

    for(int j=selectedIndex;j<productcount-1;j++) {//Start from selectedIndex, and use productcount-1 to make sure it will not over the area.
        products[j]=products[j+1];//Take content in product[j] which come from [j+1] to overwrite it.
    }
    productcount--;//Delete a product successfully.
    saveData(products, productcount);
    cout<<"Product deleted successfully.\n";
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


