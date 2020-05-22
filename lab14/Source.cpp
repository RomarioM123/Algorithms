#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include <locale.h>
using namespace std;

#define SIZE 100	//������ ������� ��������

struct node_st				// ��������� ����
{ 
	node_st* left, * right;	// left,right - ����� ������ �����
	int value;				// value - ��������
	bool red;				// red   - ���� (true - ���� �������)
};							

node_st* tree_root = 0;	//������

void Show();			//����� ������ � �������
void Clear();			//������� ������
void Insert(int);		//������� ��������
void Remove(int);		//�������� ��������

int Check();					//�������� ������
int Check(node_st*, int, int);	//�������� ������ (����������� �����)

bool TreeWalk(node_st*, bool*, int);	//����� ������ � ������ �������� � �������� (����������� �����)
bool TreeWalk(bool*, int);				//����� ������ � ������ �������� � ��������
	
node_st* NewItem(int);				//��������� ����� ������
void DelItem(node_st*);				//�������� �������
void Clear(node_st*);				//���� ������ (����������� �����)
void Show(node_st*, int, char);		//����� ������, ����������� �����
node_st* Rotate21(node_st*);		//�������� �����
node_st* Rotate12(node_st*);		//�������� ������
void BalanceInsert(node_st**);		//������������ �������
bool BalanceRemove1(node_st**);
bool BalanceRemove2(node_st**);
bool Insert(int, node_st**);		//����������� ����� �������
bool Insert(int, node_st**);		//����������� ����� �������
bool GetMin(node_st**, node_st**);	//����� � ������ ������������ ���� ���������
bool Remove(node_st**, int);		//����������� ����� ��������

int main()
{
	setlocale(LC_ALL, "Rus");
	int n, i, value = 0;
	bool array[SIZE];
	srand(time(0));

	memset(array, false, sizeof(array));
	printf("���������� ������� ������:\n");
	for (n = 0; n < SIZE * 100; n++) {
		printf("������: %d of %d\r", n + 1, SIZE * 100);
		i = rand() % SIZE; array[i] = true;  Insert(i);
		i = rand() % SIZE; array[i] = false; Remove(i);
	}
	putchar('\n');

	if (TreeWalk(array, SIZE)) 
		printf("*** context error\n\a");

	Show();

	printf("\n������� �����, ������� ���� �������: ");
	scanf_s("%i", &value);
	Remove(value);
	printf("���������:\n");
	Show();


	Clear();

	if (_CrtDumpMemoryLeaks())
		printf("\n\n������ ������ ����������.\n");
	else
		printf("\n\n������ ������ �����������.\n");

	return 0;
}

