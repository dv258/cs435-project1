#include <iostream>
#include <vector>

#include "../avl/avl-recursive.cpp"
#include "../bst/bst-recursive.cpp"

#include "../int-arrays.cpp"

int main(int argc, char *argv[])
{
	vector<int> random = getRandomArray(10000);

	AVL<int> avl;
	BST<int> bst;

	clock_t start = clock();

	for (int i = 0; i < random.size(); i++)
		avl.insertRec(random[i]);

	cout << "AVL levels: " << avl.levelsTraversed << endl;
	cout << "Time taken: " << (float)(clock() - start) * 1000 / CLOCKS_PER_SEC << " ms" << endl;

	start = clock();

	for (int i = 0; i < random.size(); i++)
		bst.insertRec(random[i]);

	cout << "BST levels: " << bst.levelsTraversed << endl;
	cout << "Time taken: " << (float)(clock() - start) * 1000 / CLOCKS_PER_SEC << " ms" << endl;
	return 0;
}
