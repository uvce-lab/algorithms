#include <iostream.h>
#include <stdlib.h>
#include <stdio.h>
#include <Timer.h>
#include <string.h>
#define MAX (120)
#define INF (15000)

class Floyd
{
	int **a;
	int **d;
	void createArray(int ** &arr, int size = MAX)
	{
		arr = new int*[size];
		for (int i = 0; i < size; ++i)
			arr[i] = new int[size];
	}
	void initializeArray(int **arr, int size = MAX)
	{
		for (int i = 0; i < size; ++i)
			for (int j = 0; j < size; ++j)
				arr[i][j] = rand() % 15000;
	}
public:
	Floyd()
	{
		createArray(a);
		initializeArray(a);

		createArray(d);
	}
	~Floyd()
	{
		int i;
		for (i = 0; i < MAX; ++i)
		{
			delete[] a[i];
			delete[] d[i];
		}
		delete[] a;
		delete[] d;
	}
	int ** algorithm(int **d, int **weight, int size)
	{
		int i, j, k;
		for (i = 0; i < size; ++i)
			for (j = 0; j < size; ++j)
				d[i][j] = weight[i][j];

		for (k = 0; k < size; ++k)
			for (i = 0; i < size; ++i)
				for (j = 0; j < size; ++j)
				{
					if (d[i][k] == INF || d[k][j] == INF)
						continue;
					if (d[i][j] > d[i][k] + d[k][j])
						d[i][j] = d[i][k] + d[k][j];
				}
		return d;
	}
	void demo()
	{
		int i, j, size;
		char str[40];
		cout << "\nEnter the number of nodes in the graph: ";
		cin >> size;

		Timer t;

		int **arr = NULL;
		createArray(arr, size);
		printf("Enter the weight matrix [%d * %d]\n(Enter INF for unreachable nodes):\n", size, size);
		for (i = 0; i < size; ++i)
		{
			for (j = 0; j < size; ++j)
			{
				scanf(" %s", str);
				if (strcmpi(str, "inf") == 0) arr[i][j] = INF;
				else arr[i][j] = atoi(str);
			}
		}

		t.start();
		arr = algorithm(this->d, arr, size);
		t.stop();

		cout << "All Source Shortest Path Matrix:\n";
		for (i = 0; i < size; ++i)
		{
			for (j = 0; j < size; ++j)
			{
				if (arr[i][j] == INF)
				{
					cout << "INF "; continue;
				}
				cout << arr[i][j] << " ";
			}
			cout << endl;
		}
		cout << "\nTime taken by Floyd's Algorithm: " << t.time() << endl;
	}
	void analyze()
	{
		Timer t;
		cout << "ANALYSIS\n";
		for (int i = 0; i <= MAX; i += 10)
		{
			t.start();
			algorithm(d, a, i);
			t.stop();

			cout << i << '\t' << t.time() << endl;
			t.reset();
		}
	}
};
int main()
{
	Floyd floyd;
	//floyd.demo();
	floyd.analyze();
	return 0;
}