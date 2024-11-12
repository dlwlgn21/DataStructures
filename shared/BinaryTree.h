#pragma once

#include <iostream>
#include <fstream>
#include <string> // BinaryTree 출력

#include "Queue.h"
#include "Stack.h"

template<typename T>
class BinaryTree
{
public:
	struct Node
	{
		T item = T();
		Node* pLeft = nullptr; // Left child
		Node* pRight = nullptr; // Right child
	};

	// 디버깅 도구: 큐에서 주소 대신에 아이템 출력
	class MyQueue : public Queue<Node*>
	{
	public:
		void Print()
		{
			using namespace std;

			for (int i = (this->front_ + 1) % this->capacity_; i != (this->rear_ + 1) % this->capacity_; i = (i + 1) % this->capacity_)
				cout << this->queue_[i]->item << " ";
			cout << endl;
		}
	};

	// 디버깅 도구: 스택에서 주소 대신에 아이템 출력
	class MyStack : public Stack<Node*>
	{
	public:
		void Print()
		{
			using namespace std;

			for (int i = 0; i < this->Size(); i++)
				cout << this->stack_[i]->item << " ";
			cout << endl;
		}
	};

	BinaryTree() {}

	BinaryTree(Node* root)
	{
		mpRoot = root;
	}

	bool IsEmpty()
	{
		return mpRoot == nullptr;
	}

	void Visit(Node* node)
	{
		using namespace std;
		cout << node->item << " "; // 수행하고 싶은 작업 구현(여기서는 출력)
	}

	int Sum()
	{
		return GetSumRecur(mpRoot);
	}

	int GetSumRecur(Node* pNode)
	{
		if (pNode == nullptr)
			return 0;
		return GetSumRecur(pNode->pLeft) + GetSumRecur(pNode->pRight) + pNode->item; // TODO:
	}

	int Height()
	{
		return GetHeightRecur(mpRoot);
	}

	int GetHeightRecur(Node* pNode)
	{
		int height = 1;
		if (pNode->pLeft != nullptr)
			height = std::max(GetHeightRecur(pNode->pLeft) + 1, height);
		if (pNode->pRight != nullptr)
			height = std::max(GetHeightRecur(pNode->pRight) + 1, height);
		return height;
	}

	~BinaryTree()
	{
		DeleteTreeRecur(mpRoot);
	}

	void DeleteTreeRecur(Node* pNode)
	{
		if (pNode == nullptr)
			return;
		DeleteTreeRecur(pNode->pLeft);
		DeleteTreeRecur(pNode->pRight);
		delete pNode;
	}

	void Preorder() { PreorderRecur(mpRoot); }
	void PreorderRecur(Node* pNode)
	{
		if (pNode == nullptr)
			return;
		Visit(pNode);
		PreorderRecur(pNode->pLeft);
		PreorderRecur(pNode->pRight);
	};

	void Inorder() { InorderRecur(mpRoot); }
	void InorderRecur(Node* pNode)
	{
		if (pNode == nullptr)
			return;
		InorderRecur(pNode->pLeft);
		Visit(pNode);
		InorderRecur(pNode->pRight);
	}

	void Postorder() { PostorderRecur(mpRoot); }
	void PostorderRecur(Node* pNode)
	{
		if (pNode == nullptr)
			return;
		PostorderRecur(pNode->pLeft);
		PostorderRecur(pNode->pRight);
		Visit(pNode);
	}

	void LevelOrder()
	{
		Queue<Node*> q; // 힌트: MyQueue q;
		Node* pCurr = mpRoot;
		q.Enqueue(pCurr);
		while (!q.IsEmpty())
		{
			pCurr = q.Front();
			Visit(pCurr);
			q.Dequeue();
			if (pCurr->pLeft != nullptr)
				q.Enqueue(pCurr->pLeft);
			if (pCurr->pRight != nullptr)
				q.Enqueue(pCurr->pRight);
		}
	}

	void IterPreorder()
	{
		if (!mpRoot) return;

		Stack<Node*> s; // 힌트: MyStack q;
		s.Push(mpRoot);

		while (!s.IsEmpty())
		{
			// TODO:
		}
	}

	void IterInorder()
	{
		if (!mpRoot) return;

		Stack<Node*> s;

		Node* current = mpRoot;
		while (current || !s.IsEmpty())
		{
			// TODO:
		}
	}

	void IterPostorder()
	{
		if (!mpRoot) return;

		Stack<Node*> s1, s2;
		s1.Push(mpRoot);

		while (!s1.IsEmpty())
		{
			// TODO:
		}

		while (!s2.IsEmpty())
		{
			// TODO:
		}
	}

	void Print2D();
	void PrintLevel(int n);
	void DisplayLevel(Node* p, int lv, int d);

protected:
	Node* mpRoot = nullptr;
};

// 디버깅 편의 도구
// https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
template<typename T>
void BinaryTree<T>::Print2D()
{
	using namespace std;
	int i = 0;
	while (i < Height()) {
		PrintLevel(i);
		i++;
		cout << endl;
	}
}

template<typename T>
void BinaryTree<T>::PrintLevel(int n) {
	using namespace std;
	Node* temp = mpRoot;
	int val = (int)pow(2.0, Height() - n + 1.0);
	cout << setw(val) << "";
	DisplayLevel(temp, n, val);
}

template<typename T>
void BinaryTree<T>::DisplayLevel(Node* p, int lv, int d) {
	using namespace std;
	int disp = 2 * d;
	if (lv == 0) {
		if (p == NULL) {
			cout << "   ";
			cout << setw(disp - 3) << "";
			return;
		}
		else {
			int result = ((p->item <= 1) ? 1 : (int)log10(p->item) + 1);
			cout << " " << p->item << " ";
			cout << setw(static_cast<streamsize>(disp) - result - 2) << "";
		}
	}
	else
	{
		if (p == NULL && lv >= 1) {
			DisplayLevel(NULL, lv - 1, d);
			DisplayLevel(NULL, lv - 1, d);
		}
		else {
			DisplayLevel(p->pLeft, lv - 1, d);
			DisplayLevel(p->pRight, lv - 1, d);
		}
	}
}
