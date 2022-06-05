//11. Создать класс Array для работы с двумерными массивами(как
//	целочисленными, так и дробными).Отсортировать элементы главной и
//	побочной диагонали квадратной матрицы порядка n(указанном
//		пользователем) по возрастанию.Память под массив выделять динамически.
//	Необходимо обязательно освобождать память, выделенную под массив.
//	Написать свой манипулятор, выводящий содержимое массива в табличном
//	виде.


#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <windows.h>
using namespace std;

void ShellSort(int size, double mass[]);
int CreateInt();
int CheckInt(char c[]);
double CreateDouble();
int CheckDouble(char c[]);

class Array {
private:
	int MatrixSize;
	double** mas;
public:
	Array(int n); // конструктор
	~Array();// деструктор
	void SetMatrix(); //заполняем матрицу
	void SortMainDiagonal(); //сортируем главную диагональ
	void SortSideDiagonal(); // сортируем побочную диагональ
	void PrintMatrix(); //вывод матрицы
	void ChangeMatrix(int n) { // меняем матрицу
		delete[] mas;
		MatrixSize = n;
		mas = new double* [MatrixSize];
		for (int j = 0; j < MatrixSize; j++) {
			mas[j] = new double[MatrixSize];
		}
	};
};

ostream& MyManipulator(ostream& stream) {
	stream.setf(ios::left);
	stream << '|' << setw(10) << setfill(' ') ;
	return stream;
}

Array::Array(int n) {
	MatrixSize = n;
	this->mas = new double* [MatrixSize];
	for (int j = 0; j < MatrixSize; j++) {
		mas[j] = new double[MatrixSize];
	}
}

Array::~Array() {

	delete[] mas;
}

void Array::SetMatrix() {
	cout << "Введите элементы в массив:" << endl;
	for (int i = 0; i < MatrixSize; i++) {
		for (int j = 0; j < MatrixSize; j++) {
			this->mas[i][j] = CreateDouble();
		}
	}
}

void Array::SortMainDiagonal() {
	double *diagonal;
	int size = MatrixSize;
	diagonal = new double[size];
	for (int i = 0; i < size; i++) {//сделали массив из диагонали
		diagonal[i] = mas[i][i];
	}
	ShellSort(size, diagonal);
	//вывод отсортированного массива на экран
	cout << "Отсортированный массив:" << endl;
	for (int a = 0; a < MatrixSize * 11; a++) {
		cout << '*';
	}
	cout << endl;
	for (int i = 0; i < size; i++) {
		cout << MyManipulator << diagonal[i];
	}
	cout << endl;
	for (int a = 0; a < MatrixSize * 11; a++) {
		cout << '*';
	}
	cout << endl;
	delete[] diagonal;
}

void Array::SortSideDiagonal() {
	double* diagonal;
	int size = MatrixSize;
	diagonal = new double[size];
	for (int i = 0; i < size; i++) {//сделали массив из диагонали
		diagonal[i] = mas[i][MatrixSize - i - 1];
	}
	ShellSort(size, diagonal);
	//вывод отсортированного массива на экран
	cout << "Отсортированный массив:" << endl;
	for (int a = 0; a < MatrixSize * 11; a++) {
		cout << '*';
	}
	cout << endl;
	for (int i = 0; i < size; i++) {
		cout << MyManipulator << diagonal[i];
	}
	cout << endl;
	for (int a = 0; a < MatrixSize * 11; a++) {
		cout << '*';
	}
	cout << endl;
	delete[] diagonal;
}

