#include <iostream>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

constexpr int STR_LENGTH = 10 + 1; //+1 for '\0'
constexpr int MAX_NUM = 999999;
constexpr int MIN_NUM = 100000;

struct AutoInsurance
{
	int regNum;
	char companyName[STR_LENGTH];
};

void genRecords(AutoInsurance* records, int N);

AutoInsurance getLastRecord(FILE* fp, int N);

AutoInsurance linearSearch(FILE* fp, int N, int searchNum);

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
		int key = last.regNum;
		start_time = chrono::high_resolution_clock::now();
		last = linearSearch(fp, N, key);
		end_time = chrono::high_resolution_clock::now();
		auto elapsed_time = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
		cout << "TIME = " << elapsed_time.count() * pow(10, -4) << "; Last record: " << last.regNum << " - " <<
			last.companyName <<  endl;
		cout << endl;
		fclose(fp);
	}
}

AutoInsurance linearSearch(FILE* fp, int N, int searchNum)
{
	AutoInsurance temp;
	for (int i = 0; i < N; ++i)
	{
		size_t r = fread(&temp, sizeof(AutoInsurance), 1, fp);
		if (temp.regNum == searchNum) 
			return temp;
		if (r == 0) 
			return { 0, "not found"};
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


AutoInsurance getLastRecord(FILE* fp, int N)
{
	fseek(fp, (N - 1) * sizeof(AutoInsurance), SEEK_SET);
	AutoInsurance temp;
	fread(&temp, sizeof(AutoInsurance), 1, fp);
	return temp;
}
