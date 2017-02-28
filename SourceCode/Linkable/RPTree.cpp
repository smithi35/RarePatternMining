#include "RPTree.h"

#include <iostream>
#include <cstdlib>

RPTree::RPTree()
{
	root = NULL;
}

RPTree::~RPTree()
{
	delete root;
}

void RPTree::add_transaction(Transaction *transaction)
{
	int *items = transaction->get_items();
	
	int i;
	for (i = 0; i < root->get_children_number(); i++)
	{
		Node *curr = root->get_child(i);
		
		if (curr->get_name() == items[0])
		{
			
		}
	}
}

/*
int main()
{
	RPTree *tree = new RPTree();
	delete tree;
}
*/
