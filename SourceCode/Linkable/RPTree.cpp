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
	int size = transaction->get_length();
	
	int i;
	bool stop = false;
	for (i = 0; i < root->get_children_number() && !stop; i++)
	{
		Node *curr = root->get_child(i);
		
		if (curr->get_name() == items[0])
		{
			curr->add_transaction(items, 1, size);
			stop = true;
		}
	}
	
	if (!stop)
	{
		// otherwise, add to the root
		Node *child = new Node(items[0], 1);
		root->add_child(child);
		child->add_transaction(items, 1, size);
	}
}

void RPTree::print()
{
	root->print();
}

/*
int main()
{
	RPTree *tree = new RPTree();
	delete tree;
}
*/
