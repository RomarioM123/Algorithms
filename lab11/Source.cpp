#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

#include <iostream>
#include <clocale>
#include <chrono>
using namespace std;

typedef bool (comp)(const int&, const int&);
bool sortAsc(const int& a, const int& b) { return a > b; }
bool sortDesc(const int& a, const int& b) { return a < b; }

void CreateArray(int*, int*, int);
void OutputArray(int*, int);
void ShakerSort(int* , int, unsigned long long*, unsigned long long*, comp);

int main()
{
	setlocale(0, "");
	srand(time(NULL));
	const int SIZE = 50000;				//размер массивов
	unsigned long long comparisons = 0;		//количество сравнений
	unsigned long long swaps = 0;				//количество перестановок
	unsigned long long* pSwaps = &swaps;
	unsigned long long*pComparison = &comparisons;

	int array[SIZE];					//статичный массив
	int* pArray = array;
	int* dynamicArray = new int[SIZE];	//динамичный массив

	CreateArray(pArray,dynamicArray, SIZE);
	//OutputArray(pArray, SIZE);
	//OutputArray(dynamicArray, SIZE);

	cout << "Количество элементов: " << SIZE << endl;
	cout << "==========================" << endl;
	cout << "Не отсортированные данные" << endl;
	auto begin = chrono::steady_clock::now();
	ShakerSort(pArray, SIZE, pComparison, pSwaps, sortAsc);
	auto end = chrono::steady_clock::now();
	auto resultClock = chrono::duration_cast<chrono::milliseconds>(end - begin);
	cout << "\nСтатичный массив" << endl;
	cout << "Время сортировки: " << resultClock.count() << "мс" << endl;
	cout << "Количество сравнений: " << *pComparison << endl;
	cout << "Количество перестановок: " << *pSwaps << endl;

	*pComparison = 0, * pSwaps = 0;
	begin = chrono::steady_clock::now();
	ShakerSort(dynamicArray, SIZE, pComparison, pSwaps, sortAsc);
	end = chrono::steady_clock::now();
	resultClock = chrono::duration_cast<chrono::milliseconds>(end - begin);
	cout << "\nДинамический массив" << endl;
	cout << "Время сортировки: " << resultClock.count() << "мс" << endl;
	cout << "Количество сравнений: " << *pComparison << endl;
	cout << "Количество перестановок: " << *pSwaps << endl;

	cout << "==========================" << endl;

	*pComparison = 0, * pSwaps = 0;
	cout << "Отсортированные данные" << endl;
	begin = chrono::steady_clock::now();
	ShakerSort(pArray, SIZE, pComparison, pSwaps, sortAsc);
	end = chrono::steady_clock::now();
	resultClock = chrono::duration_cast<chrono::milliseconds>(end - begin);
	cout << "\nСтатичный массив" << endl;
	cout << "Время сортировки: " << resultClock.count() << "мс" << endl;
	cout << "Количество сравнений: " << *pComparison << endl;
	cout << "Количество перестановок: " << *pSwaps << endl;

	*pComparison = 0, * pSwaps = 0;
	begin = chrono::steady_clock::now();
	ShakerSort(dynamicArray, SIZE, pComparison, pSwaps, sortAsc);
	end = chrono::steady_clock::now();
	resultClock = chrono::duration_cast<chrono::milliseconds>(end - begin);
	cout << "\nДинамический массив" << endl;
	cout << "Время сортировки: " << resultClock.count() << "мс" << endl;
	cout << "Количество сравнений: " << *pComparison << endl;
	cout << "Количество перестановок: " << *pSwaps << endl;

	cout << "==========================" << endl;

	*pComparison = 0, * pSwaps = 0;
	cout << "Отсортированные данные в обратном порядке" << endl;
	begin = chrono::steady_clock::now();
	ShakerSort(pArray, SIZE, pComparison, pSwaps, sortDesc);
	end = chrono::steady_clock::now();
	resultClock = chrono::duration_cast<chrono::milliseconds>(end - begin);
	cout << "\nСтатичный массив" << endl;
	cout << "Время сортировки: " << resultClock.count() << "мс" << endl;
	cout << "Количество сравнений: " << *pComparison << endl;
	cout << "Количество перестановок: " << *pSwaps << endl;

	*pComparison = 0, * pSwaps = 0;
	begin = chrono::steady_clock::now();
	ShakerSort(dynamicArray, SIZE, pComparison, pSwaps, sortDesc);
	end = chrono::steady_clock::now();
	resultClock = chrono::duration_cast<chrono::milliseconds>(end - begin);
	cout << "\nДинамический массив" << endl;
	cout << "Время сортировки: " << resultClock.count() << "мс" << endl;
	cout << "Количество сравнений: " << *pComparison << endl;
	cout << "Количество перестановок: " << *pSwaps << endl;

	delete[] dynamicArray;
	if (_CrtDumpMemoryLeaks()) 
		cout << "\nУтечка памяти обнаружена." << endl;
	else 
		cout << "\nУтечка памяти отсутствует." << endl;
}

void CreateArray(int* array, int* dArray, int size)
{
	int value;
	for (size_t i = 0; i < size; i++)
	{
		value = rand();
		*(array + i) = value;
		*(dArray + i) = value;
	}
}
void OutputArray(int* array, int size)
{
	cout << endl;
	for (size_t i = 0; i < size; i++)
	{
		cout << *(array + i) << "  ";
	}
	cout << endl;
}
void ShakerSort(int* a, int N, unsigned long long* comparisons, unsigned long long* swaps, comp condition)
{
	int i, b = 0, e = N - 1;

	while (b <= e)
	{
		for (i = e; i >/*=*/ b; i--)
		{
			if (condition(a[i - 1],a[i]))
			{
				swap(a[i - 1], a[i]);
				*(swaps) += 1;
			}
			*(comparisons) += 2;

		}
		b++;
		
		for (i = b; i <= e; i++)
		{
			if (condition (a[i - 1], a[i]))
			{
				swap(a[i - 1], a[i]);
				*(swaps) += 1;
			}
			*(comparisons) += 2;
		}
		*(comparisons) += 3;
		e--;
	}
	*(comparisons) += 1;
}
