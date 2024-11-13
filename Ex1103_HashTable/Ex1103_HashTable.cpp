﻿#include <iostream>
#include <string> // std::string
#include <assert.h>

using namespace std;

template<typename K, typename V>
class HashTable
{
public:
	struct Item
	{
		K key = K();
		V value = V();
	};

	HashTable(const int& cap = 8)
	{
		mCapa = cap;
		mpTable = new Item[mCapa];
	}

	~HashTable()
	{
		delete[] mpTable;
	}

	void Insert(const Item& item)
	{
		// TODO:
		size_t index = HashFunc(item.key); // 키를 인덱스로 사용
		int iterCnt = 0;
		while (mpTable[index].key != K())
		{
			index = (index + 1) % mCapa;
			++iterCnt;
			if (iterCnt >= mCapa)
				assert(false);
		}
		mpTable[index] = item;
	}

	V Get(const K& key)
	{
		// TODO: 못 찾으면 0을 반환
		size_t index = HashFunc(key);
		for (int i = 0; i < mCapa; ++i)
		{
			index = (index + i) % mCapa;
			if (mpTable[index].key == key)
				return mpTable[index].value;
		}
		return V();
	}

	// 정수 -> 해시값
	size_t HashFunc(const int& key)
	{
		return key % mCapa;
	}

	// 문자열을 정수 인덱스(해시값)로 변환
	// Horner's method
	size_t HashFunc(const string& s)
	{
		size_t key = 0;
		for (int i = 0; i < s.size(); ++i)
			key = 31 * static_cast<int>(s[i]) + key;

		return key % mCapa;
	}

	void Print()
	{
		for (int i = 0; i < mCapa; i++)
			cout << i << " : " << mpTable[i].key << " " << mpTable[i].value << endl;
		cout << endl;
	}

private:
	Item* mpTable = nullptr;
	int mCapa = 0;
};

int main()
{
	// 충돌 
	// - 개방 주소법: 선형 조사법
	// - 체이닝: 멤버 변수 Item* table_ 대신에 LinkedList<Item>* table_사용

	// 키: int, 값: int 인 경우
	// 키의 범위가 아주 크고 아이템의 개수는 적을 경우
	{
		using Item = HashTable<int, int>::Item;

		HashTable<int, int> h(8);

		h.Insert(Item{ 123, 456 });

		h.Print();

		cout << "Get 123 " << h.Get(123) << endl;

		h.Insert(Item{ 1000021, 9898 });

		h.Print();

		cout << "Get 1000021 " << h.Get(1000021) << endl;

		h.Insert(Item{ 1211, 999 }); // 충돌!

		h.Print();

		cout << "Get 123 " << h.Get(123) << endl;
		cout << "Get 1211 " << h.Get(1211) << endl;
	}

	// 키: std::string, 값: int
	{
		using Item = HashTable<string, int>::Item;

		HashTable<string, int> h(8);

		h.Insert(Item{ "apple", 1 });
		h.Insert(Item{ "orange", 2 });
		h.Insert(Item{ "mandarin", 4 });

		h.Print();

		cout << "apple " << h.Get("apple") << endl;
		cout << "orange " << h.Get("orange") << endl;
		cout << endl;

		h.Print();

		h.Insert(Item{ "tomato", 4 });

		h.Print(); 

		cout << "apple " << h.Get("apple") << endl;
		cout << "orange " << h.Get("orange") << endl;
		cout << "pineapple " << h.Get("pineapple") << endl;
		cout << endl;
	}

	return 0;
}