#include <iostream.h>
#include <Timer.h>
#include <stdlib.h>

#define MAX (160)
class Knapsack
{
	//x and y are the two values whose maximum will be returned
	int max(int x, int y)
	{
		return (x > y) ? x : y;
	}
	int * randomArray(int size)
	{
		int *arr = new int[size];
		for (int i = 0; i < size; ++i)
			arr[i] = rand() % MAX;
		return arr;
	}
public:
	int knapsack(int *values, int *weights, int n, int capacity)
	{
		int row = n + 1, col = capacity + 1;
		int i, j;

		//Create a table with 'n + 1' rows and 'capacity + 1' columns.
		int **t = new int*[row];
		for (i = 0; i < row; ++i)
			t[i] = new int[col];

		for (i = 0; i < row; ++i)
		{
			for (j = 0; j < col; ++j)
			{
				if (i == 0 || j == 0)t[i][j] = 0;
				else if (j - weights[i - 1] >= 0)t[i][j] = max(t[i - 1][j], values[i - 1] + t[i - 1][j - weights[i - 1]]);
				else t[i][j] = t[i - 1][j];
			}
		}
		int res = t[n][capacity];

		for (i = 0; i < row; ++i)delete t[i];
		delete t;
		return res;
	}

	void demo()
	{
		int size, cap, res;
		cout << "\nEnter the number of items: ";
		cin >> size;

		int *val = new int[size];
		int *w = new int[size];

		cout << "\nEnter the weight and value pairs:\n";
		for (int i = 0; i < size; ++i)cin >> w[i] >> val[i];

		cout << "\nEnter the capacity of the knapsack: ";
		cin >> cap;

		cout << "The maximum profit that can be earned equals ";
		Timer t;
		t.start();
		res = knapsack(val, w, size, cap);
		t.stop();
		cout << res << endl;

		cout << "\nTime taken to calculate profit: " << t.time() << " s." << endl;
	}
	void analyze()
	{
		Timer t;
		cout << "\nANALYSIS\nItems\tTime Taken\n";
		int *val = randomArray(MAX);
		int *weights = randomArray(MAX);

		for (int i = 10; i <= MAX; i += 10)
		{
			t.start();
			knapsack(val, weights, i, MAX);
			t.stop();

			cout << i << '\t' << t.time() << endl;
			t.reset();
		}
	}
};

int main()
{
	Knapsack k;
	k.demo();
	k.analyze();
}
