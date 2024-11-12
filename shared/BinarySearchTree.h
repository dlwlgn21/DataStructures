#pragma once

#include <iomanip>
#include <cassert>
#include <iostream>

template<typename K, typename V>
class BinarySearchTree
{
public:
	struct Item // key와 value의 쌍(pair)
	{
		K key = K();	// first
		V value = V();	// second
	};

	struct Node
	{
		Item item;

		Node* pLeft = nullptr;
		Node* pRight = nullptr;
		Node(Item item, Node* pLeft, Node* pRight)
		{
			this->item = item;
			this->pLeft = pLeft;
			this->pRight = pRight;
		}
	};

	void Preorder()
	{
		using namespace std;
		Preorder(mpRoot);
		cout << endl;
	}

	void PreorderRecur(Node* pNode)
	{
		using namespace std;
		if (pNode)
		{
			cout << pNode->item.key << " ";
			PreorderRecur(pNode->pLeft);
			PreorderRecur(pNode->pRight);
		}
	}

	void Inorder()
	{
		using namespace std;
		InorderRecur(mpRoot);
		cout << endl;
	}

	void InorderRecur(Node* pNode)
	{
		using namespace std;
		if (pNode)
		{
			InorderRecur(pNode->pLeft);
			cout << pNode->item.key << " ";
			InorderRecur(pNode->pRight);
		}
	}

	Item* RecurGetOrNull(const K& key)
	{
		return RecurGetOrNull(mpRoot, key);
	}

	Item* RecurGetOrNull(Node* pNode, const K& key)
	{
		if (!pNode) return nullptr; // <- 동일한 키를 가진 노드를 찾지 못하면 nullptr을 반환하는 기능

		if (key < pNode->item.key)
			return RecurGetOrNull(pNode->pLeft, key);
		if (key > pNode->item.key)
			return RecurGetOrNull(pNode->pRight, key);

		return &pNode->item; // if (key == node->item.key)
	}

	Item* IterGetOrNull(const K& key)
	{
		// TODO:
		Node* pCurr = mpRoot;
		while (pCurr != nullptr)
		{
			if (pCurr->item.key == key)
				return &pCurr->item;

			if (key < pCurr->item.key)
				pCurr = pCurr->pLeft;
			else
				pCurr = pCurr->pRight;
		}
		return nullptr;
	}

	void Insert(const Item& item)
	{
		using namespace std;
		cout << "Insert " << item.key << item.value << endl;
		mpRoot = InsertRecur(mpRoot, item);
	}

	Node* InsertRecur(Node* pNode, const Item& item)
	{
		if (pNode == nullptr)
			return new Node(item, nullptr, nullptr);

		if (item.key < pNode->item.key)
			pNode->pLeft = InsertRecur(pNode->pLeft, item);
		else if (item.key > pNode->item.key)
			pNode->pRight = InsertRecur(pNode->pRight, item);
		else
		{
			pNode->item = item;
			return pNode;
		}
		return pNode;
	}

	void IterInsert(const Item& item)
	{
		if (mpRoot == nullptr)
		{
			mpRoot = new Node(item, nullptr, nullptr);
			return;
		}
		Node* pCurr = mpRoot;
		Node* pPrev = pCurr;
		while (pCurr != nullptr)
		{
			pPrev = pCurr;
			if (item.key < pCurr->item.key)
				pCurr = pCurr->pLeft;
			else if (item.key > pCurr->item.key)
				pCurr = pCurr->pRight;
			else
			{
				pCurr->item = item;
				return;
			}
		}
		Node* pNewNode = new Node(item, nullptr, nullptr);
		if (item.key < pPrev->item.key)
			pPrev->pLeft = pNewNode;
		else
			pPrev->pRight = pNewNode;
	}

	Node* GetMinKeyNodeFromRightSubTree(Node* pNode)
	{
		assert(pNode);
		while (pNode->pLeft != nullptr)
			pNode = pNode->pLeft;
		return pNode;
	}

	void Remove(const K& key)
	{
		using namespace std;
		cout << "Remove " << key << endl;
		mpRoot = RemoveRecur(mpRoot, key);
	}

	Node* RemoveRecur(Node* pNode, const K& key)
	{
		if (pNode == nullptr) 
			return pNode;

		if (key < pNode->item.key)
			pNode->pLeft = RemoveRecur(pNode->pLeft, key);
		else if (key > pNode->item.key)
			pNode->pRight = RemoveRecur(pNode->pRight, key);
		else
		{
			if (pNode->pLeft == nullptr && pNode->pRight == nullptr)
			{
				delete pNode;
				return nullptr;
			}

			if (pNode->pRight == nullptr)
			{
				Node* pLeft = pNode->pLeft;
				pNode->item = pLeft->item;
				delete pLeft;
				pNode->pLeft = nullptr;
				return pNode;
			}
			else if (pNode->pLeft == nullptr)
			{
				Node* pRight = pNode->pRight;
				pNode->item = pRight->item;
				delete pRight;
				pNode->pRight = nullptr;
				return pNode;
			}
			else
			{
				Node* pMinNode = GetMinKeyNodeFromRightSubTree(pNode->pRight);
				pNode->item = pMinNode->item;
				pNode->pRight = RemoveRecur(pNode->pRight, pNode->item.key);
				return pNode;
			}
		}

		return pNode;
	}

	int Height()
	{
		return GetHeightRecur(mpRoot);
	}

	int GetHeightRecur(Node* pNode)
	{
		if (!pNode) return 0;
		return 1 + std::max(GetHeightRecur(pNode->pLeft), GetHeightRecur(pNode->pRight));
	}

	void Print2D();
	void PrintLevel(int n);
	void DisplayLevel(Node* p, int lv, int d);

protected:
	Node* mpRoot = nullptr;
};

// 디버깅 편의 도구
// https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
template<typename K, typename V>
void BinarySearchTree<K, V>::Print2D()
{
	using namespace std;
	cout << "Height = " << Height() << endl;
	int i = 0;
	while (i < Height()) {
		PrintLevel(i);
		i++;
		cout << endl;
	}
	cout << endl;
}

template<typename K, typename V>
void BinarySearchTree<K, V>::PrintLevel(int n) {
	using namespace std;
	Node* temp = mpRoot;
	int val = (int)pow(2.0, Height() - n + 1.0);
	cout << setw(val) << "";
	DisplayLevel(temp, n, val);
}

template<typename K, typename V>
void BinarySearchTree<K, V>::DisplayLevel(Node* p, int lv, int d) {
	using namespace std;
	int disp = 2 * d;
	if (lv == 0) {
		if (p == NULL) {
			cout << "   ";
			cout << setw(disp - 3) << "";
			return;
		}
		else {
			int result = ((p->item.key <= 1) ? 1 : (int)log10(p->item.key) + 1);
			cout << " " << p->item.key << p->item.value << " ";
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
