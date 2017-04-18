#include "RPTree.h"

#include <iostream>
#include <cstdlib>

RPTree::RPTree()
{
	roots = NULL;
	present = 0;
	size = 0;
}

RPTree::~RPTree()
{
	int i;
	for (i = 0; i < present; i++)
		delete roots[i];
	delete [] roots;
}

void RPTree::add_root(TreeNode *root)
{
	if (present > 0)
	{
		if (present == size)
		{
			int new_size = size+5;
			TreeNode **rep = new TreeNode*[new_size];
			
			int i;
			for (i = 0; i < present; i++)
			{
				rep[i] = roots[i];
			}
			delete [] roots;
			rep[present] = root;
			present++;
			size = new_size;
			roots = rep;
		}
		else
		{
			roots[present] = root;
			present++;
		}
	}
	else
	{
		// add first root
		present = 1;
		size = 1;
		roots = new TreeNode*[size];
		roots[0] = root;
	}
}

// The order of the items in the transaction does not matter!!!
// Find a root that is included in the given transaction, if none exists
	// then a new root must be added to the roots array
void RPTree::add_transaction(Transaction *transaction)
{
	int *items = transaction->get_items();
	int size = transaction->get_length();
	int *copy = (int *)malloc(sizeof(int) * size);
	bool added = false;
	
	// copy transaction's items
	int i;
	for (i = 0; i < size; i++)
		copy[i] = items[i];
	items = copy;
	
	if (present > 0)
	{
		// find an item in the transaction that is equal to one of the roots
		for (i = 0; i < present && !added; i++)
		{
			ListItem *item = roots[i]->get_item();
			
			if (Item *temp = dynamic_cast<Item *>(item))
			{
				int name = temp->get_name();
				
				int j;
				for (j = 0; j < size && !added; j++)
				{
					if (name == items[j])
					{
						temp->increment_support();
						
						// move items[j] to the front of items
						int q = items[j];
						items[j] = items[0];
						items[0] = q;
						
						roots[i]->add_transaction(items, size, 1);
						added = true;
					}
				}
			}
		}
		
		if (!added)
		{
			// none of the items in the transaction correspond to a branch, need a new root
			Item *q = new Item(items[0]);
			TreeNode *add = new TreeNode(q);
			add->add_transaction(items, size, 1);
			add_root(add);
		}
	}
	else
	{
		// first root case
		Item *q = new Item(items[0]);
		TreeNode *add = new TreeNode(q);
		add->add_transaction(items, size, 1);
		add_root(add);
	}
	
	free(copy);
}

// examine the tree
Set *RPTree::examine()
{
	Set *out = new Set();
	
	int i;
	for (i = 0; i < present; i++)
	{
		Set *root = roots[i]->examine();
		out->add_sets(root);
		delete root;
	}
	
	return out;
}

// determine the size of the tree
int RPTree::tree_size()
{
	int total = 0;
	int i;
	for (i = 0; i < present; i++)
		total += roots[i]->count();
	
	return total;
}

void RPTree::print()
{
	std::cout << "Printing RPTree" << std::endl;
	int i;
	for (i = 0; i < present; i++)
	{
		roots[i]->print();
	}
}
