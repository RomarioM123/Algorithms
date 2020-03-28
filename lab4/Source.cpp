#include <iostream>
#include <conio.h>
#include <chrono>
using namespace std;

void BYTE(unsigned char A)  //виведення вмісту байта
{
    for (int bit = 128; bit >= 1; bit >>= 1)
        cout << (A & bit ? "1" : "0");
   
    cout << " ";
}

struct Tstruct1
{
    int s;	/* 4 bytes */
    short flip1 : 1;
    short flip2 : 1;
    short flip3 : 1;
    short flip4 : 1;
    short flip5 : 1;
    short flip6 : 4;
    short flip7 : 4;
    bool earlyRipeness;
    
    union
    {
        struct
        {
            bool kernel;
            double trunkLength;
        } wildTree;
        
        struct
        {
            short st;
        }gardenTree;

    } un;
};

struct Tstruct2
{
    short s;    /* 4 bytes */
    int flip1;
    int flip2;
    int flip3;
    int flip4;
    int flip5;
    int flip6;
    int flip7;
    bool earlyRipeness;
    bool kernel;
};

void main()
{
    cout << "Structure with alignment" << endl << endl;
   
    auto begin = chrono::steady_clock::now();
    
    Tstruct1 obj1 = { 5, 1, 0, 1, 0, 1, 12, 1 };
    
    obj1.un.wildTree.trunkLength = 2.5;
    obj1.un.wildTree.kernel = true;
    obj1.earlyRipeness = true;
   
    unsigned char* p = (unsigned char*)&obj1;
    int byte = 0;
    for (; byte < sizeof(Tstruct1); byte++, p++)
    {
        if (byte && !(byte % 8)) cout << endl;
        BYTE(*p);
    }
    
    cout << endl << endl;
    
    auto end = chrono::steady_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::nanoseconds>(end - begin);
   
    cout << "Time with alignment: " << elapsed_ms.count() / 10 << "ns" << endl << endl << endl;
    cout << "Structure without alignment " << endl << endl;
    
    auto begin2 = chrono::steady_clock::now();
    
    Tstruct2 obj2 = { 5, 1, 0, 1, 0, 1, 12, 1 };
    obj2.earlyRipeness = true;
    obj2.kernel = true;
   
    p = (unsigned char*)&obj2;
    for (int byte = 0; byte < sizeof(Tstruct2); byte++, p++)
    {
        if (byte && !(byte % 8)) cout << endl;
        BYTE(*p);
    }
   
    cout << endl;
    
    auto end2 = chrono::steady_clock::now();
    auto elapsed_ms2 = chrono::duration_cast<chrono::nanoseconds>(end2 - begin2);
    
    cout << endl;
    cout << "Time without alignment: " << elapsed_ms2.count() / 10 << "ns" << endl;
}