int Check()		//�������� ������
{
	int d = 0;
	
	if (!tree_root) 
		return 0;
	
	return Check(tree_root, d, 0);
}
int Check(node_st* tree, int b_d, int d)	//�������� ������ (����������� �����)
{
	int n;
	node_st* left = tree->left;
	node_st* right = tree->right;
	
	if (!tree->red) 
		b_d++;
	
	n = Check(left, b_d, d + 1); 
	
	if (n) 
		return n;
	
	return Check(right, b_d, d + 1);
}
bool TreeWalk(node_st* node, bool* array, int size)		//����� ������ � ������ �������� � �������� (����������� �����)
{
	if (!node) 
		return false;

	int value = node->value;

	if (value < 0 || value >= size || !array[value]) 
		return true;

	array[value] = false;

	return TreeWalk(node->left, array, size) || TreeWalk(node->right, array, size);
}
bool TreeWalk(bool* array, int size)	//����� ������ � ������ �������� � ��������
{
	if (TreeWalk(tree_root, array, size)) 
		return true;
	
	for (int n = 0; n < size; n++) 
		if (array[n]) 
			return true;

	return false;
}
void Show()		//����� ������
{
	printf("\n������\n");
	Show(tree_root, 0, '*');
}
void Insert(int value)	//������� �������
{
	Insert(value, &tree_root);
	
	if (tree_root) 
		tree_root->red = false;
}
void Remove(int value)	//�������� ����
{
	Remove(&tree_root, value);
}
void Clear()	//���� ������
{
	Clear(tree_root);
	tree_root = 0;
}
node_st* NewItem(int value)		//��������� ����� ������
{
	node_st* node = new node_st;
	node->value = value;
	node->left = node->right = 0;
	node->red = true;

	return node;
}
void DelItem(node_st* node)		//�������� �������
{
	delete node;
}
void Clear(node_st* node)	//���� ������ (����������� �����)
{
	if (!node) 
		return;
	
	Clear(node->left);
	Clear(node->right);
	DelItem(node);
}
void Show(node_st* node, int depth, char dir)	//����� ������, ����������� �����
{
	int n;
	
	if (!node) 
		return;
	
	for (n = 0; n < depth; n++) 
		putchar(' ');
	
	printf("%c%d (%s)\n", dir, node->value, node->red ? "�������" : "׸����");
	Show(node->left, depth + 2, '-');
	Show(node->right, depth + 2, '+');
}
node_st* Rotate21(node_st* node)	//�������� �����
{
	node_st* right = node->right;
	node_st* p21 = right->left;
	right->left = node;
	node->right = p21;

	return right;
}
node_st* Rotate12(node_st* node)	//�������� ������
{
	node_st* left = node->left;
	node_st* p12 = left->right;
	left->right = node;
	node->left = p12;

	return left;
}
void BalanceInsert(node_st** root)	//������������ �������
{
	node_st* left, * right, * px1, * px2;
	node_st* node = *root;
	
	if (node->red) 
		return;
	
	left = node->left;
	right = node->right;
	
	if (left && left->red) 
	{
		px2 = left->right;
		
		if (px2 && px2->red) 
			left = node->left = Rotate21(left);
		
		px1 = left->left;

		if (px1 && px1->red) 
		{
			node->red = true;
			left->red = false;

			if (right && right->red)
			{	
				px1->red = true;
				right->red = false;

				return;
			}

			*root = Rotate12(node);
		}
	}

	if (right && right->red) 
	{
		px1 = right->left;
		
		if (px1 && px1->red) 
			right = node->right = Rotate12(right);
		
		px2 = right->right;

		if (px2 && px2->red) 
		{
			node->red = true;
			right->red = false;
			
			if (left && left->red) 
			{
				px2->red = true;
				left->red = false;

				return;
			}
			*root = Rotate21(node);
		}
	}
}
bool BalanceRemove1(node_st** root)
{
	node_st* node = *root;
	node_st* left = node->left;
	node_st* right = node->right;
	
	if (left && left->red) 
	{
		left->red = false; 
		return false;
	}

	if (right && right->red)
	{
		node->red = true;
		right->red = false;
		node = *root = Rotate21(node);
		
		if (BalanceRemove1(&node->left)) 
			node->left->red = false;
		
		return false;
	}
	
	unsigned int mask = 0;
	node_st* p21 = right->left;
	node_st* p22 = right->right;
	
	if (p21 && p21->red) 
		mask |= 1;
	if (p22 && p22->red) 
		mask |= 2;
	
	switch (mask)
	{
	case 0:
		right->red = true;
		return true;

	case 1:
	case 3:
		right->red = true;
		p21->red = false;
		right = node->right = Rotate12(right);
		p22 = right->right;

	case 2:
		right->red = node->red;
		p22->red = node->red = false;
		*root = Rotate21(node);

	}
	
	return false;
}
bool BalanceRemove2(node_st** root)
{
	node_st* node = *root;
	node_st* left = node->left;
	node_st* right = node->right;
	
	if (right && right->red)
	{
		right->red = false;

		return false;
	}

	if (left && left->red) 
	{
		node->red = true;
		left->red = false;
		node = *root = Rotate12(node);
		
		if (BalanceRemove2(&node->right)) 
			node->right->red = false;
		
		return false;
	}
	
	unsigned int mask = 0;
	node_st* p11 = left->left;
	node_st* p12 = left->right;
	
	if (p11 && p11->red) 
		mask |= 1;
	if (p12 && p12->red) 
		mask |= 2;
	
	switch (mask) 
	{
	case 0:
		left->red = true;
		return true;

	case 2:
	case 3:
		left->red = true;
		p12->red = false;
		left = node->left = Rotate21(left);
		p11 = left->left;

	case 1:
		left->red = node->red;
		p11->red = node->red = false;
		*root = Rotate12(node);

	}
	
	return false;
}
bool Insert(int value, node_st** root)
{
	node_st* node = *root;
	if (!node) 
		*root = NewItem(value);
	else 
	{
		if (value == node->value) 
			return true;
		if (Insert(value, value < node->value ? &node->left : &node->right)) 
			return true;
		
		BalanceInsert(root);
	}
	
	return false;
}
bool GetMin(node_st** root, node_st** res)	//����� � ������ ������������ ���� ���������
{
	node_st* node = *root;
	
	if (node->left) 
	{
		if (GetMin(&node->left, res)) 
			return BalanceRemove1(root);
	}
	else 
	{
		*root = node->right;
		*res = node;
		
		return !node->red;
	}
	
	return false;
}
bool Remove(node_st** root, int value)	//����������� ����� ��������
{
	node_st* t, * node = *root;
	
	if (!node) 
		return false;
	
	if (node->value < value) 
	{
		if (Remove(&node->right, value))	
			return BalanceRemove2(root);
	}
	else if (node->value > value) 
	{
		if (Remove(&node->left, value))	
			return BalanceRemove1(root);
	}
	else 
	{
		bool res;
		
		if (!node->right) 
		{
			*root = node->left;
			res = !node->red;
			DelItem(node);
			return res;
		}
		
		res = GetMin(&node->right, root);
		t = *root;
		t->red = node->red;
		t->left = node->left;
		t->right = node->right;
		DelItem(node);
		
		if (res) 
			res = BalanceRemove2(root);
		
		return res;
	}
	
	return 0;
}