#include <iostream>
#include <bitset>
#include <vector>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <chrono>

using namespace std;

void printBits(char c) {
	for (int i = 7; i >= 0; i--) {
		int bit = (c >> i) & 1;
		cout << bit;
	}
	cout << endl;
};

void task1_v() {
	cout << "Программа осуществляет перевод из 10сс в 2сс" << endl;
	unsigned int x = 25;     // 25 = 0x19
	cout << "Число x = 25, в 16-сс = 19" << endl;
	const int n = sizeof(int) * 8; // 32 - количество разрядов в числе типа int
	unsigned maska = (1 << n - 1); // 1 в старшем бите 32-разрядной сетки
	cout << "Начальный вид маски: " << bitset<n>(maska) << endl;
	cout << "Результат: ";
	for (int i = 1; i <= n; i++) // 32 раза - по количеству разрядов 
	{
		// maska проверяет, присутствует ли бит в числе, а сдвиг влево обеспечивает вывод цифры 0 или 1
		cout << ((x & maska) >> (n - i));
		maska = maska >> 1; // смещение 1 в маске на разряд вправо (для проверки следующего разряда)
	}
	cout << endl;
}

void task1() {
	cout << "Реализация примера 1.а" << endl;
	unsigned char x = 255;								// 8-разрядное двоичное число 11111111
	cout << "Значение x в 2сс = "; printBits(x);
	cout << "Значение x в 10сс = " << int(x) << endl;

	cout << endl;
	cout << "Установка 5-го бита в 0" << endl;
	unsigned char maska = 1;		//1=00000001 – 8-разрядная маска
	x = x & (~(maska << 4));		//результат x=239
	cout << "Значение x в 2сс = "; printBits(x);
	cout << "Значение x в 10сс = " << int(x) << endl;

	cout << endl;
	cout << "Введите число от 0 до 255: ";
	int input;
	cin >> input;
	x = char(input);
	cout << "Старое значение x в 2сс = "; printBits(x);
	cout << "Старое значение x в 10сс = " << int(x) << endl;
	x = x & (~(maska << 4));
	cout << "Новое значение x в 2сс = "; printBits(x);
	cout << "Новое значение x в 10сс = " << int(x) << endl;

	cout << endl;
	cout << "Реализация задания 1.б" << endl;
	const int n = 7;
	cout << "Установка " << n << "-го бита в 1" << endl;
	cout << "Введите число от 0 до 255: ";
	cin >> input;
	x = char(input);
	cout << "Старое значение x в 2сс = "; printBits(x);
	cout << "Старое значение x в 10сс = " << int(x) << endl;
	x = x | ((maska << (n - 1)));
	cout << "Новое значение x в 2сс = "; printBits(x);
	cout << "Новое значение x в 10сс = " << int(x) << endl;

	cout << endl;
	cout << "Реализация задания 1.в" << endl; // вывод битов числа (перевод в 2 сс)
	task1_v();
};

void task2_a() {
	const int n = 8;
	unsigned char list = 0;
	int input;
	cout << "Вводите восемь чисел от 0 до 7 через пробел (для завершения \"-1\")" << endl;
	cin >> input;
	int cnt = 1;
	while (input != -1 && cnt < 8) {
		list = list | ((1 << (n - 1 - input))); // установка 1 под индексом введенного числа
		cin >> input;
		cnt++;
	}
	cout << "Получился массив битов: {" << bitset<n>(list) << "}" << endl;

	unsigned maska = (1 << n - 1); // 1 в старшем бите
	cout << "Результат сортировки: { ";
	for (int i = 1; i <= n; i++)
	{
		// maska проверяет, присутствует ли бит в числе, а сдвиг влево обеспечивает проверку на наличие бита
		if ((list & maska) >> (n - i)) {
			cout << i - 1 << " ";
		}
		maska = maska >> 1; // смещение 1 в маске на разряд вправо (для проверки следующего разряда)
	}
	cout << "}" << endl;
}

