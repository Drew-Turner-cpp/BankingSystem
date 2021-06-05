/*
        Banking System Header File

        Made by Drew Turner

        06/01/21

        Happy Pride month :)
*/


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "bits.h"
#include <stdio.h>
#include <string.h>
#include <sstream>


using namespace std;


/*

            Class Discription:

            Stores the account holder's name, the interest rate of the account
            the balance of the account and the account pin. Two methods for
            assigning the vars and printing all the info are included.


            The class was easy to write but the file handling was a... learning
            experience.

*/
class Account
{
    public:
    // INIT.
    string accountHolder;
    float intrest;
    float accBalance;
    string pin;

    // Assigns values
    void construct(string accH, float inter, string p, float accBal = 0)
    {
        accountHolder = accH;
        intrest = inter;
        accBalance = accBal;
        pin = p;
    }
    
    // Outputs all account information
    void accInfo()
    {
        cout << "ACCOUNT HOLDER:        " + accountHolder << endl;
        cout << "ACCOUNT INTEREST RATE: " + to_string(intrest) << endl;
        cout << "CURRENT ACC. BALANCE:  " + to_string(accBalance)<< endl;
        cout << "ACCOUNT PIN:           " + pin << endl;
    }
};

/*

            Function documentation:

            createAccount(all vars for creating an account):
            Creates an account by using the .construct method
            then it returns the class object to be stored later

            returns: Account object


            sift(string filename):
            Combs through a list or vector and removes the
            duplcate elements by comparing each item.

            returns: void


            saveAccount(Account object):
            Saves an account to a file named "account.txt"

            returns: void


            readSavedAccounts(string filename):
            Reads all lines of a specified file and returns a vector of
            accounts that it finds on said file

            returns: Account object of string inputted

*/



// Creates an account and returns it
Account createAccount(string accH, float inter, float accBal, string p)
{
    Account x;  // Create new Account object
    x.construct(accH, inter, p, accBal);  // Construct Account
    return x;  // Return Account
}


// Removes duped items from the file 'account.txt'
void sift(string filename)
{
    vector <string> storage;
    string* read;
    read = new string;

    ifstream file(filename);

    while(getline(file, *read))
    {
        storage.push_back(*read);  // Push all info to vector
    }
    file.close();  // Close file
    delete read;   // Deallocate string

    sort(storage.begin(), storage.end());      // Sorting algorithm
    for (int i = 0; i <= storage.size(); i++)  // this sorts and removes all dupes
    {
        sort(storage.begin(), storage.end());
        for (int internal = 0; internal <= storage.size(); internal++)
        {
            storage.erase(unique(storage.begin(), storage.end()), storage.end());
        }
    }
    storage.erase(storage.end());

    // Overwrite file with new info
    ofstream overw(filename);

    for (int z = 0; z <= storage.size(); z++)
    {
       overw << storage[z] << endl;
    }
    overw.close();  
    storage.clear();  // Deallocate all memory used
}


// Saves account to file  
void saveAccount(Account a)
{
    ofstream accFile;  // Create ofstream
    accFile.open("account.txt", ios_base::app);  // Open file using append mode
    accFile << a.accountHolder + " " + to_string(a.intrest) + " " + to_string(a.accBalance) + " " + a.pin << endl;  // Print account information to file
    accFile.close();
}   

// Tokenizes a string by the separation specified and returns the account within that string
Account toked(string toker, char part)
{
    vector <string> tStr;
    stringstream str(toker);
    string* blank = new string;
    
    while (getline(str, *blank, part))  // Push back all substrings in main arg
    {
        tStr.push_back(*blank);
    }
    delete blank;
    str.clear();  // Deallocate str and blank

    float in = stof(tStr[1]);  // Convert floats
    float ba = stof(tStr[2]);

    Account ret = createAccount(tStr[0], in, ba, tStr[3]);  // Create account object to return
    tStr.clear(); // Deallocate vector

    return ret;
}


// Reads all accounts on file, returns a vector containing all accounts
void readSavedAccounts(string filename, bool ifsift)
{
    if (ifsift)
    {
        sift(filename);
    }

    vector <string> storage;
    string* read;
    read = new string;

    ifstream file(filename);

    while(getline(file, *read))
    {
        storage.push_back(*read);  // Push all info to vector
    }
    file.close();  // Close file
    delete read;   // Deallocate string

    Account* acc = new Account();  // Create new account object
    for (int i = 0; i <= storage.size() - 1; i++)
    {
        *acc = toked(storage[i], ' ');
        acc->accInfo();
        cout << "<><><><><><><><><><>" << endl;
    }
    delete acc;  // Deallocate account
    
}
