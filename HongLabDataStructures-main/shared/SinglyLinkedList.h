#pragma once

#include <cassert>
#include <stdint.h>

template<typename T>
class SinglyLinkedList
{
public:
	struct Node
	{
		T Item = T();
		Node* pNext = nullptr;
	};

	SinglyLinkedList()
	{
	}

	SinglyLinkedList(const SinglyLinkedList& other)
	{
		Node* pOtherCurrent = other.mpHead;
		while (pOtherCurrent != nullptr)
		{
			PushBack(pOtherCurrent->Item);
			pOtherCurrent = pOtherCurrent->pNext;
		}
	}

	~SinglyLinkedList()
	{
		Clear();
	}

	void Clear() // 모두 지워야(delete) 합니다.
	{
		Node* pIter = mpHead;
		if (pIter != nullptr)
		{
			Node* pNext = pIter->pNext;
			delete pIter;
			pIter = pNext;
		}
	}

	bool IsEmpty()
	{
		return mpHead == nullptr;
	}

	int Size()
	{
		int size = 0;
		if (mpHead == nullptr)
		{
			return 0;
		}
		Node* pIter = mpHead;
		while (pIter != nullptr)
		{
			++size;
			pIter = pIter->pNext;
		}
		return size;
	}

	T Front()
	{
		assert(mpHead != nullptr);

		return mpHead->Item;
	}

	T Back()
	{
		assert(mpHead != nullptr);
		Node* pIter = mpHead;
		while (pIter->pNext != nullptr) 
		{
			pIter = pIter->pNext;
		}
		return pIter->Item;
	}

	Node* Find(T item)
	{
		// TODO: item이 동일한 노드 포인터 반환
		if (mpHead == nullptr)
		{
			return nullptr;
		}

		Node* pIter = mpHead;
		while (pIter != nullptr)
		{
			if (item == pIter->Item)
			{
				return pIter;
			}
			pIter = pIter->pNext;
		}
		return nullptr;
	}

	void InsertBack(Node* pNode, T item)
	{
		assert(pNode != nullptr);

		Node* pNew = new Node();
		pNew->Item = item;

		Node* pTmpNext = pNode->pNext;
		pNode->pNext = pNew;
		pNew->pNext = pTmpNext;
	}

	void Remove(Node* pNode)
	{
		assert(mpHead != nullptr && pNode != nullptr);
		if (mpHead == pNode)
		{
			Node* pTmp = mpHead;
			if (mpHead->pNext != nullptr)
			{
				mpHead = mpHead->pNext;
				delete pTmp;
				return;
			}
			else
			{
				delete pTmp;
				mpHead = nullptr;
				return;
			}
		}

		// 하나 앞의 노드를 찾아야 합니다.
		// TODO:
		Node* pCurrent = mpHead;
		Node* pPrev = mpHead;
		while (pCurrent != nullptr)
		{
			pPrev = pCurrent;
			pCurrent = pCurrent->pNext;
			if (pCurrent != nullptr)
			{
				if (pCurrent == pNode)
				{
					break;
				}
			}
			else
			{
				// NO FOUND
				std::cout << "In Remove() No Found pNode" << std::endl;
				return;
			}
		}

		pPrev->pNext = pCurrent->pNext;
		delete pCurrent;
	}

	void PushFront(T item)
	{
		Node* pNew = new Node();
		pNew->Item = item;

		pNew->pNext = mpHead;
		mpHead = pNew;
	}

	void PushBack(T item)
	{
		if (mpHead != nullptr)
		{
			Node* pIter = mpHead;

			while (pIter->pNext != nullptr)
			{
				pIter = pIter->pNext;
			}

			pIter->pNext = new Node();
			pIter->pNext->Item = item;
		}
		else
		{
			mpHead = new Node();
			mpHead->Item = item;
		}
	}

	void PopFront()
	{
		if (IsEmpty())
		{
			using namespace std;
			cout << "Nothing to Pop in PopFront()" << endl;
			return;
		}

		assert(mpHead != nullptr);
		Node* pTmp = mpHead->pNext;
		delete mpHead;
		mpHead = pTmp;
	}

	void PopBack()
	{
		if (IsEmpty())
		{
			using namespace std;
			cout << "Nothing to Pop in PopBack()" << endl;
			return;
		}

		// 맨 뒤에서 하나 앞의 노드를 찾아야 합니다.

		assert(mpHead != nullptr);
		if (mpHead->pNext == nullptr)
		{
			PopFront();
			return;
		}

		// More than One
		Node* pCurrent = mpHead;
		Node* pPrev = mpHead;
		while (pCurrent->pNext != nullptr)
		{
			pPrev = pCurrent;
			pCurrent = pCurrent->pNext;
		}

		delete pCurrent;
		pPrev->pNext = nullptr;

	}

	void Reverse()
	{
		if (mpHead == nullptr)
		{
			return;
		}
		Node* pCurrIter = mpHead;
		Node* pPrev = nullptr;
		Node* pNext = mpHead;
		while (pNext != nullptr)
		{
			pNext = pCurrIter->pNext;
			if (pNext == nullptr) break;
			pCurrIter->pNext = pPrev;
			pPrev = pCurrIter;
			pCurrIter = pNext;
		}

		mpHead = pCurrIter;
		mpHead->pNext = pPrev;
	

	}

	void SetPrintDebug(bool bFlag)
	{
		mbIsDebuggingMode = bFlag;
	}

	void Print()
	{
		using namespace std;

		Node* current = mpHead;

		if (IsEmpty())
			cout << "Empty" << endl;
		else
		{
			cout << "Size = " << Size() << " ";

			while (current)
			{
				if (mbIsDebuggingMode)
				{
					//cout << "[" << current << ", " << current->item << ", " << current->next << "]";

					// 주소를 짧은 정수로 출력 (앞 부분은 대부분 동일하기때문에 뒷부분만 출력)
					cout << "[" << reinterpret_cast<uintptr_t>(current) % 100000 << ", "
						<< current->Item << ", "
						<< reinterpret_cast<uintptr_t>(current->pNext) % 100000 << "]";
				}
				else
				{
					cout << current->Item;
				}

				if (current->pNext)
					cout << " -> ";
				else
					cout << " -> NULL";

				current = current->pNext;
			}
			cout << endl;
		}
	}

protected:
	Node* mpHead = nullptr;

	bool mbIsDebuggingMode = false;
};