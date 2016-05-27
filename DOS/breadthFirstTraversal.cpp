#include <iostream.h>
#include <stdio.h>
#include <Timer.h>
#include <stdlib.h>

#define MAX 120

enum bool
{
	false,
	true
};

template<class T>
class Node
{
public:
	T info;
	Node<T> *next;
	Node(T info)
	{
		this->info = info;
		this->next = NULL;
	}
};

template<class T>
class Queue
{
	Node<T> *start;
	int count;

public:
	Queue()
	{
		this->start = NULL;
		this->count = 0;
	}
	void Add(T item)
	{
		Node<T> *newNode = new Node<T>(item);
		if (newNode == NULL)
		{
			printf("\nOut of memory.");
			return;
		}
		if (start == NULL) start = newNode;
		else
		{
			Node<T> *temp = start;
			while (temp->next != NULL)
			{
				temp = temp->next;
			}
			temp->next = newNode;
		}
		++count;
	}
	void Delete()
	{
		if (start == NULL)
		{
			printf("\nQueue underflow.");
			return;
		}
		Node<T> *temp = start;
		start = start->next;
		delete temp;
		--count;
	}
	void Clear()
	{
		for (int i = 0; i < this->count; ++i)
			Delete();
	}
	bool Empty()
	{
		return count == 0;
	}
	T Peep()
	{
		return start->info;
	}
};
class Graph
{
	int vertices;
	bool *visited;
	Queue<int> queue;

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
			visited[i] = false;
		queue.Clear();
	}
	void resetAdjacency()
	{
		int i, j;
		for (i = 0; i < vertices; ++i)
			for (j = 0; j < vertices; ++j)
				adjacency[i][j] = 1;
	}
public:
	int **adjacency;
	//int *dfsArray;

	Graph(int vertices = MAX)
	{
		this->vertices = vertices;
		//this->dfsArray = new int[vertices];

		this->visited = new bool[vertices];

		adjacency = new int *[vertices];
		for (int i = 0; i < vertices; ++i)
		{
			adjacency[i] = new int[vertices];
		}

		reset();
	}

	static void BFS(int **a, int n, int source, bool *visited, bool printOrNot, Queue<int> &q)
	{
		int i = source;
		visited[i] = true;
		q.Add(i);

		while (!q.Empty())
		{
			i = q.Peep();
			if (printOrNot)
				printf("\n%d", i);
			q.Delete();
			for (int j = 0; j < n; ++j)
				if (a[i][j] == 1 && visited[j] == false)
				{
					visited[j] = true;
					q.Add(j);
				}
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
		cout << "\nThe Breadth First Traversal is:";
		BFS(adjacency, size, source, visited, true, queue);
		cout << '\n';
	}
	void analyze()
	{
		int i, source;
		Timer t;
		cout << "\nSIZE \t TIME\n";
		resetAdjacency();
		for (i = 10; i <= MAX; i += 10)
		{
			//Re-initialize the visited array and adjacency matrix
			reset();

			source = 0;
			//BFS
			t.start();
			BFS(adjacency, i, source, visited, false, queue);
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