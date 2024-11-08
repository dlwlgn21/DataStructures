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
	K Key = K();	// first
	V Value = V();	// second
};

struct Node
{
	Item Item;

	Node* pLeft = nullptr;
	Node* pRight = nullptr;
};

void Preorder()
{
	using namespace std;
	Preorder(mpRoot);
	cout << endl;
}

void Preorder(Node* pNode)
{
	using namespace std;
	if (pNode != nullptr)
	{
		cout << pNode->Item.Key << " ";
		Preorder(pNode->pLeft);
		Preorder(pNode->pRight);
	}
}

void Inorder()
{
	using namespace std;
	Inorder(mpRoot);
	cout << endl;
}

void Inorder(Node* pNode)
{
	using namespace std;
	if (pNode)
	{
		Inorder(pNode->pLeft);
		cout << pNode->Item.Key << " ";
		Inorder(pNode->pRight);
	}
}

Item* RecurGet(const K& key)
{
	return RecurGet(mpRoot, key);
}

Item* RecurGet(Node* pNode, const K& key)
{
	if (pNode == nullptr) 
		return nullptr; // <- 동일한 키를 가진 노드를 찾지 못하면 nullptr을 반환하는 기능

	if (key < pNode->Item.Key)
		return RecurGet(pNode->pLeft, key);
	if (key > pNode->Item.Key)
		return RecurGet(pNode->pRight, key);

	return &pNode->Item; // if (key == node->item.key)
}

Item* IterGetOrNull(const K& key)
{
	if (mpRoot == nullptr) return nullptr;
	Node* pNode = mpRoot;
	while (true)
	{
		if (pNode == nullptr) return nullptr;

		if (key < pNode->Item.Key) pNode = pNode->pLeft;
		else if (key > pNode->Item.Key) pNode = pNode->pRight;
		else return &pNode->Item;
	}

	return nullptr; // No matching
}

void Insert(const Item& item)
{
	using namespace std;
	cout << "Insert " << item.Key << item.Value << endl;
	mpRoot = InsertRecursive(mpRoot, item);
}

Node* InsertRecursive(Node* pNode, const Item& item)
{
	// 힌트: RecurGet()
	if (pNode == nullptr)
	{
		Node* pNew = new Node();
		pNew->Item = item;
		return pNew;
	}

	if (item.Key < pNode->Item.Key)			pNode->pLeft = InsertRecursive(pNode->pLeft, item);
	else if (item.Key > pNode->Item.Key)	pNode->pRight = InsertRecursive(pNode->pRight, item);
	else									pNode->Item.Value = item.Value;
	return pNode;
}

void IterInsert(const Item& item)
{
	if (mpRoot == nullptr)
	{
		Node* pNew = new Node();
		pNew->Item = item;
		mpRoot = pNew;
		return;
	}

	Node* pNode = mpRoot;
	Node* pCache = mpRoot;
	while (true)
	{
		if (pNode == nullptr)
		{
			Node* pNew = new Node();
			pNew->Item = item;
			if (item.Value < pCache->Item.Value) pCache->pLeft = pNew;
			if (item.Value > pCache->Item.Value) pCache->pRight = pNew;
			return;
		}
		pCache = pNode;
		if (item.Key < pNode->Item.Key)			pNode = pNode->pLeft;
		else if (item.Key > pNode->Item.Key)	pNode = pNode->pRight;
		else 
		{
			pNode->Item.Value = item.Value; 
			return;
		}
	}
}

Node* GetMinKeyNodeFromRightSubTree(Node* pNode)
{
	assert(pNode != nullptr);
	while (pNode->pLeft != nullptr)
	{
		pNode = pNode->pLeft;
	}
	return pNode;
}

void Remove(const K& key)
{
	using namespace std;
	cout << "Remove " << key << endl;
	mpRoot = RemoveRecursive(mpRoot, key);
}

Node* RemoveRecursive(Node* pNode, const K& key)
{
	if (pNode == nullptr) return pNode;

	if (key < pNode->Item.Key)
		pNode->pLeft = RemoveRecursive(pNode->pLeft, key);
	else if (key > pNode->Item.Key)
		pNode->pRight = RemoveRecursive(pNode->pRight, key);
	else
	{
		// Case Only One Child
		if (pNode->pLeft == nullptr)
		{
			Node* pRight = pNode->pRight;
			delete pNode;
			return pRight;

		}
		else if (pNode->pRight == nullptr)
		{
			Node* pLeft = pNode->pLeft;
			delete pNode;
			return pLeft;
		}

		// Case Two Children
		Node* pMinNode = GetMinKeyNodeFromRightSubTree(pNode->pRight);
		pNode->Item.Key = pMinNode->Item.Key;
		pNode->Item.Value = pMinNode->Item.Value;
		pNode->pRight = RemoveRecursive(pNode->pRight, pMinNode->Item.Key);
		return pNode;

	}

	return pNode;
}

int Height()
{
	return Height(mpRoot);
}

int Height(Node* pNode)
{
	if (pNode == nullptr) return 0;
	return 1 + std::max(Height(pNode->pLeft), Height(pNode->pRight));
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
			int result = ((p->Item.Key <= 1) ? 1 : (int)log10(p->Item.Key) + 1);
			cout << " " << p->Item.Key << p->Item.Value << " ";
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