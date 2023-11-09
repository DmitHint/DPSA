#include <iostream>
#include <map>
#include <vector>

using namespace std;

// Функция для создания таблицы смещений
map<char, int> createCharTable(const string& pattern) {

	const int patternLength = pattern.length();
	map<char, int> charTable;

	// Инициализируем таблицу максимальным смещением
	for (int i = 0; i < patternLength; ++i) {
		charTable[pattern[i]] = patternLength - 1 - i;
	}

	return charTable;
}

bool searchBoyerMooreHorspool(string& text, string& pattern) {

	int textLength = text.length();
	int patternLength = pattern.length();

	if (textLength < patternLength) {
		return false;
	}

	map<char, int> charTable = createCharTable(pattern);

	int i = patternLength - 1;      // Индекс в строке
	while (i < textLength) {
		int j = patternLength - 1;  // Индекс в подстроке

		while (j >= 0 && text[i] == pattern[j]) {
			--i;
			--j;
		}

		if (j < 0) {
			return true;            // Подстрока найдена
		}

		if (charTable.find(text[i]) == charTable.end())
		{
			i += patternLength - 1 + (patternLength == 1 ? 1 : 0);
		}
		else
		{
			// Смещение на основе таблицы смещений для символа в тексте
			i += charTable[text[i]];
		}
	}

	return false;
}

int main()
{
	setlocale(LC_ALL, "ru");

	string input_string = "word1,word2,word3,word4,abbab,ababb";
	vector<string> words, answer;

	string delimiter = ",";

	size_t pos = 0;

	while ((pos = input_string.find(delimiter)) != string::npos) {
		string word = input_string.substr(0, pos);
		words.push_back(word);
		input_string.erase(0, pos + delimiter.length());
	}
	words.push_back(input_string);

	string pattern;
	cout << "Введите подстроку для поиска: ";
	cin >> pattern;

	for (auto w : words) {
		if (searchBoyerMooreHorspool(w, pattern)) {
			answer.push_back(w);
		}
	}

	for (auto ans : answer) {
		cout << ans << endl;
	}

	return 0;
}
