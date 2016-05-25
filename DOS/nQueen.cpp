#include <iostream.h>
#include <Timer.h>

enum bool { false, true };

class NQueensProblem
{
private:
	int **arr, n;
	bool calculated;
	bool isSafeToPlace(int **arr, int row, int col)
	{
		int i, j;

		/* Check this row on left side */
		for (i = 0; i < col; i++)
			if (arr[row][i])
				return false;

		/* Check upper diagonal on left side */
		for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
			if (arr[i][j])
				return false;

		/* Check lower diagonal on left side */

		for (i = row, j = col; j >= 0 && i < n; i++, j--)
			if (arr[i][j])
				return false;

		return true;
	}
	bool internalNQueen(int **arr, int n, int col)
	{
		if (col >= n)return true;

		for (int i = 0; i < n; ++i)
		{
			if (isSafeToPlace(arr, i, col))
			{
				arr[i][col] = 1;
				if (internalNQueen(arr, n, col + 1))
					return true;
				arr[i][col] = 0;
			}
		}
		return false;
	}
	int ** createArray(int x, int y)
	{
		int ** temp = new int*[x], i, j;
		for (i = 0; i < x; ++i)
		{
			temp[i] = new int[y];
			for (j = 0; j < y; ++j)
				temp[i][j] = 0;
		}

		return temp;
	}
public:
	NQueensProblem(int n)
	{
		this->n = n;
		this->calculated = false;
	}
	~NQueensProblem()
	{
		for (int i = 0; i < n; ++i)
			delete arr[i];
		delete arr;
	}
	bool NQueen()
	{
		arr = createArray(n, n);
		calculated = true;
		return internalNQueen(arr, n, 0);
	}
	void display()
	{
		if (this->calculated == false)
		{
			cout << "\nUse NQueen method to solve the problem first...\n";
			return;
		}
		cout << "\nSolution\n";
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				cout << ((arr[i][j] == 0) ? "- " : "Q ");
			}
			cout << endl;
		}
	}
	static void analyze(int max)
	{
		cout << "\nANALYSIS\n";
		Timer t;

		cout << "\nSize\tTime\n";
		for (int i = 0; i <= max; ++i)
		{
			NQueensProblem temp(i);

			t.start();
			temp.NQueen();
			t.stop();

			cout << i << "\t" << t.time() << endl;
			t.reset();
		}

	}
};
int main()
{
	int n;
	cout << "\nEnter size of board: ";
	cin >> n;
	NQueensProblem nq1(n);

	bool solvable = nq1.NQueen();
	if (solvable)
		nq1.display();
	else cout << "\nA solution is not possible for the given size.";

	NQueensProblem::analyze(10);
}