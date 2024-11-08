#include <iostream>

#include "../shared/Stack.h"

using namespace std;

constexpr int kNumRows = 10;
constexpr int kNumCols = 9;
const int DIR[4][2]
{
	{1, 0},
	{-1, 0},
	{0, 1},
	{0, -1}
};
char maze[kNumRows][kNumCols] =
{
	{'1', '1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', 'S', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '0', '1', '0', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '1', '1', '1', '1', '1', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '1', '0', '1', '1', '1'},
	{'1', '1', '1', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', 'G', '1'}, // <- 'G'를 만나면 종료
	{'1', '1', '1', '1', '1', '1', '1', '1', '1'},
};

void PrintMaze()
{
	for (int j = 0; j < kNumRows; j++)
	{
		for (int i = 0; i < kNumCols; i++)
			cout << maze[j][i] << " ";
		cout << endl;
	}
}

struct Pos
{
	int row;
	int col;

	// 디버깅을 위한 편의 기능
	friend ostream& operator<<(ostream& os, const Pos& pos)
	{
		cout << "(" << pos.row << ", " << pos.col << ")" << flush;
		return os;
	}
};

void RecurMaze(Pos p)
{
	const char mark = maze[p.row][p.col];
	maze[p.row][p.col] = 'X';
	if (mark == 'G')
	{
		cout << "Found!" << endl;
		return;
	}

	for (int i = 0; i < 4; ++i)
	{
		const int ny = p.row + DIR[i][0];
		const int nx = p.col + DIR[i][1];
		if (maze[ny][nx] == '0')
		{

			RecurMaze({ny, nx});
		}
	}

}

//조기 종료가 가능한 버전
bool RecurMazes(Pos p)
{
	const char mark = maze[p.row][p.col];
	if (mark == 'G')
	{
		cout << "Found!" << endl;
		return true;
	}

	if (mark != 'X' && mark != '1')
	{
		maze[p.row][p.col] = 'X';
		if (RecurMazes({ p.row + 1, p.col })) return true;
		if (RecurMazes({ p.row - 1, p.col })) return true;
		if (RecurMazes({ p.row, p.col + 1})) return true;
		if (RecurMazes({ p.row, p.col - 1})) return true;
	}
	return false;
}

void StackMaze()
{
	Stack<Pos> s;

	Pos start = { 1, 1 }; // i = 1, j = 1  시작 지점
	//Pos start;
	//start.row = 1;
	//start.col = 1;

	s.Push(start); // s.Push({1, 1});

	// s.Print(); // 디버깅에 사용 가능

	while (!s.IsEmpty())
	{
		Pos p = s.Top();
		s.Pop();
		const char mark = maze[p.row][p.col];
		if (mark == 'G')
		{
			cout << "Found!" << endl;
			break;
		}
		maze[p.row][p.col] = 'X';
		for (int i = 0; i < 4; ++i)
		{
			const int ny = p.row + DIR[i][0];
			const int nx = p.col + DIR[i][1];
			if (maze[ny][nx] == '0')
			{
				s.Push({ny, nx});
			}
		}
	}
}

int main()
{
	PrintMaze();

	//RecurMaze({ 1, 1 });

	//StackMaze();

	RecurMazes({1, 1});
	PrintMaze();

	return 0;
}

