#pragma once

class Matrix
{
public:
	Matrix(int num_rows, int num_cols);

	Matrix(const Matrix& b);

	~Matrix();

	void SetValue(int row, int col, float value);

	float GetValue(int row, int col) const;

	Matrix Add(const Matrix& b);

	Matrix Transpose();

	void Print();

private:
	float* mpValues = nullptr;
	int mNumRows = 0;
	int mNumCols = 0;
};
