#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

#include <iostream>
#include <locale>
#include <chrono>
using namespace std;

#define P 10
#define D 5             // �� ����� �-� �������� � ������ ������

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
	const int SIZE = 50000;		//������ �������
	int* array = new int[SIZE];	//������������ �������
    int* array2 = new int[SIZE];
    int* array3 = new int[SIZE];

    long long comparisons = 0;		//���������� ���������
    long long swaps = 0;				//���������� ������������
    long long* pSwaps = &swaps;
    long long* pComparison = &comparisons;

	CreateArray(array, array2, array3, SIZE);
    //OutputArray(array, SIZE);

	cout << "���������� ���������: " << SIZE << endl;
	cout << "==========================" << endl;
    cout << "�� ��������������� ������" << endl << endl;
    cout << "��������� ����������" << endl;
	auto begin = chrono::steady_clock::now();
	TournSort(array, SIZE, pComparison, pSwaps);
	auto end = chrono::steady_clock::now();
	auto resultClock = chrono::duration_cast<chrono::nanoseconds>(end - begin);
	cout << "����� ����������: " << resultClock.count() << "��" << endl;
	cout << "���������� ���������: " << *pComparison << endl;
    cout << "���������� ������������: " << *pSwaps << endl << endl;

    *pComparison = 0, * pSwaps = 0;

    cout << "����������� �������� ����������" << endl;
    begin = chrono::steady_clock::now();
    RadixSort(array2, SIZE, pComparison, pSwaps);
    end = chrono::steady_clock::now();
    resultClock = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    cout << "����� ����������: " << resultClock.count() << "��" << endl;
    cout << "���������� ���������: " << *pComparison << endl;
    cout << "���������� ������������: " << *pSwaps << endl << endl;

    *pComparison = 0, * pSwaps = 0;

    cout << "����������� �������� ����������" << endl;
    begin = chrono::steady_clock::now();
    DirectMergeSort(array3, 0, SIZE - 1, pComparison, pSwaps);
    end = chrono::steady_clock::now();
    resultClock = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    cout << "����� ����������: " << resultClock.count() << "��" << endl;
    cout << "���������� ���������: " << *pComparison << endl;
    cout << "���������� ������������: " << *pSwaps << endl << endl;
	
    *pComparison = 0, * pSwaps = 0;

    cout << "==========================" << endl;
    cout << "��������������� ������" << endl << endl;

    cout << "��������� ����������" << endl;
    begin = chrono::steady_clock::now();
    TournSort(array, SIZE, pComparison, pSwaps);
    end = chrono::steady_clock::now();
    resultClock = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    cout << "����� ����������: " << resultClock.count() << "��" << endl;
    cout << "���������� ���������: " << *pComparison << endl;
    cout << "���������� ������������: " << *pSwaps << endl << endl;

    *pComparison = 0, * pSwaps = 0;

    cout << "����������� �������� ����������" << endl;
    begin = chrono::steady_clock::now();
    RadixSort(array2, SIZE, pComparison, pSwaps);
    end = chrono::steady_clock::now();
    resultClock = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    cout << "����� ����������: " << resultClock.count() << "��" << endl;
    cout << "���������� ���������: " << *pComparison << endl;
    cout << "���������� ������������: " << *pSwaps << endl << endl;

    *pComparison = 0, * pSwaps = 0;

    cout << "����������� �������� ����������" << endl;
    begin = chrono::steady_clock::now();
    DirectMergeSort(array3, 0, SIZE - 1, pComparison, pSwaps);
    end = chrono::steady_clock::now();
    resultClock = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    cout << "����� ����������: " << resultClock.count() << "��" << endl;
    cout << "���������� ���������: " << *pComparison << endl;
    cout << "���������� ������������: " << *pSwaps << endl << endl;

    UsualSort(array, SIZE);
    UsualSort(array2, SIZE);
    UsualSort(array3, SIZE);
    *pComparison = 0, * pSwaps = 0;

    cout << "==========================" << endl;
    cout << "��������������� ������ � �������� �������" << endl << endl;

    cout << "��������� ����������" << endl;
    begin = chrono::steady_clock::now();
    TournSort(array, SIZE, pComparison, pSwaps);
    end = chrono::steady_clock::now();
    resultClock = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    cout << "����� ����������: " << resultClock.count() << "��" << endl;
    cout << "���������� ���������: " << *pComparison << endl;
    cout << "���������� ������������: " << *pSwaps << endl << endl;

    *pComparison = 0, * pSwaps = 0;

    cout << "����������� �������� ����������" << endl;
    begin = chrono::steady_clock::now();
    RadixSort(array2, SIZE, pComparison, pSwaps);
    end = chrono::steady_clock::now();
    resultClock = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    cout << "����� ����������: " << resultClock.count() << "��" << endl;
    cout << "���������� ���������: " << *pComparison << endl;
    cout << "���������� ������������: " << *pSwaps << endl << endl;

    *pComparison = 0, * pSwaps = 0;

    cout << "����������� �������� ����������" << endl;
    begin = chrono::steady_clock::now();
    DirectMergeSort(array3, 0, SIZE - 1, pComparison, pSwaps);
    end = chrono::steady_clock::now();
    resultClock = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    cout << "����� ����������: " << resultClock.count() << "��" << endl;
    cout << "���������� ���������: " << *pComparison << endl;
    cout << "���������� ������������: " << *pSwaps << endl << endl;

    delete[] array;
    delete[] array2;
    delete[] array3;

	if (_CrtDumpMemoryLeaks())
		cout << "\n������ ������ ����������." << endl;
	else
		cout << "\n������ ������ �����������." << endl;
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
    for (int i = (array_size / 2) - 1; i >= 0; i--)     // ��������� ������ ��� ��������
    {
        *(comparison) += 1;
        ShiftDown(numbers, i, array_size - 1, comparison, swaps);
    }
    for (int i = array_size - 1; i >= 1; i--)           // ���������� ����� �������� ��������� ��������
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
    int maxChild;   // ������ ������������� �������
    int done = 0;   // ���� ����, ��� ���� ������������
    while ((root * 2 <= bottom) && (!done))     // ���� �� ����� �� ���������� ����
    {
        if (root * 2 == bottom)                 // ���� �� � ��������� ����, ���������� ����� �������
        {
            maxChild = root * 2;
            *(comparison) += 1;
        }
        else if (numbers[root * 2] > numbers[root * 2 + 1]) // ����� ���������� ������� ������� �� ����
        {
            maxChild = root * 2;
            *(comparison) += 2;
        }
        else                                    // ���� ������� ������� ������ ������������� �������
        {
            maxChild = root * 2 + 1;
            *(comparison) += 2;
        }
        if (numbers[root] < numbers[maxChild])
        {
            int temp = numbers[root];           // ������ �� �������
            numbers[root] = numbers[maxChild];
            numbers[maxChild] = temp;
            root = maxChild;
            *(comparison) += 1;
            *(swaps) += 1;
        }
        else // ����� �������� ������������
        {
            done = 1;
            *(comparison) += 1;
        }
        *(comparison) += 1;
    }
    *(comparison) += 1;
}

