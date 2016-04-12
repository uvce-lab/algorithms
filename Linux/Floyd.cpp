#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX (600)
#define INF (15000)
using namespace std;

class Floyd
{
public:
	int ** algorithm(int ** d, int **weight, int size)
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
    int **createArray(int size)
    {
        int i, j;
        int **arr = new int *[size];
        for (i = 0; i < size; ++i)
        {
            arr[i] = new int[size];
        }
        return arr;
    }
    int ** initializeArray(int &size)
    {
        int i, j;
        char str[40];
        cout << "Enter the number of nodes in the graph: ";
        cin >> size;
        int **arr = createArray(size);
        printf("Enter the weight matrix [%d * %d]\n(Enter INF for unreachable nodes):\n", size, size);
        for (i = 0; i < size; ++i)
        {
            for (j = 0; j < size; ++j)
            {
                scanf(" %s", str);
                if (_strcmpi(str, "inf") == 0) arr[i][j] = INF;
                else arr[i][j] = atoi(str);
            }
        }
        return arr;
    }
};
int main()
{
    Floyd f;

	int i, j, size;
    int ** arr = f.initializeArray(size);
    
	int ** d = f.createArray(size);
	d = f.algorithm(d, arr, size);

	cout << "All Source Shortest Path Matrix:\n";
	for (i = 0; i < size; ++i)
	{
		for (j = 0; j < size; ++j)
        {
            if(d[i][j] == INF) cout << "INF\t";    
            else cout << d[i][j] << "\t";
        }
		cout << endl;
	}

	return 0;
}