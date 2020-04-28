#define _CRT_SECURE_NO_WARNINGS
#define CRTDBG_MAP_ALLOC
#define DEBUG_NEW new(_NORMAL_BLOCK, FILE, __LINE)
#define new DEBUG_NEW
#include <crtdbg.h>
#include <stdlib.h>
#include <iostream>
#include <locale.h>
#include <chrono>

struct Element 
{
	int value;		//число
	int number;		//номер в списке
};
struct List 
{
	Element info;
	List* next, * prev;
};

using namespace std;

List* Init();
void InitList(List*, List*);	
void CreateListAndArr(List*, int*, int);
void GiveNumber(List*);
void FreeList(List*);

void SortList(List*, List*);
void SortArr(int*, int);

int BinSearchQuickArr(int*, int, int, int*);
int BinSearchQuickList(List*,List*, int, int, int*);

void OutputArr(int*, int);
void OutputList(List*);

int main() {
	setlocale(LC_ALL, "Rus");
	struct List* h = Init();
	struct List* t = Init();
	const int SIZE = 20;		//размер массивов
	int array[SIZE];			//массив
	int* pArray = array;		//указатель на массив
	int key;					//искомое число
	int result;					//результат поиска
	int comparison = 0;			//количество сравнений
	int* pComparison = &comparison;

	InitList(h, t);
	CreateListAndArr(h, pArray, SIZE);
	SortList(h, t);
	GiveNumber(h);
	SortArr(pArray, SIZE);

	OutputList(h);
	//OutputArr(pArray, SIZE);

	cout << "Введите число, которое надо найти в массиве: ";
	cin >> key;

	auto beginClock = chrono::steady_clock::now();
	result = BinSearchQuickArr(array, key, SIZE, pComparison);
	auto endClock = chrono::steady_clock::now();
	auto resultClock = chrono::duration_cast<chrono::nanoseconds>(endClock - beginClock);
	if (result == -1) cout << "Элемент в массиве отсутствует." << endl;
	else cout << "\nИндекс элемента " << key << ": " << result << endl;
	*pComparison += 2;
	cout << "Время поиска элемента: " << resultClock.count() << "ns" << endl;
	cout << "Количество сравнений: " << *pComparison << endl;

	*pComparison = 0;

	beginClock = chrono::steady_clock::now();
	result = BinSearchQuickList(h, t, key, SIZE, pComparison);
	endClock = chrono::steady_clock::now();
	resultClock = chrono::duration_cast<chrono::nanoseconds>(endClock - beginClock);
	if (result == -1) cout << "Элемент в массиве отсутствует." << endl;
	else cout << "\nИндекс элемента " << key << ": " << result << endl;
	*pComparison += 2;
	cout << "Время поиска элемента: " << resultClock.count() << "ns" << endl;
	cout << "Количество сравнений: " << *pComparison << endl;

	FreeList(h);

	if (_CrtDumpMemoryLeaks()) cout << "\nУтечка памяти обнаружена." << endl;
	else cout << "\nУтечка памяти отсутствует." << endl;

	return 0;
}


List* Init() {
	struct List* p = (struct List*)malloc(sizeof(List)); /**- Виділення пам'яті на наступний елемент списка. */
	return p;			/**- Повернення покажчика. */
}
void InitList(List* h, List* t) {
	h->next = t;			/**- Переміщення покажчиків. */
	h->prev = NULL;
	t->next = NULL;
	t->prev = h;
}
void CreateListAndArr(List* h,int* arr, int size) {
	struct List* p;
	int value = 0, temp;

	while (value != size)
	{
		p = (List*)malloc(sizeof(List));
		temp = rand();
		p->info.value = temp;
		p->next = h->next;
		p->next->prev = p;
		p->prev = h;
		h->next = p;

		arr[value] = temp;
		value++;
	}
}
void OutputList(List* h)
{
	struct List* p = h->next;

	cout << "Числа в списке:" << endl;
	while (p->next)
	{
		cout << p->info.value << "  ";
		p = p->next;
	}
	cout << endl;
	/*p = h->next;
	while (p->next)
	{
		cout << p->info.number << "  ";
		p = p->next;
	}
	cout << endl;*/
}
void OutputArr(int* array, int size)
{
	for (size_t i = 0; i < size; i++)
	{
		cout << array[i] << "  ";
	}
	cout << endl;
}
void SortList(List* h, List* t) {
	bool pr = 0;
	struct List* p = h->next;

	do {
		pr = false;
		p = h->next;
		while (p->next)
		{
			if (p->info.value > p->next->info.value&& p->next != t)
			{
				p->next->prev = p->prev;
				p->next->next->prev = p;
				p->prev = p->next;
				p->next = p->next->next;
				p->prev->next = p;
				p->prev->prev->next = p->prev;
				pr = 1;
			}
			p = p->next;
		}
	} while (pr == 1);
}
void SortArr(int* array, int size)
{
	bool pr;
	int temp;

	do {
		pr = 0;
		for (size_t i = 0; i < size - 1; i++)
		{
			if (*(array + i) > *(array + i + 1))
			{
				temp = *(array + i);
				*(array + i) = *(array + i + 1);
				*(array + i + 1) = temp;
				pr = 1;
			}
		}
	} while (pr == 1);
}
int BinSearchQuickArr(int* arr, int key, int size, int* numberOfComparisons)
{
	int middle, left = 0, right = size; 	// начальные значения границ
	while (left <= right) 					//пока интервал не сузится до 0
	{
		middle = (left + right) / 2; 		//середина интервала
		if (arr[middle] >= key) right = middle - 1;
		else left = middle + 1;
		*numberOfComparisons += 2;
	}
	if (arr[left] == key) return left;
	else return -1;
}
int BinSearchQuickList(List* h, List* t, int key, int size, int* numberOfComparisons)
{
	List* left = h->next;
	List* right = t->prev;
	List* middle = h->next;
	int value;
	int i = 1, b = 0;

	while (left->info.number <= right->info.number) 					//пока интервал не сузится до 0
	{
		value = (left->info.number + right->info.number + i) / 2;
		for (i = middle->info.number,b = 0; i != value;b++)		//находим середину интервала
		{
			if (i < value)
			{
				middle = middle->next;
				i++, b++;
			}
			else
			{
				middle = middle->prev;
				i--, b++;
			}
		}
		
		if (middle->info.value >= key)
		{
			right = middle->prev;
		}
		else
		{
			left = middle->next;
		}
		*numberOfComparisons += (2+b);
		i = 0, b = 0;
	}
	
	if (left->info.value == key)
	{
		return left->info.number;
	}
	else return -1;
}
void GiveNumber(List* h)
{
	struct List* p = h->next;
	int i = 0;
	
	while (p->next)
	{
		p->info.number = i;
		p = p->next;
		i++;
	}
}
void FreeList(List* h)
{
	struct List* p = h;

	while (p)
	{
		h = p;
		p = p->next;
		free(h);
	}
}






