#pragma once

#include <cassert>
#include <stdint.h>
#include <algorithm>

template<typename T>
class DoublyLinkedList
{
public:
	struct Node
	{
		T Item = T();

		Node* pLeft = nullptr;
		Node* pRight = nullptr;
	};

	DoublyLinkedList()
	{
	}
	DoublyLinkedList(const DoublyLinkedList<T>& other)
	{
		Node* pIter = other.mpHead;
		while (pIter != nullptr)
		{
			PushBack(pIter->Item);
			pIter = pIter->pRight;
		}
	}
	~DoublyLinkedList()
	{
		Clear();
	}

	void Clear() // 모두 지워야(delete) 합니다.
	{
		Node* pIter = mpHead;
		while (pIter != nullptr)
		{
			Node* pRight = pIter->pRight;
			delete pIter;
			pIter = pRight;
		}
	}

	bool IsEmpty()
	{
		return mpHead == nullptr;
	}

	int Size()
	{
		if (mpHead == nullptr)
		{
			return 0;
		}
		int size = 0;
		Node* pIter = mpHead;
		while (pIter != nullptr)
		{
			++size;
			pIter = pIter->pRight;
		}
		return size;
	}

	void Print()
	{
		using namespace std;

		Node* current = mpHead;

		if (IsEmpty())
			cout << "Empty" << endl;
		else
		{
			cout << "Size = " << Size() << endl;

			cout << " Forward: ";
			Node* pIter = mpHead;
			Node* pLastIter = mpHead;
			while (pIter != nullptr)
			{
				cout << pIter->Item << "-> ";
				pLastIter = pIter;
				pIter = pIter->pRight;
			}
			cout << " NULL ";
			cout << endl;

			cout << "Backward: ";
			while (pLastIter != nullptr)
			{
				cout << pLastIter->Item << "-> ";
				pLastIter = pLastIter->pLeft;
			}
			cout << " NULL ";
			cout << endl;
		}
	}

	Node* Find(T item)
	{
		if (mpHead == nullptr)	return nullptr;
		
		Node* pIter = mpHead;
		while (pIter != nullptr)
		{
			if (pIter->Item == item)
			{
				return pIter;
			}
			pIter = pIter->pRight;
		}
		return nullptr;
	}

	void InsertBack(Node* pNode, T item)
	{
		if (IsEmpty())
		{
			PushBack(item);
		}
		else
		{
			Node* pTmpRight = pNode->pRight;
			Node* pNew = new Node();
			pNode->pRight = pNew;
			pNew->Item = item;
			pNew->pLeft = pNode;
			pNew->pRight = pTmpRight;
			if (pTmpRight != nullptr)
			{
				pTmpRight->pLeft = pNew;
			}
		}
	}

	void PushFront(T item)
	{
		Node* pNew = new Node();
		pNew->Item = item;
		if (mpHead != nullptr)
		{
			mpHead->pLeft = pNew;
			pNew->pRight = mpHead;
			pNew->pLeft = nullptr;
		}
		mpHead = pNew;
	}

	void PushBack(T item)
	{
		Node* pIter = mpHead;
		if (pIter == nullptr)
		{
			PushFront(item);
			return;
		}

		while (pIter->pRight != nullptr)
		{
			pIter = pIter->pRight;
		}
		Node* pNew = new Node();
		pNew->Item = item;
		pIter->pRight = pNew;
		pNew->pLeft = pIter;
		pNew->pRight = nullptr;
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

		Node* pRight = mpHead->pRight;
		delete mpHead;
		mpHead = pRight;
		if (mpHead == nullptr)	return;
		mpHead->pLeft = nullptr;
	}

	void PopBack()
	{
		if (IsEmpty())
		{
			using namespace std;
			cout << "Nothing to Pop in PopBack()" << endl;
			return;
		}

		assert(mpHead != nullptr);
		Node* pIter = mpHead;
		while (pIter->pRight != nullptr)
		{
			pIter = pIter->pRight;
		}
		Node* pLeft = pIter->pLeft;
		if (pLeft == nullptr)	mpHead = nullptr;
		else					pLeft->pRight = nullptr;
		delete pIter;
	}

	void Reverse()
	{
		if (mpHead == nullptr)
		{
			return;
		}
		Node* pIter = mpHead;
		while (pIter != nullptr)
		{
			Node* pRight = pIter->pRight;
			std::swap(pIter->pLeft, pIter->pRight);
			if (pRight == nullptr)
			{
				mpHead = pIter;
				break;
			}
			pIter = pRight;
		}
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
		while (pIter->pRight != nullptr)
		{
			pIter = pIter->pRight;
		}
		return pIter->Item;
	}

protected:
	Node* mpHead = nullptr;
};