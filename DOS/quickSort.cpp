#include <iostream.h>
#include <Timer.h>
#include <conio.h>
#include <stdlib.h>
#define MAX 5000

class QuickSort
{
	int partition(int a[], int low, int high)
	{
		int p, i, j;
		i = low + 1;
		j = high;
		p = a[low];
		while (1)
		{
			while (i<high && p >= a[i])++i;
			while (j >= low && p<a[j])--j;
			if (i < j)
			{
				int t = a[i];
				a[i] = a[j];
				a[j] = t;
			}
			else
			{
				int t = a[low];
				a[low] = a[j];
				a[j] = t;
				return j;
			}
		}
	}
	void display(int a[], int size)
	{
		for (int i = 0; i<size; ++i)cout << a[i] << " ";
		cout << endl;
	}
public:
	void quick(int a[], int low, int high)
	{
		if (low<high)
		{
			int j = partition(a, low, high);
			quick(a, low, j - 1);
			quick(a, j + 1, high);
		}
	}
	void demo()
	{
		int size;
		cout << "\nEnter the size of the  array: ";
		cin >> size;

		int *a = new int[size];
		cout << "\nEnter " << size << " numbers: ";
		for (int i = 0; i<size; ++i)cin >> a[i];

		cout << "Array contents: \n";
		display(a, size);

		quick(a, 0, size - 1);

		cout << "Array contents after sorting: ";
		display(a, size);
	}
	void analyze()
	{
		int a[MAX], i;
		Timer t;
		for (i = 0; i<MAX; i += 500)
		{
			for (int j = 0; j < i; ++j)a[j] = rand() % 5000;
			t.start();
			quick(a, 0, i - 1);
			t.stop();
			cout << i << "\t" << t.time() << endl;
			t.reset();
		}
	}
};

int main()
{
	clrscr();
	QuickSort q;
	q.demo();
	q.analyze();
	return 0;
}