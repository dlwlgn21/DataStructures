#include <iostream>

#include "../shared/SinglyLinkedList.h"

using namespace std;
typedef SinglyLinkedList<int>::Node ListNode;
int main()
{
	SinglyLinkedList<int> list;
	// Original Test
	{
		list.SetPrintDebug(false);

		list.PushFront(3);
		list.PushBack(4);
		list.PushFront(2);
		list.PushFront(1);
		list.PushBack(5);

		list.Print();

		// copy constructor
		{
			SinglyLinkedList<int> list2 = list; // copy constructor
			list2.SetPrintDebug(false);
			list2.Print();
		}

		list.Reverse();
		list.Print();
		SinglyLinkedList<int>::Node* temp = list.Find(3);
		list.InsertBack(temp, 1000);
		list.Print();

		list.InsertBack(temp, 50);
		list.Print();
		list.Remove(temp);
		list.Print();

		// PopFront()/Back() 테스트
		std::cout << "PopFront/Back TEST" << std::endl;
		for (int i = 0; i < 5; i++)
		{
			list.PopFront();
			list.Print();

			list.PopBack();
			list.Print();

			if (!list.IsEmpty())
				cout << list.Front() << " " << list.Back() << endl;
		}

		// Edge case 테스트 주의

	}

	list.SetPrintDebug(true);
/*
#pragma region PUSH_BACK_TEST
	list.PushBack(1);
	list.Print();
	list.PushBack(2);
	list.Print();
	list.PushBack(3);
	list.Print();
	list.PushBack(4);
	list.Print();
	list.PushBack(5);
	list.Print();
#pragma endregion

#pragma region FIND_TEST
	//ListNode* pNode = list.Find(1);
	//assert(pNode != nullptr);
	//pNode = list.Find(2);
	//assert(pNode != nullptr);
	//pNode = list.Find(3);
	//assert(pNode != nullptr);
	//pNode = list.Find(4);
	//assert(pNode != nullptr);
	//pNode = list.Find(5);
	//assert(pNode != nullptr);
	//pNode = list.Find(10);
	//assert(pNode == nullptr);
#pragma endregion

#pragma region REMOVE_TEST
	//list.Remove(list.Find(3));
	//list.Print();
	//list.Remove(list.Find(5));
	//list.Print();
	//list.Remove(list.Find(1));
	//list.Print();
	//list.Remove(list.Find(4));
	//list.Print();
	//list.Remove(list.Find(2));
	//list.Print();
#pragma endregion

#pragma region PUSH_FRONT_TEST
	list.PushFront(18);
	list.Print();
	list.PushFront(19);
	list.Print();
#pragma endregion


#pragma region POP_FRONT_TEST
	//list.PopFront();
	//list.Print();
	//list.PopFront();
	//list.Print();
#pragma endregion
#pragma region POP_BACK_TEST
	//list.PopBack();
	//list.Print();
	//list.PopBack();
	//list.Print();
#pragma endregion
*/

	return 0;
}
