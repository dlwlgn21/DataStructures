#pragma once

#include <cassert>
#include <iostream>
#include <iomanip>

template<typename T>
class Queue // Circular Queue
{
public:
	Queue(int capacity = 2)
	{
		assert(capacity > 0);

		mCapa = capacity;
		mpQue = new T[mCapa];
		mFront = mRear = 0;
	}

	~Queue()
	{
		if (mpQue) delete[] mpQue;
	}

	bool IsEmpty() const
	{
		return mFront == mRear;
	}

	bool IsFull() const
	{
		// 원형 큐에서 꽉 찼다의 기준
		return (mRear + 1) % mCapa == mFront;
	}

	T& Front() const
	{
		assert(!IsEmpty());
		return mpQue[(mFront + 1) % mCapa]; // 주의 + 1
	}

	T& Rear() const
	{
		assert(!IsEmpty());
		return mpQue[mRear];
	}

	int Size() const
	{
		// 하나하나 세는 방법 보다는 경우를 따져서 바로 계산하는 것이 빠릅니다.
		if (mFront <= mRear)
			return mRear - mFront;
		else
			return mCapa - (mFront - mRear);
	}

	void Resize() // 2배씩 증가
	{
		// 조언
		// - 새로운 개념이 항상 그렇듯 원형 큐도 처음에는 어렵고 나중에는 당연해집니다.
		// - 처음 공부하실 때 답을 맞추려고 하지 마시고 "어떻게 디버깅을 잘 할까?"를 찾으세요.
		// - 부지런히 여러가지 출력해보고 "출력하는 도구(예: 배열 출력)"도 만들어서 사용해보고
		// - 머리도 쓰고 고민도 하다 보면 인생을 지탱해줄 능력을 갖추게 됩니다.
		// - 힘들면 디스코드에서 조금씩 도움 받으시는 것도 좋아요.

		// TODO: 하나하나 복사하는 방식은 쉽게 구현할 수 있습니다. 
		//       (도전) 경우를 나눠서 memcpy()로 블럭 단위로 복사하면 더 효율적입니다.
		mCapa = mCapa << 1;
		T* p = new T[mCapa];
		int oriCapa = mCapa >> 1;
		if (mFront < mRear)
		{
			memcpy(p, mpQue, sizeof(T) * (oriCapa));
			mFront = 0;
		}
		else
		{
			memcpy(p + 1, mpQue + mFront + 1, sizeof(T) * (oriCapa - mFront - 1));
			memcpy(p + (oriCapa - mFront - 1) + 1, mpQue, sizeof(T) * (mRear + 1));
			mFront = 0;
			mRear = (oriCapa - 1);
		}
		delete[] mpQue;
		mpQue = p;
	}

	void Enqueue(const T& item) // 맨 뒤에 추가, Push()
	{
		if (IsFull())
			Resize();
		mRear = (mRear + 1) % mCapa;
		mpQue[mRear] = item;
	}

	void Dequeue() // 큐의 첫 요소 삭제, Pop()
	{
		assert(!IsEmpty());
		mFront = (mFront + 1) % mCapa;
	}

	void Print()
	{
		using namespace std;

		for (int i = (mFront + 1) % mCapa; i != (mRear + 1) % mCapa; i = (i + 1) % mCapa)
			cout << mpQue[i] << " ";
		cout << endl;

		if (mbIsPrintDebug)
			PrintDebug();
	}

	void PrintDebug()
	{
		using namespace std;

		cout << "Cap = " << mCapa << ", Size = " << Size();
		cout << endl;

		// front와 rear 위치 표시
		for (int i = 0; i < mCapa; i++) {
			if (i == mFront) cout << " F ";
			else if (i == mRear) cout << " R ";
			else cout << "   ";
		}
		cout << endl;

		// 0 based index
		for (int i = 0; i < mCapa; i++)
			cout << setw(2) << i << " ";
		cout << endl;

		if (mFront < mRear)
		{
			// front 앞 사용하지 않은 공간
			for (int i = 0; i < mFront + 1; i++)
				cout << " - ";

			// 저장된 내용물
			for (int i = mFront + 1; i <= mRear; i++)
				cout << setw(2) << mpQue[i] << " ";

			// rear 뒤 사용하지 않은 공간
			for (int i = mRear + 1; i < mCapa; i++)
				cout << " * ";

			cout << endl << endl;
		}
		else if (mFront > mRear)
		{
			// rear 이전에 저장된 내용물
			for (int i = 0; i <= mRear; i++)
				cout << setw(2) << mpQue[i] << " ";

			// rear와 front 사이 사용하지 않은 공간
			for (int i = mRear + 1; i <= mFront; i++)
				cout << " * ";

			// front 뒤 내용물
			for (int i = mFront + 1; i < mCapa; i++)
				cout << setw(2) << mpQue[i] << " ";

			cout << endl << endl;
		}
		else // 비었을 경우
		{
			for (int i = 0; i < mCapa; i++)
				cout << " - ";
			cout << endl << endl;
		}
	}

	void SetDebugFlag(bool flag)
	{
		mbIsPrintDebug = flag;
	}

protected: // 뒤에서 상속해서 사용
	T* mpQue; // array for queue elements
	int mFront = 0; // 시작 인덱스보다 하나 작은 값
	int mRear = 0; // 마지막 인덱스 (첫 값은 1에 추가)
	int mCapa; // 빈 칸을 하나 둬야 하기 때문에 필요 메모리는 최대 저장량 + 1
	bool mbIsPrintDebug = false;
};
