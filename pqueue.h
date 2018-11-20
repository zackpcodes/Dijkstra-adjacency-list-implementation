// CSCI 2530
// Assignment: 6
// Author:     zackary pulaski
// File:       pqueue.h
// Tab stops:  4


#include "event.h"
#include <cstdio>
using namespace std;

struct PQCell;
//Type definitions
typedef Event* ItemType;
typedef double      PriorityType;
typedef void (*ItemPrinter)(ItemType);
typedef void (*PriorityPrinter)(PriorityType);





//PriorityQueue holds a pointer to a linked
//lists of PQCell objects.

struct PriorityQueue
{
    PQCell* pointerToQueue;
    PriorityQueue()
    {
        pointerToQueue = NULL;
    }
};

//Forward declarations
bool isEmpty(const PriorityQueue& q);
void insert(PriorityQueue& q, ItemType x, PriorityType p);
void printPriorityQueue(const PriorityQueue& q, ItemPrinter pi, PriorityPrinter pp);
void remove(PriorityQueue& q, ItemType& x, PriorityType& p);
