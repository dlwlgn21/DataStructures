#include <iostream>
#include <cassert>
#include <algorithm> // swap
#include <iomanip> // setw

using namespace std;

int Fibonacci(int n)
{
	if (n == 0)
		return 0; // F0 = 0 
	else if (n == 1)
		return 1; // F1 = 1
	else
	{
		int f0 = 0;
		int f1 = 1;
		int fn = f0 + f1;
		for (int i = 2; i <= n; ++i)
		{
			fn = f0 + f1;
			f0 = f1;
			f1 = fn;
		}
		return fn;
	}
}
int dp[1024];
int RecurFibonacci(int n)
{
	if (n == 1)
		return dp[1];
	if (n == 0)
		return dp[0];

	if (dp[n] == 0)
	{
		dp[n] = RecurFibonacci(n - 2) + RecurFibonacci(n - 1);
		return dp[n];
	}
	else
	{
		return dp[n];
	}
};

int main()
{
	// Input      : 0   1   2   3   4   5   6   7   8   9  10  11  12  13  14
	// Fibonnacci : 0   1   1   2   3   5   8  13  21  34  55  89 144 233 377
	// Fibonnacci : 0   1   1   2   3   5   8  13  21  34  55  89 144 233 377
	dp[0] = 0;
	dp[1] = 1;
	cout << "Input     : ";
	for (int i = 0; i < 20; i++)
		cout << setw(3) << i << " ";
	cout << endl;

	// Fibonnacci
	cout << "Fibonnacci: ";
	for (int i = 0; i < 20; i++)
		cout << setw(3) << Fibonacci(i) << " ";
	cout << endl;

	cout << "Fibonnacci: ";
	for (int i = 0; i < 20; i++)
		cout << setw(3) << RecurFibonacci(i) << " ";
	cout << endl;

	return 0;
}
