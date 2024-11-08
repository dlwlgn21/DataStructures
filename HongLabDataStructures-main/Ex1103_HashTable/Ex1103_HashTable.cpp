#include <iostream>
#include <string> // std::string

using namespace std;

template<typename K, typename V>
class HashTable
{
public:
	struct Item
	{
		K Key = K();
		V Value = V();
	};

	HashTable(const int& cap = 8)
	{
		mCapacity = cap;
		mpTable = new Item[mCapacity];
		for (int i = 0; i < mCapacity; ++i)
		{
			mpTable[i].Value = 0;
		}
	}

	~HashTable()
	{
		delete[] mpTable;
	}

	void Insert(const Item& item)
	{
		size_t index = HashFunc(item.Key); // 키를 인덱스로 사용

		for (int i = 0; i < mCapacity; ++i)
		{
			index = (index + i) % mCapacity;
			if (mpTable[index].Key == K())
			{
				mpTable[index] = item;
				return;
			}
		}

		cout << "Failed To Insert!!!" << endl;
	}

	V Get(const K& key)
	{
		size_t index = HashFunc(key);
		if (mpTable[index].Value == 0)	return V();
		else
		{
			for (int i = 0; i < mCapacity; ++i)
			{
				index = (index + i) % mCapacity;
				if (mpTable[index].Key == key)
					return mpTable[index].Value;
			}
		}
		return V();
	}

	// 정수 -> 해쉬값
	size_t HashFunc(const int& key)
	{
		return key % mCapacity;
	}

	// 문자열을 정수 인덱스(해쉬값)로 변환
	// Horner's method
	size_t HashFunc(const string& s)
	{
		int g = 31;
		size_t index = 0;
		for (int i = 0; i < s.size(); ++i)
		{
			index = g * index + static_cast<int>(s.at(i));
		}
		return index % mCapacity;
	}

	void Print()
	{
		for (int i = 0; i < mCapacity; i++)
			cout << i << " : " << mpTable[i].Key << " " << mpTable[i].Value << endl;
		cout << endl;
	}

private:
	Item* mpTable = nullptr;
	int mCapacity = 0;
};

int main()
{
	// 충돌 
	// - 개방 주소법: 선형 조사법
	// - 체이닝: 멤버 변수 Item* table_ 대신에 LinkedList<Item>* table_사용

	// 키: int, 값: int 인 경우
	// 키의 범위가 아주 크고 아이템의 개수는 적을 경우
	//{
	//	using Item = HashTable<int, int>::Item;

	//	HashTable<int, int> h(8);

	//	h.Insert(Item{ 123, 456 });

	//	h.Print();

	//	cout << "Get 123 " << h.Get(123) << endl;

	//	h.Insert(Item{ 1000021, 9898 });

	//	h.Print();

	//	cout << "Get 1000021 " << h.Get(1000021) << endl;

	//	h.Insert(Item{ 1211, 999 }); // 충돌!

	//	h.Print();

	//	cout << "Get 123 " << h.Get(123) << endl;
	//	cout << "Get 1211 " << h.Get(1211) << endl;
	//}

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