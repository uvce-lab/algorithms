#include <iostream>
#include <Timer.h>
#include <stdio.h>

#define MAX 5000

using namespace std;
class Array
{
public:
	int a[MAX];
	void randomGenerator(int size, int limit)
	{
		for (int i = 0; i < size; ++i)
		{
			// Make sure all elements are different in the array
			a[i] = limit - i;
		}
	}
};
class SequentialSearch
{
public:
	int sequentialSearch(int a[], int size, int key)
	{
		for (int i = 0; i < size; ++i)
			if (a[i] == key) return i;
		return -1;
	}
	void analyze(Array arr)
	{
		Timer t;
		cout << "\nANALYSIS \nN\tTIME\n";
		for (int i = 0; i <= 5000; i += 500)
		{
			arr.randomGenerator(i, 5000);
			t.start();
			this->sequentialSearch(arr.a, i, arr.a[i - 1]);
			//key as arr.a[i - 1] ensures worst case
			t.stop();
			cout << i << "\t" << t.time() << endl;
			t.reset();
		}
	}
	void demo()
	{
		Timer t;
		int size, *a, key;

		cout << "\nEnter size of the array: ";
		cin >> size;

		a = new int[size];

		cout << "\nEnter " << size << " numbers: ";
		
		for (int i = 0; i < size; ++i) cin >> a[i];
		
		cout << "\nEnter the number to be searched for: ";
		cin >> key;
		
		t.start();
		int pos = sequentialSearch(a, size, key);
		t.stop();
		
		if (pos == -1)
			cout << "\nThe number was not found.\n";
		else cout << "\nThe number was found at position: " << pos << '\n';
		
		printf("\nSize of array: %d\nTime taken: %lf s\n", size, t.time());
	}
};
int main()
{
	Array arr;
	SequentialSearch seq;
	seq.demo();
	seq.analyze(arr);
	return 0;
}
