#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <string>
#include <ostream>
#include <cctype>
#include <string>
#include <vector>

#include "HashNode.h"
#include "HashTable.h"
#include "Stock.h"

using namespace std;

int FindSmallestPrime(int n); // Determine Hash Size

int main()
{
    string inputFileName;
    cout << "Input file name: ";
    getline(cin, inputFileName);

    ifstream inFile(inputFileName);
    if (!inFile) {
        cout << "Error opening the input file: \"" << inputFileName << "\"" << endl;
        exit(EXIT_FAILURE);
    }

    int number_of_lines = 0;
    string line;

    //finding the next prime number of input lines * 2
    while (!inFile.eof()) {
        getline(inFile, line);
//        cout << line << endl;
        number_of_lines++;
    }

    int hashsize = FindSmallestPrime(number_of_lines * 2);

    HashTable hash(hashsize);

    //insert all items from input file
    inFile.seekg(0);
    while (getline(inFile, line))
    {
        string tk, company, date = "";
        int price, int_ch, vol = -1;
        float percent_ch = 0;

        stringstream temp(line);   // create temp with data from line

        temp >> tk;              // read from temp
        temp.ignore();             // to ignore space in front of name
        temp >> company;
        temp >> price;
        temp >> percent_ch;
        temp >> int_ch;
        temp >> vol;
        temp >> date;

        Stock* st = new Stock;
        st->setTicker(tk);
        st->setCname(company);
        st->setPrice(price);
        st->setPchange(percent_ch);
        st->setChange(int_ch);
        st->setVolume(vol);
        st->setDate(date);

        hash.insert(st);
    }

    inFile.close();

    // test search
    Stock st, st1, st2;
    string search_key, delete_key, second_search;
    cout << "====================" << endl;
    cout << "     Test Search" << endl;
    cout << "====================" << endl;
    
    while(search_key != "Q")
    {
        cout << "Enter name(Ticker) or Q for quit : ";
        getline(cin, search_key);
        if (search_key == "Q") break;
        else if (hash.search(st, search_key)) cout << st.getTicker() << " is found!" << endl; ;
     
    }
    
    // test delete
    cout << "====================" << endl;
    cout << "     Test Delete" << endl;
    cout << "====================" << endl;

    cout << "Total " << hash.getCount() << " items are inserted" << endl;
    while (delete_key != "Q")
    {
        cout << "Enter name or Q to quit : ";
        getline(cin, delete_key);
        if (delete_key == "Q") break;
        else if (hash.search(st1, delete_key) == -1) cout << "Incorrect Ticker Name. Please try again!" << endl;
        else 
        {
            hash.remove(st1, delete_key);
            cout << st1.getTicker() << " is deleted" << endl;
        }
        cout << "Total " << hash.getCount() << " items are left" << endl;
    }

    //test search
    cout << "====================" << endl;
    cout << "     Test Search" << endl;
    cout << "====================" << endl;
    while ( second_search != "Q")
    {
        cout << "Enter name(Ticker) or Q for quit : ";
        getline(cin, second_search);
        if (second_search == "Q") break;
        else if (hash.search(st2, second_search) == -1) cout << second_search << " is not found!" << endl;
        else if(hash.search(st2, second_search) > 0) cout << st2.getTicker() << " is found!" << endl;
    }

    //Statistics 
    cout << "====================" << endl;
    cout << "     Statistics " << endl;
    cout << "====================" << endl;
    cout << " load factor: " << hash.getLoadFactor() << endl;
    cout << " how many items are in: " << hash.getCount() << endl;
    cout << " number of collision(total) " << hash.collisionCount() << endl;
    cout << " the length of longest linked list: " << hash.longestLinkedListCount() << endl;
    cout << "====================" << endl;
    cout << "     Done " << endl;
    cout << "====================" << endl;


    return 0;
}

int FindSmallestPrime(int n) 
{
    std::vector<int> sieve;

    sieve.reserve(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        sieve.push_back(i);
    }

    for (int i = 2; i * i < 2 * n; i++) {
        if (sieve[i] == 0) continue;
        int pivot = sieve[i];
        for (int j = pivot * 2; j < 2 * n; j += pivot) {
            sieve[j] = 0;
        }
    }
/*
    for (int i = 0; i < 2 * n; i++) {
        std::cout << sieve[i] << " ";
    }
    std::cout << std::endl;
*/
    for (int i = n; i < 2 * n; i++) {
        if (sieve[i] != 0) {
 //           std::cout << "Found the smallest prime: " << sieve[i] << std::endl;
            return sieve[i];
        }
    }

    return 0;
}
