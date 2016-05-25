#include <iostream.h>
#include <conio.h>
#include <Timer.h>
#include <stdlib.h>
#define MAX (160)

enum bool { false, true };

class HeapSort
{
	int *a, size;
	void bottomUpHeapify(int *H, int n)
	{
		int i, k, j, v;
		bool heap;
		for (i = n / 2; i > 0; --i)
		{
			k = i;
			v = H[k - 1];
			heap = false;
			while (heap != true && 2 * k <= n)
			{
				j = 2 * k;
				if (j < n)
					if (H[j - 1] < H[j])j++;
				if (v >= H[j - 1])
					heap = true;
				else
				{
					H[k - 1] = H[j - 1]; k = j;
				}
			}
			H[k - 1] = v;
		}
	}
public:
	HeapSort(int size = MAX)
	{
		this->size = size;
		a = new int [size];
	}
	void printArray(int *a, int size)
	{
		cout << "[ ";
		for (int i = 0; i < size - 1; ++i) cout << a[i] << ", ";
		cout << a[size - 1];
		cout << " ]";
	}

	//a: The array to be sorted
	//n: The size of the array
	void sort(int *a, int n)
	{
		int i, temp;
		int index = n - 1;
		for (i = n; i > 0; --i, index--)
		{
			bottomUpHeapify(a, i);
			temp = a[0];
			a[0] = a[index];
			a[index] = temp;
		}
	}
	void demo()
	{
		int i, size;
		cout << "\nEnter the number of elements: ";
		cin >> size;

		for (i = 0; i < size; ++i)
		{
			cin >> a[i];
		}

		cout << "\nArray before sorting: ";
		printArray(a, size);

		sort(a, size);

		cout << "\nArray after sorting: ";
		printArray(a, size);

	}
	void analyze()
	{
		Timer t;
		int i, j;
		cout << "\nANALYSIS\nSIZE\tTIME\n";
		for (i = 10; i <= MAX; i += 10)
		{
			for (j = 0; j < i; ++j)
			{
				this->a[j] = rand() % MAX;
			}
			//Store elements in increasing order

			t.start();
			sort(this->a, i);
			t.stop();

			cout << i << '\t' << t.time() << endl;
			t.reset();
		}
	}
};

int main()
{
	HeapSort hs;
	hs.demo();
	hs.analyze();
	cout << endl;
}