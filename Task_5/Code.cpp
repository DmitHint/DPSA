#include "RedBlackTree.cpp"


int main()
{
    RedBlackTree rbTree;

    rbTree.insert("New York");
    rbTree.insert("London");
    rbTree.insert("Tokyo");
    rbTree.insert("Madrid");
    rbTree.insert("Moscow");
    rbTree.insert("Paris");
    rbTree.insert("Ottawa");



	cout << "*** TREE ***" << endl;
	rbTree.printTree();

    rbTree.insert("Rome");
	cout << "\nTREE after insertion 'Rome'" << endl;
	rbTree.printTree();

	cout << "\nInorder" << endl;
	rbTree.inorder();
	cout << "\nPreorder" << endl;
	rbTree.preorder();
	cout << "\n\nTree height: " << rbTree.treeHeight(rbTree.getRoot()) << endl;
	cout << "\nPath length to 'Rome': " << rbTree.searchTreeCnt("Rome") << endl;

    return 0;
}
