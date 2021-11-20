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
    int collisionCount(); // return number of collisions (total)
    int longestLinkedListCount(); // return length of the longest linked list

private:
    int _hash(string key) const;
};


int HashTable::_hash(string key) const // have to improve hash function, other than using modulo Division
{
    int sum = 0;
    for (int i = 0; key[i]; i++)
        sum += key[i];
    return sum % hashSize;
};

/*~*~*~*
  hash insert - hash table with chanining
*~**/

bool HashTable::insert(Stock* stIn)
{
    int bucketN = _hash(stIn->getTicker());

    if (HashTable::search(stIn, stIn->getTicker())) return false; //duplicate a primary key

    // insert a new item
    if (hashAry[bucketN]==NULL) {
        HashNode* node = new HashNode;
        hashAry[bucketN] = node;
        node->setItem(stIn);
        node->setNextNode(NULL);
        node->setNoCollisions(1);
        node->setOccupied(1);

        count++;
    }
    else {
        HashNode* head = hashAry[bucketN];
        while (head) {
            if (head->getNextNode()) head = head->getNextNode();
        }

        HashNode* node = new HashNode;
        head->setNextNode(node);
        node->setItem(stIn);
        node->setNextNode(NULL);
        node->setNoCollisions(head->getNoCollisions() + 1);
        node->setOccupied(1);

        count++;
    }

    return true;
}

/*~*~*~*
  hash remove - hashnode delete from hashtable by primary key(Ticker)
*~**/

bool HashTable::remove(Stock* stOut, string key)
{
    Stock* found = new Stock;

    if (HashTable::search(found, key) == -1) return false; // No such a item.
    else
    {
        stOut = found;

        int bucketN = _hash(key);



/*
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
*/
    }

    return true;
}

/*~*~*~*

*~**/

int HashTable::search(Stock* target, string key)
{
    int bucketN = _hash(key);

    if (hashAry[bucketN] == NULL) return -1;
    else {
        HashNode* head = hashAry[bucketN];
        while (head) {
            if (head->getItem()->getTicker() == key) target = head->getItem();
            else head = head->getNextNode();
        }

        if (target == NULL && head->getNextNode() == NULL) return -1;
    }

    return 0;
}

/*~*~*~*

*~**/

int HashTable::collisionCount()
{
    return 0;
}


/*~*~*~*

*~**/

int HashTable::longestLinkedListCount()
{

}


#endif // HASHTABLE_H_
