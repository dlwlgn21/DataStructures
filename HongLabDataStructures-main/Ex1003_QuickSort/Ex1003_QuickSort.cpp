#include <iostream>
#include <iomanip>
#include <math.h>
#include <random>
#include <assert.h>

using namespace std;

bool CheckSorted(int* arr, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		if (arr[i] > arr[i + 1])
			return false;
	}

	return true;
}

void Print(int* arr, int low, int high, int n)
{
	for (int i = 0; i < n; i++)
		if (i >= low && i <= high)
			cout << setw(3) << arr[i] << " ";
		else
			cout << "    ";
	cout << endl;
}

// Hoare partition scheme
int Partition(int arr[], int low, int high, int n)
{
	int pivot = arr[(low + high) / 2];
	int i = low - 1;
	int j = high + 1;

	while (true)
	{
		do 
		{
			++i;
		} 
		while (arr[i] < pivot);

		do 
		{
			--j;
		} 
		while (arr[j] > pivot);

		if (i >= j)
		{
			return j;
		}
		std::swap(arr[i], arr[j]);

		cout << "pivot=" << pivot << ", i=" << i << ", j=" << j << endl;
		cout << "         ";
		Print(arr, low, high, n);
	}
}

void QuickSort(int arr[], int low, int high, int n) // 마지막 n은 출력용
{
	if (low >= 0 && high >= 0 && low < high)
	{
		// Partitioning Index
		int p = Partition(arr, low, high, n);
		QuickSort(arr, low, p, n); // Note: the pivot is now included
		QuickSort(arr, p + 1, high, n);
	}
}

int main()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 60);
	const int SIZE = 20;
	int arr[SIZE];
	for (int i = 0; i < SIZE; ++i)
	{
		arr[i] = dist(gen);
	}
	arr[0] = 15;
	arr[6] = 15;
	//int arr[] = { 4, 17, 2, 9, 7, 5, 8, 1, 14, 6 };
	//int arr[] = { 4, 17, 2, 9, 7, 5, 8, 1, 14, 6 };
	int n = SIZE;

	cout << "         ";
	Print(arr, 0, n - 1, n);
	cout << endl;

	QuickSort(arr, 0, n - 1, n);
	assert(CheckSorted(arr, SIZE));
	cout << "         ";
	Print(arr, 0, n - 1, n);
	cout << endl;
}
