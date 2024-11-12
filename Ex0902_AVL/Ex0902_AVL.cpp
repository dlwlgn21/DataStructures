#include <iostream>

#include "../shared/AVL.h"

using namespace std;

int main()
{
	using Item = AVL<int, char>::Item;

	AVL<int, char> bst;

	for (int i : { 9, 8, 7, 6, 5, 4, 3, 2, 1 })
		//for (int i : { 1, 2, 3, 4, 5, 6, 7, 8, 9 })
	{
		bst.Insert(Item{ i, char('A' + i) });
		bst.Print2D();
	}

	bst.Inorder(); // key에 대해 정렬

	cout << bst.RecurGetOrNull(5)->value << endl;
	cout << bst.RecurGetOrNull(3)->value << endl;
	cout << bst.RecurGetOrNull(7)->value << endl;
	cout << bst.RecurGetOrNull(1)->value << endl;
	cout << bst.RecurGetOrNull(4)->value << endl;

	for (int i : {5, 4, 7, 8, 9})
	{
		bst.Remove(i);
		bst.Print2D();
	}

	return 0;
}