void RadixSort(int* a, int N, long long* comparison, long long* swaps)  // ����������� ����������
{
    int b[P];			                    // ������ ��������, �������������� �� ��������� � i-� ������
    int i, j, k, m, x;
    for (m = 0; m < D; m++)		            // ���������� ��� �����, ������� � �������� �������
    {
        for (i = 0; i < P; i++)             // �������� �������
        {
            b[i] = 0;
            *(comparison) += 1;
        }
        for (i = 0; i < N; i++)	            // �������� ������
        {
            k = Digit(a[i], m, comparison, swaps);	            // ���������� m-� �����
            x = a[i];			            // ��������� �������
            for (j = i; j > b[k]; j--)	    // � �������� ��� ������� ������ ������
            {
                a[j] = a[j - 1];
                *(swaps) += 1;
                *(comparison) += 1;
            } 
            a[b[k]] = x;		            // ���������� ��� � ����� k-� ������
            for (j = k; j < P; j++)	        // ������������ ��� ������� �� ������� k
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
int Digit(unsigned int v, int r, long long* comparison, long long* swaps)   // ���������� n-� ����� ������ � ���� � ����� v
{
    for (; r > 0; r--)
    {
        v /= P;
        *(comparison) += 1;
    }
    *(comparison) += 1;
    return v % P;
}

void DirectMergeSort(int* a, int b, int e, long long* comparison, long long* swaps)  // ���� ������� ���������� ��������
{
    long m;			                        // ������, �� �������� ����� ������
    if (b < e)			                    // ���� ���� ����� 1 ��������
    {
        m = (b + e) / 2;
        *(comparison) += 1;
        DirectMergeSort(a, b, m, comparison, swaps);	        // ����������� ����� ��������
        DirectMergeSort(a, m + 1, e, comparison, swaps);	    // ����������� ������ ��������
        Merge(a, b, m, e, comparison, swaps);	                // ����� ���������� � ����� ������
    }
    *(comparison) += 1;
}
void Merge(int* a, int b, int m, int e, long long* comparison, long long* swaps)
{
    int pos1 = b;                   // ������� ������� ������ �� ������ ������������������ a[b]...a[m]
    int pos2 = m + 1;               // ������� ������� ������ �� ������ ������������������ a[m+1]...a[e]
    int pos3 = 0;                   // ������� ������� ������ � temp
    int* temp = new int[e - b + 1];
    while (pos1 <= m && pos2 <= e)  // �������, ���� ���� ���� �� ���� ������� � ������ ������������������
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
    // ���� ������������������ ����������� - ���������� ������� ������ � ����� ������
    while (pos2 <= e)			    // ���� ������ ������������������ �������
    {
        temp[pos3++] = a[pos2++];
        *(comparison) += 1;
        *(swaps) += 1;
    }
    while (pos1 <= m)				// ���� ������ ������������������ �������
    {
        temp[pos3++] = a[pos1++];
        *(comparison) += 1;
        *(swaps) += 1;
    }
    for (pos3 = 0; pos3 < e - b + 1; pos3++) // ����������� ����� temp � a[b]...a[e]
    {
        a[b + pos3] = temp[pos3];
        *(comparison) += 1;
        *(swaps) += 1;
    }
    *(comparison) += 4;
    delete[] temp;
}






