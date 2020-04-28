#include <iostream>
#include <locale>
#include <string>
#include <iomanip>
#include <exception>
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::setw;
using std::exception;

typedef struct List
{
	string info;
	List* next;
}List;

typedef struct MultiList
{
	int studcode;
	string info;

	MultiList* next;
	List* deeper;
}MultiList;

void AddStudent(MultiList*, List*, string, int);
void CreateList(MultiList*);
MultiList* DeleteStudent(MultiList*);
void DeleteList(MultiList*);
void OutputData(MultiList*);

int main()
{
	setlocale(LC_ALL, "Russian");
	MultiList* head = new MultiList;
	head->deeper = new List;
	head->next = NULL;
	head->deeper->next = NULL;
	head->info = "0";
	string data, data2;
	int studcode;

	CreateList(head);
	OutputData(head);
	
	cout << "\nДобавление нового елемента списка\n\nВведите код студента\n";
	cout << "1) Обычный студент\n2) Студенты-иностранцы\n3) Студенты первокурсники\n";
	cout << "4) Магистры\n========================\n";
	cout << "Ваш выбор: ";
	cin >> studcode;
	cout << "Введите имя студента: ";
	cin >> data;
	getline(cin, data2);
	data = data + data2;

	AddStudent(head, head->deeper, data, studcode);
	OutputData(head);
	head = DeleteStudent(head);
	OutputData(head);
	DeleteList(head);

	return 0;
}

