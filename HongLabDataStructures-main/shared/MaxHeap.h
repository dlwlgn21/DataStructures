#pragma once

#include <cassert>
#include <iostream>
#include <iomanip>

template<typename T>
class MaxHeap
{
public:
MaxHeap(int cap = 128)
{
	assert(cap > 0);

	mCapacity = cap;
	mSize = 0;
	mpArr = new T[mCapacity + 1]; // heap[0]은 비워둡니다.
}

void Resize(int new_capacity)
{
	T* pNew = new T[new_capacity];
	memcpy(pNew, mpArr, sizeof(T) * (mSize + 1)); // +1 주의
	if (mpArr != nullptr) delete[] mpArr;
	mpArr = pNew;
	mCapacity = new_capacity;
}

T Top()
{
	return mpArr[1]; // 1번 인덱스 자리
}

bool IsEmpty()
{
	return mSize == 0;
}

void Print()
{
	using namespace std;
	cout << "Index: ";
	for (int i = 1; i <= mSize; i++)
		cout << setw(3) << i;
	cout << endl;

	cout << "Value: ";
	for (int i = 1; i <= mSize; i++)
		cout << setw(3) << mpArr[i];
	cout << endl << endl;
}

void Push(const T& newItem)
{
	//using namespace std;
	//cout << "Push " << item << endl;

	if (mSize == mCapacity)
		Resize(mCapacity * 2);

	// 삽입: 일단 맨 마지막에 삽입한 후에 부모 노드로 올린다.

	mSize += 1;
	int currIdx = mSize; // 마지막에 추가가될 위치 (인덱스)

	while (currIdx != 1) 
	{
		T parentVal = mpArr[currIdx / 2];
		if (parentVal < newItem) 
		{
			mpArr[currIdx] = parentVal;			// 부모 위치의 값이 추가하려는 값보다 작다면 부모값을 넣으려는 위치에 복사하고,
			currIdx /= 2;						// 부모로 올라감.
		}
		else						break;
		//cout << "Current = " << current << endl;
		//Print();

		// TODO:
	}

	mpArr[currIdx] = newItem; // 최종적으로 결정된 위치에 복사
}

void Pop()
{
	assert(!IsEmpty());

	//using namespace std;
	//cout << "Pop()" << endl;

	// heap[1].~T(); // 소멸자 호출 

	// 삭제: 가장 마지막 값을 루트로 옮긴 후에 내려 보낸다.

	T lastItem = mpArr[mSize]; // 마지막 아이템 복사
	--mSize;					// 크기 줄이기

	int currIdx = 1;						// 루트 노드에서 시작
	int childIdx = currIdx * 2;				// current * 2 (루트의 왼쪽 자식 인덱스)
	while (childIdx <= mSize)
	{
		// left, right 중에서 더 큰 자식의 인덱스를 찾는다. 이때 자식이 하나라면 찾을 필요 없음
		// TODO:
		int nextCurrIdx = 0;
		T biggerChildItem = mpArr[childIdx];
		if (childIdx + 1 <= mSize)
		{
			if (mpArr[childIdx] > mpArr[childIdx + 1])
			{
				biggerChildItem = mpArr[childIdx];
				nextCurrIdx = childIdx;
			}
			else
			{
				biggerChildItem = mpArr[childIdx + 1];
				nextCurrIdx = childIdx + 1;
			}
		}
		else
		{
			nextCurrIdx = childIdx;
		}

		if (biggerChildItem < lastItem)
		{
			// 현재(current) 값이 더 큰 자식의 값 이상이면 더이상 적절한 위치를 찾을 필요가 없기 때문에 루프 중단
			break;
		}
		else
		{
			// 자식 값을 부모 위치로 복사, 
			mpArr[currIdx] = biggerChildItem;
			// 그 자식 위치로 current 인덱스 변경, child 인덱스도 그 다음 자식 위치로 변경
			currIdx = nextCurrIdx;
			childIdx = currIdx * 2;
		}
	}

	mpArr[currIdx] = lastItem;
}

private:
T* mpArr = nullptr;
int mSize = 0;
int mCapacity = 0;
};

