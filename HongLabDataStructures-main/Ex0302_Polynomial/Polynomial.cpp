#include "Polynomial.h"

#include <cassert>
#include <iostream>
#include <math.h> // std::powf()

using namespace std;

Polynomial::Polynomial(int max_degree) // 편의상 기본값 사용
{
	assert(max_degree > 0);

	// - 상수항 포함
	// - 예: max_degree가 2이면 c0*x^0 + c1*x^1 + c2*x^2 총 3개의 항들
	mCapa = max_degree + 1;

	// 동적 메모리 할당
	mpCoefs = new float[mCapa];

	// 0으로 초기화
	for (int i = 0; i < mCapa; i++)
	{
		mpCoefs[i] = 0.0f;
	}
}

Polynomial::Polynomial(const Polynomial& other)
{
	this->mCapa = other.mCapa;
	mpCoefs = new float[mCapa];
	for (int i = 0; i < mCapa; i++)
		mpCoefs[i] = other.mpCoefs[i];
}

Polynomial::~Polynomial()
{
	if (mpCoefs != nullptr) delete[] mpCoefs;
}

int Polynomial::MaxDegree()
{
	return this->mCapa - 1;
}

void Polynomial::NewTerm(const float coef, const int exp)
{
	assert(exp < mCapa); // exp가 너무 크면 resize 하도록 구현할 수도 있음
	mpCoefs[exp] = coef;
}

Polynomial Polynomial::Add(const Polynomial& other)
{
	assert(other.mCapa == this->mCapa); // 문제를 단순화하기 위한 가정

	Polynomial retNew(this->MaxDegree());

	for (int i = 0; i < mCapa; ++i)
	{
		retNew.mpCoefs[i] = this->mpCoefs[i] + other.mpCoefs[i];
	}

	return retNew;
}

Polynomial Polynomial::Mult(const Polynomial& other)
{
	assert(other.mCapa == this->mCapa); // 문제를 단순화하기 위한 가정

	// coeff_[i]가 0.0f가 아닌 경우에 대해서만 계산 (곱하면 0이 되기 때문)

	Polynomial retNew(this->MaxDegree());

	// TODO: 항상 인덱싱 오류 조심
	for (int i = 0; i < mCapa; ++i)
	{
		if (this->mpCoefs[i] == 0.0f)	continue;

		for (int j = 0; j < mCapa; ++j)
		{
			if (other.mpCoefs[j] == 0.0f)	continue;

			retNew.mpCoefs[i + j] += this->mpCoefs[i] * other.mpCoefs[j];
		}
	}

	return retNew;
}

float Polynomial::Eval(float x)
{
	float temp = 0.0f;

	for (int i = 0; i < mCapa; ++i)
	{
		temp += mpCoefs[i] * std::powf(x, static_cast<float>(i));
	}

	return temp;
}

void Polynomial::Print()
{
	bool is_first = true; // 더하기 출력시 확인용

	for (int i = 0; i < mCapa; i++)
	{
		if (mpCoefs[i] != 0.0f) // 주의: 0이 아닌 항들만 출력
		{
			if (!is_first)
				cout << " + "; // 첫 항이 아니라면 사이사이에 더하기 출력

			cout << mpCoefs[i];

			if (i != 0) cout << "*" << "x^" << i;

			is_first = false;
		}
	}

	cout << endl;
}