void OutputData(MultiList* h)
{
	MultiList* p = h;
	List* pDeeper = h->deeper;
	int i = 0;
	cout << endl;
	do
	{
		i = 0;
		if (p->studcode == 1)
		{
			cout << "Обычный студент " << p->info << setw(20) << "|| Код: " << p->studcode << endl;
		}
			
		else if (p->studcode == 2)
		{
			cout << "\nИностранцы" << endl;
			pDeeper = p->deeper;
			while (pDeeper != NULL)
			{
				
				if (i == 0)
				{
					cout << "Студент " << p->info << setw(20) << "|| Код: " << p->studcode << endl;
					i = 1;
				}
				cout << "  Студент: " << pDeeper->info << endl;
				pDeeper = pDeeper->next;

			}
		}
		else if (p->studcode == 3)
		{
			cout << "\nПервокурсники" << endl;
			pDeeper = p->deeper;
			while (pDeeper != NULL)
			{
				if (i == 0)
				{
					cout << "Студент " << p->info << setw(20) << "|| Код: " << p->studcode << endl;
					i = 1;
				}
				cout << "  Студент " << pDeeper->info << endl;
				pDeeper = pDeeper->next;

			}
		}
		else if (p->studcode == 4)
		{
			cout << "\nМагистры" << endl;
			pDeeper = p->deeper;
			while (pDeeper != NULL)
			{
				if (i == 0)
				{
					cout << "Студент " << p->info << setw(20) << "|| Код: " << p->studcode << endl;
					i = 1;
				}
				cout << "  Студент " << pDeeper->info << endl;
				pDeeper = pDeeper->next;
			}
		}
		p = p->next;
	} while (p != NULL);
}
void DeleteList(MultiList* h)
{
	MultiList* p = h, * pCopy;
	List* pDeeper, * dCopy;

	if (h)
		do
		{
			p = h;
			pCopy = h;
			if (h->next)
			{
				while (p->next) p = p->next;
				if (p->studcode == 1)
				{
					while (pCopy->next != p) pCopy = pCopy->next;
					delete p;
					pCopy->next = NULL;
				}
				else
				{
					pDeeper = p->deeper;
					dCopy = p->deeper;
					do
					{
						if (dCopy == pDeeper)
						{
							delete p->deeper;
							p->deeper = NULL;
						}
						else
						{
							pDeeper = p->deeper;
							dCopy = p->deeper;
							while (pDeeper->next != NULL)
							{
								pDeeper = pDeeper->next;
							}
							while (dCopy->next != pDeeper)
								dCopy = dCopy->next;
							delete pDeeper;
							dCopy->next = NULL;
							pDeeper = p->deeper;
							dCopy = p->deeper;
						}
					} while (p->deeper);
					while (pCopy->next != p) pCopy = pCopy->next;
					delete p;
					pCopy->next = NULL;
				}
			}
			else
			{
				if (p->studcode == 1)
				{
					delete h;
					h = NULL;
				}
				else
				{
					pDeeper = p->deeper;
					dCopy = p->deeper;
					do
					{
						if (dCopy == pDeeper)
						{
							delete p->deeper;
							p->deeper = NULL;
						}
						else
						{
							pDeeper = p->deeper;
							dCopy = p->deeper;
							while (pDeeper->next != NULL)
							{
								pDeeper = pDeeper->next;
							}
							while (dCopy->next != pDeeper)
								dCopy = dCopy->next;
							delete pDeeper;
							dCopy->next = NULL;
							pDeeper = p->deeper;
							dCopy = p->deeper;
						}
					} while (p->deeper);
					delete h;
					h = NULL;
				}
			}
		} while (h);
}
MultiList* DeleteStudent(MultiList* h)
{
	MultiList* p = h, * pCopy = h;
	List* pDeeper = h->deeper, * dCopy;
	string data, data2;
	int studcode;

	cout << "Введите код списка из которого хотите удалить студента: ";
	cin >> studcode;
	cout << "Введите имя студента которого хотите удалить: ";
	cin >> data;
	getline(cin, data2);
	data = data + data2;

	if (studcode == 1)
	{
		if (h->info == data)
		{
			h = h->next;
			delete p;
		}
		else
		{
			while (p->next != NULL)
			{
				if (p->info == data) break;
				p = p->next;
			}
			if (p->next)
			{
				while (pCopy->next != p) pCopy = pCopy->next;
				pCopy->next = p->next;
				delete p;
			}
			else
			{
				delete p;
				p = NULL;
			}

		}
	}
	else
	{
		if (p->studcode == studcode)
		{
			if (p->deeper->info == data)
			{
				if (!p->deeper->next)
				{
					delete p->deeper;
					if (p->info == data)
					{
						if (h->next)
						{
							h = h->next;
							delete p;
						}
						else delete p;
					}
				}
				else
				{
					pDeeper = p->deeper->next;
					delete p->deeper;
					p->deeper = pDeeper;
				}
			}
			else
			{
				pDeeper = p->deeper;
				while (pDeeper->next)
				{
					if (pDeeper->info == data) break;
					pDeeper = pDeeper->next;
				}
				if (pDeeper->next)
				{
					dCopy = p->deeper;
					while (dCopy->next != pDeeper) dCopy = dCopy->next;
					dCopy->next = dCopy->next->next;
					delete pDeeper;
				}
				else
				{
					dCopy = p->deeper;
					while (dCopy->next != pDeeper) dCopy = dCopy->next;
					delete pDeeper;
					dCopy->next = NULL;
					p->info = dCopy->info;
				}

			}
		}
		else
		{
			while (p->next)
			{
				if (p->studcode == studcode) break;
				p = p->next;
			}
			if (p->deeper->info == data)
			{
				if (!p->deeper->next)
				{
					delete p->deeper;
					if (p->info == data)
					{
						if (p->next)
						{
							while (pCopy->next != p) pCopy = pCopy->next;
							pCopy->next = p->next;
							delete p;
						}
						else
						{
							while (pCopy->next != p) pCopy = pCopy->next;
							delete p;
							pCopy->next = NULL;
						}
					}
				}
				else
				{
					pDeeper = p->deeper->next;
					delete p->deeper;
					p->deeper = pDeeper;
				}
			}
			else
			{
				pDeeper = p->deeper;
				while (pDeeper->next)
				{
					if (pDeeper->info == data) break;
					pDeeper = pDeeper->next;
				}
				if (p->next)
				{
					dCopy = p->deeper;
					while (dCopy->next != pDeeper) dCopy = dCopy->next;
					dCopy->next = dCopy->next->next;
					delete pDeeper;
				}
				else
				{
					dCopy = p->deeper;
					while (dCopy->next != pDeeper) dCopy = dCopy->next;
					delete pDeeper;
					dCopy->next = NULL;
					p->info = dCopy->info;
				}
			}
		}
	}
	return h;
}
void CreateList(MultiList* h)
{
	List* pDeeper = h->deeper;
	string data, data2;
	int choise;
	
	do
	{
		try
		{
			cout << "\nВведите код студента\n1) Обычный студент\n";
			cout << "2) Иностранец\n3) Первокурсник\n";
			cout << "4) Магистр\n5) Закончить заполнение списка\n";
			cout << "========================\nВаш выбор: ";
			cin >> choise;

			if (choise == 5) break;
			else if (choise >= 6 || choise <= 0) throw exception("Ошибка. Вы ввели неверный номер действия.");

			cout << endl << "Введите имя студента: ";
			cin >> data;
			getline(cin, data2);
			data = data + data2;

			AddStudent(h, pDeeper, data, choise);
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << endl;
		}

	} while (true);

}
void AddStudent(MultiList* h, List* pDeeper, string info, int studcode)
{

	MultiList* p = h;

	while (p->next)
	{
		if (p->studcode == studcode) break;
		p = p->next;
	}
	if (studcode == p->studcode && p->studcode == 1)
	{
		while (p->next) p = p->next;
		p->next = new MultiList;
		p = p->next;
		p->studcode = studcode;
		p->info = info;
		p->next = NULL;
	}
	else if (studcode == p->studcode && p->studcode == 2)
	{
		pDeeper = new List;
		pDeeper->info = info;
		pDeeper->next = p->deeper;
		p->deeper = pDeeper;
	}
	else if (studcode == p->studcode && p->studcode == 3)
	{
		pDeeper = new List;
		pDeeper->info = info;
		pDeeper->next = p->deeper;
		p->deeper = pDeeper;
	}
	else if (studcode == p->studcode && p->studcode == 4)
	{
		pDeeper = new List;
		pDeeper->info = info;
		pDeeper->next = p->deeper;
		p->deeper = pDeeper;
	}
	else
	{
		if (h->info == "0")
		{
			p->info = info;
			p->studcode = studcode;
			if (studcode != 1) p->deeper->info = info;
		}
		else
		{
			p->next = new MultiList;
			p = p->next;
			p->studcode = studcode;
			p->info = info;
			p->next = NULL;
			p->deeper = new List;
			p->deeper = NULL;
			
			if (studcode != 1)
			{
				pDeeper = new List;
				pDeeper->info = info;
				pDeeper->next = p->deeper;
				p->deeper = pDeeper;
			}
		}
	}
}