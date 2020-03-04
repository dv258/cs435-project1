#include <iostream>
#include <queue>
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
				this->levelsTraversed++;
			}else
			if(value > node->value)
			{
				if(node->right == NULL)
				{
					node->setRightChild(new BSTNode<T>(value));
					return node->right;
				}

				node = node->right;
				this->levelsTraversed++;
			}else
			{
				break;
			}
		}

		return NULL;
	}

	bool deleteIter(T value)
	{
		if(this->root == NULL)
			return false;

		BSTNode<T> *node = this->root;
		BSTNode<T> *deleteJmp = NULL;

	lbldelete:
		while(true)
		{
			if(node == NULL)
				return false;

			if(value < node->value)
			{
				node = node->left;
				this->levelsTraversed++;
				continue;
			}
			if(value > node->value)
			{
				node = node->right;
				this->levelsTraversed++;
				continue;
			}

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
				node = left;
				deleteJmp = left;
			}else
			if(node->left == NULL && node->right != NULL)
			{
				BSTNode<T> *right = node->right;
				node->value = right->value;
				node = right;
				deleteJmp = right;
			}else
			{
				BSTNode<T> *replacer = this->findNextIter(node);
				node->value = replacer->value;
				node = replacer;
				deleteJmp = replacer;
			}

			if(deleteJmp != NULL)
			{
				node = deleteJmp;
				value = deleteJmp->value;
				deleteJmp = NULL;
				goto lbldelete;
			}

			return true;
		}

		return false;
	}

	BSTNode<T> *findNextIter(BSTNode<T> *node)
	{
		if(node->right != NULL)
			return this->findMinIter(node->right);

		for (BSTNode<T> *parent = node->parent; parent != NULL; parent = node->parent)
		{
			if(parent->value > node->value)
				return parent;

			this->levelsTraversed++;
		}

		return NULL;
	}

	BSTNode<T> *findPrevIter(BSTNode<T> *node)
	{
		if(node->left != NULL)
			return this->findMaxIter(node->left);

		for (BSTNode<T> *parent = node->parent; parent != NULL; parent = node->parent)
		{
			if(parent->value < node->value)
				return parent;

			this->levelsTraversed++;
		}

		return NULL;
	}

	BSTNode<T> *findMinIter(BSTNode<T> *node)
	{
		while(node->left != NULL)
		{
			node = node->left;

			this->levelsTraversed++;
		}

		return node;
	}

	BSTNode<T> *findMaxIter(BSTNode<T> *node)
	{
		while(node->right != NULL)
		{
			node = node->right;

			this->levelsTraversed++;
		}

		return node;
	}

	vector<T> getInOrder()
	{
		vector<T> vec;
		inOrder(vec, this->root);
		return vec;
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
		tree.insertIter(arr[i]);

	return tree.getInOrder();
}
