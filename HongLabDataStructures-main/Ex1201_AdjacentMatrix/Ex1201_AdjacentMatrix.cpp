#include <iostream>
#include <cassert>
#include <stack>
#include <queue>

#include "../shared/Stack.h"
#include "../shared/Queue.h"

using namespace std;

template<typename T>
class AdjMatGraph // Adjacent Matrix Graph
{
public:
	struct Vertex // Node
	{
		T item = T();
	};

	AdjMatGraph(int max_vertices)
	{
		mMaxVertices = max_vertices; // capacity

		mppMatrix = new int* [mMaxVertices];
		for (int r = 0; r < mMaxVertices; r++) 
		{
			mppMatrix[r] = new int[mMaxVertices];
			for (int c = 0; c < mMaxVertices; c++)
			{
				mppMatrix[r][c] = 0;
			}
		}

		mpVertices = new Vertex[mMaxVertices];

		mSize = 0;
	}

	~AdjMatGraph()
	{
		delete[] mpVertices;

		for (int i = 0; i < mMaxVertices; i++)
		{
			delete[] mppMatrix[i];
		}
		delete[] mppMatrix;

		if (mpIsVisiteds != nullptr)	delete[] mpIsVisiteds;
		
	}

	void PrintMatrix()
	{
		using namespace std;
		if (mSize)
			for (int r = 0; r < mSize; r++) {
				for (int c = 0; c < mSize; c++)
					cout << mppMatrix[r][c] << ", ";
				cout << endl;
			}
		else
			cout << "Empty" << endl;

		cout << endl;
	}

	void InsertVertex(T item)
	{
		mpVertices[mSize].item = item;
		mSize++;
	}

	void InsertEdge(int u, int v) // 여기서 u, v는 인덱스
	{
		assert(u < mSize && v < mSize);

		mppMatrix[u][v] = 1;
	}

	int Capacity()
	{
		return mMaxVertices;
	}

	void DepthFirstTraversal()
	{
		ResetVisited();

		DepthFirstTraversalRecursive(0);

		cout << endl;
	}

	void DepthFirstTraversalRecursive(int v) // v는 인덱스
	{
		if (mpIsVisiteds[v])	return;
		// TODO:
		mpIsVisiteds[v] = true;
		cout << v << ", ";

		for (int j = 0; j < mSize; ++j)
		{
			if (mppMatrix[v][j] != 0 && !mpIsVisiteds[j])
			{
				DepthFirstTraversalRecursive(mpVertices[j].item);
				mpIsVisiteds[j] = true;
			}
		}
	}

	void IterDFT()
	{
		// TODO:
		stack<Vertex> s;
		
		ResetVisited();

		s.push(mpVertices[0]);

		while (!s.empty())
		{
			Vertex vertex = s.top();
			mpIsVisiteds[vertex.item] = true;
			cout << vertex.item << std::endl;
			s.pop();

			for (int j = mSize - 1; j >= 0; --j)
			{
				if (mppMatrix[vertex.item][j] != 0 && !mpIsVisiteds[j])
				{
					std::cout << " [Vertex " << vertex.item << " Edge is " << mpVertices[j].item << "]  " << std::endl;
					s.push(mpVertices[j]);
					mpIsVisiteds[mpVertices[j].item] = true;
				}
			}
		}

		

	}

	void BreadthFirstTraversal()
	{
		queue<Vertex> q;

		ResetVisited();

		q.push(mpVertices[0]);

		while (!q.empty())
		{
			Vertex vertex = q.front();
			cout << vertex.item << ", ";
			q.pop();
			mpIsVisiteds[vertex.item] = true;

			for (int i = 0; i < mMaxVertices; ++i)
			{
				if (mppMatrix[vertex.item][i] != 0 && !mpIsVisiteds[i])
				{
					mpIsVisiteds[i] = true;
					q.push(mpVertices[i]);
				}
			}
		}
		cout << endl;
	}

	void ResetVisited()
	{
		if (!mpIsVisiteds)
			mpIsVisiteds = new bool[mMaxVertices];
		for (int i = 0; i < mMaxVertices; i++) mpIsVisiteds[i] = false; // 초기화
	}

private:
	int** mppMatrix = nullptr;
	Vertex* mpVertices = nullptr;
	int mSize = 0;					// size
	int mMaxVertices = 0;		// capacity

	bool* mpIsVisiteds = nullptr;
};

int main()
{
	// 정점(vertex), 간선(edge)

	AdjMatGraph<int> g(7);

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

	g.PrintMatrix();

	g.IterDFT();
	//g.DepthFirstTraversal();
	//g.BreadthFirstTraversal();

	return 0;
}