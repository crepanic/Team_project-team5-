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
    HashTable() 
    { count = 0; 
      hashSize = 53; 
      hashAry = new HashNode*[hashSize];
      
      for(int i = 0; i < hashSize; i++)
      {
          hashAry[i] = NULL;
      }
    }
    HashTable(int n)
    {
        count = 0;
        hashSize = n;
        hashAry = new HashNode * [hashSize];

        for (int i = 0; i < hashSize; i++)
        {
            hashAry[i] = NULL;
        }
    }
    ~HashTable() { delete[] hashAry; }

    int getCount() const { return count; }
    int getSize() const { return hashSize; }
    double getLoadFactor() const { return 100.0 * count / hashSize; }
    bool isEmpty() const { return count == 0; }
    bool isFull()  const { return count == hashSize; }

    bool insert(Stock *stIn);
    bool remove(Stock* stOut, string key);
    int search(Stock& target, string key);
    int collisionCount() { return count - hashSize; } // return number of collisions (total)
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

 //   if (HashTable::search(stIn, stIn->getTicker())) return false; //duplicate a primary key

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
    Stock found;
    int position = HashTable::search(found, key); // position => position in the linked list

    if (position == -1) return false; // No such a item.
    else
    {
        *stOut = found;

        int bucketN = _hash(key);
        HashNode* head = hashAry[bucketN];

        while (head->getNoCollisions() == position - 1) {
            head = head->getNextNode();
        }

        head->setNextNode(head->getNextNode()->getNextNode());
        count--;
        
        head = head->getNextNode();

        while (head) {
            head->setNoCollisions(head->getNoCollisions() - 1);
        }
    }

    return true;
}

/*~*~*~*

*~**/

int HashTable::search(Stock& target, string key)
{
    int bucketN = _hash(key);

    if (hashAry[bucketN] == NULL) return -1;
    else {
        HashNode* head = hashAry[bucketN];
        while (head) {
            if (head->getItem()->getTicker() == key) {
                target = *head->getItem();
                return head->getNoCollisions();
            }
            else head = head->getNextNode();
        }

 //       if (target == NULL && head->getNextNode() == NULL) return -1;
    }

    return -1;
}


/*~*~*~*

*~**/

int HashTable::longestLinkedListCount()
{
    return 0;
}


#endif // HASHTABLE_H_
