#include <iostream>
#include <cassert>
#include <stack>
#include <queue>

#include "../shared/Stack.h"
#include "../shared/Queue.h"

using namespace std;

template<typename T>
class AdjListGraph // Adjacent List Graph
{
public:
	struct Vertex
	{
		T item = T();
	};

	struct Node
	{
		//Vertex* vertex = nullptr;
		int vertex = -1; // vertex의 index
		Node* next = nullptr;
	};

	AdjListGraph(int max_vertices)
	{
		mMasxVertices = max_vertices; // capacity

		mpVertices = new Vertex[mMasxVertices];
		mppLists = new Node * [mMasxVertices];
		for (int i = 0; i < mMasxVertices; i++)
			mppLists[i] = nullptr;

		mSize = 0;
	}

	~AdjListGraph()
	{
		delete[] mpVertices;
		delete[] mppLists;

		if (mpVisiteds)
			delete[] mpVisiteds;
	}

	void InsertVertex(T item)
	{
		mpVertices[mSize].item = item;
		mSize++;
	}

	void InsertEdge(int from, int to) // 여기서 u, v는 인덱스
	{
		assert(from < mSize && to < mSize);
		/*
		g.InsertEdge(0, 2);	g.InsertEdge(2, 0);
		g.InsertEdge(0, 1);	g.InsertEdge(1, 0);
		
		*/
		Node* temp = new Node{ to, mppLists[from] };
		// Change Head
		mppLists[from] = temp;
	}

	int Capacity()
	{
		return mMasxVertices;
	}

	void Print()
	{
		for (int v = 0; v < mSize; v++)
		{
			cout << mpVertices[v].item << " : ";

			Node* current = mppLists[v];
			while (current)
			{
				cout << mpVertices[current->vertex].item << " ";
				current = current->next;
			}
			cout << endl;
		}

		cout << endl;
	}

	void DepthFirstTraversal()
	{
		ResetVisited();
		assert(mSize != 0);
		cout << "DFS Recursive version Start" << endl;
		DepthFirstTraversalRecursive(0);

		cout << endl;
	}

	void DepthFirstTraversalRecursive(int v) // v는 인덱스
	{
		// TODO:
		if (mpVisiteds[v]) return;
		cout << v << ", ";
		mpVisiteds[v] = true;
		Node* pCurr = mppLists[v];
		while (pCurr != nullptr)
		{
			if (!mpVisiteds[pCurr->vertex])
			{
				DepthFirstTraversalRecursive(pCurr->vertex);
				mpVisiteds[pCurr->vertex] = true;
			}
			pCurr = pCurr->next;
		}
	}

	void IterDFT()
	{
		ResetVisited();
		assert(mSize != 0);

		// TODO:
		cout << "DFS Iter version Start" << endl;
		stack<int> s;
		s.push(mpVertices[0].item);

		while (!s.empty())
		{
			int value = s.top();
			cout << value << ", ";
			mpVisiteds[value] = true;
			s.pop();

			Node* pCurr = mppLists[value];
			while (pCurr != nullptr)
			{
				if (!mpVisiteds[pCurr->vertex])
				{
					s.push(pCurr->vertex);
					mpVisiteds[pCurr->vertex] = true;
				}
				pCurr = pCurr->next;
			}
		}

		cout << endl;

	}

	void BreadthFirstTraversal()
	{
		ResetVisited();
		cout << "BFS Start" << endl;
		// TODO:
		assert(mSize != 0);
		queue<int> q;
		q.push(mpVertices[0].item);

		while (!q.empty())
		{
			int vIdx = q.front();
			cout << vIdx << ", ";
			q.pop();
			mpVisiteds[vIdx] = true;

			Node* pCurr = mppLists[vIdx];
			while (pCurr != nullptr)
			{
				if (!mpVisiteds[pCurr->vertex])
				{
					q.push(pCurr->vertex);
					mpVisiteds[pCurr->vertex] = true;
				}
				pCurr = pCurr->next;
			}
		}

		cout << endl;
	}

	void ResetVisited()
	{
		if (!mpVisiteds)
			mpVisiteds = new bool[mMasxVertices];
		for (int i = 0; i < mMasxVertices; i++) mpVisiteds[i] = false; // 초기화
	}

private:
	Vertex* mpVertices = nullptr;
	Node** mppLists = nullptr;
	int mSize = 0;					// size
	int mMasxVertices = 0;		// capacity

	bool* mpVisiteds = nullptr;
};

int main()
{
	AdjListGraph<int> g(7);

	for (int i = 0; i < g.Capacity(); i++)
		g.InsertVertex(i);

	g.InsertEdge(0, 2);	g.InsertEdge(2, 0);
	g.InsertEdge(0, 1);	g.InsertEdge(1, 0);
	g.InsertEdge(1, 4);	g.InsertEdge(4, 1);
	g.InsertEdge(1, 3);	g.InsertEdge(3, 1);
	g.InsertEdge(2, 4);	g.InsertEdge(4, 2);
	g.InsertEdge(3, 6);	g.InsertEdge(6, 3);
	g.InsertEdge(4, 6);	g.InsertEdge(6, 4);
	g.InsertEdge(5, 6);	g.InsertEdge(6, 5);

	g.Print();

	g.DepthFirstTraversal();
	cout << endl;

	g.IterDFT();

	g.BreadthFirstTraversal();

	return 0;
}
