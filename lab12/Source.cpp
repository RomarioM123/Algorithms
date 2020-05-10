#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

#include <iostream>
#include <locale>
#include <chrono>
using namespace std;

#define P 10
#define D 5             // Не более з-х разрядов в числах набора

void CreateArray(int*, int*, int*, int);
void OutputArray(int*, int);
void UsualSort(int*, int);

void TournSort(int*, int, long long*, long long*);
void ShiftDown(int*, int, int, long long*, long long*);

void RadixSort(int*, int, long long*, long long*);
int Digit(unsigned int, int, long long*, long long*);

void DirectMergeSort(int*, int, int, long long*, long long*);
void Merge(int*, int, int, int, long long*, long long*);

int main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(0));
	const int SIZE = 50000;		//размер массива
	int* array = new int[SIZE];	//динамические массивы
    int* array2 = new int[SIZE];
    int* array3 = new int[SIZE];

    long long comparisons = 0;		//количество сравнений
    long long swaps = 0;				//количество перестановок
    long long* pSwaps = &swaps;
    long long* pComparison = &comparisons;

	CreateArray(array, array2, array3, SIZE);
    //OutputArray(array, SIZE);

	cout << "Количество элементов: " << SIZE << endl;
	cout << "==========================" << endl;
    cout << "Не отсортированные данные" << endl << endl;
    cout << "Турнирная сортировка" << endl;
	auto begin = chrono::steady_clock::now();
	TournSort(array, SIZE, pComparison, pSwaps);
	auto end = chrono::steady_clock::now();
	auto resultClock = chrono::duration_cast<chrono::nanoseconds>(end - begin);
	cout << "Время сортировки: " << resultClock.count() << "нс" << endl;
	cout << "Количество сравнений: " << *pComparison << endl;
    cout << "Количество перестановок: " << *pSwaps << endl << endl;

    *pComparison = 0, * pSwaps = 0;

    cout << "Поразрядная цифровая сортировка" << endl;
    begin = chrono::steady_clock::now();
    RadixSort(array2, SIZE, pComparison, pSwaps);
    end = chrono::steady_clock::now();
    resultClock = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    cout << "Время сортировки: " << resultClock.count() << "нс" << endl;
    cout << "Количество сравнений: " << *pComparison << endl;
    cout << "Количество перестановок: " << *pSwaps << endl << endl;

    *pComparison = 0, * pSwaps = 0;

    cout << "Поразрядная цифровая сортировка" << endl;
    begin = chrono::steady_clock::now();
    DirectMergeSort(array3, 0, SIZE - 1, pComparison, pSwaps);
    end = chrono::steady_clock::now();
    resultClock = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    cout << "Время сортировки: " << resultClock.count() << "нс" << endl;
    cout << "Количество сравнений: " << *pComparison << endl;
    cout << "Количество перестановок: " << *pSwaps << endl << endl;
	
    *pComparison = 0, * pSwaps = 0;

    cout << "==========================" << endl;
    cout << "Отсортированные данные" << endl << endl;

    cout << "Турнирная сортировка" << endl;
    begin = chrono::steady_clock::now();
    TournSort(array, SIZE, pComparison, pSwaps);
    end = chrono::steady_clock::now();
    resultClock = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    cout << "Время сортировки: " << resultClock.count() << "нс" << endl;
    cout << "Количество сравнений: " << *pComparison << endl;
    cout << "Количество перестановок: " << *pSwaps << endl << endl;

    *pComparison = 0, * pSwaps = 0;

    cout << "Поразрядная цифровая сортировка" << endl;
    begin = chrono::steady_clock::now();
    RadixSort(array2, SIZE, pComparison, pSwaps);
    end = chrono::steady_clock::now();
    resultClock = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    cout << "Время сортировки: " << resultClock.count() << "нс" << endl;
    cout << "Количество сравнений: " << *pComparison << endl;
    cout << "Количество перестановок: " << *pSwaps << endl << endl;

    *pComparison = 0, * pSwaps = 0;

    cout << "Поразрядная цифровая сортировка" << endl;
    begin = chrono::steady_clock::now();
    DirectMergeSort(array3, 0, SIZE - 1, pComparison, pSwaps);
    end = chrono::steady_clock::now();
    resultClock = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    cout << "Время сортировки: " << resultClock.count() << "нс" << endl;
    cout << "Количество сравнений: " << *pComparison << endl;
    cout << "Количество перестановок: " << *pSwaps << endl << endl;

    UsualSort(array, SIZE);
    UsualSort(array2, SIZE);
    UsualSort(array3, SIZE);
    *pComparison = 0, * pSwaps = 0;

    cout << "==========================" << endl;
    cout << "Отсортированные данные в обратном порядке" << endl << endl;

    cout << "Турнирная сортировка" << endl;
    begin = chrono::steady_clock::now();
    TournSort(array, SIZE, pComparison, pSwaps);
    end = chrono::steady_clock::now();
    resultClock = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    cout << "Время сортировки: " << resultClock.count() << "нс" << endl;
    cout << "Количество сравнений: " << *pComparison << endl;
    cout << "Количество перестановок: " << *pSwaps << endl << endl;

    *pComparison = 0, * pSwaps = 0;

    cout << "Поразрядная цифровая сортировка" << endl;
    begin = chrono::steady_clock::now();
    RadixSort(array2, SIZE, pComparison, pSwaps);
    end = chrono::steady_clock::now();
    resultClock = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    cout << "Время сортировки: " << resultClock.count() << "нс" << endl;
    cout << "Количество сравнений: " << *pComparison << endl;
    cout << "Количество перестановок: " << *pSwaps << endl << endl;

    *pComparison = 0, * pSwaps = 0;

    cout << "Поразрядная цифровая сортировка" << endl;
    begin = chrono::steady_clock::now();
    DirectMergeSort(array3, 0, SIZE - 1, pComparison, pSwaps);
    end = chrono::steady_clock::now();
    resultClock = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    cout << "Время сортировки: " << resultClock.count() << "нс" << endl;
    cout << "Количество сравнений: " << *pComparison << endl;
    cout << "Количество перестановок: " << *pSwaps << endl << endl;

    delete[] array;
    delete[] array2;
    delete[] array3;

	if (_CrtDumpMemoryLeaks())
		cout << "\nУтечка памяти обнаружена." << endl;
	else
		cout << "\nУтечка памяти отсутствует." << endl;
}

