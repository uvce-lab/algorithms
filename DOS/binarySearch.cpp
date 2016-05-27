#include <iostream.h>
#include <Timer.h>
#include <conio.h>
#include <stdlib.h>
#define MAX 5000
class BinarySearch
{
	int bs(int a[], int low, int high, int key)
	{
		if(low>high) return -1;
		int mid = (low+high)/2;
		if(a[mid] == key)return mid;
		if(key>a[mid]) return bs(a, mid+1, high, key);
		else return bs(a, low, mid-1, key);
	}
public:
	void demo()
	{

		int size;
		cout << "Enter the size of the array: ";
		cin >> size;

		int *arr = new int[size];
		for(int i=0; i<size; ++i)
		{
			cin >> arr[i];
		}

		int key;
		cout << "Enter the key to be searched for: ";
		cin >> key;

		int res = bs(arr, 0, size, key);
		if(res != -1)
		{
			for(int i=0; i<size; ++i)
			{
				cout << arr[i] << " ";
			}
			cout << "\nElement found at index: " << res << "\n";
		}
		else
		{
			cout << "\nElement was not present in the array.\n";
		}
	}
	void analyze()
	{
		int a[MAX], i;
		cout << "\nANALYSIS\n";
		Timer t;
		for(i = 0; i<MAX; ++i)a[i] = i;
		for(i=0; i<=MAX; i+=500)
		{
			t.start();
			bs(a, 0, i, -1);
			t.stop();
			cout << i << "\t" << t.time() << endl;
			t.reset();
		}
	}
};
int main()
{
	clrscr();
	BinarySearch bs;
	bs.demo();
	bs.analyze();
	return 0;
}