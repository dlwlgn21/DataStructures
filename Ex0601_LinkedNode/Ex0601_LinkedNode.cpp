#include <iostream>

using namespace std;

struct Node
{
	int item = 0;	  // <- 큰 데이터도 가능
	Node* pNext = nullptr;

	friend ostream& operator<<(ostream& os, const Node& n)
	{
		cout << "[" << &n << ", " << n.item << ", " << n.pNext << "]" << flush;
		return os;
	}
};

void RecurPrint(Node* pNode)
{
	// TODO:
	if (pNode != nullptr)
	{
		cout << *pNode << endl;
		RecurPrint(pNode->pNext);
	}
}

void IterPrint(Node* pNode)
{
	// TODO:
	Node* pCurr = pNode;
	while (pCurr != nullptr)
	{
		cout << *pCurr << endl;
		pCurr = pCurr->pNext;
	}
}

int main()
{
	// ListArray와 비교

	Node* first = nullptr;
	first = new Node;
	first->item = 1;
	first->pNext = nullptr;

	Node* second = nullptr;
	second = new Node;
	second->item = 2;
	second->pNext = nullptr;

	Node* third = nullptr;
	third = new Node;
	third->item = 3;
	third->pNext = nullptr;

	Node* fourth = nullptr;
	fourth = new Node;
	fourth->item = 4;
	fourth->pNext = nullptr;

	Node* fifth = nullptr;
	fifth = new Node;
	fifth->item = 5;
	fifth->pNext = nullptr;

	// 계속 추가 가능

	//cout << *first << endl;
	//cout << *second << endl;
	//cout << *third << endl;
	//cout << *fourth << endl;
	//cout << *fifth << endl;
	cout << endl;

	// 연결 관계 만들어 주기
	 first->pNext = second;
	 second->pNext = third;
	 third->pNext = fourth;
	 fourth->pNext = fifth;
	// 마지막

	//cout << *(first) << endl;
	//cout << *(first->pNext) << endl;
	//cout << *(first->pNext->pNext) << endl;
	//cout << *(first->pNext->pNext->pNext) << endl;
	//cout << *(first->pNext->pNext->pNext->pNext) << endl;
	//// cout << *(first->next->next->next->next->next) << endl; // 오류

	cout << endl;

	// 임시 변수 사용
	//{
	//	cout << "While!!" << endl;
	//	Node* pCurr = first;
	//	while (pCurr != nullptr)
	//	{
	//		cout << *pCurr << endl;
	//		pCurr = pCurr->pNext;
	//	}
	//	cout << endl;
	//}

	// 재귀 호출 이용
	RecurPrint(first);
	cout << endl;

	// 반복문 이용
	IterPrint(first);
	cout << endl;

	// TODO: 데이터 삭제
	Node* pCurr = first;
	while (pCurr != nullptr)
	{
		Node* pDelete = pCurr;
		pCurr = pCurr->pNext;
		delete pDelete;
	}

	return 0;
}
