#include <iostream>
#include <limits.h>
#include <Timer.h>
#include <stdlib.h>
using namespace std;

#define INF (INT_MAX)
#define MAX 160
class Prim
{

	int ** createArray2D(int row, int col, int init = 0)
	{
		int i, j;
		int **arr = new int*[row];
		for (i = 0; i < row; ++i)
			arr[i] = new int[col];

		for (i = 0; i < row; ++i)
		{
			for (j = 0; j < col; ++j)
			{
				arr[i][j] = init;
			}
		}
		return arr;
	}
	void deleteArray2D(int **&arr, int rows)
	{
		for (int i = 0; i < rows; ++i)
			delete arr[i];
		delete arr;
	}

public:
	//a: The adjacency matrix
	//n: Number of nodes in the graph
	//source: The source node (Zero based indexing)
	int * prim(int **a, int n)
	{
		int i, min, minAt;

		//Set to keep track of selected nodes in the Minimal Spannnf Tree
		bool *mstSet = new bool[n];
		for (int i = 0; i < n; ++i) mstSet[i] = false;

		//Array that will hold the minimal spanning tree
		int *mst = new int[n];

		//Array to help select the next node
		int *keys = new int[n];
		for (i = 0; i < n; ++i)keys[i] = INF;

		//So that source node is selected first
		keys[0] = 0;

		for (int i = 0; i < n - 1; ++i)
		{
			//Pick vertex with minimum key and which has not been visited
			min = INF;
			for (int i = 0; i < n; i++)
			{
				if (mstSet[i] == false && keys[i] < min)
				{
					min = keys[i];
					minAt = i;
				}
			}
			//min contains the node be to selected for insertion in MST
			mstSet[minAt] = true;

			//Update the key values to the weight of the selected node to its adjacent node if it is less.
			for (int i = 0; i < n; ++i)
			{
				if ((a[minAt][i] != INF) && (keys[i] > a[minAt][i]))
				{
					keys[i] = a[minAt][i];
					if (mstSet[i] == false) mst[i] = minAt;
				}
			}
		}
		delete mstSet; delete keys;
		return mst;
	}
	void demo()
	{
		int n, i, edges, from, to;
		char ch[10];

		cout << "\nEnter number of nodes in the graph: ";
		cin >> n;
		int **graph = createArray2D(n, n, INF);

		cout << "\nEnter the number of edges: ";
		cin >> edges;
		cout << "Enter edges:\n";
		for (i = 0; i < edges; ++i)
		{
			cin >> from >> to;
			cin >> ch;
			if (_strcmpi(ch, "inf") == 0)graph[from][to] = graph[to][from] = INF;
			else graph[from][to] = graph[to][from] = atoi(ch);
		}

		Timer t;
		t.start();
		int *mst = prim(graph, n);
		t.stop();

		cout << "\nThe MST contains the following edges\n";
		for (int i = 1; i < n; ++i)
		{
			cout << mst[i] << " - " << i << '\t' << graph[i][mst[i]] << endl;
		}
		cout << "\nTime taken to calculate: " << t.time() << " s.\n";

		deleteArray2D(graph, n);
	}
	void analyze()
	{
		int i;
		int **graph = createArray2D(MAX, MAX, MAX);

		Timer t;
		cout << "\nAnalysis\nVertices\tTime\n";
		for (i = 10; i <= MAX; i += 10)
		{
			t.start();
			prim(graph, i);
			t.stop();

			cout << i << '\t' << t.time() << endl;
			t.reset();
		}
	}
};
int main()
{
	Prim p;
	//p.demo();
	p.analyze();
}