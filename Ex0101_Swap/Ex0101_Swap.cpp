#include <iostream>

using namespace std;

void MySwapPtr(int* i, int* j)
{
	int tmp = *i;
	*i = *j;
	*j = tmp;
}

void MySwapRef(int& i, int& j)
{
	int tmp = i;
	i = j;
	j = tmp;
}

bool CheckSorted(int a, int b)
{
	return a <= b;
}

int main()
{
	// Swap
	//{
	//	int a = 3;
	//	int b = 2;

	//	cout << a << " " << b << endl;

	//	// TODO:
	//	int tmp = a;
	//	a = b;
	//	b = tmp;

	//	cout << a << " " << b << endl;
	//}


	// 정렬(sorting)
	{
		int arr[] = { 6, 13 };

		cout << arr[0] << " " << arr[1] << endl;

		// TODO:
		if (arr[0] > arr[1])
			MySwapRef(arr[0], arr[1]);

		cout << arr[0] << " " << arr[1] << endl;
	}

	// 값과 상관 없이 항상 작은 값이 먼저 출력되게 하려면?
	// 두 값이 같을 때는 순서가 상관 없음 -> 큰 값이 먼저 출력되지 않게 하려면?
	{
		int arr[2];

		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				arr[0] = j;
				arr[1] = i;
				if (arr[0] > arr[1])
				{
					MySwapRef(arr[0], arr[1]);
				}
				cout << arr[0] << " " << arr[1] << " " << " true\n";
			}
		}
	}

	return 0;
}
