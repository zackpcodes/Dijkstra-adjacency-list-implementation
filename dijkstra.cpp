// CSCI 2530
// Assignment: 7
// Author:     Zackary Pulaski
// File:       dijkstra.cpp
// Tab stops:  4

//This program reads a graph from the standard input
//prints this graph, a path of the shortest distance
//from a start vertex to an end vertex within the graph,
//and the shortest distance between thoughs vertices.

//Example output:

/*
There are 5 vertices and 6 edges.
The edges are as follows.

(1,3) weight 12.000
(1,2) weight 9.000
(2,5) weight 20.000
(2,3) weight 6.000
(2,4) weight 18.000
(3,5) weight 15.000

The shortest path from 1 to 5 has length 27.000 and is
1 -> 3 -> 5
*/



#include "pqueue.h"
#include <cstdlib>
#include <cstdio>
#include <string.h>
using namespace std;

typedef PriorityQueue EventQueue;
int tracing = 0;

//Edge structure represents an object
//within a linked list of Edges
//where "u" is vertex 1, "v" is vertex 2
//and "w" is the weight of that edge.
//Also, a Edge object contains a pointer
//to the next item in the linked list.

struct Edge
{
	int u;
	int v;
	double w;
	Edge* next;

	Edge(int vert1, int vert2, double weight, Edge* nx)
	{
		u = vert1;
		v = vert2;
		w = weight;
		next = nx;
	}
};

//Vertex structure represents an object
//that stores a pointer to a linked list
//of Edge objects "listOfEdges", the ditance
//between vertexs "shortestTime" and the
//vertex of the sender "sender".

struct Vertex
{
	Edge* listOfEdges;
	double shortestTime;
	int sender;

	Vertex()
	{
		listOfEdges = NULL;
		shortestTime = -1;
		sender = -1;
	}
};

//Graph structure represents and object
//with the following properties. numberOfVerts
//which holds the graphs number of vertices,
//numberOfEdges which holds the graphs current
//number of edges and a pointer to an array of
//Vertex objects.

struct Graph
{
	int numberOfVerts;
	int numberOfEdges;
	Vertex* vertices;

	Graph(int nv)
	{
		numberOfVerts = nv;
		vertices = new Vertex[numberOfVerts+1];
		numberOfEdges = 0;
	}
};

//TracingRequest turns tracing on or off
//depending on argv[1] = "-t".

void tracingRequest(int argc, char* argv[])
{
	if(argc != 1)
	{
		if(strcmp(argv[1],"-t")==0)
		{
			tracing = 1;
		}
		else
		{
			printf("usage: dijkstra [-t]");
			exit(1);
		}
	}

}



//InsertCell inserts a Edge with vert1,vert2
//and the weight into Graph g.

void insertHelper(int vert1, int vert2, double weight, Graph* g)
{
	Edge* A = new Edge(vert1, vert2, weight, NULL);

	if (g->vertices[vert1].listOfEdges == NULL)
	{
		g->vertices[vert1].listOfEdges = A;
	}
	else
	{
		Edge* curr = g->vertices[vert1].listOfEdges;
		while (curr->next != NULL)
		{
			curr = curr->next;
		}
		curr->next = A;
	}
}


//InsertCell(vert1,vert2 ,weight, g) inserts
//a bidirectional edge with vert1 vert2 and weight into
//graph g.

void insertCell(int vert1, int vert2, double weight, Graph* g)
{
	insertHelper(vert1,vert2,weight,g);
	insertHelper(vert2,vert1,weight,g);
	g->numberOfEdges++;
}



//WriteList prints a linked list g
//to the standard output.

void writeList(Edge* g)
{
	while(g != NULL)
	{
		printf("%d   %d \t\t%.3lf\n", g->u, g->v, g->w);
		g = g->next;
	}
}




//WriteGraph prints Graph g Vertices array
// of linked lists.

void writeGraph(Graph* g)
{
	printf("Vertices   Weight\n");

	for(int i = 1; i <= g->numberOfVerts; i++)
	{
		Edge* curr = g->vertices[i].listOfEdges;
		writeList(curr);
	}

}




//ReadGraph reads edges from standard input
//and returns a Graph A of these edges.

Graph* readGraph()
{
	int n = 0;
	scanf("%d",&n);

	Graph* A = new Graph(n);

	while(true)
	{
		int vert1,vert2;
		double weight;
		scanf("%d",&vert1);
		if(vert1 == 0)
		{
			break;
		}
		scanf(" %d %lf",&vert2, &weight);

		insertCell(vert1,vert2,weight,A);

	}


	return A;
}


//SendSignal inserts an event "event(u,v,t)"
//into EventQueue q.

void sendSignal(int u, int v, double t, EventQueue* q)
{
	Event* e = new Event(u,v,t);
	insert(*q, e, t);
	if(tracing == 1)
	{
		printf("Signal Sent");
		printf("Current time: %lf Time sent: %lf Arrival time: %d Sender: %d Reciever: %d\n", t, t, u, v);
	}
}



//SignalsToAdjacent sends a signal
//from v to every vertex that is adjacent
//to v in graph q.

void signalsToAdjacent(Graph* g, int v, EventQueue* q)
{
	Edge* curr = g->vertices[v].listOfEdges;
	while(curr != NULL)
	{
		sendSignal(v, curr->v,(curr->w + g->vertices[v].shortestTime), q);
		curr = curr->next;
	}
}

//ProcessEvent(g,q,e) processes an Event e
//and sends signals to adjacent edges.

void processEvent(Graph* g, EventQueue* q, Event* e)
{
	if(tracing == 1)
	{
		printf("Current time: %d Sender: &d Receiver: %d",
		e->timeArrived, e->vertexSender, e->vertexReceiver);
	}
	if(g->vertices[e->vertexReceiver].shortestTime < 0)
	{
		g->vertices[e->vertexReceiver].shortestTime = e->timeArrived;
		g->vertices[e->vertexReceiver].sender = e->vertexSender;
		signalsToAdjacent(g,e->vertexReceiver,q);
	}
}

//DijkstraAlgo(g,start,end) retrives and processes
//events starting at vertex start and ending at
//vertex end.

void dijkstraAlgo(Graph* g, int start, int end)
{
	EventQueue eq;
	double t = 0.0;
	Event* e = new Event(0,start,t);

	sendSignal(0,start,t,&eq);

	while(g->vertices[end].shortestTime < 0)
	{
		remove(eq,e,t);
		processEvent(g,&eq,e);

	}
}

//PrintChain(g,start,end) prints to the standard
//output the shortest path within graph g
//from start to end.

void printChain(Graph* g, int start, int end)
{
	if(start == end)
	{
		printf("%d", start);
	}
	else
	{
		printChain(g,start,g->vertices[end].sender);
		printf(" -> %d", end);
	}
}


int main(int argc, char* argv[])
{
	tracingRequest(argc, argv);
	int start, end, nv;


	Graph* g = new Graph(nv);
	g = readGraph();

	scanf("%d %d", &start, &end);

	printf("There are %d vertices and %d edges.\n", g->numberOfVerts, g->numberOfEdges);
	printf("The edges are as follows.\n\n");

	writeGraph(g);



	dijkstraAlgo(g,start,end);

	printf("The shortest path from %d to %d has length %.3lf and is\n",
	start, end, g->vertices[end].shortestTime);

	printChain(g,start,end);
	printf("\n");

	return 0;
}
