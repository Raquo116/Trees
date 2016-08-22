#include "tree.hpp"

template <typename Type>
class BinarySearchTree : public tree<Type>
{
public:
	BinarySearchTree() : tree<Type>() { }
	BinarySearchTree(branch<Type> *root) : tree<Type>(root) { }
	branch<Type> *Root() { return this->root; }
	void insert(Type e);
	void remove(Type e);
	bool check(Type e);
	void print() {
		if (this->root) this->root->inOrderPrint();
	}
};

template <typename Type>
void BinarySearchTree<Type>::insert(Type e)
{
	branch<Type> **t = &this->root;
	while (*t)
	{
		if ((*t)->data == e)
		{
			cerr << "Error: Unable to insert duplicate element\n";
			return;
		}
		t = (*t)->data > e ? &(*t)->left : &(*t)->right;
	}
	*t = new branch<Type>(e);
}

template <typename Type>
void BinarySearchTree<Type>::remove(Type e)
{
	branch<Type> **t = &this->root;
	while (*t)
	{
		if ((*t)->data == e)
		{
			branch<Type> *z = *t;
			if ((*t)->isLeaf())
				*t = NULL;
			else if ((*t)->isOnlyLeftLinked())
				*t = (*t)->left;
			else if ((*t)->isOnlyRightLinked())
				*t = (*t)->right;
			else
			{
				t = &(*t)->right;
				while ((*t)->left)
					t = &(*t)->left;
				z->data = (*t)->data;
				z = *t;
				*t = (*t)->right;
			}
			delete z;
			return;
		}
		t = (*t)->data > e ? &(*t)->left : &(*t)->right;
	}
	cerr << "Error: Element not in the tree\n";
}

template <typename Type>
bool BinarySearchTree<Type>::check(Type e)
{
	branch<Type> *t = this->root;
	while (t)
		if (t->data == e)
			return true;
		else
			t = t->data > e ? t->left : t->right;
	return false;
}
