#pragma once

#include <cassert>
#include <stdint.h>

template<typename T>
class SinglyLinkedList
{
public:
	struct Node
	{
		T item = T();
		Node* pNext = nullptr;
	};

	SinglyLinkedList()
	{
	}

	SinglyLinkedList(const SinglyLinkedList& list)
	{
		// TODO: 연결 리스트 복사
		Node* pOther = list.mpRoot;
		while (pOther != nullptr)
		{
			PushBack(pOther->item);
			pOther = pOther->pNext;
		}
	}

	~SinglyLinkedList()
	{
		Clear();
	}

	void Clear() // 모두 지워야(delete) 합니다.
	{
		Node* pCurr = mpRoot;
		while (pCurr != nullptr)
		{
			Node* pTmp = pCurr;
			pCurr = pCurr->pNext;
			delete pTmp;
		}
	}

	bool IsEmpty()
	{
		return mpRoot == nullptr;
	}

	int Size()
	{
		int size = 0;

		// TODO: size를 하나하나 세어서 반환
		Node* pCurr = mpRoot;
		while (pCurr != nullptr)
		{
			++size;
			pCurr = pCurr->pNext;
		}

		return size;
	}

	T Front()
	{
		assert(mpRoot);

		return mpRoot->item; // TODO: 수정
	}

	T Back()
	{
		assert(mpRoot);
		Node* pCurr = mpRoot;
		while (pCurr->pNext != nullptr)
		{
			pCurr = pCurr->pNext;
		}
		return pCurr->item; // TODO: 수정
	}

	Node* Find(T item)
	{
		Node* pCurr = mpRoot;
		while (pCurr != nullptr)
		{
			if (pCurr->item == item)
				return pCurr;
			pCurr = pCurr->pNext;
		}
		return nullptr;
	}

	void InsertBack(Node* pNode, T item)
	{
		// TODO:
		if (pNode == nullptr)
			return;
		Node* pOriNext = pNode->pNext;
		Node* pNewNode = new Node();
		pNewNode->item = item;
		pNode->pNext = pNewNode;
		pNewNode->pNext = pOriNext;
	}

	void Remove(Node* pNode)
	{
		assert(mpRoot);
		// 하나 앞의 노드를 찾아야 합니다.
		// TODO:
		if (pNode == mpRoot)
		{
			delete pNode;
			mpRoot = nullptr;
			return;
		}

		Node* pCurr = mpRoot;
		Node* pPrev = pCurr;
		while (pCurr != nullptr)
		{
			if (pCurr == pNode)
			{
				break;
			}
			pPrev = pCurr;
			pCurr = pCurr->pNext;
		}
		pPrev->pNext = pNode->pNext;
		delete pNode;
	}

	void PushFront(T item)
	{
		Node* pNewNode = new Node();
		pNewNode->item = item;
		pNewNode->pNext = mpRoot;
		mpRoot = pNewNode;
	}

	void PushBack(T item)
	{
		Node* pCurr = mpRoot;
		Node* pNewNode = new Node();
		pNewNode->item = item;
		if (pCurr != nullptr)
		{
			while (pCurr->pNext != nullptr)
				pCurr = pCurr->pNext;
			pCurr->pNext = pNewNode;
		}
		else
		{
			mpRoot = pNewNode;
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

		assert(mpRoot != nullptr);
		Node* pTmp = mpRoot->pNext;
		delete mpRoot;
		mpRoot = pTmp;
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

		assert(mpRoot != nullptr);
		Node* pCurr = mpRoot;
		Node* pPrev = pCurr;
		while (pCurr->pNext != nullptr)
		{
			pPrev = pCurr;
			pCurr = pCurr->pNext;
		}
		delete pCurr;
		pPrev->pNext = nullptr;
	}

	void Reverse()
	{
		// TODO: 
		if (Size() > 1)
		{
			Node* pReverseNext = nullptr;
			Node* pCurr = mpRoot;
			Node* pTmp = nullptr;
			while (pCurr != nullptr)
			{
				pTmp = pCurr->pNext;
				pCurr->pNext = pReverseNext;
				pReverseNext = pCurr;
				pCurr = pTmp;
			}
			mpRoot = pReverseNext;
		}
	}

	void SetPrintDebug(bool flag)
	{
		mbIsPrintDebug = flag;
	}

	void Print()
	{
		using namespace std;

		Node* current = mpRoot;

		if (IsEmpty())
			cout << "Empty" << endl;
		else
		{
			cout << "Size = " << Size() << " ";

			while (current)
			{
				if (mbIsPrintDebug)
				{
					//cout << "[" << current << ", " << current->item << ", " << current->next << "]";

					// 주소를 짧은 정수로 출력 (앞 부분은 대부분 동일하기때문에 뒷부분만 출력)
					cout << "[" << reinterpret_cast<uintptr_t>(current) % 100000 << ", "
						<< current->item << ", "
						<< reinterpret_cast<uintptr_t>(current->pNext) % 100000 << "]";
				}
				else
				{
					cout << current->item;
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
	Node* mpRoot = nullptr;
	bool mbIsPrintDebug = false;
};