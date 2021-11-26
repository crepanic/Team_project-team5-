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
    int totalNoColl;

public:
    HashTable() 
    { count = 0; 
      hashSize = 20;
      totalNoColl = 0;
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
        totalNoColl = 0;
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
    bool remove(Stock& stOut, string key);
    int search(Stock& target, string key);
    int collisionCount() { return totalNoColl; } // return number of collisions (total)
    int longestLinkedListCount(); // return length of the longest linked list

private:
    int _hash(string key) const;
};


int HashTable::_hash(string key) const // have to improve hash function, other than using modulo Division
{
    int sum = 0;
    for (unsigned int i = 0; i < key.length() ; i++)
        sum += int(key[i]);

    return sum % hashSize;
};

/*~*~*~*
  hash insert - hash table with chanining
*~**/

bool HashTable::insert(Stock* stIn)
{
    int bucketN = _hash(stIn->getTicker());
    Stock temp;
    if (HashTable::search(temp, stIn->getTicker()) > 0) return false; //duplicate a primary key
    

    // insert a new item
    if (hashAry[bucketN]==NULL) {
        HashNode* node = new HashNode;
        hashAry[bucketN] = node;
        node->setItem(stIn);
        node->setNextNode(NULL);
        node->setNoCollisions(1);
        node->setOccupied(1);

        count++;

//        node->getItem()->hDdisplay(); 
//        cout << "bucketN: "<<bucketN << " " << node->getNoCollisions() << endl;
    }
    else {
        HashNode* head = hashAry[bucketN];
        while (1) {
            if (head->getNextNode()) head = head->getNextNode();
            else break;
        }

        HashNode* node = new HashNode;
        head->setNextNode(node);
        node->setItem(stIn);
        node->setNextNode(NULL);
        node->setNoCollisions(head->getNoCollisions()+1);
        node->setOccupied(1);

        totalNoColl++;
        count++;

//        node->getItem()->hDdisplay();
//        cout << "bucketN: " << bucketN << " " << node->getNoCollisions() << endl;
    }
    return true;
}

/*~*~*~*
  hash remove - hashnode delete from hashtable by primary key(Ticker)
*~**/

bool HashTable::remove(Stock &stOut, string key)
{
    Stock found;
    int position = HashTable::search(found, key); // position => position in the linked list 1 -> first, 2 -> second

    if (position == -1) return false; // No such a item.
    else
    {
        int bucketN = _hash(key);
        HashNode* head = hashAry[bucketN];

        if (position == 1 && head->getNextNode() == NULL)
        {
            hashAry[bucketN] = NULL;
            count--;
        }
        else if (position == 1 && head->getNextNode() != NULL) 
        {
            hashAry[bucketN] = head->getNextNode();
            head = hashAry[bucketN];
            totalNoColl--;
            count--;

            while (head)
            {
                head->setNoCollisions(head->getNoCollisions() - 1);
                head = head->getNextNode();
            }
        }
        else
        {   
            while (head->getNoCollisions() < position - 1) //move to privious position of removing item
            {
                head = head->getNextNode();
            }

            head->setNextNode(head->getNextNode()->getNextNode());
            head = head->getNextNode();
            totalNoColl--;
            count--;

            while (head)
            {
                head->setNoCollisions(head->getNoCollisions() - 1);
                head = head->getNextNode();
            }
        }
    }

/*    cout << " check for array 0 " << endl;

    HashNode* check = hashAry[0];
    int helper = 0;
    while (check) {
        check->getItem()->hDdisplay();
        check = check->getNextNode();
        helper++;
    }
    cout << "helper: " << helper << endl;
*/
    stOut = found;
    return true;
}

/*~*~*~*
hash search - item by primary key
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
    }

    return -1;
}


/*~*~*~*

*~**/

int HashTable::longestLinkedListCount()
{
    int longest = 0;

    for (int i = 0; i < hashSize; i++)
    {
        HashNode* head;
        if (hashAry[i] != NULL) {
            head = hashAry[i];

            int countoflist = 0;
            while (head) {
                countoflist++;
                head = head->getNextNode();
            }

            if (longest < countoflist) longest = countoflist;
        }
    }
    return longest;
}


#endif // HASHTABLE_H_
