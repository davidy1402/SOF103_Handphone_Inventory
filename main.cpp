#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

int main(){

    ifstream readF;
    string readFile;

    readF.open ("inventory.txt");

    if (readF)                                                  //Check if file opened
        cout << "File has been read succesfully!"<<endl; 
    else 
        cout << "File read Error!!"<<endl;

    while(getline(readF,readFile)){                                        //Extract File
    cout << readFile<<endl;}

    readF.close();
    return 0;

    //asdjahskdasjkdhkasd
    // sajkdhkjasd
    // sdahsdkjhk
    // sdkasdhk
    // kjhasjd
}
