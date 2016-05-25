#include <iostream.h>
#include <limits.h>
#include <Timer.h>
#include <stdlib.h>
#include <string.h>

#define INF (INT_MAX)
#define MAX 160

enum bool
{
	false,
	true
};

template<class T>
class InsertionSort
{
public:
	static void insertionSort(T a[], int size)
	{
		T item;
		int i, j;
		for (i = 1; i < size; ++i)
		{
			item = a[i];
			j = i - 1;
			while (j >= 0 && item < a[j])
			{
				a[j + 1] = a[j];
				j = j - 1;
			}
			a[j + 1] = item;
		}
	}
};

struct Edge
{
	int source, dest, weight;
	Edge() {}
	Edge(int s, int d, int w)
	{
		source = s;
		dest = d;
		weight = w;
	}
	bool operator <(Edge e1)
	{
		return this->weight < e1.weight;
	}
};

class Kruskal
{
private:
	//Returns minimum of two values
	int min(int x, int y)
	{
		return (x < y) ? x : y;
	}
	Edge *generateEdges(int n)
	{
		Edge *e = new Edge[2 * n];
		for (int i = 0; i < 2 * n; ++i)
		{
			e[i].source = rand() % n;
			e[i].dest = rand() % n;
			e[i].weight = rand() % MAX;
		}
		return e;
	}
public:
	//a: The list of edges in the graph. Edge -> {source, destination, weight}
	//n: Number of nodes in the graph
	Edge * kruskal(Edge *a, int n, int numberOfEdges)
	{
		int i, count;
		Edge *curr;
		//Sort the edges according to weights
		InsertionSort<Edge>::insertionSort(a, numberOfEdges);

		//List that notes to which set nodes belong to
		int *set = new int[n];
		for (i = 0; i < n; ++i)set[i] = i;

		Edge *mst = new Edge[n - 1];

		count = 0;
		for (i = 0; count < n - 1; ++i)
		{
			curr = &a[i];

			if (set[curr->source] != set[curr->dest])
			{
				int min = this->min(curr->source, curr->dest);
				set[curr->source] = min;
				set[curr->dest] = min;

				mst[count].source = curr->source;
				mst[count].dest = curr->dest;
				mst[count].weight = curr->weight;

				++count;
			}
		}
		return mst;
	}
	void demo()
	{
		int n, i, e;
		char ch[10];

		cout << "\nEnter number of nodes in the graph: ";
		cin >> n;
		Edge *edges = new Edge[n];

		cout << "\nEnter the number of edges: ";
		cin >> e;
		cout << "Enter edges:\n";
		for (i = 0; i < e; ++i)
		{
			cin >> edges[i].source >> edges[i].dest;
			cin >> ch;
			if (strcmpi(ch, "inf") == 0)edges[i].weight = INF;
			else edges[i].weight = atoi(ch);
		}

		Timer t;
		t.start();
		Edge *mst = kruskal(edges, n, e);
		t.stop();

		cout << "\nThe MST contains the following edges\n";
		for (i = 0; i < n - 1; ++i)
		{
			cout << mst[i].source << " - " << mst[i].dest << '\t' << mst[i].weight << endl;
		}
		cout << "\nTime taken to calculate: " << t.time() << " s.\n";
		return;
	}
	void analyze()
	{
		int i;
		Edge * edges;

		Timer t;
		cout << "\nAnalysis\nVertices\tTime\n";
		for (i = 20; i <= MAX; i += 20)
		{
			edges = generateEdges(i);
			t.start();
			kruskal(edges, i, 2 * i);
			t.stop();

			cout << i << '\t' << t.time() << endl;
			delete edges;
			t.reset();
		}
	}
};
int main()
{
	Kruskal k;
	k.analyze();
	return 0;
}


