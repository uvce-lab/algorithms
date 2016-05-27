#include <iostream.h>
#include <Timer.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX (120)
enum bool
{
	false,
	true
};
class Graph
{
	int vertices, source;
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

	Graph(int vertices = MAX)
	{
		this->vertices = vertices;

		this->visited = new bool[vertices];

		adjacency = new int *[vertices];
		for (int i = 0; i < vertices; ++i)
		{
			adjacency[i] = new int[vertices];
		}
		reset();
	}
	/*
	~Graph()
	{
		delete dfsArray;
		delete visited;
		for(int i=0; i<vertices; ++i)
			delete adjacency[i];
		delete adjacency;
	}
	*/
	static void DFS(int **a, int n, int source, bool * visited, bool printOrNot)
	{
		int i = source;
		if (visited[i] == false)
		{
			visited[i] = true;
			if(printOrNot)
				printf("\n%d\n", i);
			for (int j = 0; j < n; ++j)
				if (a[i][j] == 1 && visited[j] == false)
					DFS(a, n, j, visited, printOrNot);
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
		cout << "The Depth First Traversal is:";
		DFS(adjacency, size, source, visited, true);
	}
	void analyze()
	{
		int i, j, k, source;
		Timer t;
		cout << "\nSIZE\tTIME\n";
		for (j = 0; j < vertices; ++j)
			for (k = 0; k < vertices; ++k)
				adjacency[j][k] = 1;
		for (i = 10; i <= MAX; i += 10)
		{
			//Re-initialize the visited array
			reset();

			source = rand() % i;
			//DFS
			t.start();
			DFS(adjacency, i, source, visited, false);
			t.stop();
			cout << i << '\t' << t.time() << endl;
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