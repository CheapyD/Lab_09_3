#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h> 

using namespace std;

struct Price
{
	string goods;
	string shop;
	int price;
};

void Create(Price* p, const int N);
void Print(Price* p, const int N);
void Sort(Price* p, const int N);
int GoodsSearch(Price* p, const int N, const string goods);
void SaveToFile(Price* p, const int N, const char* filename);
void LoadFromFile(Price*& p, int& N, const char* filename);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int N;
	cout << "Введіть N: "; cin >> N;

	Price* p = new Price[N];

	char filename[100];
	string goods;
	int found;
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - вивід фізичного впорядкуваного масиву" << endl;
		cout << " [4] - пошук потрібного товару" << endl;
		cout << " [5] - запис даних у файл" << endl;
		cout << " [6] - зчитування даних із файлу" << endl << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl;

		switch (menuItem)
		{
		case 1:
			Create(p, N);
			break;
		case 2:
			Print(p, N);
			break;
		case 3:
			Sort(p, N);
			break;
		case 4:
			cout << "Введіть ключі пошуку:" << endl;
			cout << " Товар: "; cin >> goods;
			cout << endl;
			if ((found = GoodsSearch(p, N, goods)) != -1)
			{
			int m = found;
			cout << "Товар знайдено: " << endl;
			cout << "============================================="
				 << endl;
			cout << "| № |    Товар    |   Магазин   | Ціна(грн.)|"
				 << endl;
			cout << "---------------------------------------------"
				 << endl;
				cout << "| " << setw(1) << right << m + 1 << " ";
				cout << "| " << setw(12) << left << p[m].goods
					 << "| " << setw(11) << left << p[m].shop << " "
					 << "| " << setw(9) << left << p[m].price << " " << "|" << endl;
				cout << "---------------------------------------------"
					 << endl;
			}
			else
				cout << "Товар не знайдено" << endl;
			break;
		case 5:
			cin.sync();
			cin.get();
			cout << "Введіть ім'я файлу: "; cin.getline(filename, 99);
			SaveToFile(p, N, filename);
			break;
		case 6:
			cin.sync();
			cin.get();
			cout << "Введіть ім'я файлу: "; cin.getline(filename, 99);
			LoadFromFile(p, N, filename);
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);
	system("pause");
	return 0;
}

void Create(Price* p, const int N)
{
	for (int i = 0; i < N; i++)
	{
		cout << "Товар № " << i + 1 << ":" << endl;
		cin.sync();
		cin.get();
		cout << " Товар: "; getline(cin, p[i].goods);
		cin.sync();
		cout << " Магазин: "; getline(cin, p[i].shop);
		do
		{
			cout << " Ціна(грн.): "; cin >> p[i].price;
		} while (!(p[i].price > 0));
		cout << endl << endl << endl;
	}
}

void Print(Price* p, const int N)
{
		cout << "============================================="
			<< endl;
		cout << "| № |    Товар    |   Магазин   | Ціна(грн.)|"
			<< endl;
		cout << "---------------------------------------------"
			<< endl;
		for (int i = 0; i < N; i++)
		{
			cout << "| " << setw(1) << right << i + 1 << " ";
			cout << "| " << setw(12) << left << p[i].goods
				 << "| " << setw(11) << left << p[i].shop << " "
				 << "| " << setw(9) << left << p[i].price << " " << "|" << endl;
			cout << "---------------------------------------------"
				 << endl;
		}
}

void Sort(Price* p, const int N)
{
	Price tmp;
	for (int i0 = 0; i0 < N - 1; i0++)
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if ((p[i1].shop > p[i1 + 1].shop))			
			{
				tmp = p[i1];
				p[i1] = p[i1 + 1];
				p[i1 + 1] = tmp;
			}
}

int GoodsSearch(Price* p, const int N, const string goods)
{ 
	int L = 0, R = N - 1, m;
	do {
		m = (L + R) / 2;
		if (p[m].goods == goods)
			return m;
		if (p[m].goods < goods)
		{
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	} while (L <= R);
	return -1;
}

void SaveToFile(Price* p, const int N, const char* filename)
{
	ofstream fout(filename, ios::binary); 

	fout.write((char*)&N, sizeof(N)); 

	for (int i = 0; i < N; i++)
		fout.write((char*)&p[i], sizeof(Price)); 

	fout.close(); 
}

void LoadFromFile(Price*& p, int& N, const char* filename)
{
	delete[] p;

	ifstream fin(filename, ios::binary);

	fin.read((char*)&N, sizeof(N));

	p = new Price[N];

	for (int i = 0; i < N; i++)
		fin.read((char*)&p[i], sizeof(Price));

	fin.close();
}