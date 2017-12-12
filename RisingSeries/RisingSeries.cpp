// RisingSeries.cpp: ���������� ����� ����� ��� ����������� ����������.
// 19. � ������ ������� ������� ���������� ����� ������ ������ ���������, ������������� �� �����������.
// ��������� �������� ����, 9 ������
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <io.h>
#include <ctime>

using namespace std;

// ���� ������� ������� � ����������
int InputNumber() {
	int num;
	cout << "\n������� ������ �������: ";
	try {
		cin >> num;
		cout << endl;
	}
	catch (int) {
		exception("������ �����.\n");
		num = 0;
	}
	while (num <= 0)
	{
		cout << "������ ������� ������������ ������ ������ ����. ��������� ����: ";
		try {
			cin >> num;
			cout << endl;
		}
		catch (int) {
			exception("������ �����.\n");
			num = 0;
		}
	}
	cin.clear();
	return num;
};

// ���� �������� � ����������
int* InputArray(int* arr, int size) {
	cout << "������� ������: \n";
	for (int i = 0; i < size; i++) {
		cin >> arr[i];
	}
	cin.clear();
	return 0;
};

// ����� �� ����� ������� arr ������� size
void PrintArray(int* arr, int size) {
	cout << "���������� ������: ";
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
};

// �������� ������������� ����� � ������ fname
bool FileExists(const char* fname) {
	bool res;
	if (!_access(fname, 0))
		res = true;
	else res = false;
	return res;
}

// ���� ����� �����
string InputFileName() {
	string fname;
	const char* name = fname.c_str();
	cout << "������� ��� ���������� �����(������ ������ - ������ �����): ";
	cin >> fname;
	while (!FileExists(name)){
		cout << "������ ����� �� ����������, ��������� ����: ";
		cin >> fname;
    }
	cin.clear();
	return fname;
}

/* ������� ������������ ��������������������� ������������ ����� � ������� arr ������� size � ���������� ����� ������ mas ������� x,
 ���������� ��������� ���������������������*/
int* MaxSeries(int* arr, int size, int *x) {
	int t = 1; // ����� ������� ������������ ������������������
	int	max = 1; // ����� ������������ ������������ ������������������
	int k; // ������ ���������� ������������� ��������
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
	cout << "\n������ ������� ������" << endl;
	return mas;
};



//��������� ������ (������ arr) �� ���������� ����� � ������ fname, ����� ���������� ������ ���������� �������
int* LoadFromTxt(string fname, int* x) {
	ifstream fin;
	fin.open(fname); //��������� ����
	//�������� ���������� �������� ����� ��� ������
	if (!fin.good()) {
		cout << "\n ������ �������� �����";
		exit(1);
	}
	else {
		cout << "���� ������� ������ \n";
	}

	int i = 0;
	int n; // ������ ��c����
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
		exception("������ ����������");
	}
	if (i < n)
	{		
		cout << "� ����� ������������ ������.\n" << endl;
		ok = false;
	}
	*x = n;
	fin.close(); //�������� �����
	return arr;
}

//��������� ������ (������ arr ������� n) � ��������� ����� � ������ fname
int SaveToFile(string fname, int* arr, int n) {
	ofstream fout;
	fout.open(fname); //��������� ����
	//�������� ���������� �������� �����:
	if (!fout.is_open()) {
		cout << "\n ������ �������� �����";
		exit(1);
	}

	for (int i = 0; i < n; i++) {
		fout << arr[i] << " ";
	}
	fout.close(); //�������� �����
	cout << "������ � ���� ������� ���������" << endl;
	return 0;
}

// ����
void PrintMenu(bool b)
{
	if (!b) {
		cout << "---------------------------------------------------------------" << endl;
		cout << "[1] � ���� ������� � ����������" << endl;
		cout << "[2] � ������ ������� �� ���������� �����" << endl;
		cout << "[3] � ������� ������ ��������� �����" << endl;
	}
	else {
		cout << "---------------------------------------------------------------" << endl;
		cout << "[4] � ����� ���������� ����� ������ ������ ���������, ������������� �� �����������" << endl;
		cout << "[5] � ����� ����������� �� �����" << endl;
		cout << "[6] � ������ ����������� � ��������� ����" << endl;
		cout << "[0] � �����" << endl;
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");

	int p;
	int n; //������ ��������� �������
	int v = 0; //������ ��������������� �������
	bool ok = false;
	int* mas; // �������� ������
	int* res; // ������ � ���������������������� �� mas

	PrintMenu(ok);
	cout << "������� �������: ";
	cin >> p;
	cout << endl;
	cin.clear();

	switch (p)
	{
	case 1://���� ������� � ����������
	{
		n = InputNumber();
		mas = new int[n];
		InputArray(mas, n);
		ok = true;
		break;
	}

	case 2://������ ������� �� ���������� �����
	{
		string finname = InputFileName();
		mas = LoadFromTxt(finname, &n);
		PrintArray(mas, n);
		ok = true;
		break;
	}

	case 3://������� ������ ��������� �����
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
		cout << "����������� ������� �������" << endl;
		cin.get();
		cin.get();
	}
	
	while (ok) {
		PrintMenu(ok);
		cout << "������� �������: ";
		cin >> p;
		cout << endl;
		cin.clear();

		switch (p)
		{
		case 4://����� ���������� ����� ������ ������ ���������, ������������� �� �����������
		{
			res = MaxSeries(mas, n, &v);
			break;
		}

		case 5://����� ����������� �� �����
		{
			if (v == 0) {
				cout << "�������������� ������ ��� �� ���� ��������" << endl;
			}
			else {
				PrintArray(res, v);
			}
			
			break;
		}

		case 6://������ ����������� � ��������� ����
		{
			if (v == 0) {
				cout << "�������������� ������ ��� �� ���� ��������" << endl;
			}
			else {
				string foutname;
				cout << "������� ��� ��������������� �����(0 - output.txt �� ���������): ";
				cin >> foutname;
				if (foutname == "0")
					foutname = "output.txt";
				SaveToFile(foutname, res, v);
			}
			break;
		}

		case 0://�����
		{
			ok = false;
			cout << "������ ��������� ��������� \n";
			break;
		}

		default:
			cout << "����������� ������� �������" << endl;
		}
	}
	
	return 0;
}