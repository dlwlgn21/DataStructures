#include "SparseMatrix.h"

#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

bool Cmp(const MatrixTerm& a, const MatrixTerm& b)
{
	if (a.row == b.row)
		return a.col < b.col;
	return a.row < b.row;
}

SparseMatrix::SparseMatrix(int num_rows, int num_cols, int capacity)
{
	// TODO:
	mNumRows = num_rows;
	mNumCols = num_cols;
	mCapacity = capacity;
	mNumTerms = 0;
	mpTerms = new MatrixTerm[mCapacity];
}

// 복사 생성자 (b를 복사)
SparseMatrix::SparseMatrix(const SparseMatrix& b)
{
	// TODO:
}

SparseMatrix::~SparseMatrix()
{
	// TODO:
	delete[] mpTerms;
}

void SparseMatrix::SetValue(int row, int col, float value)
{
	if (value == 0.0f) return; // value가 0이 아닌 term만 저장
	MatrixTerm mat = { row, col, value };
	mpTerms[mNumTerms++] = mat;
	if (mNumTerms > 1)
		std::sort(mpTerms[0], mpTerms[mNumTerms], Cmp);
}

float SparseMatrix::GetValue(int row, int col) const // 맨 뒤의 const는 함수 안에서 멤버 변수의 값을 바꾸지 않겠다는 의미
{
	// TODO: key = col + num_cols * row;
	
	return 0.0f;
}

SparseMatrix SparseMatrix::Transpose()
{
	SparseMatrix temp(mNumCols, mNumRows, mCapacity); // num_cols_, num_rows_ 순서 주의

	// TODO:

	return temp;
}

void SparseMatrix::PrintTerms()
{
	for (int i = 0; i < mNumTerms; i++)
		cout << "(" << mpTerms[i].row
		<< ", " << mpTerms[i].col
		<< ", " << mpTerms[i].value
		<< ")" << endl;
}

void SparseMatrix::Print()
{
	for (int r = 0; r < mNumRows; r++)
	{
		for (int c = 0; c < mNumCols; c++)
			cout << GetValue(r, c) << " ";
		cout << endl;
	}
}
