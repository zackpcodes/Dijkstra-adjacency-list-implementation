// CSCI 2530
// Assignment: 6
// Author:     Zackary Pulaski
// File:       pqueue.cpp
// Tab stops:  4

//This file is a module that is to be used
//to create, delete, and fill a priority
//queue.

#include "pqueue.h"
#include <cstdio>
using namespace std;


//PQCell represents an object in a linked list
//with the following properties  item, priority
//and next(points to next object in linked list.

struct PQCell
{
    ItemType item;
    PriorityType priority;
    PQCell* next;

    PQCell(ItemType i, PriorityType p, PQCell* pq)
    {
        item = i;
        priority = p;
        next = pq;
    }
};


//IsEmpty returns true if priority queue q is empty
//and false if priority queue q is not empty.

bool isEmpty(const PriorityQueue& q)
{
    if(q.pointerToQueue == NULL)
    {
        return true;
    }
    return false;
}


//InsertCell inserts a new cell, composed of
//itemtype x and prioritytype p, into priority
//queue L, while preserving the non-descending
//order of the queue.

void insertCell(PQCell*& L, ItemType x, PriorityType p)
{
	if (L == NULL)
	{
		L = new PQCell(x, p, NULL);
	}
	else if (L->priority < p)
	{
		insertCell(L->next, x, p);
	}
	else
	{
		L = new PQCell(x, p, L);
	}
}


//Insert inserts a new cell in the priority
//queue q with item x and priority p.

void insert(PriorityQueue& q, ItemType x, PriorityType p)
{
    insertCell(q.pointerToQueue,x,p);
}


//PrintPriorityQueue prints priority
//queue q to the standard output, using
//ItemPrinter pi and PriorityPrinter pp.

void printPriorityQueue(const PriorityQueue& q, ItemPrinter pi, PriorityPrinter pp)
{
	printf("Priority Queue : \n");
	PQCell *cell = q.pointerToQueue;

	while (cell != NULL)
	{
		printf("Item : ");
		pi(cell->item);
		printf(" Priority : ");
		pp(cell->priority);
		printf("\n");
		cell = cell->next;
	}
}


//Remove removes the cell from priority queue q
//with the lowest priority. Sets x equal to item
//and p equal to the priority.

void remove(PriorityQueue& q, ItemType& x, PriorityType& p)
{
        PQCell* tempCell = q.pointerToQueue;
        q.pointerToQueue = tempCell->next;

        p = tempCell->priority;
        x = tempCell->item;

        delete tempCell;
}
