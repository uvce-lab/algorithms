#include<iostream.h>
#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100
#define INF (INT_MAX)

class TSP
{
	int n, a[MAX][MAX], v[MAX];
	int Least(int c)
	{
		int i, nc = INF, min = INF;

		for (i = 0; i < n; i++)
		{
			if (a[c][i] != 0 && v[i] == 0)
			{
				if (a[c][i] < min)
				{

					min = a[c][i];
					nc = i;
				}
			}

		}
		if (min != INF)
			cost += min;
		return nc;
	}
public:
	int source;
	int cost;
	void ReadData()
	{
		cout << "Enter the no. of cities: " ;
		cin >> n;

		cout << "Enter the cost matrix (INF for unreachable cities):\n";

		char ch[10];
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				scanf("%s", ch);
				a[i][j] = ((strcmpi(ch, "inf") == 0)? INF: atoi(ch));
				v[i] = 0;
			}
		}
	}
public:
	TSP() { cost = 0; }
	void Mincost(int city)
	{
		int ncity;
		v[city] = 1;
		printf(" %5d ", city);
		ncity = Least(city);

		if (ncity == INF)
		{
			ncity = source;
			cout << ncity;
			cost += a[city][ncity];
			return;
		}
		Mincost(ncity);
	}
};



void main()
{
	int i, j;
	TSP t;

	t.ReadData();

	cout << "Enter the source city: ";
	cin >> t.source;

	cout << "Sequences of cities visited:\n";

	t.Mincost(t.source);

	cout << endl << "The min cost is: " << t.cost << endl;
}
