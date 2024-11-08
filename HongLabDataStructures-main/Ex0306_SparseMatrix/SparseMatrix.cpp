#include "SparseMatrix.h"

#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

SparseMatrix::SparseMatrix(int num_rows, int num_cols, int capacity)
{
	mpTerms = new MatrixTerm[capacity];
	mCapacity = capacity;
	mNumRow = num_rows;
	mNumCol = num_cols;
	mNumTerms = 0;
}

// 복사 생성자 (b를 복사)
SparseMatrix::SparseMatrix(const SparseMatrix& b)
{
	mpTerms = new MatrixTerm[b.mCapacity];
	mCapacity = b.mCapacity;
	mNumRow = b.mNumRow;
	mNumCol = b.mNumCol;
	mNumTerms = b.mNumTerms;

	for (int i = 0; i < mNumTerms; ++i)
	{
		mpTerms[i].Row = b.mpTerms[i].Row;
		mpTerms[i].Col = b.mpTerms[i].Col;
		mpTerms[i].Value = b.mpTerms[i].Value;
	}
}

SparseMatrix::~SparseMatrix()
{
	if (mpTerms != nullptr) delete[] mpTerms;
}

void SparseMatrix::SetValue(int row, int col, float value)
{
	if (value == 0.0f) return; // value가 0이 아닌 term만 저장
	assert(mNumTerms <= mCapacity);

	
	int key = row * mNumCol + col;
	int insertIdx = 0;
	for (; insertIdx < mNumTerms; ++insertIdx)
	{
		int iKey = mpTerms[insertIdx].Row * mNumCol + mpTerms[insertIdx].Col;
		// 덮어 쓰기
		if (key == iKey)
		{
			mpTerms[insertIdx].Row = row;
			mpTerms[insertIdx].Col = col;
			mpTerms[insertIdx].Value = value;
			return;
		}

		if (iKey > key)
		{
			break;
		}
	}

	++mNumTerms;
	for (int j = mNumTerms - 1; j > insertIdx; --j)
	{
		mpTerms[j].Row = mpTerms[j - 1].Row;
		mpTerms[j].Col = mpTerms[j - 1].Col;
		mpTerms[j].Value = mpTerms[j - 1].Value;
	}

	mpTerms[insertIdx].Row = row;
	mpTerms[insertIdx].Col = col;
	mpTerms[insertIdx].Value = value;
}

float SparseMatrix::GetValue(int row, int col) const // 맨 뒤의 const는 함수 안에서 멤버 변수의 값을 바꾸지 않겠다는 의미
{
	// TODO: key = col + num_cols * row;
	int key = mNumCol * row + col;
	for (int i = 0; i < mNumTerms; ++i)
	{
		int hasKey = mpTerms[i].Row * mNumCol + mpTerms[i].Col;
		if (key == hasKey)
		{
			return mpTerms[i].Value;
		}
		else if (hasKey > key)
		{
			return 0.0f;
		}
	}
	return 0.0f;
}

SparseMatrix SparseMatrix::Transpose()
{
	SparseMatrix temp(mNumCol, mNumRow, mCapacity); // num_cols_, num_rows_ 순서 주의
	for (int i = 0; i < mNumTerms; ++i)
	{
		temp.SetValue(mpTerms[i].Col, mpTerms[i].Row, mpTerms[i].Value);
	}
	return temp;
}

void SparseMatrix::PrintTerms()
{
	for (int i = 0; i < mNumTerms; i++)
		cout << "(" << mpTerms[i].Row
		<< ", " << mpTerms[i].Col
		<< ", " << mpTerms[i].Value
		<< ")" << endl;
}

void SparseMatrix::Print()
{
	for (int r = 0; r < mNumRow; r++)
	{
		for (int c = 0; c < mNumCol; c++)
			cout << GetValue(r, c) << " ";
		cout << endl;
	}
}
