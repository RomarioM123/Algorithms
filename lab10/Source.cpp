#include <iostream>
#include <iomanip>
#include <chrono>
#include <sstream>
#include <fstream>
#include <cmath>
using namespace std;
const int SIZE = 50000;			//количество элементов в списке
static int amountOfComparisons = 0;
static int value = 0;

struct HashTable
{
	long long PhoneNumber;
	string Surname;
	int TalkTime;
	string Address;

	HashTable* next;
} *Htable[SIZE];

int Hash(int);
void TableInitialization();
HashTable* Search(int);
void Insert(long long, int, string, string);
void Task();
void DeleteTable();

void main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
	
	Task();

	if (_CrtDumpMemoryLeaks())
		cout << endl << "Есть утечка памяти." << endl;
	else
		cout << endl << "Утечка памяти отсуствует." << endl;

}

void Task()
{
	string* SurnameList = new string[SIZE];
	long long* PhoneNumbersList = new long long[SIZE];
	int* TalkTimeList = new int[SIZE];
	string* AddressList = new string[SIZE];
	long long key;
	int SurnameLength;
	int AddressLength;
	long long value, value2;

	TableInitialization();

	for (size_t i = 0; i < SIZE; i++)
	{
		SurnameLength = rand() % 10 + 5;

		SurnameList[i] = rand() % 31 + 192;
		for (int j = 0; j < SurnameLength - 1; j++)
			SurnameList[i] += rand() % 31 + 224;
	}

	for (size_t i = 0; i < SIZE; i++)
	{
		PhoneNumbersList[i] = rand () % 9 + 0;
		for (size_t j = 1; j <= 3; j++)
		{
			key = rand() % 9 + 0;
			value = pow(10, j);
			
			PhoneNumbersList[i] += (key*value);
		}
	}
	key = 0;
	
	for (size_t i = 0; i < SIZE; i++)
		TalkTimeList[i] = rand() % 5000 + 10;

	for (int i = 0; i < SIZE; i++)
	{
		AddressLength = rand() % 15 + 5;

		AddressList[i] = rand() % 31 + 192;
		for (int j = 0; j < AddressLength - 1; j++)
			AddressList[i] += rand() % 31 + 224;
	}
	
	for (size_t i = 0; i < SIZE; i++)
		Insert(PhoneNumbersList[i], TalkTimeList[i], SurnameList[i], AddressList[i]);
	
	auto time = chrono::steady_clock::now();
	auto timeCopy = time;
	for (size_t i = 0; i < 10; i++)
	{
		key = rand() % 9 + 0;
		for (size_t j = 1; j <= 3; j++)
		{
			value = rand() % 9 + 0;
			value2 = pow(10, j);

			key += (value * value2);
		}
		
		auto begin = chrono::steady_clock::now();
		Search(key);
		auto end = chrono::steady_clock::now();
		auto elapsed_ms = chrono::duration_cast<chrono::nanoseconds>(end - begin);
		time += elapsed_ms;
	}
	auto result = (time - timeCopy) / 10;
	if (value == 0) value = 1;

	cout << "\nКоличество элементов: " << SIZE << "\nСреднее время поиска: " << result.count() << endl;
	cout << "Количество сравнений: " << amountOfComparisons / value << endl;
	
	delete[] SurnameList;
	delete[] PhoneNumbersList;
	delete[] TalkTimeList;
	delete[] AddressList;
	DeleteTable();
}

void TableInitialization()
{
	for (int i = 0; i < SIZE; i++)
		Htable[i] = NULL;
}

void Insert(long long phone, int talkTime, string surname, string address)
{
	HashTable* temp = new HashTable;
	long long key = Hash(phone);

	temp->next = NULL;
	temp->PhoneNumber = phone;
	temp->TalkTime = talkTime;
	temp->Surname = surname;
	temp->Address = address;
	
	//cout << setw(3) << key << "  ";
	//cout << temp->PhoneNumber << "\t" << temp->TalkTime << "\t" << temp->Surname << "\t" << temp->Address << endl;
	
	if (!Htable[key]) Htable[key] = temp;
	else
	{
		temp->next = Htable[key];
		Htable[key] = temp;
	}
}

int Hash(int key)
{
	key *= key;           // возвести ключ в квадрат
	int result = 0;
	while (key > 0)
	{
		result += key % 100;
		key = (key - key % 100) / 100;
	}
	result = result % SIZE;
	return result;

}

HashTable* Search(int x)
{
	int key = Hash(x), count = 0;
	bool check = 0;
	HashTable* temp = Htable[key];
	
	if (!temp) return NULL;
	while ((temp->next) && (temp->PhoneNumber != x))
	{
		temp = temp->next;
		count++;
		check = 1;
	}
	amountOfComparisons += count + 1;
	if (check) value++;
	if (temp->PhoneNumber != x) return NULL;
	
	return temp;
}

void DeleteTable()
{
	struct HashTable* p, * pCopy;

	for (size_t i = 0; i < SIZE; i++)
	{
		p = Htable[i];
		if (Htable[i] != NULL)
			while (p)
			{
				pCopy = p;
				p = p->next;
				delete pCopy;
			}
	}
}

