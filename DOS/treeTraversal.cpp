#include <iostream.h>
#include <stdlib.h>
#include <Timer.h>
#include <stdio.h>

#define MAX (500)

enum bool { false, true };

char const choice[3][2] =
{
	{ 0, 1 },
	{ 1, 0 },
	{ 1, 1 }
};

template<class T>
class Node
{

public:
	T info;
	Node<T> *lchild, *rchild;
	Node(T info)
	{
		this->lchild = this->rchild = NULL;
		this->info = info;
	}
	void AddChild(T info, int leftChild)
	{
		Node<T> *temp = new Node<T>(info);
		if (leftChild) this->lchild = temp;
		else this->rchild = temp;

	}
	void Create(int &curr, int &size)
	{
		int v = rand() % 3;
		int temp = choice[v][0];
		if (temp && curr < size)
		{
			this->AddChild(rand() % MAX, 0);
			curr++;
			this->rchild->Create(curr, size);
		}
		temp = choice[v][1];
		if (temp && curr < size)
		{
			this->AddChild(rand() % MAX, 1);
			curr++;
			this->lchild->Create(curr, size);
		}
	}

	static void PreOrder(Node<T> *n, bool &print)
	{
		if (n != NULL)
		{
			if (print)
				cout << n->info << " => ";
			PreOrder(n->lchild, print);
			PreOrder(n->rchild, print);
		}
	}
	static void PostOrder(Node<T> *n, bool &print)
	{
		if (n != NULL)
		{
			PostOrder(n->lchild, print);
			PostOrder(n->rchild, print);
			if (print)
				cout << n->info << " => ";
		}
	}
	static void InOrder(Node<T> *n, bool &print)
	{
		if (n != NULL)
		{
			InOrder(n->lchild, print);
			if (print)
				cout << n->info << " => ";
			InOrder(n->rchild, print);
		}
	}
};

template<class T>
class Tree
{
private:
	Node<T> *root;
public:
	Tree()
	{
		root = NULL;
	}
	static void Delete(Node<T> *n)
	{
		if (n != NULL)
		{
			if (n->lchild == NULL && (n->rchild == NULL))
			{
				delete n;
				return;
			}
			Delete((*n).lchild);
			Delete((*n).rchild);
		}
	}
	static Tree<T> * CreateAI(int size)
	{
		Tree<T> *tree = new Tree<T>();
		int count = 0;

		tree->root = new Node<T>(rand() % MAX);
		count++;
		tree->root->Create(count, size);
		return tree;
	}
	static Node<T> * CreateHuman(char *ch)
	{
		T r; int ans;
		printf("Enter the data for %s: ", ch);
		cin >> r;
		Node<T> * node = new Node<T>(r);

		cout << "Create a left child for " << r << "? ";
		cin >> ans;
		if (ans) node->lchild = CreateHuman("Left Child");

		cout << "Create a right child for " << r << "? ";
		cin >> ans;
		if (ans) node->rchild = CreateHuman("Right Child");

		return node;
	}
	static void analyze()
	{
		bool print = false;
		Timer t;
		cout << "SIZE\tPRE-ORDER\tIN-ORDER\tPOST-ORDER\n";
		for (int i = 50; i <= MAX; i += 50)
		{
			//Create tree with i nodes
			Tree<T> * tree = CreateAI(i);
			//Traverse and watch time taken

			t.start();
			Node<T>::PreOrder(tree->root, print);
			t.stop();
			cout << i << "\t" << t.time();
			t.reset();

			t.start();
			Node<T>::InOrder(tree->root, print);
			t.stop();
			cout << "\t" << t.time();
			t.reset();

			t.start();
			Node<T>::PostOrder(tree->root, print);
			t.stop();
			cout << "\t" << t.time();
			t.reset();

			Tree<T>::Delete(tree->root);
			cout << endl;
		}
	}
	static void demo()
	{
		Tree<T> *tree = new Tree<T>();
		cout << '\n';
		tree->root = CreateHuman("Root");
		bool p = true;
		cout << "\n\nPreOrder: ";
		Node<T>::PreOrder(tree->root, p);

		cout << "\n\nInOrder: ";
		Node<T>::InOrder(tree->root, p);

		cout << "\n\nPostOrder: ";
		Node<T>::PostOrder(tree->root, p);
	}
};



int main()
{
	Tree<int>::demo();
	cout << "\nANALYSIS\n";
//	Tree<int>::analyze();
	return 0;
}
