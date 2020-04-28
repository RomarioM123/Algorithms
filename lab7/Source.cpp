#include <iostream>
#include <chrono>
#include <new>
using namespace std;
#define N 10

struct value {
	int value;
    int priority;
};
struct valueSp {
	value info;
	valueSp* next;
};
struct valueSp* MainEl()
{
    struct valueSp* p = new valueSp;
    p->next = NULL;
    return p;
};

class QueueP
{
private:
    int* A;
    int* P;
    int count;
public:
    QueueP() { count = 0; }

    void Push(int item, int priority);
    int Pop();
    void Clear();
    int Count();
    void Print();
    int element(int i);

    ~QueueP()
    {
        if (count > 0)
        {
            delete[] A;
            delete[] P;
        }
    }
};

struct valueSp* MainEl();
void createSp(struct valueSp*, int*);
void freeSp(struct valueSp*);
void List();
void Array();

void main()
{
    List();
    Array();
}

int QueueP::Count()
{
    return count;
}
void QueueP::Clear()
{
    if (count > 0)
    {
        delete[] A;
        delete[] P;
        count = 0;
    }
}
void QueueP::Push(int item, int priority)
{
    int* A2;
    int* P2;
    try {
        A2 = new int[count + 1];
        P2 = new int[count + 1];
    }
    catch (bad_alloc e)
    {
        cout << e.what() << endl;
        return;
    }
    int pos;
    if (count == 0)
        pos = 0;
    else
    {
        pos = 0;
        while (pos < count)
        {
            if (P[pos] == priority)
                break;
            else if (P[pos] > priority)
                break;
            pos++;
        }
    }
    for (int i = 0; i < pos; i++)
    {
        A2[i] = A[i];
        P2[i] = P[i];
    }
    A2[pos] = item;
    P2[pos] = priority;
    for (int i = pos + 1; i < count + 1; i++)
    {
        A2[i] = A[i - 1];
        P2[i] = P[i - 1];
    }
    if (count > 0)
    {
        delete[] A;
        delete[] P;
    }
    A = A2;
    P = P2;
    count++;
}
int QueueP::Pop()
{
    if (count == 0)
        return 0;
    int* A2;
    int* P2;
    try {
        A2 = new int[count - 1];
        P2 = new int[count - 1];
    }
    catch (bad_alloc e)
    {
        cout << e.what() << endl;
        return 0;
    }
    int item;
    item = A[0];
    for (int i = 0; i < count - 1; i++)
    {
        A2[i] = A[i];
        P2[i] = P[i];
    }
    if (count > 0)
    {
        delete[] A;
        delete[] P;
    }
    count--;
    A = A2;
    P = P2;
    return item;
}
void QueueP::Print()
{
    cout << "Objects and their priority" << endl;
    for (int i = 0; i < count; i++)
        cout << A[i] << ":" << P[i] << "\t" << endl;
    cout << endl;
    cout << "---------------" << endl;
}
int QueueP::element(int i)
{
    return A[i];
}

void List()
{
    QueueP c_array;
    int arr[N] = { -2, 1, 0, 2, -555, 0, 15, 3, 57, 4 };
    int* fArray = new int[N / 2];
    struct valueSp* h = MainEl();
    createSp(h, arr);
    struct valueSp* p = h->next;
    auto begin = chrono::steady_clock::now();
    while (p)
    {
        c_array.Push(p->info.value, p->info.priority);
        p = p->next;
    }
    


    for (size_t i = 0; i < N / 2; i++)
        fArray[i] = c_array.element(i);    //запись
    c_array.Print();
    auto end = chrono::steady_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    cout << "Priority queue time of work using list: " << elapsed_ms.count() << "ns" << endl << endl << endl;
    for (size_t i = 0; i < N / 2; i++)
        c_array.Pop();
}
void createSp(struct valueSp* h, int* arr)
{
    struct valueSp* p = h;
    for (size_t i = 0, j = 1; i < N; i += 2, j += 2)
    {
        p->next = new valueSp;
        p = p->next;
        p->info.value = arr[i];
        p->info.priority = arr[j];
    }
    p->next = NULL;
}
void Array()
{
    QueueP s_array;
    int array[N] = { -2, 1, 0, 2, -555, 0, 15, 3, 57, 4 };
    int* tempArray;
    auto begin2 = chrono::steady_clock::now();
    for (size_t i = 0, j = 1; i < N; i += 2, j+=2)
    {
        s_array.Push(array[i], array[j]);
    }
    int* fArray = new int[N / 2];
    s_array.Print();
    for (size_t i = 0; i < N / 2; i++)
        fArray[i] = s_array.element(i);
    auto end2 = chrono::steady_clock::now();
    auto elapsed_ms2 = chrono::duration_cast<chrono::nanoseconds>(end2 - begin2);
    cout << "Priority queue time of work using array: " << elapsed_ms2.count() << "ns" << endl;
    for (size_t i = 0; i < N / 2; i++)
        s_array.Pop();
}
void freeSp(struct valueSp* h)
{
    struct valueSp* p;
    while (h)
    {
        p = h;
        h = h->next;
        delete p;
    }
}