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
	// 크기(size_) 결정
	const char* p = &init[0];
	int size = 0;
	while (*p != '\0')
	{
		++size;
		++p;
	}
	mSize = size;
	mpStr = new char[size + 1];
	memcpy(mpStr, init, size);
	mpStr[size] = '\0';
}

// MyString의 다른 instance로부터 초기화
MyString::MyString(const MyString& str)
{
	mpStr = new char[str.mSize + 1];
	mSize = str.mSize;
	memcpy(mpStr, str.mpStr, mSize);
	mpStr[mSize] = '\0';
}

MyString::~MyString()
{
	// 메모리 해제
	if (mpStr != nullptr)
		delete[] mpStr;
}

bool MyString::IsEmpty()
{
	return Length() == 0;
}

bool MyString::IsEqual(const MyString& str) // 편의상 참조& 사용
{
	// 힌트: str.str_, str.size_ 가능
	if (mSize != str.mSize)
		return false;

	const char* mp = &mpStr[0];
	const char* op = &str.mpStr[0];
	int size = 0;
	while (*mp == *op && *mp != '\0')
	{
		++mp;
		++op;
		++size;
	}

	if (size != mSize)
		return false;
	else
		return true;
}

int MyString::Length()
{
	return mSize;
}

void MyString::Resize(int newSize)
{
	// 메모리 재할당과 원래 갖고 있던 내용 복사
	char* pNew = new char[newSize + 1];
	memcpy(pNew, mpStr, mSize);
	pNew[mSize] = '\0';
	char* pTmp = mpStr;
	mpStr = pNew;
	pNew = pTmp;
	delete[] pNew;
}

// 인덱스 start위치의 글자부터 num개의 글자로 새로운 문자열 만들기
MyString MyString::Substr(int start, int num)
{
	// 복사할 인덱스: start, start + 1, ... , start + num - 1
	// assert(start + num - 1 < this->size_); // 문제를 단순하게 만들기 위해 가정

	MyString tmp;
	tmp.mpStr = new char[num + 1];
	tmp.mSize = num;
	int j = 0;
	for (int i = start; i < start + num; ++i)
	{
		tmp.mpStr[j++] = mpStr[i];
	}
	tmp.mpStr[num] = '\0';
	return tmp;
}

MyString MyString::Concat(MyString app_str)
{
	MyString tmp;
	tmp.mpStr = new char[app_str.mSize + mSize + 1];
	memcpy(tmp.mpStr, mpStr, mSize);
	memcpy(tmp.mpStr + mSize, app_str.mpStr, app_str.mSize);
	tmp.mpStr[app_str.mSize + mSize] = '\0';
	tmp.mSize = app_str.mSize + mSize;
	return tmp;
}

MyString MyString::Insert(MyString t, int start)
{
	assert(start >= 0);
	assert(start <= this->mSize);

	MyString tmp;
	tmp.mpStr = new char[mSize + t.mSize + 1];
	tmp.mSize = mSize + t.mSize;
	int i = 0;
	int j = 0;
	int z = 0;
	tmp.mpStr[tmp.mSize] = '\0';
	while (i < tmp.mSize)
	{
		if (i >= start && i < start + t.mSize)
		{
			tmp.mpStr[i++] = t.mpStr[j++];
		}
		else
		{
			tmp.mpStr[i++] = mpStr[z++];
		}
	}
	return tmp;
}

int MyString::Find(MyString pat)
{
	for (int i = 0; i < mSize; ++i)
	{
		if (mpStr[i] == pat.mpStr[0])
		{
			int tmpI = i;
			if (pat.mSize > mSize - i)
				return -1;

			bool isSame = true;
			for (int j = 0; j < pat.mSize; ++j)
			{
				if (mpStr[tmpI++] != pat.mpStr[j])
				{
					isSame = false;
					break;
				}
			}
			if (isSame)
				return i;
		}
	}

	return -1;
}

void MyString::Print()
{
	for (int i = 0; i < mSize; i++)
		cout << mpStr[i];
	cout << endl;
}

