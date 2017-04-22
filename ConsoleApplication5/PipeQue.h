#include "Pipe.h"
class PipeQue
{
public:
	Pipe* data[4];
	int maxlenght;
	int front;//队列头元素
	int rear;//队列尾元素的下一个位置
	Pipe** getData()
	{
		return data;
	}
	PipeQue(int lenght)
	{
		this->maxlenght = lenght;
		//this->data = (Pipe*)malloc(sizeof(int)*lenght);
		front = 0;
		rear = 0;
	}
	bool empty()
	{
		return front == rear;
	}
	bool full()
	{
		return (rear + 1) % maxlenght == front;
	}
	~PipeQue()
	{
		free(data);
	}
	void push(Pipe* n)
	{
		if (full())return;
		data[rear] = n;
		rear = (rear + 1) % maxlenght;
	}
	void pop()
	{
		front = (front + 1) % maxlenght;
	}
	Pipe* gfront()
	{
		return data[front];
	}
};