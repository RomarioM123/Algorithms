#include "LongNumber.h"

int main()
{
    setlocale(LC_ALL, "Rus");

    cout << "Оператор *\n";
    auto beginClock = chrono::steady_clock::now();
    for (LongNumber i = 2; i < 1000000; i = i * 2);
    auto endClock = chrono::steady_clock::now();
    auto resultClock = chrono::duration_cast<chrono::nanoseconds>(endClock - beginClock);
    cout << "LongNumber: " << resultClock.count() << " нс\n";

    beginClock = chrono::steady_clock::now();
    for (unsigned long i = 2; i < 1000000; i = i * 2);
    endClock = chrono::steady_clock::now();
    resultClock = chrono::duration_cast<chrono::nanoseconds>(endClock - beginClock);
    cout << "unsigned long: " << resultClock.count() << " нс\n";

    cout << "\n";

    cout << "Оператор /\n";
    beginClock = chrono::steady_clock::now();
    for (LongNumber i = 1000000; i > 0; i = i / 2);
    endClock = chrono::steady_clock::now();
    resultClock = chrono::duration_cast<chrono::nanoseconds>(endClock - beginClock);
    cout << "LongNumber: " << resultClock.count() << " нс\n";

    beginClock = chrono::steady_clock::now();
    for (unsigned long i = 1000000; i > 0; i = i / 2);
    endClock = chrono::steady_clock::now();
    resultClock = chrono::duration_cast<chrono::nanoseconds>(endClock - beginClock);
    cout << "unsigned long: " << resultClock.count() << " нс\n";

    if (_CrtDumpMemoryLeaks())
        cout << "\nУтечка памяти обнаружена." << endl;
    else
        cout << "\nУтечка памяти отсутствует." << endl;

    return 0;
}
