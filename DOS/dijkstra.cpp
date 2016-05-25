#include <iostream.h>
#include <limits.h>
#include <Timer.h>
#include <stdlib.h>


#define INF (INT_MAX)
#define MAX 160

enum bool { false, true };

class Dijkstra
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
	int * dijkstra(int **a, int n, int source)
	{
		int i, min, minAt;

		//Set to keep track of selected nodes in the Minimal Spannnf Tree
		bool *sptSet = new bool[n];
		for (i = 0; i < n; ++i) sptSet[i] = false;

		//Array to help select the next node and which will hold the minimum distances
		int *d = new int[n];
		for (i = 0; i < n; ++i)d[i] = INF;

		//So that source node is selected first
		d[source] = 0;

		for (i = 0; i < n - 1; ++i)
		{
			//Pick vertex with minimum key and which has not been visited
			min = INF;
			for (int i = 0; i < n; i++)
			{
				if (sptSet[i] == false && d[i] < min)
				{
					min = d[i];
					minAt = i;
				}
			}
			//min contains the node be to selected for insertion in MST
			sptSet[minAt] = true;

			//Update the key values to the weight of the selected node to its adjacent node if it is less.
			for (i = 0; i < n; ++i)
			{
				if (!sptSet[i] && a[minAt][i] != INF && d[i] > d[minAt] + a[minAt][i])
				{
					d[i] = d[minAt] + a[minAt][i];
				}
			}
		}
		delete sptSet;
		return d;
	}
	void demo()
	{
		int n, i, edges, from, to, source, dist;

		cout << "\nEnter number of nodes in the graph: ";
		cin >> n;
		int **graph = createArray2D(n, n, INF);

		cout << "\nEnter the number of edges: ";
		cin >> edges;
		cout << "Enter edges:\n";
		for (i = 0; i < edges; ++i)
		{
			cin >> from >> to >> dist;
			graph[from][to] = graph[to][from] = dist;
		}

		cout << "\nEnter the source node (Zero based indexing): ";
		cin >> source;
		Timer t;
		t.start();
		int *minDist = dijkstra(graph, n, source);
		t.stop();

		cout << "\nThe distance to all the notes from " << source << endl;
		for (i = 0; i < n; ++i)
		{
			cout << source << " - " << i << '\t' << minDist[i] << endl;
		}
		cout << "\nTime taken to calculate: " << t.time() << " s.\n";

		deleteArray2D(graph, n);
	}
	void analyze()
	{
		int i;
		int **graph = createArray2D(MAX, MAX, MAX);

		Timer t;
		cout << "\nAnalysis\nNodes\tTime\n";
		for (i = 20; i <= MAX; i += 20)
		{
			t.start();
			dijkstra(graph, i, rand() % i);
			t.stop();

			cout << i << '\t' << t.time() << endl;
			t.reset();
		}
	}
};
int main()
{
	Dijkstra p;
	p.demo();
	p.analyze();
}

