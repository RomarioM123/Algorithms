#define N 9  
#include <iostream>
#include <chrono>   
#include <locale>
using namespace std;

static int firstThird = N / 3 - 1;
static int thirdThird = N / 3 * 2;
static int nonEmpty = N / 3;

int NewIndex(int, int);
void Put(int[], int, int, int);
int Get(int[], int, int);
void RandArray(int[N][N]);
void PrintArray(int[N][N]);

void main()
{
    setlocale(LC_ALL, "Rus");
    const int econSizeX = N, econSizeY = N / 3;
    const int econSize = econSizeX * econSizeY;
    int arr[N][N];
    int econArr[econSize];
    int i, j, element;

    RandArray(arr);
    PrintArray(arr);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            Put(econArr, i, j, arr[i][j]);

    printf("\n������  ���c��\n");
    for (int i = 0; i < econSize; i++)
        printf("%2i\t", econArr[i]);
    printf("\n");

    cout << endl << "������� i ����������: ";
    cin >> i;
    cout << "������� j ����������: ";
    cin >> j;

    auto begin = chrono::steady_clock::now();
    for (int k = 0; k < N; k++)
        for (int l = 0; l < N; l++)
            if ((i - 1) == k && l == (j - 1))
            {
                element = arr[k][l];
                l = N;
                k = N;
            }
    auto end = chrono::steady_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    
    cout << "\n�������������� ����� ������� ������������ �������� = " << elapsed_ms.count() << "ns" << endl; // ����� ������ ���������  
    printf("������� ����� = %d\n\n", element);

    cout << endl << "������� i ����������: ";
    cin >> i;
    cout << "������� j ����������: ";
    cin >> j;

    auto begin2 = chrono::steady_clock::now();
    element = Get(econArr, i-1, j-1);
    auto end2 = chrono::steady_clock::now();
    auto elapsed_ms2 = chrono::duration_cast<chrono::nanoseconds>(end2 - begin2);
    
    cout << "\n�������������� ����� ������� � ��������� ������������� = " << elapsed_ms2.count() << "ns" << endl; // ����� ������ ���������  
    printf("�������� ����� = %d\n", element);
}

int NewIndex(int x, int y)                  //�������� ��������
{
    int j = 0;
    for (int i = 0; i < y - nonEmpty; i++)
        j += N;
    return x + j;
}

void Put(int vec[], int i, int j, int v)    //������ �� ���������� ������� � ������
{
    if (j > firstThird&& j < thirdThird) vec[NewIndex(i, j)] = v;
}

int Get(int vec[], int i, int j)            //������ ������ � ������. ������
{
    if (j > firstThird&& j < thirdThird) return vec[NewIndex(i, j)];
    else return 0;
}

void RandArray(int a[N][N])                 //���������� ������� ������� ����������
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (j > firstThird&& j < thirdThird) a[i][j] = rand() % 50;
            else a[i][j] = 0;
}

void PrintArray(int a[N][N])
{
    printf("��������� ������\n\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%3i", a[i][j]);
        printf("\n");
    }
}