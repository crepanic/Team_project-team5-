// Specification file for the HashNode class
// Written By: Sunmi Reu
// Changed by:

#ifndef _HASH_NODE
#define _HASH_NODE

#include "Stock.h"

using std::string;

class HashNode
{
private:
    Stock *st;
    int occupied;
    int noCollisions;
    HashNode *nextNode;

public:
    // constructors
    HashNode() { occupied = 0; noCollisions = 0; nextNode = NULL; }
    HashNode(Stock& anSt) { st = &anSt; occupied = 1; noCollisions = 0; nextNode = NULL; }
    HashNode(Stock& anSt, int ocp, int nCol, HashNode* nNode)
    {
        st = &anSt; occupied = ocp; noCollisions = nCol, nextNode = nNode;
    }
    // setters
    void setItem(Stock* anSt) { st = anSt; }
    void setOccupied(int ocp) { occupied = ocp; }
    void setNoCollisions(int nCol) { noCollisions = nCol; }
    void setNextNode(HashNode* nNode) { nextNode = nNode; }
    
    // getters
    Stock* getItem() const { return st; }
    int getOccupied() const { return occupied; }
    int getNoCollisions() const { return noCollisions; }
    HashNode* getNextNode() const { return nextNode; }
};

#endif
