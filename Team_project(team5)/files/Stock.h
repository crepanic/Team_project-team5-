#pragma once
#include <string>
// Specification file for the Stock class
// written by: Sunmi Reu
// IDE: Visual Studio

#ifndef STOCK_H
#define STOCK_H

using std::string;

class Stock
{
private:
    string ticker; // primary key
    string cname; // secondary key (company name)
    int price;
    float pchange; // % change
    int change; // $ change
    int volume; // how many stocks have been traded in a day
    string date; // format YYYY-MM-DD

public:
    Stock() { ticker = ""; cname = ""; price = 0; }  // Constructor
    Stock(string tk, string n, int p) { ticker = tk; cname = n; price = p; }  // Overloaded Constructor

    // Setters and getters
    void setTicker(string tk) { ticker = tk; }
    void setCname(string n) { cname = n; }
    void setPrice(int p) { price = p; }
    void setPchange(float pchg) { pchange = pchg; }
    void setChange(int chg) { change = chg; }
    void setVolume(int vol) { volume = vol; }
    void setDate(string dt) { date = dt;  }

    string getTicker() const { return ticker; }
    string getCname() const { return cname; }
    int getPrice() const { return price; }
    float getPchange() const { return pchange; }
    int getChange() const { return change; }
    int getVolume() const { return volume; }
    string getDate() const { return date; }

    // Overloaded operators
    bool operator==(const Stock& st) { return this->getTicker() == st.getTicker(); }
};
#endif
