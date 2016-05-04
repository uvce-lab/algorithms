#include <iostream.h>
#include <timer.h>

#define MAX 5000

class Array
{
public:
	int a[MAX];
	void valueGenerator(int size, int limit)
	{
		for (int i = 0; i < size; ++i) a[i] = limit - i;
	}
};
class Printer
{
public: static void print(int a[], int size)
	{
		for(int i=0; i<size; ++i) cout << a[i] << " ";
	}
};
class SelectionSort
{
public:
	void selectionSort(int a[], int size)
	{
		int minAt, temp;
		for (int i = 0; i < size; ++i)
		{
			minAt = i;
			for (int j = i+1; j < size; ++j)
				if (a[j] < a[minAt])
					minAt = j;
			temp = a[i];
			a[i] = a[minAt];
			a[minAt] = temp;
		}
	}
	void analyze(Array arr)
	{
		Timer t;
		cout << "\nANALYSIS\nSIZE\tTIME" << endl;
		for (int i = 0; i <= 5000; i += 500)
		{
			arr.valueGenerator(i, 5000);
			t.start();
			this->selectionSort(arr.a, i);
			t.stop();
			cout << i << "\t" << t.time() << endl;
			t.reset();
		}
	}
	void demo()
	{
		Timer t;
		int size, *a;
		cout << "\nEnter size of the array: ";
		cin >> size;
		a = new int[size];
		cout << "\nEnter " << size << " numbers: ";
		for(int i=0; i<size; ++i) cin >> a[i];
		t.start();
		this->selectionSort(a, size);
		t.stop();
		cout << "\nSorted array: "; Printer::print(a, size);
		cout << "\nSize: " << size << "\tTime: " << t.time() << " s\n";
	}

};
int main()
{
	Array arr;
	SelectionSort sel;
	sel.demo();
	sel.analyze(arr);
	return 0;
}

