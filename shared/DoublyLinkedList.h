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
		T item = T();

		Node* pLeft = nullptr;
		Node* pRight = nullptr;
	};

	DoublyLinkedList()
	{
	}

	~DoublyLinkedList()
	{
		Clear();
	}

	void Clear() // 모두 지워야(delete) 합니다.
	{
		// TODO:
		Node* pCurr = mpRoot;
		while (pCurr != nullptr)
		{
			Node* pTmp = pCurr->pRight;
			delete pCurr;
			pCurr = pTmp;
		}
	}

	bool IsEmpty()
	{
		return mpRoot == nullptr;
	}

	int Size()
	{
		int size = 0;

		Node* pCurr = mpRoot;
		while (pCurr != nullptr)
		{
			++size;
			pCurr = pCurr->pRight;
		}
		return size;
	}

	void Print()
	{
		using namespace std;

		Node* pCurr = mpRoot;
		Node* pPrev = pCurr;
		if (IsEmpty())
			cout << "Empty" << endl;
		else
		{
			cout << "Size = " << Size() << endl;

			cout << " Forward: ";
			// TODO:
			while (pCurr != nullptr)
			{
				cout << pCurr->item << " ";
				pPrev = pCurr;
				pCurr = pCurr->pRight;
			}
			cout << endl;

			cout << "Backward: ";
			// TODO:
			pCurr = pPrev;
			while (pCurr != nullptr)
			{
				cout << pCurr->item << " ";
				pCurr = pCurr->pLeft;
			}
			cout << endl;
		}
	}

	Node* Find(T item)
	{
		Node* pCurr = mpRoot;
		while (pCurr != nullptr)
		{
			if (pCurr->item == item)
				return pCurr;
			pCurr = pCurr->pRight;
		}
		return nullptr; // TODO:
	}

	void InsertBack(Node* pNode, T item)
	{
		if (IsEmpty())
		{
			PushBack(item);
		}
		else
		{
			Node* pRight = pNode->pRight;
			Node* pNewNode = new Node();
			pNewNode->item = item;
			pNode->pRight = pNewNode;
			pNewNode->pRight = pRight;
			pNewNode->pLeft = pNode;
			if (pRight != nullptr)
				pRight->pLeft = pNewNode;
		}
	}

	void PushFront(T item)
	{
		Node* pNewNode = new Node();
		pNewNode->item = item;
		if (mpRoot != nullptr)
			mpRoot->pLeft = pNewNode;
		pNewNode->pLeft = nullptr;
		pNewNode->pRight = mpRoot;
		mpRoot = pNewNode;
	}

	void PushBack(T item)
	{
		// TODO:
		if (mpRoot == nullptr)
		{
			PushFront(item);
			return;
		}
		Node* pCurr = mpRoot;
		while (pCurr->pRight != nullptr)
			pCurr = pCurr->pRight;

		Node* pNewNode = new Node();
		pNewNode->item = item;
		pNewNode->pLeft = pCurr;
		pCurr->pRight = pNewNode;
	}

	void PopFront()
	{
		if (IsEmpty())
		{
			using namespace std;
			cout << "Nothing to Pop in PopFront()" << endl;
			return;
		}

		assert(mpRoot);

		Node* pRight = mpRoot->pRight;
		delete mpRoot;
		mpRoot = pRight;
		if (mpRoot != nullptr)
			pRight->pLeft = nullptr;
	}

	void PopBack()
	{
		if (IsEmpty())
		{
			using namespace std;
			cout << "Nothing to Pop in PopBack()" << endl;
			return;
		}

		assert(mpRoot);
		Node* pCurr = mpRoot;
		while (pCurr->pRight != nullptr)
			pCurr = pCurr->pRight;

		Node* pLeft = pCurr->pLeft;
		if (pLeft != nullptr)
			pLeft->pRight = nullptr;
		else
			mpRoot = nullptr;
		delete pCurr;
	}

	void Reverse()
	{
		Node* pCurr = mpRoot;
		while (pCurr != nullptr)
		{
			Node* pNext = pCurr->pRight;
			if (pNext == nullptr)
			{
				mpRoot = pCurr;
			}
			Node* pTmp = pCurr->pLeft;
			pCurr->pLeft = pCurr->pRight;
			pCurr->pRight = pTmp;
			pCurr = pNext;
		}
	}

	T Front()
	{
		assert(mpRoot);

		return mpRoot->item; // TODO:
	}

	T Back()
	{
		assert(mpRoot);
		Node* pCurr = mpRoot;
		while (pCurr->pRight != nullptr)
			pCurr = pCurr->pRight;
		return pCurr->item; // TODO:
	}

protected:
	Node* mpRoot = nullptr;
};