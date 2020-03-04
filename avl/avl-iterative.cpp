#include <iostream>
#include <queue>
#include <vector>

using namespace std;

template <class T>
class AVLNode
{
public:
	AVLNode<T> *parent;
	AVLNode<T> *left;
	AVLNode<T> *right;

	unsigned int height;
	int balanceFactor; //left - right
	T value;

	AVLNode(T value)
	{
		this->parent = NULL;
		this->left = NULL;
		this->right = NULL;

		this->height = 0;
		this->balanceFactor = 0;
		this->value = value;
	}

	void setLeftChild(AVLNode<T> *node)
	{
		if(this->left != NULL)
			this->left->parent = NULL;

		if(node != NULL)
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
			}

			node->parent = this;
		}

		this->left = node;
	}

	void setRightChild(AVLNode<T> *node)
	{
		if(this->right != NULL)
			this->right->parent = NULL;

		if(node != NULL)
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
			}

			node->parent = this;
		}

		this->right = node;
	}

	bool isBalanced()
	{
		return this->balanceFactor != 2 && this->balanceFactor != -2;
	}
};

template <class T>
class AVL
{
public:
	AVLNode<T> *root;

	unsigned int levelsTraversed;

	AVL()
	{
		this->root = NULL;

		this->levelsTraversed = 0;
	}

	AVLNode<T> *insertIter(T value)
	{
		if(this->root == NULL)
		{
			this->root = new AVLNode<T>(value);
			return this->root;
		}

		AVLNode<T> *node = this->root;
		while(true)
		{
			if(value < node->value)
			{
				if(node->left == NULL)
				{
					node->setLeftChild(new AVLNode<T>(value));
					node = node->left;
					break;
				}

				node = node->left;
				this->levelsTraversed++;
			}else
			if(value > node->value)
			{
				if(node->right == NULL)
				{
					node->setRightChild(new AVLNode<T>(value));
					node = node->right;
					break;
				}

				node = node->right;
				this->levelsTraversed++;
			}else
			{
				break;
			}
		}

		if(this->updateNodesUpwards(node))
			this->checkNodeRotateUpwards(node);

		return node;
	}

	bool deleteIter(T value)
	{
		if(this->root == NULL)
			return false;

		AVLNode<T> *node = this->root;
		AVLNode<T> *deleteJmp = NULL;

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
				AVLNode<T> *parent = node->parent;

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
				node = parent;
			}else
			if(node->left != NULL && node->right == NULL)
			{
				AVLNode<T> *left = node->left;
				node->value = left->value;
				node = left;
				deleteJmp = left;
			}else
			if(node->left == NULL && node->right != NULL)
			{
				AVLNode<T> *right = node->right;
				node->value = right->value;
				node = right;
				deleteJmp = right;
			}else
			{
				AVLNode<T> *replacer = this->findNextIter(node);
				node->value = replacer->value;
				node = replacer;
				deleteJmp = replacer;
			}

			if(this->updateNodesUpwards(node))
				this->checkNodeRotateUpwards(node);

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

	AVLNode<T> *leftRotate(AVLNode<T> *node)
	{
		AVLNode<T> *parent = node->parent;
		AVLNode<T> *right = node->right;

		if(node != this->root)
		{
			if(parent->right == node)
			{
				parent->setRightChild(right);
			}else
			{
				parent->setLeftChild(right);
			}
		}else
		{
			this->root = right;
		}

		node->setRightChild(right->left);
		right->setLeftChild(node);
		return right;
	}

	AVLNode<T> *rightRotate(AVLNode<T> *node)
	{
		AVLNode<T> *parent = node->parent;
		AVLNode<T> *left = node->left;

		if(node != this->root)
		{
			if(parent->left == node)
			{
				parent->setLeftChild(left);
			}else
			{
				parent->setRightChild(left);
			}
		}else
		{
			this->root = left;
		}

		node->setLeftChild(left->right);
		left->setRightChild(node);
		return left;
	}

	AVLNode<T> *rotateNode(AVLNode<T> *node)
	{
		if(node->balanceFactor == 2)
		{
			if(node->left->balanceFactor == -1)
				leftRotate(node->left);
			return rightRotate(node);
		}else
		if(node->balanceFactor == -2)
		{
			if(node->right->balanceFactor == 1)
				rightRotate(node->right);
			return leftRotate(node);
		}
	}

	bool updateNodesUpwards(AVLNode<T> *node)
	{
		bool needsRotating = false;

		for (; node != NULL; node = node->parent)
		{
			this->updateNode(node);

			if(!node->isBalanced())
				needsRotating = true;

			this->levelsTraversed++;
		}

		return needsRotating;
	}

	void checkNodeRotateUpwards(AVLNode<T> *node)
	{
		for (; node != NULL; node = node->parent)
		{
			if(!node->isBalanced())
			{
				node = this->rotateNode(node);

				this->updateNode(node->left);
				this->updateNode(node->right);

				this->updateNodesUpwards(node);
			}

			this->levelsTraversed++;
		}
	}

	void updateNode(AVLNode<T> *node)
	{
		unsigned int lh = node->left != NULL ? node->left->height + 1 : 0;
		unsigned int rh = node->right != NULL ? node->right->height + 1 : 0;

		node->height = lh > rh ? lh : rh;
		node->balanceFactor = lh - rh;
	}

	AVLNode<T> *findNextIter(AVLNode<T> *node)
	{
		if(node->right != NULL)
			return this->findMinIter(node->right);

		for (AVLNode<T> *parent = node->parent; parent != NULL; parent = node->parent)
		{
			this->levelsTraversed++;

			if(parent->value > node->value)
				return parent;
		}

		return NULL;
	}

	AVLNode<T> *findPrevIter(AVLNode<T> *node)
	{
		if(node->left != NULL)
			return this->findMaxIter(node->left);

		for (AVLNode<T> *parent = node->parent; parent != NULL; parent = node->parent)
		{
			this->levelsTraversed++;

			if(parent->value < node->value)
				return parent;
		}

		return NULL;
	}

	AVLNode<T> *findMinIter(AVLNode<T> *node)
	{
		while(node->left != NULL)
		{
			node = node->left;
			this->levelsTraversed++;
		}

		return node;
	}

	AVLNode<T> *findMaxIter(AVLNode<T> *node)
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
	void inOrder(vector<T> &vec, AVLNode<T> *node)
	{
		if(node->left != NULL)
			inOrder(vec, node->left);
		vec.push_back(node->value);
		if(node->right != NULL)
			inOrder(vec, node->right);
	}
};

template <typename T>
vector<T> sortAVL(vector<T> arr)
{
	AVL<T> tree;

	for (int i = 0; i < arr.size(); i++)
		tree.insertIter(arr[i]);

	return tree.getInOrder();
}
