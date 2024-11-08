#define _CRT_SECURE_NO_WARNINGS
#include "MyString.h"

using namespace std;

// 비어 있는 MyString() 생성
MyString::MyString()
{
	mpStr = nullptr;
	mSize = 0;
}

// 맨 뒤에 널 캐릭터'\0'가 들어 있는 문자열로부터 초기화
MyString::MyString(const char* init)
{
	allocNewMemory(init);
}

// MyString의 다른 instance로부터 초기화
MyString::MyString(const MyString& str)
{
	// 기본 복사 생성자는 포인터 주소만 복사하기 때문에 
	// 소멸시 오류 발생
	// 여기서는 새로 메모리를 할당 받아서 복사
	allocNewMemory(str.mpStr);
}

MyString::~MyString()
{
	// 메모리 해제
	delete[] mpStr;
}

bool MyString::IsEmpty()
{
	return Length() == 0;
}

bool MyString::IsEqual(const MyString& str) // 편의상 참조& 사용
{
	if (mSize != str.mSize)    return false;
	// 힌트: str.str_, str.size_ 가능
	for (int i = 0; i < mSize; ++i)
	{
		if (mpStr[i] != str.mpStr[i])    return false;
	}

	return true;
}

int MyString::Length()
{
	return mSize;
}

void MyString::Resize(int new_size)
{
	// 메모리 재할당과 원래 갖고 있던 내용 복사
}

// 인덱스 start위치의 글자부터 num개의 글자로 새로운 문자열 만들기
MyString MyString::Substr(int start, int num)
{
	// 복사할 인덱스: start, start + 1, ... , start + num - 1
	assert(start + num - 1 < this->mSize); // 문제를 단순하게 만들기 위해 가정

	MyString retNew;
	retNew.mpStr = new char[num + 1];

	for (int i = start, j = 0; j < num; ++i, ++j)
	{
		retNew.mpStr[j] = mpStr[i];
	}

	retNew.mpStr[num] = '\0';
	return retNew;
}

MyString MyString::Concat(MyString app_str)
{
	MyString retNew;
	int newLength = mSize + app_str.mSize;
	retNew.mpStr = new char[newLength + 1];
	for (int i = 0; i < mSize; ++i)
	{
		retNew.mpStr[i] = mpStr[i];
	}

	for (int i = mSize, j = 0; i < newLength; ++i, ++j)
	{
		retNew.mpStr[i] = app_str.mpStr[j];
	}

	retNew.mpStr[newLength] = '\0';

	return retNew;
}

MyString MyString::Insert(MyString t, int start)
{
	assert(start >= 0);
	assert(start <= this->mSize);

	MyString newRet;
	size_t newLength = t.mSize + mSize;
	newRet.mSize = static_cast<int>(newLength);
	newRet.mpStr = new char[newLength + 1];

	for (size_t i = start, j = 0; j < t.mSize; ++i, ++j)
	{
		newRet.mpStr[i] = t.mpStr[j];
	}

	for (size_t i = 0, j = 0; i < newLength; ++i)
	{
		if (i >= start && i < start + t.mSize) continue;
		else
		{
			newRet.mpStr[i] = mpStr[j++];
		}
	}

	newRet.mpStr[newLength] = '\0';
	return newRet;
}

int MyString::Find(MyString pat)
{
	//TODO:
	if (pat.mSize > mSize)		return -1;
	for (int i = 0; i < mSize; ++i)
	{
		int innerIdx = i;
		int correctCount = 0;
		for (int j = 0; j < pat.mSize; ++j)
		{
			if (mpStr[innerIdx] == pat.mpStr[j])
			{
				++innerIdx;
				++correctCount;
				continue;
			}
			else
			{
				break;
			}
		}
		if (correctCount == pat.mSize)	return i;
	}
	return -1;
}

void MyString::Print()
{
	for (int i = 0; i < mSize; i++)
		cout << mpStr[i];
	cout << endl;
}

void MyString::allocNewMemory(const char* pStr)
{
	size_t length = strlen(pStr);
	mpStr = new char[length + 1];
	memcpy(mpStr, pStr, length);
	mpStr[length] = '\0';
	mSize = static_cast<int>(length);
}

