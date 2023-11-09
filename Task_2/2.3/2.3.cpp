#include <iostream>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

constexpr int STR_LENGTH = 10 + 1; //+1 for '\0'
constexpr int MAX_NUM = 999999;
constexpr int MIN_NUM = 100000;

struct AutoInsurance
{
	int regNum;
	char companyName[STR_LENGTH];
};

struct searchRecord
{
	int key;
	int ref; //index
};

void genRecords(AutoInsurance* records, int N);

AutoInsurance getRecord(FILE* fp, int pos);

int interpolationSearch(searchRecord* table, int n, int key);

AutoInsurance getLastRecord(FILE* fp, int N);

void createSearchTable(searchRecord* table, int N, FILE* fp);

bool compareTwoRecords(searchRecord a, searchRecord b);


int main()
{
	srand(time(NULL));
	int N = 100;
	const char* fname = "file_insurances.txt";
	FILE* fp;
	chrono::time_point<chrono::steady_clock> start_time;
	chrono::time_point<chrono::steady_clock> end_time;
	for (int N = 100; N <= 100000; N *= 10)
	{
		cout << "*** N = " << N << " ***" << endl;
		AutoInsurance* records = new AutoInsurance[N];
		genRecords(records, N);
		fopen_s(&fp, fname, "wb+");
		if (!fp)
		{
			cout << "Failed to create or write to file" << endl;
			return 0;
		}

		size_t r1 = fwrite(records, sizeof(AutoInsurance), N, fp) * sizeof(AutoInsurance);
		AutoInsurance last = getLastRecord(fp, N);
		cout << "Last record: " << last.regNum << " - " << last.companyName << endl;
		cout << "================================" << endl;

		fseek(fp, (0) * sizeof(AutoInsurance), SEEK_SET);

		searchRecord* table = new searchRecord[N];
		start_time = chrono::high_resolution_clock::now();
		createSearchTable(table, N, fp);
		end_time = chrono::high_resolution_clock::now();
		auto elapsed_time = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
		cout << "Creation time = " << elapsed_time.count() * pow(10, -4) << endl;

		int key = last.regNum;
		start_time = chrono::high_resolution_clock::now();
		int ref = interpolationSearch(table, N, key);
		end_time = chrono::high_resolution_clock::now();

		fseek(fp, (0) * sizeof(AutoInsurance), SEEK_SET);
		AutoInsurance rec = getRecord(fp, ref);


		elapsed_time = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
		cout << "TIME = " << elapsed_time.count() * pow(10, -4) << "; Last record: " << rec.regNum << " - " << rec.companyName << endl;
		cout << endl;
		fclose(fp);
	}
}


void genRecords(AutoInsurance* records, int N)
{
	string alph = "abcdefghijklmnopqrstuvwxyz";
	int size = MAX_NUM - MIN_NUM + 1;
	int* nums = new int[size];
	for (int i = 0; i < size; ++i)
		nums[i] = i + MIN_NUM;

	for (int i = size - 1; i > 0; i--)
	{
		int j = rand() % (i + 1);
		swap(nums[i], nums[j]);
	}

	AutoInsurance* rec;

	for (int r = 0; r < N; ++r)
	{
		rec = new AutoInsurance;
		int nameLength = rand() % ((STR_LENGTH - 1) - 2) + 3; // 3 <= rand < length ( (STR_LENGTH-1) for '\0' )

		rec->regNum = nums[r];
		for (int g = 0; g < nameLength; ++g)
		{
			rec->companyName[g] = alph[rand() % (alph.size())];
		}
		rec->companyName[nameLength] = '\0';
		records[r] = *rec;
	}
}

AutoInsurance getRecord(FILE* fp, int pos)
{
	fseek(fp, (pos) * sizeof(AutoInsurance), SEEK_SET);
	AutoInsurance temp;
	fread(&temp, sizeof(AutoInsurance), 1, fp);
	return temp;
}

int interpolationSearch(searchRecord* table, int n, int key)
{
	int left = 0;
	int right = n - 1;

	while (left <= right && key >= table[left].key && key <= table[right].key)
	{
		// Вычисляем оценку позиции ключа в массиве
		int pos = left + (((double)(right - left) / (table[right].key - table[left].key)) * (key - table[left].key));

		if (table[pos].key == key)
		{
			return table[pos].ref;
		}

		if (table[pos].key < key)
		{
			left = pos + 1;
		}
		else
		{
			right = pos - 1;
		}
	}

	return -1; // Если ключ не найден
}

void createSearchTable(searchRecord* table, int N, FILE* fp)
{
	AutoInsurance temp;
	for (int i = 0; i < N; i++)
	{
		size_t r = fread(&temp, sizeof(AutoInsurance), 1, fp);
		table[i].key = temp.regNum;
		table[i].ref = i;
	}
	sort(table, table + N, compareTwoRecords); // sort by key;
}

bool compareTwoRecords(searchRecord a, searchRecord b)
{
	return (a.key < b.key);
}

AutoInsurance getLastRecord(FILE* fp, int N)
{
	fseek(fp, (N - 1) * sizeof(AutoInsurance), SEEK_SET);
	AutoInsurance temp;
	fread(&temp, sizeof(AutoInsurance), 1, fp);
	return temp;
}
