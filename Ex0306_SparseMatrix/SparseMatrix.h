#pragma once

struct MatrixTerm
{
	int row;
	int col;
	float value;
};

class SparseMatrix
{
public:
	SparseMatrix(int num_rows, int num_cols, int capacity);

	SparseMatrix(const SparseMatrix& b);

	~SparseMatrix();

	void SetValue(int row, int col, float value); // NewTerm()

	float GetValue(int row, int col) const;

	SparseMatrix Transpose();

	void PrintTerms();
	void Print();;

private:
	MatrixTerm* mpTerms = nullptr; // Non-zero terms
	int mNumRows = 0; // 최대 rows 갯수
	int mNumCols = 0; // 최대 columns 갯수
	int mCapacity = 0;
	int mNumTerms = 0;
};
