//@file queuea.h

#ifndef Queue_
#define Queue_

#include <iostream>
#include <stdexcept>

using namespace std;

template<class QueueItemType>
class Queue {
	// FIFO objects
public:
	Queue(int MaxQueueSize = 10);
	Queue(Queue<QueueItemType> &Q);
	~Queue() { delete[] queue; }
	bool IsEmpty() const { return front == rear; }
	bool IsFull() const {
		if ((rear + 1) % MaxSize == front) return 1;
		else return 0;
	};
	QueueItemType Front() const; // return front element
	void enqueue(const QueueItemType& x);
	void dequeue();
	int getMaxSize(){ return MaxSize; };
private:
	int front;   // one counterclockwise from first
	int rear;    // last element
	int MaxSize; // size of array queue
	QueueItemType *queue;    // element array
};

#endif


template<class QueueItemType>
Queue<QueueItemType>::Queue(int MaxQueueSize)
{// Create an empty queue whose capacity
	// is MaxQueueSize.
	MaxSize = MaxQueueSize + 1;
	queue = new QueueItemType[MaxSize];
	front = rear = 0;
}

template<class QueueItemType>
Queue<QueueItemType>::Queue(Queue<QueueItemType> &Q)
{
	int i;
	front = 0; rear = 0;
	MaxSize = Q.getMaxSize();
	queue = new QueueItemType[MaxSize];

	while (!Q.IsEmpty())
	{
		queue[rear] = Q.Front();
		Q.dequeue();
		rear = (rear + 1) % MaxSize;
	}

	for (i = front; i != rear; i = (i + 1) % MaxSize)
		Q.enqueue(queue[i]);
}

template<class QueueItemType>
QueueItemType Queue<QueueItemType>::Front() const
{// Return first element of queue.  Throw
	// OutOfBounds exception if the queue is empty.

	if (IsEmpty())
		throw logic_error("Queue exception: cannot retrieve from empty queue ");
	return queue[front];
}

template<class QueueItemType>
void Queue<QueueItemType>::enqueue(const QueueItemType& x)
{// Add x to the rear of the queue.  Throw
	// NoMem exception if the queue is full.
	if (IsFull()) throw logic_error("Queue exception: Queue is full ");
	queue[rear] = x;
	rear = (rear + 1) % MaxSize;
}





template<class QueueItemType>
void Queue<QueueItemType>::dequeue()
{// Delete first element and put in x.  Throw
	// OutOfBounds exception if the queue is empty.
	if (IsEmpty())
		throw logic_error("Queue exception:  cannot delete from empty queue ");
	front = (front + 1) % MaxSize;

}