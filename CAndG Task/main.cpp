#include "LongNumber.h"

int main()
{
    setlocale(LC_ALL, "Rus");

    cout << "�������� *\n";
    auto beginClock = chrono::steady_clock::now();
    for (LongNumber i = 2; i < 1000000; i = i * 2);
    auto endClock = chrono::steady_clock::now();
    auto resultClock = chrono::duration_cast<chrono::nanoseconds>(endClock - beginClock);
    cout << "LongNumber: " << resultClock.count() << " ��\n";

    beginClock = chrono::steady_clock::now();
    for (unsigned long i = 2; i < 1000000; i = i * 2);
    endClock = chrono::steady_clock::now();
    resultClock = chrono::duration_cast<chrono::nanoseconds>(endClock - beginClock);
    cout << "unsigned long: " << resultClock.count() << " ��\n";

    cout << "\n";

    cout << "�������� /\n";
    beginClock = chrono::steady_clock::now();
    for (LongNumber i = 1000000; i > 0; i = i / 2);
    endClock = chrono::steady_clock::now();
    resultClock = chrono::duration_cast<chrono::nanoseconds>(endClock - beginClock);
    cout << "LongNumber: " << resultClock.count() << " ��\n";

    beginClock = chrono::steady_clock::now();
    for (unsigned long i = 1000000; i > 0; i = i / 2);
    endClock = chrono::steady_clock::now();
    resultClock = chrono::duration_cast<chrono::nanoseconds>(endClock - beginClock);
    cout << "unsigned long: " << resultClock.count() << " ��\n";

    if (_CrtDumpMemoryLeaks())
        cout << "\n������ ������ ����������." << endl;
    else
        cout << "\n������ ������ �����������." << endl;

    return 0;
}
