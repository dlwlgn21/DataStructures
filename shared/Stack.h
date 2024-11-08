#pragma once

#include <cassert>
#include <iostream>

template<typename T> // 템플릿 사용
class Stack
{
public:
	Stack(int capacity = 1)
	{
		assert(capacity > 0);
		Resize(capacity);
	}

	~Stack()
	{
		if (mpStack) delete[] mpStack;
	}

	void Resize(int newCapacity)
	{
		T* new_stack = new T[newCapacity];
		memcpy(new_stack, mpStack, sizeof(T) * Size());
		if (mpStack) delete[] mpStack;
		mpStack = new_stack;
		mCapacity = newCapacity;
	}

	bool IsEmpty() const
	{
		return mTop < 0;
	}

	int Size() const
	{
		return mTop + 1; //TODO:
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

		return mpStack[mTop];
	}

	// Insert item into the TOP of the stack
	void Push(const T& item)
	{
		if (Size() >= mCapacity)
			Resize(mCapacity * 2);
		mpStack[++mTop] = item;
	}

	// Delete the TOP element of the stack
	void Pop()
	{
		assert(!IsEmpty());
		--mTop;
	}

protected: // 뒤에서 상속해서 사용
	T* mpStack = nullptr;
	int mTop = -1; // 0 아님
	int mCapacity = 0;
};
