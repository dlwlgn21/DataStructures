#include "../shared/Queue.h"

#include <iostream>
#include <queue>


using namespace std;

int Solution(int n, int k)
{
	assert(n > 1 && k > 1);
	queue<int> q;

	for (int i = 1; i <= n; ++i)
	{
		q.push(i);
	}

	while (q.size() != 1)
	{
		for (int i = 0; i < k - 1; ++i)
		{
			int front = q.front();
			q.pop();
			q.push(front);
		}
		cout << q.front() << " Is Excuted" << endl;
		q.pop();
	}

	return q.front();
}

int main()
{
	int n = 7, k = 3; // set n and k to the desired values

	//Queue<int> q(n + 1);
	//q.SetDebugFlag(false);

	// 처음에 n명 추가 (1, 2, ..., n)
	//for (int i = 1; i <= n; i++)
	//	q.Enqueue(i);
	//q.Print();

	std::cout << "Answer is " << Solution(4, 3) << endl;
	std::cout << "Answer is " << Solution(5, 2) << endl;
	std::cout << "Answer is " << Solution(7, 3) << endl;

	// 마지막 한 명이 남을 때까지 반복
	{
		// k-1 명은 맨 앞에서 뒤로 보내기

		// k 번째 사람 처형
		// cout << "Executed " << ... << endl;
	}

	// 최후의 생존자 번호
	// cout << "Survivor: " << ... << endl;

	return 0;
}