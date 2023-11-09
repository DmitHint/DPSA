#include <iostream>

using namespace std;

bool isPalindrome(const string& s) {
	int i = 0;
	int j = s.length() - 1;

	while (i < j) {
		if (s[i] != s[j]) {
			return false;
		}
		i++;
		j--;
	}

	return true;
}


int main() {
	string text = "abcd_effe_avbva_w4t", maxSubstring;
	setlocale(LC_ALL, "ru");

	int n = text.length();
	string max_palindrome = "";

	int maxLength = 0;
	for (int start = 0; start < text.length(); ++start) {
		for (int end = (start + 1) + maxLength; end < text.length(); ++end) {
			string substring = text.substr(start, end - start);
			if (isPalindrome(substring)) {
				maxLength = substring.length();
				maxSubstring = substring;
			}
		}
	}
	cout << "Палиндром максимальной длины: " << maxSubstring;
}
