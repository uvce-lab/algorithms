#include <iostream.h>
#include <timer.h>
#include <stdio.h>

#define MAX 5000

class InsertionSort
{
	int *arr, size;
public:
	InsertionSort(int size = MAX)
	{
		this->size = size;
		arr = new int[size];
	}
	void display(int *arr, int size)
	{
		cout << "[ ";
		for (int i = 0; i < size - 1; ++i)
			cout << arr[i] << ", ";
		cout << arr[size - 1] << " ]";
	}
	void insertionSort(int *a, int size)
	{
		int item;
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
	void demo()
	{
		int size;
		cout << "\nEnter number of elements: ";
		cin >> size;
		cout << "\nEnter " << size << " numbers: ";
		for (int i = 0; i < size; ++i)
		{
			cin >> this->arr[i];
		}
		cout << "\nArray contents before sorting: ";
		display(this->arr, size);
		cout << endl;

		insertionSort(this->arr, size);

		cout << "\nArray contents after sorting: ";
		display(this->arr, size);
		cout << endl;
	}
	void analyze()
	{
		Timer t;
		for (int i = 0; i <= 5000; i += 500)
		{
			for (int j = 0; j < i; ++j) arr[j] = 5000 - j;
			t.start();
			insertionSort(arr, i);
			t.stop();
			cout << i << "\t" << t.time() << endl;
			t.reset();
		}
	}
};
int main()
{
	InsertionSort is;
	is.demo();
	is.analyze();
	return 0;
}