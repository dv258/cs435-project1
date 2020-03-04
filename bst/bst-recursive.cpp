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

	unsigned int levelsTraversed;

	BST()
	{
		this->root = NULL;

		this->levelsTraversed = 0;
	}

	BSTNode<T> *insertRec(T value)
	{
		if(this->root == NULL)
		{
			this->root = new BSTNode<T>(value);
			return this->root;
		}

		return this->_insertRec(this->root, NULL, value);
	}

	bool deleteRec(T value)
	{
		return this->_deleteRec(this->root, value);
	}

	BSTNode<T> *findNextRec(BSTNode<T> *node)
	{
		if(node->right != NULL)
			return this->findMinRec(node->right);

		for (BSTNode<T> *parent = node->parent; parent != NULL; parent = node->parent)
		{
			this->levelsTraversed++;

			if(parent->value > node->value)
				return parent;
		}

		return NULL;
	}

	BSTNode<T> *findPrevRec(BSTNode<T> *node)
	{
		if(node->left != NULL)
			return this->findMaxRec(node->left);

		for (BSTNode<T> *parent = node->parent; parent != NULL; parent = node->parent)
		{
			this->levelsTraversed++;

			if(parent->value < node->value)
				return parent;
		}

		return NULL;
	}

	BSTNode<T> *findMinRec(BSTNode<T> *node)
	{
		if(node->left == NULL)
			return node;

		this->levelsTraversed++;
		return this->findMinRec(node->left);
	}

	BSTNode<T> *findMaxRec(BSTNode<T> *node)
	{
		if(node->right == NULL)
			return node;

		this->levelsTraversed++;
		return this->findMaxRec(node->right);
	}

	vector<T> getInOrder()
	{
		vector<T> vec;
		inOrder(vec, this->root);
		return vec;
	}

private:
	BSTNode<T> *_insertRec(BSTNode<T> *node, BSTNode<T> *prev, T value)
	{
		if(node == NULL)
		{
			BSTNode<T> *newNode = new BSTNode<T>(value);
			if(value < prev->value)
			{
				prev->setLeftChild(newNode);
			}else
			{
				prev->setRightChild(newNode);
			}

			return newNode;
		}

		if(value < node->value)
		{
			this->levelsTraversed++;
			return this->_insertRec(node->left, node, value);
		}

		if(value > node->value)
		{
			this->levelsTraversed++;
			return this->_insertRec(node->right, node, value);
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
				BSTNode<T> *parent = node->parent;

				if(node != this->root)
				{
					if(parent->left == node)
					{
						parent->setLeftChild(NULL);
					}else
					{
						parent->setRightChild(NULL);
					}
				}else
				{
					this->root = NULL;
				}

				delete node;
			}else
			if(node->left != NULL && node->right == NULL)
			{
				BSTNode<T> *left = node->left;
				node->value = left->value;

				this->levelsTraversed++;
				this->_deleteRec(left, left->value);
			}else
			if(node->left == NULL && node->right != NULL)
			{
				BSTNode<T> *right = node->right;
				node->value = right->value;

				this->levelsTraversed++;
				this->_deleteRec(right, right->value);
			}else
			{
				BSTNode<T> *replacer = this->findNextRec(node);
				node->value = replacer->value;
				this->_deleteRec(replacer, replacer->value);
			}

			return true;
		}

		this->levelsTraversed++;

		if(value < node->value)
			return this->_deleteRec(node->left, value);
		return this->_deleteRec(node->right, value);
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
vector<T> sortBST(vector<T> arr)
{
	BST<T> tree;

	for (int i = 0; i < arr.size(); i++)
		tree.insertRec(arr[i]);

	return tree.getInOrder();
}
