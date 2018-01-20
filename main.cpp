#include <iostream>
#include <fstream>
#include <limits>
#include <vector>

using namespace std;

int printMain();

int menuSelection = -3;
int printEncryptDecrypt();
void Encryption();
void Decryption();

vector<char*> keys;

int main(){
    int selection;
    while(selection != -2){
        menuSelection = -3;
        selection = printMain();
        if(selection == 1){
            selection = printEncryptDecrypt();
            if(selection == 1){
                Encryption();
            }
            else if (selection == 2){
                Decryption();
            }
        }
    }
    return 0;
}
 int printMain(){

     while(menuSelection != 1 && menuSelection != 2 && menuSelection != -2){
        cout << "1. Encrypt/Decrypt" << endl;
        cout << "0. Exit" << endl;
        cin >> menuSelection;
        if(menuSelection == 0){
            return -2;
        }
        else if(menuSelection == 1 || menuSelection == 2){
            return menuSelection;
        }
        {
            cout << "Invalid Selection" << endl;
            if(!cin){
                cin.clear();
                cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
            }
        }
    }
    return menuSelection;
 }

int printEncryptDecrypt(){
    menuSelection = -1;
    while(menuSelection != 1 && menuSelection != 2 && menuSelection != 0){
        cout << "1. Encrypt" << endl;
        cout << "2. Decrypt" << endl;
        cout << "0. Main Menu" << endl;
        cin >> menuSelection;
        if(menuSelection == 1 || menuSelection == 2){
            return menuSelection;
        }
        else if (menuSelection == 0){
            return -1;
        }
        else
        {
            cout << "Invalid Selection" << endl;
            if(!cin){
                cin.clear();
                cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
            }
        }
    }
    return menuSelection;
}

void Encryption(){
    string key = "";
    string input = "";
    string output = "";
    ifstream inputfile;
    ofstream outputfile;
    string line;
    char valueOfKey;
    int index = 0;

    keys.clear();

    cout << "Please Enter and Encryption Key" << endl;
    cin >> key;
    cout << "Please Enter a File To Encrypt" << endl;
    cin >> input;
    cout << "Please Enter the Output Filename" << endl;
    cin >> output;

    locale loc;
    for (string::size_type i=0; i<key.length(); ++i)
        cout << tolower(key[i],loc);

    for(int i = 0; i < key.length(); i++){
        valueOfKey = key[i];
        char* keyvalue = new char[26];
        keyvalue[0] = key[i];
        for(int j = 1; j <= 25; j++){
            keyvalue[j] = (++valueOfKey);
            if(valueOfKey == 'z'){
                valueOfKey = 'a';
                valueOfKey--;
            }
        }
        keys.push_back(keyvalue);
    }

    inputfile.open(input.c_str());
    outputfile.open(output.c_str());

    if (inputfile.is_open())
    {
        char c;
        while (inputfile.get(c)){
            if(isalpha(c)){
                outputfile << keys[index++][(c-97)];
            }
            else
            {
                outputfile.put(c);
            }
            if(index > keys.size()-1){
                index = 0;
            }
        }
    }

    inputfile.close();
    outputfile.close();
}
void Decryption(){
    string key = "";
    string input = "";
    string output = "";
    ifstream inputfile;
    ofstream outputfile;
    string line;
    char valueOfKey;
    int index = 0;
    int calcindex;
    int offset;
    char printchar;

    keys.clear();

    cout << "Please Enter and Encryption Key" << endl;
    cin >> key;
    cout << "Please Enter a File To Decrypt" << endl;
    cin >> input;
    cout << "Please Enter the Output Filename" << endl;
    cin >> output;

    locale loc;
    for (string::size_type i=0; i<key.length(); ++i)
        cout << tolower(key[i],loc);

    for(int i = 0; i < key.length(); i++){
        valueOfKey = key[i];
        char* keyvalue = new char[26];
        keyvalue[0] = key[i];
        for(int j = 1; j <= 25; j++){
            keyvalue[j] = (++valueOfKey);
            if(valueOfKey == 'z'){
                valueOfKey = 'a';
                valueOfKey--;
            }
        }
        keys.push_back(keyvalue);
    }

    inputfile.open(input.c_str());
    outputfile.open(output.c_str());

    if (inputfile.is_open())
    {
        char c;
        while (inputfile.get(c)){
            if(isalpha(c)){
                offset = key[index]-97;
                calcindex = c-offset;
                if(calcindex < 97){
                    calcindex += 26;
                }
                printchar = calcindex;
                outputfile << printchar;
                index++;
            }
            else
            {
                outputfile.put(c);
            }
            if(index > keys.size()-1){
                index = 0;
            }
        }
    }

    inputfile.close();
    outputfile.close();
}
