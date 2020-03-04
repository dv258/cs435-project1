#include <iostream>
#include <vector>

#include <time.h>

#include "../avl/avl-iterative.cpp"
#include "../bst/bst-iterative.cpp"

#include "../int-arrays.cpp"

int main(int argc, char *argv[])
{
	vector<int> random = getRandomArray(10000);

	AVL<int> avl;
	BST<int> bst;

	clock_t start = clock();

	for (int i = 0; i < random.size(); i++)
		avl.insertIter(random[i]);

	while(avl.root != NULL)
		avl.deleteIter(avl.root->value);

	cout << "AVL levels: " << avl.levelsTraversed << endl;
	cout << "Time taken: " << (float)(clock() - start) * 1000 / CLOCKS_PER_SEC << " ms" << endl;

	start = clock();

	for (int i = 0; i < random.size(); i++)
		bst.insertIter(random[i]);

	while(bst.root != NULL)
		bst.deleteIter(bst.root->value);

	cout << "BST levels: " << bst.levelsTraversed << endl;
	cout << "Time taken: " << (float)(clock() - start) * 1000 / CLOCKS_PER_SEC << " ms" << endl;

	return 0;
}
