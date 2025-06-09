#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

int main() {
    ofstream inventory;
    ifstream readF;
    string readFile;

    inventory.open ("inventory.txt");                               // Open File

    if (inventory)                                                  //Check if file opened
        cout << "File has been opened succesfully!"<<endl; 
    else 
        cout << "File Error!!"<<endl;

    getline(readF,readFile);                                        //Extract File
    cout << readFile;
    return 0;
}
