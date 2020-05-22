#ifndef _LONGNUMBER_H_
#define _LONGNUMBER_H_
#define MAX_BITS 512

#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

#include <iostream>
#include <string>
#include <chrono>
#include <locale>

using namespace std;

class LongNumber {
    char m_bits[MAX_BITS];
    int m_nbits;

public:
    void clear();

    LongNumber operator*(LongNumber);
    LongNumber operator/(LongNumber);
    bool operator==(LongNumber);
    bool operator<(LongNumber);
    bool operator>(LongNumber);
    bool operator<=(LongNumber);

    LongNumber(unsigned long int k = 0);
    LongNumber(const LongNumber&);
    ~LongNumber();

};

#endif