void CreateArray(int* array,int* array2, int* array3, int size)
{
    int value = 0;
    for (size_t i = 0; i < size; i++)
    {
        value = rand();
        *(array + i) = value;
        *(array2 + i) = value;
        *(array3 + i) = value;
    }
		
}
void OutputArray(int* array, int size)
{
	cout << endl;
	for (size_t i = 0; i < size; i++)
		cout << *(array + i) << "  ";
	cout << endl;
}
void UsualSort(int* array, int size)
{
    int temp;
    bool pr = 0;
    do
    {
        pr = 0;
        for (size_t i = 0; i < size; i++)
            if (array[i] < array[i + 1])
            {
                temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
                pr = 1;
            }
    } while (pr);
}

void TournSort(int* numbers, int array_size, long long* comparison, long long* swaps)
{
    for (int i = (array_size / 2) - 1; i >= 0; i--)     // Формируем нижний ряд пирамиды
    {
        *(comparison) += 1;
        ShiftDown(numbers, i, array_size - 1, comparison, swaps);
    }
    for (int i = array_size - 1; i >= 1; i--)           // Просеиваем через пирамиду остальные элементы
    {
        *(comparison) += 1;
        *(swaps) += 1;
        int temp = numbers[0];
        numbers[0] = numbers[i];
        numbers[i] = temp;
        ShiftDown(numbers, 0, i - 1, comparison, swaps);
    }
    *(comparison) += 2;
}
void ShiftDown(int* numbers, int root, int bottom, long long* comparison, long long* swaps)
{
    int maxChild;   // индекс максимального потомка
    int done = 0;   // флаг того, что куча сформирована
    while ((root * 2 <= bottom) && (!done))     // Пока не дошли до последнего ряда
    {
        if (root * 2 == bottom)                 // если мы в последнем ряду, запоминаем левый потомок
        {
            maxChild = root * 2;
            *(comparison) += 1;
        }
        else if (numbers[root * 2] > numbers[root * 2 + 1]) // иначе запоминаем больший потомок из двух
        {
            maxChild = root * 2;
            *(comparison) += 2;
        }
        else                                    // если элемент вершины меньше максимального потомка
        {
            maxChild = root * 2 + 1;
            *(comparison) += 2;
        }
        if (numbers[root] < numbers[maxChild])
        {
            int temp = numbers[root];           // меняем их местами
            numbers[root] = numbers[maxChild];
            numbers[maxChild] = temp;
            root = maxChild;
            *(comparison) += 1;
            *(swaps) += 1;
        }
        else // иначе пирамида сформирована
        {
            done = 1;
            *(comparison) += 1;
        }
        *(comparison) += 1;
    }
    *(comparison) += 1;
}

