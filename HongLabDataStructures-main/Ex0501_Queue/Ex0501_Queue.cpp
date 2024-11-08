#include "../shared/Queue.h"

#include <iostream>

int main()
{
	// FIFO(First In First Out)

	Queue<char> q(2); // capacity_ = 2에서 시작 (메모리 증가 확인)

	q.SetDebugFlag(true);

	q.Print();

	q.Enqueue('A');
	q.Print();
	q.Enqueue('B');
	q.Print();

	q.Enqueue('C');
	q.Dequeue();
	q.Print();
	q.Enqueue('D');
	q.Dequeue();
	q.Print();
	q.Enqueue('E');
	q.Print();


	q.Enqueue('F');
	q.Print();
	q.Dequeue();
	q.Print();
	return 0;
}
