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
	
	int i;
	for (i = 0; i < size; i++)
		copy[i] = items[i];
	items = copy;
	
	if (present > 0)
	{
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
						int q = items[j];
						items[j] = items[0];
						items[0] = q;						
						
						// remove items[j] from items array
						int rep[size-1];
						
						for (q = 1; q < size; q++)
						{
							rep[q-1] = items[q];
						}
						size--;
						
						
						roots[i]->add_transaction(rep, size);
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
			int replacement[size-1];
			
			for (i = 1; i < size; i++)
			{
				replacement[i-1] = items[i];
			}
			size--;
			items = replacement;
			
			add->add_transaction(replacement, size);
			add_root(add);
		}
	}
	else
	{
		// first root case
		Item *q = new Item(items[0]);
		TreeNode *add = new TreeNode(q);
		int replacement[size-1];
		
		int i;
		for (i = 1; i < size; i++)
		{
			replacement[i-1] = items[i];
		}
		size--;
		
		add->add_transaction(replacement, size);
		add_root(add);
	}
	
	free(copy);
}

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

/*
int main()
{
	RPTree *tree = new RPTree();
	delete tree;
}
*/
