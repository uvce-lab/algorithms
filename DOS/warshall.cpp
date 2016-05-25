#include <iostream.h>
#include <stdlib.h>
#include <Timer.h>
#include <stdio.h>
#define MAX (0)
//using namespace std;



class Warshall
{
	int **a;
	int ***storage;
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
				arr[i][j] = rand() % 2;
	}
public:
	Warshall()
	{
		createArray(a);
		initializeArray(a);

		storage = new int **[MAX + 1];
		for (int i = 0; i <= MAX; ++i)
		{
			storage[i] = new int *[MAX];
			for (int j = 0; j < MAX; ++j)
			{
				storage[i][j] = new int[MAX];
			}
		}
	}
	~Warshall()
	{
		int i;
		for (i= 0; i < MAX; ++i)
			delete[] a[i];
		delete[] a;

		for (i = 0; i <= MAX; i++)
		{
			for (int j = 0; j < MAX; j++)
			{
				delete[] storage[i][j];
			}
			delete[] storage[i];
		}
		delete[] storage;
	}
	int ** transitiveClosure(int ***s, int *adjacency[], int size)
	{
		int i, j, k;
		for (i = 0; i < size; ++i)
			for (j = 0; j < size; ++j)
				s[0][i][j] = adjacency[i][j];

		for (k = 1; k < size; ++k)
			for (i = 0; i < size; ++i)
				for (j = 0; j < size; ++j)
					s[k][i][j] = (s[k - 1][i][j] | (s[k - 1][i][k] & s[k - 1][k][j]));
		return s[k - 1];
	}
	void demo()
	{
		int i, j, size;
		cout << "Enter the number of nodes in the graph: ";
		cin >> size;

		Timer t;


		int **arr = NULL;
		createArray(arr, size);

		printf("Enter the adjacency matrix [%d * %d]:\n", size, size);
		for (i = 0; i < size; ++i)
		{
			for (j = 0; j < size; ++j)
			{
				cin >> arr[i][j];
			}
		}

		t.start();
		transitiveClosure(this->storage, arr, size);
		t.stop();

		cout << "The transitive closure:\n";
		for (i = 0; i < size; ++i)
		{
			for (j = 0; j < size; ++j)
			{
				cout << arr[i][j] << " ";
			}
			cout << endl;
		}
		cout << "\nTime taken to calculate closure: " << t.time() << endl;
	}
	void analyze()
	{
		Timer t;
		cout << "ANALYSIS\n";
		for (int i = 0; i <= MAX; i+=50)
		{
			t.start();
			transitiveClosure(storage, a, i);
			t.stop();

			cout << i << '\t' << t.time() <<  endl;
			t.reset();
		}
	}
};
int main()
{
	Warshall warshall;
	warshall.demo();
	warshall.analyze();
	return 0;
}