void Array::PrintMatrix() {
	cout << "Двумерный массив:" << endl;
	for (int a = 0; a < MatrixSize * 11; a++) {
		cout << '*';
	}
	for (int i = 0; i < MatrixSize; i++) {
		cout << endl;
		for (int j = 0; j < MatrixSize; j++) {
			cout << MyManipulator << mas[i][j];
		}
		cout << endl;
		for (int a = 0; a < MatrixSize * 11; a++) {
			cout << '*';
		}
	}
	cout << endl;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int working = 1;
	int n = 0;
	int choise;
	cout << "Введите порядок матрицы: " << endl;
	n = CreateInt();
	Array a = Array(n);
	a.SetMatrix();
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	while (working) {
		cout << "" << endl;
		cout << "Выберите действие для работы с матрицей:" << endl;
		cout << "1. Создать матрицу 3х3." << endl;
		cout << "2. Создать матрицу произвольного порядка." << endl;
		cout << "3. Отсортировать главную диагональ." << endl;
		cout << "4. Отсортировать побочную диагональ." << endl;
		cout << "5. Вывести матрицу." << endl;
		cout << "6. Выйти." << endl;
		cout << endl;
		cin >> choise;
		switch (choise) {
		case 1:
		{
			a.ChangeMatrix(3);
			a.SetMatrix();
			break;
		}
		case 2:
		{
			cout << "Введите порядок матрицы: " << endl;
			n = CreateInt();
			a.ChangeMatrix(n);
			a.SetMatrix();
			break;
		}
		case 3:
		{
			a.SortMainDiagonal();
			break;
		}
		case 4:
		{
			a.SortSideDiagonal();
			break;
		}
		case 5:
		{
			a.PrintMatrix();
			break;
		}
		case 6:
		{
			working = 0;
			break;
		}
		default:
		{
			cout << "Некорректный ввод." << endl;
			break;
		}
		}
	}
	return 0;
}

void ShellSort(int size, double mass[])
{
	int i, j, step;
	double tmp;
	for (step = size / 2; step > 0; step /= 2)
		for (i = step; i < size; i++)
		{
			tmp = mass[i];
			for (j = i; j >= step; j -= step)
			{
				if (tmp < mass[j - step])
					mass[j] = mass[j - step];
				else
					break;
			}
			mass[j] = tmp;
		}
}

int CreateInt()
{
	char str[70] = "a";//заведомо ложное условие (не целое число)
	while (!CheckInt(str))
	{
		cin >> str;
		if (!CheckInt(str))
		{
			cout << "Некорректный ввод." << endl;
		}
	}
	int n = atoi(str);//перевод в целочисленный формат
	return n;
}

int CheckInt(char c[])
{
	for (int i = 0; i < strlen(c); i++)
	{
		if (c[i] > '9' || c[i] < '0')
		{
			return 0;//это не целое число
		}
	}
	return 1;//это целое число
}

double CreateDouble()
{
	char c[70] = "a";//заведомо ложное условие (не вещественное число)
	while (!CheckDouble(c))
	{
		cin >> c;
		if (!CheckDouble(c))
		{
			cout << "Некорректный ввод." << endl;
		}
	}
	double a = 0; //для целой части
	double b = 0; //для дробной части
	int i = 0;
	while (c[i] != '.' && c[i] != ',' && i < strlen(c)) //перебираем символы до '.' или ','
	{													//получаем целую часть
		char d[2];
		d[0] = c[i];
		d[1] = '\0';
		a *= 10;
		a += atoi(d);
		i++;
	}
	i++; //пропускаем '.' или ','
	if (i < strlen(c))//если число не закончилось после '.' или ','
	{
		while (c[i] >= '0' && c[i] <= '9' && i < strlen(c))
		{								//получение дробной части
			char d[2];
			d[0] = c[i];
			d[1] = '\0';
			b *= 10;
			b += atoi(d);
			i++;
		}
		while (b > 1)
		{
			b = b / 10;
		}
	}
	return (a + b); //возвращение вещественного числа
}

int CheckDouble(char c[])
{
	int flag = 0; //количество '.' или ','
	for (int i = 0; i < strlen(c); i++)
	{

		if ((c[i] < '0' && c[i] != '.' && c[i] != ',') || (c[i] > '9' && c[i] != '.' && c[i] != ',') || (flag > 0 && c[i] == '.') || (flag > 0 && c[i] == ','))
		{
			return 0;//это не вещественное число
		}
		else if (c[i] == '.' || c[i] == ',')
		{
			flag++;
		}
	}
	return 1;//это вещественное число
}