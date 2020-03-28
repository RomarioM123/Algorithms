#include "stdlib.h"
#include "iostream"
#define PB(value)(byte*)(value)
using namespace std;
typedef unsigned char byte;
typedef unsigned int dword;
template <class T> void show(const T& value)
{
	for (dword i = 0; i < sizeof(T); i++)
	{
		byte Byte = *(PB(&value) + i);
		for (dword j = 0; j < 8; j++)
			cout << dword((Byte >> (7 - j)) & 1);
		cout << ' ';
	}
	cout << endl;
}
void main()
{
	short int val1 = 0;
	float val2 = 0;
	char val3 = 'a';

	cout << "Enter short int value: ";
	cin >> val1;
	show(val1);

	cout << "Enter float value: ";
	cin >> val2;
	show(val2);

	cout << "Enter char value: ";
	cin >> val3;
	show(val3);

	return;
}