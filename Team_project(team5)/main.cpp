#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <string>
#include <ostream>
#include <cctype>
#include <string>

#include "HashNode.h"
#include "HashTable.h"
#include "Stock.h"

using namespace std;

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

    HashTable stockHashTable;

    string line;
    while (getline(inFile, line))
    {
        string tk = "";
        string company = "";
        int price = -1;
        float percent_ch = 0;
        int int_ch = -1;
        int vol = -1;
        string date = "";

        stringstream temp(line);   // create temp with data from line

        temp >> tk;              // read from temp
        temp.ignore();             // to ignore space in front of name
        getline(temp, company);  // stop reading name at ';'
        temp >> price;
        temp >> percent_ch;
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

        stockHashTable.insert(st);
        cout << st->getTicker() << " was inserted\n";
    }

    inFile.close();

    Stock st1;
    string search_key;

    cout << "Which stock do you want to search? (ticker) : ";
    getline(cin, search_key);
    stockHashTable.search(st1, search_key);
    cout << st1;

    return 0;
}