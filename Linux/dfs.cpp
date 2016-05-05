#include <iostream>
#include <Timer.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;


class Graph
{
	static const int MAX = 3000;
	int vertices;
	bool *visited;

	void readAdjacency(int size)
	{
		int i, j;
		printf("Enter the adjacency matrix [%d * %d]:\n\n", size, size);
		for (i = 0; i < size; ++i)
		{
			for (j = 0; j < size; ++j)
			{
				cin >> adjacency[i][j];
			}
		}
	}
	void reset()
	{
		int i;
		for (i = 0; i < vertices; ++i)
		{
			visited[i] = false;
		}
	}
public:
	int **adjacency;
	int *dfsArray;

	Graph(int vertices = MAX)
	{
		this->vertices = vertices;
		this->dfsArray = new int[vertices];

		this->visited = new bool[vertices];
		
		adjacency = new int *[vertices];
		for (int i = 0; i < vertices; ++i)
		{
			adjacency[i] = new int[vertices];
		}
		reset();
	}

	static void DFS(int **a, int n, int source, bool * visited, int *t, bool printOrNot)
	{
		int i = source;
		if (visited[i] == false)
		{
			visited[i] = true;
			if(printOrNot)
				printf("\n%d", i);
			for (int j = 0; j < n; ++j)
				if (a[i][j] == 1 && visited[j] == false)
					DFS(a, n, j, visited, t, printOrNot);
		}
	}
	void demo()
	{
		int size, source;
		cout << "\nEnter number of nodes in the graph: ";
		cin >> size;
		this->readAdjacency(size);
		cout << "\nEnter the source node: [0 - " << size - 1 << "]: ";
		cin >> source;
		cout << "\nThe Depth First Traversal is:";
		DFS(adjacency, vertices, source, visited, dfsArray, true);
		cout << '\n';
	}
	void analyze()
	{
		int i, j, k, source;
		Timer t;
		cout << "\nSIZE \t TIME\n";
		for (i = 250; i <= MAX; i += 250)
		{
			//Re-initialize the visited array
			reset();

			//Create adjacency
			for (j = 0; j < i; ++j)
			{
				for (k = 0; k < i; ++k)
				{
					adjacency[j][k] = rand() % 2;
				}
			}

			source = rand() % i;
			//DFS
			t.start();
			DFS(adjacency, vertices, source, visited, dfsArray, false);
			t.stop();
			cout << i << " \t " << t.time() << endl;
			t.reset();
		}
	}
};

int main()
{
	Graph s;
	s.demo();
	s.analyze();
	return 0;
}
