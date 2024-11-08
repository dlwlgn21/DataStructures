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
	mCapacity = max_degree + 1;

	// 동적 메모리 할당
	mpCoeffs = new float[mCapacity];

	// 0으로 초기화
	for (int i = 0; i < mCapacity; i++)
		mpCoeffs[i] = 0.0f;
}

Polynomial::Polynomial(const Polynomial& poly)
{
	this->mCapacity = poly.mCapacity;
	mpCoeffs = new float[mCapacity];
	for (int i = 0; i < mCapacity; i++)
		mpCoeffs[i] = poly.mpCoeffs[i];
}

Polynomial::~Polynomial()
{
	if (mpCoeffs) delete[] mpCoeffs;
}

int Polynomial::MaxDegree()
{
	return this->mCapacity - 1;
}

void Polynomial::NewTerm(const float coef, const int exp)
{
	assert(exp < mCapacity); // exp가 너무 크면 resize 하도록 구현할 수도 있음

	// TODO: 쉬워요
	mpCoeffs[exp] = coef;
}

Polynomial Polynomial::Add(const Polynomial& poly)
{
	assert(poly.mCapacity == this->mCapacity); // 문제를 단순화하기 위한 가정

	Polynomial tmp(this->MaxDegree());
	// TODO:
	for (int i = 0; i < MaxDegree(); ++i)
	{
		tmp.mpCoeffs[i] = mpCoeffs[i] + poly.mpCoeffs[i];
	}
	return tmp;
}

Polynomial Polynomial::Mult(const Polynomial& poly)
{
	assert(poly.mCapacity == this->mCapacity); // 문제를 단순화하기 위한 가정

	// coeff_[i]가 0.0f가 아닌 경우에 대해서만 계산 (곱하면 0이 되기 때문)

	Polynomial tmp(this->MaxDegree());
	// TODO: 항상 인덱싱 오류 조심
	for (int i = 0; i < this->mCapacity; ++i)
	{
		if (mpCoeffs[i] > FLT_EPSILON)
		{
			for (int j = 0; j < poly.mCapacity; ++j)
			{
				if (poly.mpCoeffs[j] > FLT_EPSILON && i + j < poly.mCapacity + this->mCapacity)
				{
					tmp.mpCoeffs[i + j] += mpCoeffs[i] * poly.mpCoeffs[j];
				}
			}
		}
	}



	return tmp;
}

float Polynomial::Eval(float x)
{
	float tmp = 0.0f;

	// TODO:
	// 힌트 std::powf(2.0f, float(3)); // 2.0f^3.0f = 8.0f (2.0f의 3.0f 제곱)
	tmp = mpCoeffs[0];
	for (int i = 1; i < MaxDegree(); ++i)
	{
		if (mpCoeffs[i] <= FLT_EPSILON)
			continue;
		tmp += mpCoeffs[i] * std::powf(x, static_cast<float>(i));
	}

	return tmp;
}

void Polynomial::Print()
{
	bool is_first = true; // 더하기 출력시 확인용

	for (int i = 0; i < mCapacity; i++)
	{
		if (mpCoeffs[i] != 0.0f) // 주의: 0이 아닌 항들만 출력
		{
			if (!is_first)
				cout << " + "; // 첫 항이 아니라면 사이사이에 더하기 출력

			cout << mpCoeffs[i];

			if (i != 0) cout << "*" << "x^" << i;

			is_first = false;
		}
	}

	cout << endl;
}