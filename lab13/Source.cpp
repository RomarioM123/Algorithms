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
	int key;				//ключ
	int info;				//информационное поле
	Tree* left, * right;	//указатель на левый и правый узел

public:
	Tree()					//конструктор по умолчанию
	{ 
		key = 0; 
		left = right = NULL; 
	} 
	Tree(int key, int info)	//конструктор с параметр
	{
		this->key = key;
		this->info = info;
		left = right = NULL;
	}
	~Tree() {}				//Деструктор

	void Insert(int, int, Tree*);				//функция добавления элемента в дерево. Возвращает указатель на корень
	void PrintTree(Tree*, int) const;			//вывод дерева на экран
	void DeleteTree(Tree*);						//удаление дерева
	void Task(Tree*);							//индивидуальное задание
};

int main()
{
	setlocale(LC_ALL, "Rus");
	int SIZE = 20;
	int number, info;

	number = rand() % 100 + 1;						//случайные значения
	info = rand() % 100 + 1;

	Tree* root = new Tree(number, info);	//создание корня
	
	for (size_t i = 1; i < SIZE; i++)
	{
		number = rand() % 100 + 1;				//случайные значения
		info = rand() % 100 + 1;
		root->Insert(number, info, root);
	}
	
	cout << endl;
	root->PrintTree(root, 5);
	root->Task(root);
	cout << endl << "Количество листьев: " << LEAVES;
	root->DeleteTree(root);						//освобождение памяти

	if (_CrtDumpMemoryLeaks())
		cout << "\n\nУтечка памяти обнаружена." << endl;
	else
		cout << "\n\nУтечка памяти отсутствует." << endl;

	return 0;
}

void Tree::Insert(int n, int inf, Tree* ptr)
{
	cout << "\n Добавляется элемент (" << n << ";" << inf << ")\n";
	bool flag = true;
	Tree* p, * q;
	p = ptr;
	while (flag)
	{
		if (n < p->key)
		{
			q = p->left;	 //a3
			cout << "Найден узел " << p->key << endl << "Переход влево" << endl;
			
			if (q == NULL)  
				cout << "NULL" << endl;
			else 
				cout << q->key << endl;
			
			if (q == NULL)
			{
				flag = false;
				cout << "Создается новый элемент (" << n << "," << inf << ")\n";
				q = new Tree(n, inf);
				cout << "Обновление связей: " << p->key << "->left = " << q->key << endl;
				p->left = q;
			}
			else 
				p = q;
		}
		else if (n > p->key)
		{
			q = p->right;		 //a4
			cout << "Найден узел " << p->key << endl << "Переход вправо" << endl;
			
			if (q == NULL)
				cout << "NULL" << endl;
			else 
				cout << q->key << endl;
			
			if (q == NULL)
			{
				flag = false;
				cout << "Создается новый элемент (" << n << "," << inf << ")\n ";
				q = new Tree(n, inf);
				cout << "Обновление связей: " << p->key << "->right = " << q->key << endl;
				p->right = q;
			}
			else 
				p = q;
		}
		else if (n == p->key)
		{
			cout << "Такой элемент уже существует " << endl;
			flag = false;		//выход из цикла WHILE
		}
	}
}
void Tree::PrintTree(Tree* ptr, int n) const
{
	if (ptr)
	{
		PrintTree(ptr->right, n + 3);		//вызов для правого поддерева
		for (size_t i = 1; i < n; i++)
			cout << " ";
		
		cout << ptr->key << endl;
		PrintTree(ptr->left, n + 3);		//вызов для левого поддерева
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

