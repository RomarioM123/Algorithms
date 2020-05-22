#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

#include<conio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
static int LEAVES = 0;
class Tree
{
	int key;				//����
	int info;				//�������������� ����
	Tree* left, * right;	//��������� �� ����� � ������ ����

public:
	Tree()					//����������� �� ���������
	{ 
		key = 0; 
		left = right = NULL; 
	} 
	Tree(int key, int info)	//����������� � ��������
	{
		this->key = key;
		this->info = info;
		left = right = NULL;
	}
	~Tree() {}				//����������

	void Insert(int, int, Tree*);				//������� ���������� �������� � ������. ���������� ��������� �� ������
	void PrintTree(Tree*, int) const;			//����� ������ �� �����
	void DeleteTree(Tree*);						//�������� ������
	void Task(Tree*);							//�������������� �������
};

int main()
{
	setlocale(LC_ALL, "Rus");
	int SIZE = 20;
	int number, info;

	number = rand() % 100 + 1;						//��������� ��������
	info = rand() % 100 + 1;

	Tree* root = new Tree(number, info);	//�������� �����
	
	for (size_t i = 1; i < SIZE; i++)
	{
		number = rand() % 100 + 1;				//��������� ��������
		info = rand() % 100 + 1;
		root->Insert(number, info, root);
	}
	
	cout << endl;
	root->PrintTree(root, 5);
	root->Task(root);
	cout << endl << "���������� �������: " << LEAVES;
	root->DeleteTree(root);						//������������ ������

	if (_CrtDumpMemoryLeaks())
		cout << "\n\n������ ������ ����������." << endl;
	else
		cout << "\n\n������ ������ �����������." << endl;

	return 0;
}

void Tree::Insert(int n, int inf, Tree* ptr)
{
	cout << "\n ����������� ������� (" << n << ";" << inf << ")\n";
	bool flag = true;
	Tree* p, * q;
	p = ptr;
	while (flag)
	{
		if (n < p->key)
		{
			q = p->left;	 //a3
			cout << "������ ���� " << p->key << endl << "������� �����" << endl;
			
			if (q == NULL)  
				cout << "NULL" << endl;
			else 
				cout << q->key << endl;
			
			if (q == NULL)
			{
				flag = false;
				cout << "��������� ����� ������� (" << n << "," << inf << ")\n";
				q = new Tree(n, inf);
				cout << "���������� ������: " << p->key << "->left = " << q->key << endl;
				p->left = q;
			}
			else 
				p = q;
		}
		else if (n > p->key)
		{
			q = p->right;		 //a4
			cout << "������ ���� " << p->key << endl << "������� ������" << endl;
			
			if (q == NULL)
				cout << "NULL" << endl;
			else 
				cout << q->key << endl;
			
			if (q == NULL)
			{
				flag = false;
				cout << "��������� ����� ������� (" << n << "," << inf << ")\n ";
				q = new Tree(n, inf);
				cout << "���������� ������: " << p->key << "->right = " << q->key << endl;
				p->right = q;
			}
			else 
				p = q;
		}
		else if (n == p->key)
		{
			cout << "����� ������� ��� ���������� " << endl;
			flag = false;		//����� �� ����� WHILE
		}
	}
}
void Tree::PrintTree(Tree* ptr, int n) const
{
	if (ptr)
	{
		PrintTree(ptr->right, n + 3);		//����� ��� ������� ���������
		for (size_t i = 1; i < n; i++)
			cout << " ";
		
		cout << ptr->key << endl;
		PrintTree(ptr->left, n + 3);		//����� ��� ������ ���������
	}
}
void Tree::Task(Tree* ptr)
{
	if (ptr != NULL)
	{
		Task(ptr->left);
		
		if (ptr->left == NULL && ptr->right == NULL)
			LEAVES++;

		Task(ptr->right);
	}
}
void Tree::DeleteTree(Tree* ptr)
{
	if (ptr != NULL)
	{
		DeleteTree(ptr->left);
		DeleteTree(ptr->right);
		delete(ptr);
	}
}

