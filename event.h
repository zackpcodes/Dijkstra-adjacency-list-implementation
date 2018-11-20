#ifndef EVENT_H
#define EVENT_H

//A object of type Event represents
//the arrival of a signal at a vertex.
//Event type stores the vertex of a
//sender, vertex of a receiver and the
//time a which signal arrives.

struct Event
{
	int vertexSender;
	int vertexReceiver;
	double timeArrived;

	Event(int s, int r, double t)
	{
		vertexSender = s;
		vertexReceiver = r;
		timeArrived = t;

	}

};

#endif
