#pragma once
// Specification file for the Hash class
// Written By: Sunmi Reu
// Changed by:


#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include "HashNode.h"

using std::string;

class HashTable
{
private:
    HashNode** hashAry;
    int hashSize;
    int count;

public:
    HashTable() { count = 0; hashSize = 53; hashAry = new HashNode*[hashSize]; }
    HashTable(int n) { count = 0; hashSize = n;	hashAry = new HashNode*[hashSize]; }
    ~HashTable() { delete[] hashAry; }

    int getCount() const { return count; }
    int getSize() const { return hashSize; }
    double getLoadFactor() const { return 100.0 * count / hashSize; }
    bool isEmpty() const { return count == 0; }
    bool isFull()  const { return count == hashSize; }

    bool insert(Stock *stIn);
    bool remove(Stock* stOut, string key);
    int search(Stock* target, string key);

private:
    int _hash(string key) const;
};


int HashTable::_hash(string key) const
{
    int sum = 0;
    for (int i = 0; key[i]; i++)
        sum += key[i];
    return sum % hashSize;
};

/*~*~*~*
  hash insert - linear probe
*~**/


bool HashTable::insert(Stock& stIn)
{
    if (count == hashSize)   //when hashtable is full, it returns false
        return false;
    int bucketN = _hash(stIn.getTicker());

    int bucketsProbed = 0;

    while (bucketsProbed < hashSize)
    {
        if (hashAry[bucketN].getOccupied() != 1)
        {
            hashAry[bucketN].setItem(stIn);
            hashAry[bucketN].setOccupied(1);
            hashAry[bucketN].setNoCollisions(bucketsProbed);
            this->count += 1;
            return true;
        }
        else
        {
            ++bucketsProbed;
            bucketN = (bucketN + 1) % hashSize;
        }
    }
    return true;
}

/*~*~*~*

*~**/

bool HashTable::remove(Stock& stOut, string key)
{
    Stock finding;

    if (HashTable::search(finding, key) == -1) return false;
    else
    {
        stOut = finding;

        int bucketN = _hash(key);
        int bucketsProbed = 0;

        while ((hashAry[bucketN].getOccupied() != 0 && bucketsProbed < this->getSize()))
        {
            if (hashAry[bucketN].getOccupied() != 0 && hashAry[bucketN].getItem().getName() == key)
            {
                itemOut = hashAry[bucketN].getItem();

                Student st;
                hashAry[bucketN].setItem(st);
                hashAry[bucketN].setOccupied(0);

                this->count -= 1;
                return true;
            }

            bucketN = (bucketN + 1) % hashSize;

            ++bucketsProbed;
        }
    }

    return true;
}

/*~*~*~*

*~**/

int HashTable::search(Stock& target, string key)
{
    int bucketN = _hash(key);
    int bucketsProbed = 0;

    while (((hashAry[bucketN].getOccupied() != 0 or hashAry[bucketN].getNoCollisions() > 0) && bucketsProbed < this->getSize()))
    {
        if ((hashAry[bucketN].getOccupied() != 0 or hashAry[bucketN].getNoCollisions() > 0) && hashAry[bucketN].getItem().getName() == key)
        {
            itemOut = hashAry[bucketN].getItem();
            return hashAry[bucketN].getNoCollisions();
        }

        bucketN = (bucketN + 1) % hashSize;

        ++bucketsProbed;
    }

    return -1;
}



#endif // HASHTABLE_H_
