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
	int i;
	for (i = 0; i < count; i++)
	{
		delete roots[i];
	}
	delete [] roots;
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
			roots[i] = NULL;
		}
		rep[i+1] = root;
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
						roots[i]->add_transaction(items, size);
					}
				}
			}
		}
		
		if (!added)
		{
			// need to add a new root
			Item *q = new Item(items[0]);
			TreeNode *add = new TreeNode(q);
			
			int *replacement = (int *)malloc(sizeof(int) * (size - 1));
			
			for (i = 1; i < size; i++)
			{
				replacement[i-1] = items[i];
			}
			size--;
			free(items);
			items = replacement;
			
			add->add_transaction(items, size);
			std::cout << "Printing new tree" << std::endl;
			add->print();
			
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
		free(items);
		items = replacement;
		
		add->add_transaction(items, size);
		add_root(add);
		
		TreeNode *test = roots[count-1];
		Item *qr = (Item *)test->get_item();
		std::cout << "roots[count-1]: " << qr->get_name() << std::endl;
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
	int i;
	for (i = 0; i < count; i++)
		roots[i]->print();
}

/*
int main()
{
	RPTree *tree = new RPTree();
	delete tree;
}
*/
