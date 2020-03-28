#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <chrono>
#include <time.h>
using namespace std;

int get_count_rekursiya(int n, int prev = 0) {
    if (n != 0)
        return prev ? get_count_rekursiya(n - 1, 0) : get_count_rekursiya(n - 1, 0) + get_count_rekursiya(n - 1, 1);
    else
        return 1;
}
int get_count_iteratsiya(int size)
{
    int* results = new int[size + 1];
    results[0] = 1;
    results[1] = 2;

    for (int x = 2; x <= size; x++)
        results[x] = results[x - 1] + results[x - 2];

    return results[size];
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int size, result_rekursiya;
    int result_iteratsiya;

    cout << "������� ���-�� �������� ��������� �����: ";
    do{ cin >> size;
    } while (size <= 1 && cout << "\n�� ����� ���� ������ 1. ��������� �������!\n������� ���-�� �������� ��������� �����: ");


    auto start = std::chrono::steady_clock::now();          //������ ������ �������
    result_rekursiya = get_count_rekursiya(size);           //����� ��������
    auto end_rekursiya = std::chrono::steady_clock::now();  //����� ������� ������ ��������
    auto time_rekursiya = std::chrono::duration_cast<std::chrono::nanoseconds>(end_rekursiya - start);  //���������� ������� ������


    result_iteratsiya = get_count_iteratsiya(size);             //����� ��������
    auto end_iteratsiya = std::chrono::steady_clock::now();     //����� ������� ������ ��������
    auto time_iteratsiya = std::chrono::duration_cast<std::chrono::nanoseconds>(end_iteratsiya - end_rekursiya);  //���������� ������� ������

    cout << endl << "���������� " << size << "-��������� �������� �����, �� ���������� ����� ��� �������:" << endl;
    cout << result_rekursiya << " (����������� �����)\t\t" << time_rekursiya.count() << " ����������" << endl;
    cout << result_iteratsiya << " (������������ �����)\t\t" << time_iteratsiya.count() << " ����������" << endl;

    return 0;
}