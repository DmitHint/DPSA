#include <iostream>
#include <string>

using namespace std;

struct Node {
	string data;
	Node* parent;
	Node* left;
	Node* right;
	int color;
};