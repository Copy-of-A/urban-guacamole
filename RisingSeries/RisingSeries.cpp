// RisingSeries.cpp: определяет точку входа для консольного приложения.
// 19. В данном массиве найдите наибольшую серию подряд идущих элементов, расположенных по возрастанию.
// Выполнила Маньшина Алла, 9 группа
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <io.h>
#include <ctime>

using namespace std;

// Ввод размера массива с клавиатуры
int InputNumber() {
	int num;
	cout << "\nВведите размер массива: ";
	try {
		cin >> num;
		cout << endl;
	}
	catch (int) {
		exception("Ошибка ввода.\n");
		num = 0;
	}
	while (num <= 0)
	{
		cout << "Размер массива определяется числом больше нуля. Повторите ввод: ";
		try {
			cin >> num;
			cout << endl;
		}
		catch (int) {
			exception("Ошибка ввода.\n");
			num = 0;
		}
	}
	cin.clear();
	return num;
};

// Ввод масссива с клавиатуры
int* InputArray(int* arr, int size) {
	cout << "Введите массив: \n";
	for (int i = 0; i < size; i++) {
		cin >> arr[i];
	}
	cin.clear();
	return 0;
};

// вывод на экран массива arr размера size
void PrintArray(int* arr, int size) {
	cout << "Полученный массив: ";
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
};

// Проверка существования файла с именем fname
bool FileExists(const char* fname) {
	bool res;
	if (!_access(fname, 0))
		res = true;
	else res = false;
	return res;
}

// Ввод имени файла
string InputFileName() {
	string fname;
	const char* name = fname.c_str();
	cout << "Введите имя текстового файла(Пустая строка - отмена ввода): ";
	cin >> fname;
	while (!FileExists(name)){
		cout << "Такого файла не существует, повторите ввод: ";
		cin >> fname;
    }
	cin.clear();
	return fname;
}

/* Находит возрастающую подпоследовательность максимальной длины в массиве arr размера size и возвращает новый массив mas размера x,
 содержащий найденную подпоследовательность*/
int* MaxSeries(int* arr, int size, int *x) {
	int t = 1; // длина текущей возрастающей последовательности
	int	max = 1; // длина максимальной возрастающей последовательности
	int k; // индекс последнего возрастающего элемента
	for (int i = 1; i < size; i++) {
		if (arr[i] > arr[i - 1])
		{
			t++;
		}
		else
		{
			if (max < t)
			{
				max = t;
				k = i - 1;
			}
			t = 1;
		}

	}
	if (t >= max) {
		k = size-1;
		max = t;
	}

	int* mas = new int[max];
	*x = max;
	for (int i = 0, j = k - max + 1; i < max; i++, j++) {
		mas[i] = arr[j];
	}
	cout << "\nЗадача успешно решена" << endl;
	return mas;
};



//Загружает данные (массив arr) из текстового файла с именем fname, также возвращает размер считанного массива
int* LoadFromTxt(string fname, int* x) {
	ifstream fin;
	fin.open(fname); //Открываем файл
	//Проверка успешности открытия файла для чтения
	if (!fin.good()) {
		cout << "\n Ошибка открытия файла";
		exit(1);
	}
	else {
		cout << "Файл успешно открыт \n";
	}

	int i = 0;
	int n; // размер маcсива
	bool ok = true;
	int* arr;
	try
	{
		fin >> n;
		arr = new int[n];
		while (i < n && !fin.eof()) {
			int a;
			fin >> a;
			arr[i] = a;
			i++;
		}
    }
	catch (int) {
		exception("Ошибка считывания");
	}
	if (i < n)
	{		
		cout << "В файле недостаточно данных.\n" << endl;
		ok = false;
	}
	*x = n;
	fin.close(); //Закрытие файла
	return arr;
}

//Сохраняет данные (массив arr размера n) в текстовый файлй с именем fname
int SaveToFile(string fname, int* arr, int n) {
	ofstream fout;
	fout.open(fname); //Открываем файл
	//Проверка успешности открытия файла:
	if (!fout.is_open()) {
		cout << "\n Ошибка открытия файла";
		exit(1);
	}

	for (int i = 0; i < n; i++) {
		fout << arr[i] << " ";
	}
	fout.close(); //Закрытие файла
	cout << "Данные в файл успешно загружены" << endl;
	return 0;
}

// Меню
void PrintMenu(bool b)
{
	if (!b) {
		cout << "---------------------------------------------------------------" << endl;
		cout << "[1] — Ввод массива с клавиатуры" << endl;
		cout << "[2] — Чтение массива из текстового файла" << endl;
		cout << "[3] — Создать массив случайных чисел" << endl;
	}
	else {
		cout << "---------------------------------------------------------------" << endl;
		cout << "[4] — Найти наибольшую серию подряд идущих элементов, расположенных по возрастанию" << endl;
		cout << "[5] — Вывод результатов на экран" << endl;
		cout << "[6] — Запись результатов в текстовый файл" << endl;
		cout << "[0] — Выход" << endl;
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");

	int p;
	int n; //размер исходного массива
	int v = 0; //размер результирующего массива
	bool ok = false;
	int* mas; // Исходный массив
	int* res; // Массив с подпоследовательностью из mas

	PrintMenu(ok);
	cout << "Введите команду: ";
	cin >> p;
	cout << endl;
	cin.clear();

	switch (p)
	{
	case 1://Ввод массива с клавиатуры
	{
		n = InputNumber();
		mas = new int[n];
		InputArray(mas, n);
		ok = true;
		break;
	}

	case 2://Чтение массива из текстового файла
	{
		string finname = InputFileName();
		mas = LoadFromTxt(finname, &n);
		PrintArray(mas, n);
		ok = true;
		break;
	}

	case 3://Создать массив случайных чисел
	{
		n = InputNumber();
		mas = new int[n];
		int rnd;
		srand(time(0));
		for (int i = 0; i < n; i++) {
			mas[i] = rand() % 1000;
		};
		PrintArray(mas, n);
		ok = true;
		break;
	}
	default:
		cout << "Неправильно введена команда" << endl;
		cin.get();
		cin.get();
	}
	
	while (ok) {
		PrintMenu(ok);
		cout << "Введите команду: ";
		cin >> p;
		cout << endl;
		cin.clear();

		switch (p)
		{
		case 4://Найти наибольшую серию подряд идущих элементов, расположенных по возрастанию
		{
			res = MaxSeries(mas, n, &v);
			break;
		}

		case 5://Вывод результатов на экран
		{
			if (v == 0) {
				cout << "Результирующие данные ещё не были получены" << endl;
			}
			else {
				PrintArray(res, v);
			}
			
			break;
		}

		case 6://Запись результатов в текстовый файл
		{
			if (v == 0) {
				cout << "Результирующие данные ещё не были получены" << endl;
			}
			else {
				string foutname;
				cout << "Введите имя результирующего файла(0 - output.txt по умолчанию): ";
				cin >> foutname;
				if (foutname == "0")
					foutname = "output.txt";
				SaveToFile(foutname, res, v);
			}
			break;
		}

		case 0://Выход
		{
			ok = false;
			cout << "Работа программы завершена \n";
			break;
		}

		default:
			cout << "Неправильно введена команда" << endl;
		}
	}
	
	return 0;
}