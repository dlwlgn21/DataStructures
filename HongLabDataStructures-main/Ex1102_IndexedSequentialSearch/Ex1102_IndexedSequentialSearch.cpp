#include <iostream>

using namespace std;

int SequentialSearch(int arr[], int start, int stop, int x)
{
	for (int i = start; i < stop; i++)
	{
		if (arr[i] == x)
			return i;
	}

	return -1;
}

int GetClosestKeyIndex(int keys[], int x, int size)
{
	for (int i = 0; i < size; ++i)
	{
		if (keys[i] > x)
		{
			return i;
		}
	}
}

int main()
{
	int arr[] = { 1, 2, 8, 13, 22, 45, 55, 75, 88 };
	int n = sizeof(arr) / sizeof(arr[0]);

	int keys[] = { 1, 13, 55 };
	int keyN = sizeof(keys) / sizeof(keys[0]);


	int indices[] = { 0, 3, 6, n }; // 마지막에 n 하나 더 추가

	for (int x : {1, 2, 8, 13, 22, 45, 55, 75, 88, 99, -1, 47, 101, 1000, 7, 10, 50, 60 })
	{
		if (x < arr[0] || x > arr[n - 1])
			cout << x << " was not found" << endl;
		else
		{
			// TODO: 
			int idx = GetClosestKeyIndex(keys, x, keyN);
			int startIdx = indices[idx - 1];
			int endIdx = indices[idx];
			int findIdx = SequentialSearch(arr, startIdx, endIdx, x);
			if (findIdx < 0) cout << x << " was Not found" << endl;
			else  cout << x << " was found at " << findIdx << endl;
		}
	}

	return 0;
}
