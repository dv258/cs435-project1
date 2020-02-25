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

	BSTNode<T> *insertRec(T value)
	{
		if(this->root == NULL)
		{
			this->root = new BSTNode<T>(value);
			return this->root;
		}

		return this->_insertRec(this->root, value);
	}

	bool deleteRec(T value)
	{
		return this->_deleteRec(this->root, value);
	}

	BSTNode<T> *findNextRec(BSTNode<T> *node)
	{
		if(node->right == NULL)
		{
			if(node->parent == NULL)
				return NULL;
			if(node->parent->value > node->value)
				return node->parent;
			return NULL;
		}
		return this->findMinRec(node->right);
	}

	BSTNode<T> *findPrevRec(BSTNode<T> *node)
	{
		if(node->left == NULL)
		{
			if(node->parent == NULL)
				return NULL;
			if(node->parent->value > node->value)
				return node->parent;
			return NULL;
		}
		return this->findMaxRec(node->left);
	}

	BSTNode<T> *findMinRec(BSTNode<T> *node)
	{
		if(node->left == NULL)
			return node;
		return this->findMinRec(node->left);
	}

	BSTNode<T> *findMaxRec(BSTNode<T> *node)
	{
		if(node->right == NULL)
			return node;
		return this->findMaxRec(node->right);
	}
private:
	BSTNode<T> *_insertRec(BSTNode<T> *node, T value)
	{
		if(node == NULL)
			return new BSTNode<T>(value);

		if(value < node->value)
		{
			node->setLeftChild(this->_insertRec(node->left, value));
		}else
		if(value > node->value)
		{
			node->setRightChild(this->_insertRec(node->right, value));
		}

		return node;
	}

	bool _deleteRec(BSTNode<T> *node, T value)
	{
		if(node == NULL)
			return false;

		if(value == node->value)
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
			}else
			{
				if(node->right != NULL)
				{
					BSTNode<T> *next = this->findNextRec(node);
					node->value = next->value;
					this->_deleteRec(next, next->value);
				}else
				{
					BSTNode<T> *prev = this->findNextRec(node);
					node->value = prev->value;
					this->_deleteRec(prev, prev->value);
				}
			}

			return true;
		}

		if(value < node->value)
			return this->_deleteRec(node->left, value);
		return this->_deleteRec(node->right, value);
	}
public:
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
		tree.insertRec(arr[i]);

	return tree.getInOrder();
}

int main(int argc, char *argv[])
{
	BST<int> tree;
	tree.insertRec(6);
	tree.insertRec(8);
	tree.insertRec(9);
	tree.insertRec(7);
	tree.insertRec(1);
	tree.insertRec(5);

	tree.printInOrder(tree.root);
	cout << endl;

	cout << tree.findNextRec(tree.root)->value << endl;
	cout << tree.findPrevRec(tree.root)->value << endl;

	tree.deleteRec(8);
	tree.printInOrder(tree.root);
	cout << endl;
	tree.deleteRec(1);
	tree.printInOrder(tree.root);
	cout << endl;
	tree.deleteRec(5);
	tree.printInOrder(tree.root);
	cout << endl;
	tree.deleteRec(6);
	tree.printInOrder(tree.root);
	cout << endl;
	return 0;
}
