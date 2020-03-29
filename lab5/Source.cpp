#include <iostream>
#include <chrono>
using namespace std;

#define N 9

int NewIndex(int, int);
int Get(int[], int, int);
int AddNext(int, int*, int*, int);

int main()
{
    int econIndex = 0;
    const int econSizeX = N, econSizeY = N / 3;
    const int econSize = econSizeX * econSizeY;

    int arr[N][N] = { 0 };
    int econArr[econSize];

    for (int x = 0; x < N; x++)
    {
        for (int y = 0; y < N; y++)
        {
            arr[x][y] = (y >= econSizeY && y < (float)2 / 3 * N) ? AddNext(rand() % 100, &econIndex, econArr, econSize) : 0;
            cout << arr[x][y] << "\t";
        }
        cout << endl;
    }
    cout << endl << endl;

    for (int x = 0; x < econSize; x++)
        cout << econArr[x] << "\t";
    
    int num, num2;

    cout << endl << endl << "Get element from 2 dimention array:" << endl << endl;
    cout << "Enter i coordinate: ";
    cin >> num;
    cout << "Enter j coordinate: ";
    cin >> num2;

    auto begin = chrono::steady_clock::now();
    int element;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == num-1 && j == num2-1)
                element = arr[j][i];
        }
    }
    cout << "Value of selected element is - " << element << endl;
    
    auto end = chrono::steady_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    cout << "Element access time in 2 dimentional array: " << elapsed_ms.count() / 10 << "ns" << endl << endl << endl;
    
    cout << "Get element from econom array" << endl << endl;
    cout << "Enter i coordinate: ";
    cin >> num;
    cout << "Enter j coordinate: ";
    cin >> num2;
    auto begin2 = chrono::steady_clock::now();

    cout << "Value of selected element is - " << Get(econArr, num-1, num2-1) << endl;
    
    auto end2 = chrono::steady_clock::now();
    auto elapsed_ms2 = chrono::duration_cast<chrono::nanoseconds>(end2 - begin2);
    cout << "Element access time in 1 dimentional array: " << elapsed_ms2.count() / 10 << "ns" << endl;

    if (_CrtDumpMemoryLeaks()) cout << endl << "Memory leak detected." << endl;
    else cout << endl << "No memory leak." << endl;

    return 0;
}

int Get(int vec[], int y, int x)  // Запись в вектор (сжатие) 
{
    if (y > 2 && y < 6) return vec[NewIndex(x, y)];
    else return 0;
}

int NewIndex(int x, int y)     //пересчет индексов
{
    int j = 0;

    for (size_t i = 0; i < x; i++)
        j += 3;

    for (int i = 0; i < y - 3; i++)
        j += 1;

    return j;
}

int AddNext(int val, int* ind, int* arr, int econSize)
{
    if (*ind < econSize)
    {
        *(arr + *ind) = val;
        *ind = *ind + 1;

        return val;
    }
    return 0;
}