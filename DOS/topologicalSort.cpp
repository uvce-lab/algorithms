#include <iostream.h>
#include <stdio.h>
#include <Timer.h>
#include <stdlib.h>

#define MAX 160

class TopologicalSort
{
	int **adjacency;
	int vertices;
	int *indegree;
	int *s;
	int *result;
	void reset()
	{
		int i, j;

		for (i = 0; i < vertices; ++i)
		{
			for (j = 0; j < vertices; ++j)
			{
				if (i < j) adjacency[i][j] = rand() % 2;
				else adjacency[i][j] = 0;
			}
		}
	}
public:
	TopologicalSort(int size = MAX)
	{
		int i;
		this->vertices = size;

		this->adjacency = new int *[size];
		for (i = 0; i < vertices; ++i)
		{
			adjacency[i] = new int[vertices];
		}

		indegree = new int[vertices];
		s = new int[vertices];
		result = new int[vertices];
	}
	int sort(int **adjacency, int n, int *indegree, int *s, int *result)
	{
		int i, j, sum;
		for (i = 0; i < n; ++i)
		{
			sum = 0;
			for (j = 0; j < n; ++j)
				sum = sum + adjacency[j][i];
			indegree[i] = sum;
		}

		int top = -1;
		for (i = 0; i < n; ++i)
		{
			if (indegree[i] == 0)
			{
				s[++top] = i;
				indegree[i] = -1;
			}
		}

		int u;
		i = 0;

		while (top != -1)
		{
			u = s[top--];
			result[i++] = u;

			for (j = 0; j < n; ++j)
			{
				if (adjacency[u][j] == 1) indegree[j]--;
			}
			for (j = 0; j < n; ++j)
			{
				if (indegree[j] == 0)
				{
					indegree[j] = -1;
					s[++top] = j;
				}
			}
		}
		return i;
	}

	void printArray(int *arr, int size)
	{
		cout << "[ ";
		for (int i = 0; i < size - 1; ++i)
		{
			cout << arr[i] << ", ";
		}
		cout << arr[size - 1] << " ]";
	}
	void demo() d
	{
		int i, j, size;

		Timer t;
		cout << "\nEnter number of vertices: ";
		cin >> size;
		printf("\nEnter the adjacency matrix [%d * %d]:\n", size, size);
		for (i = 0; i < size; ++i)
			for (j = 0; j < size; ++j)
				cin >> adjacency[i][j];



		t.start();
		int res = sort(this->adjacency, size, this->indegree, this->s, this->result);
		t.stop();

		cout << "\nThe topologically sorted vertices: ";
		printArray(this->result, res);

		cout << "\nTime taken to sort the graph: " << t.time() << " s" << endl;
	}
	void analyze()
	{
		int i = 0;
		Timer t;

		reset();

		cout << "\nANALYSIS\nSIZE\tTIME\n";
		for (i = 0; i <= MAX; i += 20)
		{
			t.start();
			sort(this->adjacency, i, this->indegree, this->s, this->result);
			t.stop();

			cout << i << '\t' << t.time() << endl;
		}
	}
};

int main()
{
	TopologicalSort ts;
	ts.demo();
	ts.analyze();
	return 0;
}
