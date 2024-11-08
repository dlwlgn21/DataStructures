#pragma once

//#include "Queue.h"
#include "../shared/Queue.h"

#include <cassert>
#include <iostream>
#include <iomanip>

// Double Ended Queue (덱, dequeue와 구분)
template<typename T>
class Deque : public Queue<T>
{
	typedef Queue<T> Base;
public:
	Deque(int capacity)
		: Base(capacity)
	{
	}

	T& Front()
	{
		return Base::Front();
	}

	T& Back()
	{
		return Base::Rear();
	}

	void PushFront(const T& item)
	{
		if (Base::IsFull())
			Base::Resize();
		Base::mpArr[Base::mFrontIdx] = item;
		Base::mFrontIdx = (Base::mFrontIdx - 1 + Base::mCapacity) % Base::mCapacity;
	}

	void PushBack(const T& item)
	{
		Base::Enqueue(item);
	}

	void PopFront()
	{
		Base::Dequeue();
	}

	void PopBack()
	{
		assert(!Base::IsEmpty());
		Base::mRearIdx = (Base::mRearIdx - 1 + Base::mCapacity) % Base::mCapacity;
	}


};
