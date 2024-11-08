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
		T Item = T();
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

	BinaryTree(Node* pRoot)
	{
		assert(pRoot != nullptr);
		mpRoot = pRoot;
	}

	bool IsEmpty()
	{
		return mpRoot == nullptr;
	}

	void Visit(Node* pNode)
	{
		using namespace std;
		cout << pNode->Item << " "; // 수행하고 싶은 작업 구현(여기서는 출력)
	}

	int Sum()
	{
		return SumRecursive(mpRoot);
	}

	int SumRecursive(Node* pNode)
	{
		if (pNode == nullptr)	return 0;
		return SumRecursive(pNode->pLeft) + SumRecursive(pNode->pRight) + pNode->Item;
	}

	int Height()
	{
		return HeightRecursive(mpRoot);
	}

	int HeightRecursive(Node* pNode)
	{
		if (pNode == nullptr)
		{
			return 0;
		}
		return 1 + std::max(HeightRecursive(pNode->pLeft), HeightRecursive(pNode->pRight));
	}

	~BinaryTree()
	{
		DeleteTreeRecursive(mpRoot);
	}

	void DeleteTreeRecursive(Node* pNode)
	{
		if (pNode == nullptr)	return;
		DeleteTreeRecursive(pNode->pLeft);
		DeleteTreeRecursive(pNode->pRight);
		delete pNode;
	}

	void Preorder() { PreorderRecursive(mpRoot); }
	void PreorderRecursive(Node* pNode)
	{
		if (pNode == nullptr)	return;
		Visit(pNode);
		PreorderRecursive(pNode->pLeft);
		PreorderRecursive(pNode->pRight);
	};

	void Inorder() { InorderRecursive(mpRoot); }
	void InorderRecursive(Node* pNode)
	{
		if (pNode == nullptr)	return;
		InorderRecursive(pNode->pLeft);
		Visit(pNode);
		InorderRecursive(pNode->pRight);
	}

	void Postorder() { PostorderRecursive(mpRoot); }
	void PostorderRecursive(Node* pNode)
	{
		if (pNode == nullptr)	return;
		PostorderRecursive(pNode->pLeft);
		PostorderRecursive(pNode->pRight);
		Visit(pNode);
	}

	void LevelOrder()
	{
		Queue<Node*> q; // 힌트: MyQueue q;
		Node* current = mpRoot;
		assert(mpRoot != nullptr);
		q.Enqueue(current);
		while (!q.IsEmpty())
		{
			Node* pNode = q.Front();
			Visit(pNode);
			q.Dequeue();
			if (pNode->pLeft != nullptr)	q.Enqueue(pNode->pLeft);
			if (pNode->pRight != nullptr)	q.Enqueue(pNode->pRight);
		}
	}

	void IterPreorder()
	{
		if (mpRoot == nullptr) return;

		MyStack s; // 힌트: MyStack q;
		s.Push(mpRoot);

		while (!s.IsEmpty())
		{
			Node* pNode = s.Top();
			s.Pop();
			Visit(pNode);
			if (pNode->pRight != nullptr) s.Push(pNode->pRight);
			if (pNode->pLeft != nullptr) s.Push(pNode->pLeft);
		}
	}

	void IterInorder()
	{
		if (mpRoot == nullptr) return;

		MyStack s;
		Node* current = mpRoot;
		s.Push(current);
		while (!s.IsEmpty())
		{
			Node* pNode = s.Top();
			s.Pop();
			if (pNode->pRight != nullptr) 
			{
				s.Push(pNode->pRight);
			}
			if (pNode->pLeft != nullptr)
			{
				s.Push(pNode->pLeft);
			}

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
			int result = ((p->Item <= 1) ? 1 : (int)log10(p->Item) + 1);
			cout << " " << p->Item << " ";
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