void task2_b() {
	const int n = 64;
	unsigned long long list = 0, maska = 1;
	int input, cnt;
	cout << "Вводите числа от в диапазоне 0 до 63 через пробел (для завершения \"-1\")" << endl;
	for (int cnt = 0; cnt < 64; cnt++) {
		cin >> input;
		if (input == -1) {
			break;
		}
		list = list | (maska << (n - 1 - input)); // установка 1 под индексом введенного числа
	}

	cout << "Получился массив битов: {" << bitset<n>(list) << "}" << endl;

	cout << "Результат сортировки: { ";
	maska = (maska << n - 1); // 1 в старшем бите
	for (int i = 1; i <= n; i++)
	{
		// maska проверяет, присутствует ли бит в числе, а сдвиг влево обеспечивает проверку на наличие бита
		if ((list & maska) >> (n - i)) {
			cout << i - 1 << " ";
		}
		maska = maska >> 1; // смещение 1 в маске на разряд вправо (для проверки следующего разряда)
	}
	cout << "}" << endl;
}


void task2_v() {
	const int bitsCount = 64;
	const int byteSize = 8;
	vector<unsigned char> list(bitsCount / 8, 0); // Используем вектор байтов для хранения битов
	int input;

	cout << "Вводите числа от 0 до 63 через пробел (для завершения введите -1)" << endl;

	while (true) {
		cin >> input;

		if (input == -1) {
			break;
		}

		int byteIndex = input / 8;		// "байт" для записи
		int bitIndex = input % 8; // "бит" для записи (слева)
		list[byteIndex] = list[byteIndex] | (1 << ((byteSize - 1) - bitIndex)); // Установка бита в массиве
	}

	cout << "Результат: { ";
	for (int i = 0; i < bitsCount; i++) {
		int byteIndex = i / 8;
		int bitIndex = i % 8;

		if ((list[byteIndex] >> (byteSize - 1) - bitIndex) & 1) { // установлена ли "1" в бит bitIndex
			cout << i << " ";
		}
	}
	cout << "}" << endl;
}

void task2() {
	cout << "Реализация задания 2.а" << endl;
	task2_a();

	cout << "Реализация задания 2.б" << endl;
	task2_b();

	cout << "Реализация задания 2.в" << endl;
	task2_v();

}


void task3() {
	ofstream outputFile("numbers.txt");

	// Генерируем все семизначные числа и добавляем их в вектор
	vector<int> numbers;
	for (int i = 0; i < 8388608; ++i) {
		numbers.push_back(i);
	}

	// Перемешиваем числа в векторе
	random_shuffle(numbers.begin(), numbers.end());

	// Записываем числа в файл
	for (int num : numbers) {
		outputFile << num << endl;
	}

	// Закрываем файл
	outputFile.close();

	auto start = chrono::high_resolution_clock::now(); // Засекаем начальное время

	const int bitsInByte = 8, sizeInBits = int(pow(2, 23)); // 1 Мб

	vector<unsigned char> list(sizeInBits / bitsInByte, 0); // Используем вектор байтов для хранения битов

	// Открываем файл для чтения
	ifstream inputFile("numbers.txt");

	int number;

	// Считываем числа из файла, пока не достигнем конца файла
	while (inputFile >> number) {
		int byteIndex = number / bitsInByte;		// байт для записи
		int bitIndex = number % bitsInByte;		// бит для записи (слева)

		list[byteIndex] = list[byteIndex] | (1 << ((bitsInByte - 1) - bitIndex)); // Установка бита в массиве
	}

	// Закрываем файл
	inputFile.close();

	auto end = chrono::high_resolution_clock::now(); // Засекаем конечное время
	auto duration = chrono::duration_cast<chrono::seconds>(end - start); // Вычисляем длительность выполнения
	cout << "Время выполнения программы: " << duration.count() << " секунд" << endl;

	// Определяем размер битового массива в байтах
	size_t memorySize = list.size() * sizeof(unsigned char);
	cout << "Объём оперативной памяти, занимаемый битовым массивом = " << memorySize << " бит";
}

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Введите номер задания: ";
	int taskNum;
	cin >> taskNum;
	switch (taskNum)
	{
	case 1:
		task1();
		break;
	case 2:
		task2();
		break;
	case 3:
		task3();
		break;
	default:
		break;
	}

	return 0;
}