void RadixSort(int* a, int N, long long* comparison, long long* swaps)  // Поразрядная сортировка
{
    int b[P];			                    // Индекс элемента, расположенного за последним в i-й группе
    int i, j, k, m, x;
    for (m = 0; m < D; m++)		            // Перебираем все числа, начиная с младшего разряда
    {
        for (i = 0; i < P; i++)             // Обнуляем индексы
        {
            b[i] = 0;
            *(comparison) += 1;
        }
        for (i = 0; i < N; i++)	            // Проходим массив
        {
            k = Digit(a[i], m, comparison, swaps);	            // Определяем m-ю цифру
            x = a[i];			            // Сохраняем элемент
            for (j = i; j > b[k]; j--)	    // И затираем его сдвигая массив вправо
            {
                a[j] = a[j - 1];
                *(swaps) += 1;
                *(comparison) += 1;
            } 
            a[b[k]] = x;		            // Записываем его в конец k-й группы
            for (j = k; j < P; j++)	        // Модифицируем все индексы не меньшие k
            {
                b[j] = b[j] + 1;
                *(swaps) += 1;
                *(comparison) += 1;
            }
            *(comparison) += 3;
        }
        *(comparison) += 3;
    }
    *(comparison) += 1;
}
int Digit(unsigned int v, int r, long long* comparison, long long* swaps)   // Возвращает n-ю цифру считая с нуля в числе v
{
    for (; r > 0; r--)
    {
        v /= P;
        *(comparison) += 1;
    }
    *(comparison) += 1;
    return v % P;
}

void DirectMergeSort(int* a, int b, int e, long long* comparison, long long* swaps)  // Сама функция сортировки слиянием
{
    long m;			                        // индекс, по которому делим массив
    if (b < e)			                    // если есть более 1 элемента
    {
        m = (b + e) / 2;
        *(comparison) += 1;
        DirectMergeSort(a, b, m, comparison, swaps);	        // сортировать левую половину
        DirectMergeSort(a, m + 1, e, comparison, swaps);	    // сортировать правую половину
        Merge(a, b, m, e, comparison, swaps);	                // слить результаты в общий массив
    }
    *(comparison) += 1;
}
void Merge(int* a, int b, int m, int e, long long* comparison, long long* swaps)
{
    int pos1 = b;                   // текущая позиция чтения из первой последовательности a[b]...a[m]
    int pos2 = m + 1;               // текущая позиция чтения из второй последовательности a[m+1]...a[e]
    int pos3 = 0;                   // текущая позиция записи в temp
    int* temp = new int[e - b + 1];
    while (pos1 <= m && pos2 <= e)  // слияние, пока есть хотя бы один элемент в каждой последовательности
    {
        if (a[pos1] < a[pos2])
        {
            temp[pos3++] = a[pos1++];
            *(swaps) += 1;
        }
        else
        {
            temp[pos3++] = a[pos2++];
            *(swaps) += 1;
        }
        *(comparison) += 2;
    }
    // одна последовательность закончилась - копировать остаток другой в конец буфера
    while (pos2 <= e)			    // пока вторая последовательность непуста
    {
        temp[pos3++] = a[pos2++];
        *(comparison) += 1;
        *(swaps) += 1;
    }
    while (pos1 <= m)				// пока первая последовательность непуста
    {
        temp[pos3++] = a[pos1++];
        *(comparison) += 1;
        *(swaps) += 1;
    }
    for (pos3 = 0; pos3 < e - b + 1; pos3++) // скопировать буфер temp в a[b]...a[e]
    {
        a[b + pos3] = temp[pos3];
        *(comparison) += 1;
        *(swaps) += 1;
    }
    *(comparison) += 4;
    delete[] temp;
}






