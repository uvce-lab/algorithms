#include <iomanip>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <Timer.h>
#include <stdlib.h>

using namespace std;

class Horspool
{
private:
	char *text, *pattern;
	int textLength, patternLength, count;
	int *occurences;

	int *shiftTable(char *p, int m)
	{

		int *table = new int[256];
		for (int i = 0; i < 256; ++i)
			table[i] = m;

		for (int j = 0; j < m - 1; ++j)
		{
			table[p[j] + 128] = m - 1 - j;
		}
		return table;
	}
	void reset()
	{
		count = 0;
	}
	static char * generateRandomString(int size)
	{
		char *str = new char[size + 1];
		for (int i = 0; i < size; ++i)
		{
			//Generate charactes that range from -128 to 127
			str[i] = (rand() % 256) - 128;
		}
		str[size - 1] = '\0';
		return str;
	}
public:
	Horspool(char *text, char *pattern)
	{
		this->text = text;
		this->pattern = pattern;

		textLength = (int)strlen(text);
		patternLength = (int)strlen(pattern);

		occurences = new int[textLength];
		count = 0;
	}
	~Horspool()
	{
		delete occurences;
	}
	void horspool(char *p, char *t, int n, int m, int &count)
	{
		int i, k, index = 0;
		int * table = shiftTable(p, m);


		for (i = m - 1; i <= n - 1;)
		{
			k = 0;
			while (k <= m - 1 && p[m - 1 - k] == t[i - k])
			{
				k++;
			}
			if (k == m) { occurences[index++] = i - m + 1; }

			//Index t[i] + 128 is used as the chacter with value -128 is mapped to zeroth index of the ShiftTable
			i += table[t[i] + 128];
		}
		count = index;
	}
	void print(char * arr, int start)
	{
		int end = (int)strlen(arr) - 1;
		if (start + 4 < end + 1) end = end = start + 4;
		for (int i = start; i <= end; ++i)
		{
			cout << arr[i] << " ";
		}
	}
	static void demo()
	{
		char t[1024], p[1024];
		cout << "\nEnter the text: ";
		gets(t);
		cout << "\nEnter pattern to search for: ";
		gets(p);

		Horspool h(t, p);
		Timer timer;
		timer.start();
		h.horspool(h.pattern, h.text, h.textLength, h.patternLength, h.count);
		timer.stop();

		h.display();

		cout << "\nTime taken to evaluate the occurences " << timer.time() << " s." << endl;
	}
	void display()
	{
		system("cls");
		cout << "\nRESULTS";
		cout << "\nGiven string: " << text;
		cout << "\nAll occurences of: " << pattern;
		if (count != 0)
		{
			cout << "\nTotal Number of occurences: " << count;

			cout << "\n\nIndex\tText\n";
			for (int i = 0; i < count; ++i)
			{
				cout << endl;
				cout << occurences[i] << '\t';
				print(text, occurences[i]);
			}
		}
		else cout << "\n\nThe text does not contain the specified pattern.";
		cout << endl;
	}
	static void analyze()
	{
		int max = 1000;
		char *t, *p;
		Timer timer;

		cout << "\nANALYSIS";

		cout << "\nBy varying length of pattern (Length of text = " << max << " characters)";
		cout << "\nLength \tTime\n";

		t = generateRandomString(max);
		
		for (int i = 0; i <= max; i += 50)
		{
			p = generateRandomString(i);

			Horspool h(t, p);
			timer.start();
			h.horspool(h.pattern, h.text, h.textLength, h.patternLength, h.count);
			timer.stop();

			cout << i << '\t' << setprecision(3)  << std::scientific << timer.time() << endl;
			delete p;
		}

		cout << "\n\nBy varying length of text (Length of pattern = " << int(max/10) << " characters)";
		cout << "\nLength \tTime\n";

		p = generateRandomString(int(max/10));
		for (int i = 0; i <= max; i += 50)
		{
			t = generateRandomString(i);

			Horspool h(t, p);
			timer.start();
			h.horspool(h.pattern, h.text, h.textLength, h.patternLength, h.count);
			timer.stop();

			cout << i << '\t' << setprecision(3)  << std::scientific << timer.time() << endl;
			delete t;
		}
	}
};


int main()
{
	Horspool::demo();
	Horspool::analyze();
	return 0;
}
