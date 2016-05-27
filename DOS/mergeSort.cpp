#include <iostream.h>
#include <stdlib.h>
#include <Timer.h>
#include <conio.h>

#define MAX 5000
class MergeSort
{
	int c[MAX];
	void merge(int a[], int low, int high, int mid)
	{
		int i, j, k;
		i = low;
		k = low;
		j = mid + 1;
		while (i <= mid && j <= high)
		{
			if (a[i] < a[j])
			{
				c[k++] = a[i++];
			}
			else
			{
				c[k++] = a[j++];
			}
		}
		while (i <= mid)
		{
			c[k++] = a[i++];
		}
		while (j <= high)
		{
			c[k++] = a[j++];
		}
		for (i = low; i < k; i++)
		{
			a[i] = c[i];
		}
	}
	void display(int a[], int size)
	{
		for(int i=0; i<size; ++i)
			cout << a[i] << " ";
		cout << endl;
	}
public:
	void mergeSort(int a[], int low, int high)
	{
		int mid;
		if (low < high)
		{
			mid = (low + high) / 2;
			mergeSort(a, low, mid);
			mergeSort(a, mid + 1, high);
			merge(a, low, high, mid);
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

		cout << "Array contents: ";
		display(a, size);

		mergeSort(a, 0, size - 1);

		cout << "Array contents after sorting: ";
		display(a, size);
	}
	void analyze()
	{
		int a[MAX], i;
		Timer t;
		for (int j = 0; j < MAX; ++j)a[j] = rand() % MAX;
		cout << "\nSize\tTime\n";
		for (i = 0; i <= 5000; i += 500)
		{

			t.start();
			mergeSort(a, 0, i - 1);
			t.stop();
			cout << i << "\t" << t.time() << endl;
			t.reset();
		}
	}
};


int main()
{
	MergeSort m;
	m.demo();
	cout << "\nANALYSIS\n";
	m.analyze();

	return 0;
}