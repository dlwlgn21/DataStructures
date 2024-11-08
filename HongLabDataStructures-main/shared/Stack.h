#pragma once

#include <cassert>
#include <iostream>

template<typename T> // 템플릿 사용
class Stack
{
public:
	Stack(int capacity = 128)
	{
		assert(capacity > 0);
		Resize(capacity);
	}

	~Stack()
	{
		if (mpStack != nullptr) delete[] mpStack;
	}

	void Resize(int new_capacity)
	{
		T* pNewStack = new T[new_capacity];
		memcpy(pNewStack, mpStack, sizeof(T) * Size());
		if (mpStack != nullptr) delete[] mpStack;
		mpStack = pNewStack;
		mCapacity = new_capacity;
	}

	bool IsEmpty() const
	{
		if (mTopIdx < 0)
		{
			return true;
		}
		return false;
	}

	int Size() const
	{
		return mTopIdx + 1;
	}

	void Print()
	{
		using namespace std;

		for (int i = 0; i < Size(); i++) // Size() 사용
			cout << mpStack[i] << " ";
		cout << endl;
	}

	// Returns TOP element of stack.
	T& Top() const
	{
		assert(!IsEmpty());
		return mpStack[mTopIdx];
	}

	// Insert item into the TOP of the stack
	void Push(const T& item)
	{
		// TODO: 필요하면 리사이즈 
		if (Size() >= mCapacity)
		{
			Resize(mCapacity * 2);
		}
		mpStack[++mTopIdx] = item;
	}

	// Delete the TOP element of the stack
	void Pop()
	{
		assert(!IsEmpty());
		--mTopIdx;
	}

protected: // 뒤에서 상속해서 사용
	T* mpStack = nullptr;
	int mTopIdx = -1; // 0 아님
	int mCapacity = 0;
};
