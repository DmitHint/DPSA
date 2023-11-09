#include <vector>
#include <iostream>
#include <string>

using namespace std;

struct Code {
	int index;
	string symbol;
	char sym;

	Code(int index, string symbol) : index(index), symbol(symbol), sym(NULL) {}
	Code(int index, char symbol) : index(index), symbol(""), sym(symbol) {}
};

bool find(string str, vector<Code*> nodes, int& n) {
	for (int i = 0; i < nodes.size(); i++)
		if (str == nodes[i]->symbol) {
			n = nodes[i]->index;
			return true;
		}

	return false;
}

void lz78Encode(const string& phrase) {

	string str = "";
	vector <Code*> dictionary;
	vector <Code*> nodes;
	int n = 0;

	for (int i = 0; i < phrase.size(); i++) {
		str += phrase[i];
		if (!find(str, dictionary, n)) {
			dictionary.push_back(new Code(dictionary.size() + 1, str));
			nodes.push_back(new Code(n, phrase[i]));
			n = 0;
			str = "";
		}
	}

	for (Code* node : nodes) {
		cout << "<" << node->index << ", " << node->sym << "> ";
	}
}

int main() {
	setlocale(LC_ALL, "ru");
	lz78Encode("менменаменаменатеп");
	return 0;
}