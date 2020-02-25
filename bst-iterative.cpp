#include <iostream>
#include <vector>

using namespace std;

template <class T>
class BSTNode
{
public:
	BSTNode<T> *parent;
	BSTNode<T> *left;
	BSTNode<T> *right;
	T value;

	BSTNode(T value)
	{
		this->parent = NULL;
		this->left = NULL;
		this->right = NULL;
		this->value = value;
	}

	void setLeftChild(BSTNode<T> *node)
	{
		if(this->left != NULL)
			this->left->parent = NULL;

		this->left = node;

		if(node != NULL)
			node->parent = this;
	}

	void setRightChild(BSTNode<T> *node)
	{
		if(this->right != NULL)
			this->right->parent = NULL;

		this->right = node;

		if(node != NULL)
			node->parent = this;
	}
};

template <class T>
class BST
{
public:
	BSTNode<T> *root;

	BST()
	{
		this->root = NULL;
	}

	BSTNode<T> *insertIter(T value)
	{
		if(this->root == NULL)
		{
			this->root = new BSTNode<T>(value);
			return this->root;
		}

		BSTNode<T> *node = this->root;
		while(true)
		{
			if(value < node->value)
			{
				if(node->left == NULL)
				{
					node->setLeftChild(new BSTNode<T>(value));
					return node->left;
				}

				node = node->left;
			}else
			if(value > node->value)
			{
				if(node->right == NULL)
				{
					node->setRightChild(new BSTNode<T>(value));
					return node->right;
				}

				node = node->right;
			}else
			{
				break;
			}
		}
	}

	bool deleteIter(T value)
	{
		if(this->root == NULL)
			return false;

		BSTNode<T> *node = this->root;
		while(true)
		{
			if(node == NULL)
				return false;

			if(value < node->value)
			{
				node = node->left;
			}else
			if(value > node->value)
			{
				node = node->right;
			}else
			{
				if(node->left == NULL && node->right == NULL)
				{
					if(node->parent != NULL)
					{
						if(node->parent->left == node)
						{
							node->parent->setLeftChild(NULL);
						}else
						{
							node->parent->setRightChild(NULL);
						}
					}else
					{
						this->root = NULL;
					}
					delete node;
				}else
				{
					if(node->right != NULL)
					{
						BSTNode<T> *next = this->findNextIter(node);
						node->value = next->value;
						if(next->parent->left == next)
						{
							next->parent->setLeftChild(NULL);
						}else
						{
							next->parent->setRightChild(NULL);
						}
						delete next;
					}else
					{
						BSTNode<T> *prev = this->findPrevIter(node);
						node->value = prev->value;
						if(prev->parent->left == prev)
						{
							prev->parent->setLeftChild(NULL);
						}else
						{
							prev->parent->setRightChild(NULL);
						}
						delete prev;
					}
				}

				return true;
			}
		}

		return false;
	}

	BSTNode<T> *findNextIter(BSTNode<T> *node)
	{
		if(node->right == NULL)
		{
			if(node->parent == NULL)
				return NULL;
			if(node->parent->value > node->value)
				return node->parent;
			return NULL;
		}
		return this->findMinIter(node->right);
	}

	BSTNode<T> *findPrevIter(BSTNode<T> *node)
	{
		if(node->left == NULL)
		{
			if(node->parent == NULL)
				return NULL;
			if(node->parent->value > node->value)
				return node->parent;
			return NULL;
		}
		return this->findMaxIter(node->left);
	}

	BSTNode<T> *findMinIter(BSTNode<T> *node)
	{
		while(true)
		{
			if(node->left == NULL)
				return node;

			node = node->left;
		}

		return node;
	}

	BSTNode<T> *findMaxIter(BSTNode<T> *node)
	{
		while(true)
		{
			if(node->right == NULL)
				return node;

			node = node->right;
		}

		return node;
	}

	vector<T> getInOrder()
	{
		vector<T> vec;
		inOrder(vec, this->root);
		return vec;
	}

	void printInOrder(BSTNode<T> *node)
	{
		if(node->left != NULL)
			printInOrder(node->left);
		cout << node->value << " ";
		if(node->right != NULL)
			printInOrder(node->right);
	}
private:
	void inOrder(vector<T> &vec, BSTNode<T> *node)
	{
		if(node->left != NULL)
			inOrder(vec, node->left);
		vec.push_back(node->value);
		if(node->right != NULL)
			inOrder(vec, node->right);
	}
};

template <typename T>
vector<T> sort(vector<T> arr)
{
	BST<T> tree;

	for (int i = 0; i < arr.size(); i++)
		tree.insertIter(arr[i]);

	return tree.getInOrder();
}

int main(int argc, char *argv[])
{
	BST<int> tree;
	tree.insertIter(6);
	tree.insertIter(8);
	tree.insertIter(9);
	tree.insertIter(7);
	tree.insertIter(1);
	tree.insertIter(5);

	tree.printInOrder(tree.root);
	cout << endl;

	cout << tree.findNextIter(tree.root)->value << endl;
	cout << tree.findPrevIter(tree.root)->value << endl;

	tree.deleteIter(8);
	tree.printInOrder(tree.root);
	cout << endl;
	tree.deleteIter(1);
	tree.printInOrder(tree.root);
	cout << endl;
	tree.deleteIter(5);
	tree.printInOrder(tree.root);
	cout << endl;
	tree.deleteIter(6);
	tree.printInOrder(tree.root);
	cout << endl;
	return 0;
}
