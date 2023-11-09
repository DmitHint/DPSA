#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>

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

int main()
{
	srand(time(NULL));
	int N = 100;
	const char* fname = "file_insurances.txt";
	AutoInsurance* records = new AutoInsurance[N];
	genRecords(records, N);
	FILE* fp;
	fopen_s(&fp, fname, "wb+");
	if (!fp)
	{
		cout << "Failed to create or write to file" << endl;
		return 0;
	}
	size_t r1 = fwrite(records, sizeof(AutoInsurance), N, fp) * sizeof(AutoInsurance);
	AutoInsurance last = getLastRecord(fp, N);
	cout << "Count = " << N << "; Byte = " << r1 << "; Last record: " << last.regNum << " - " << last.companyName << endl;
	fclose(fp);
}

void genRecords(AutoInsurance* records, int N)
{
	string alph = "abcdefghijklmnopqrstuvwxyz";
	int size = MAX_NUM - MIN_NUM + 1;
	int* nums = new int[size];
	for (int i = 0; i < size; ++i) 
		nums[i] = i + MIN_NUM;

	for (int i = size - 1 ; i > 0; i--)
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
