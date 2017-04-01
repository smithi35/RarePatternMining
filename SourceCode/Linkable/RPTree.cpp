#include "RPTree.h"

#include <iostream>
#include <cstdlib>

RPTree::RPTree()
{
	// root = 
	roots = NULL;
	count = 0;
}

RPTree::~RPTree()
{
	free(roots);
}

void RPTree::add_root(TreeNode *root)
{
	if (count > 0)
	{
		int new_count = count + 1;
		
		TreeNode **rep = (TreeNode **)malloc(sizeof(TreeNode *) * new_count);
		
		int i;
		for (i = 0; i < count; i++)
		{
			rep[i] = roots[i];
		}
		rep[count] = root;
		count = new_count;
		roots = rep;
	}
	else
	{
		count = 1;
		roots = (TreeNode **)malloc(sizeof(TreeNode *));
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
	bool added = false;
	
	if (count > 0)
	{
		int i;
		for (i = 0; i < count && !added; i++)
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
						
						// remove items[j] from items array
						int *rep = (int *)malloc(sizeof(int) * (size-1));
						
						int q;
						for (q = 1; q < size; q++)
						{
							rep[q-1] = items[q];
						}
						items = rep;
						size--;
						
						
						roots[i]->add_transaction(items, size);
						added = true;
					}
				}
			}
		}
		
		if (!added)
		{
			// put in function
			Item *q = new Item(items[0]);
			TreeNode *add = new TreeNode(q);
			
			int *replacement = (int *)malloc(sizeof(int) * (size - 1));
			
			for (i = 1; i < size; i++)
			{
				replacement[i-1] = items[i];
			}
			size--;
			items = replacement;
			
			add->add_transaction(items, size);
			
			add_root(add);
		}
	}
	else
	{
		Item *q = new Item(items[0]);
		TreeNode *add = new TreeNode(q);
		int *replacement = (int *)malloc(sizeof(int) * (size - 1));
		
		int i;
		for (i = 1; i < size; i++)
		{
			replacement[i-1] = items[i];
		}
		size--;
		items = replacement;
		
		add->add_transaction(items, size);
		add_root(add);
	}
}

Set *RPTree::examine()
{
	Set *out = new Set();
	
	int i;
	for (i = 0; i < count; i++)
	{
		out->merge(roots[i]->examine());
	}
	
	return out;
}

int RPTree::size()
{
	int total = 0;
	int i;
	for (i = 0; i < count; i++)
		total += roots[i]->count();
	
	return total;
}

void RPTree::print()
{
	std::cout << "Printing RPTree" << std::endl;
	int i;
	for (i = 0; i < count; i++)
	{
		std::cout << "i = " << i << std::endl;
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
