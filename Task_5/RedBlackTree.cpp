#include "Node.cpp"

class RedBlackTree {
private:
	Node* root;
	Node* TNULL;

	void initializeNULLNode(Node* node, Node* parent) {
		node->data = "null";
		node->parent = parent;
		node->left = nullptr;
		node->right = nullptr;
		node->color = 0;
	}

	// Preorder
	void preOrderHelper(Node* node) {
		if (node != TNULL) {
			cout << node->data << " ";
			preOrderHelper(node->left);
			preOrderHelper(node->right);
		}
	}

	// Inorder
	void inOrderHelper(Node* node) {
		if (node != TNULL) {
			inOrderHelper(node->left);
			cout << node->data << " ";
			inOrderHelper(node->right);
		}
	}

	Node* searchTreeHelper(Node* node, string key) {
		if (node == TNULL || key == node->data) {
			return node;
		}

		if (key < node->data) {
			return searchTreeHelper(node->left, key);
		}
		return searchTreeHelper(node->right, key);
	}


	int searchTreeCntHelper(Node* node, string key, int cnt) {
		if (node == TNULL || key == node->data) {
			return cnt;
		}

		if (key < node->data) {
			return searchTreeCntHelper(node->left, key, cnt + 1);
		}
		return searchTreeCntHelper(node->right, key, cnt + 1);
	}



	// For balancing the tree after insertion
	void insertFix(Node* k) {
		Node* u;
		while (k->parent->color == 1) {
			if (k->parent == k->parent->parent->right) {
				u = k->parent->parent->left;
				if (u->color == 1) {
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				}
				else {
					if (k == k->parent->left) {
						k = k->parent;
						rightRotate(k);
					}
					k->parent->color = 0;
					k->parent->parent->color = 1;
					leftRotate(k->parent->parent);
				}
			}
			else {
				u = k->parent->parent->right;

				if (u->color == 1) {
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				}
				else {
					if (k == k->parent->right) {
						k = k->parent;
						leftRotate(k);
					}
					k->parent->color = 0;
					k->parent->parent->color = 1;
					rightRotate(k->parent->parent);
				}
			}
			if (k == root) {
				break;
			}
		}
		root->color = 0;
	}

	void printHelper(Node* root, string indent, bool last) {
		if (root != TNULL) {
			cout << indent;
			if (last) {
				cout << "R----";
				indent += "   ";
			}
			else {
				cout << "L----";
				indent += "|  ";
			}

			string sColor = root->color ? "RED" : "BLACK";
			cout << root->data << "(" << sColor << ")" << endl;
			printHelper(root->left, indent, false);
			printHelper(root->right, indent, true);
		}
	}

public:
	RedBlackTree() {
		TNULL = new Node;
		TNULL->color = 0;
		TNULL->left = nullptr;
		TNULL->right = nullptr;
		root = TNULL;
	}

	void preorder() {
		preOrderHelper(this->root);
	}

	void inorder() {
		inOrderHelper(this->root);
	}

	int searchTreeCnt(string k) {
		return searchTreeCntHelper(this->root, k, 0);
	}

	Node* searchTree(string k) {
		return searchTreeHelper(this->root, k);
	}


	int treeHeight(Node* root) {
		if (root == nullptr) {
			return 0;
		}
		else {
			int leftHeight = treeHeight(root->left);
			int rightHeight = treeHeight(root->right);

			return std::max(leftHeight, rightHeight) + 1;
		}

	}

	void leftRotate(Node* x) {
		Node* y = x->right;
		x->right = y->left;
		if (y->left != TNULL) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		}
		else if (x == x->parent->left) {
			x->parent->left = y;
		}
		else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	void rightRotate(Node* x) {
		Node* y = x->left;
		x->left = y->right;
		if (y->right != TNULL) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		}
		else if (x == x->parent->right) {
			x->parent->right = y;
		}
		else {
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}

	// Inserting a node
	void insert(string key) {
		Node* node = new Node;
		node->parent = nullptr;
		node->data = key;
		node->left = TNULL;
		node->right = TNULL;
		node->color = 1;

		Node* y = nullptr;
		Node* x = this->root;

		while (x != TNULL) {
			y = x;
			if (node->data < x->data) {
				x = x->left;
			}
			else {
				x = x->right;
			}
		}

		node->parent = y;
		if (y == nullptr) {
			root = node;
		}
		else if (node->data < y->data) {
			y->left = node;
		}
		else {
			y->right = node;
		}

		if (node->parent == nullptr) {
			node->color = 0;
			return;
		}

		if (node->parent->parent == nullptr) {
			return;
		}

		insertFix(node);
	}

	Node* getRoot() {
		return this->root;
	}

	void printTree() {
		if (root) {
			printHelper(this->root, "", true);
		}
	}
};
