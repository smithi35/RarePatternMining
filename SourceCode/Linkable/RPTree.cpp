#include "RPTree.h"

#include <iostream>
#include <cstdlib>

RPTree::RPTree()
{
	roots = new Linkedlist();
}

RPTree::~RPTree()
{
	delete roots;
}

// The order of the items in the transaction does not matter!!!
// This might get wildly inefficient
void RPTree::add_transaction(Transaction *transaction)
{
	int *items = transaction->get_items();
	int size = transaction->get_length();
	
	root->add_transaction(items, size);
}

Set *RPTree::examine()
{
	return root->examine();
}

int RPTree::size()
{
	int count = 0;
	
	int i;
	for (i = 0; i < roots->get_length(); i++)
	{
		ListNode *curr = roots->get_node(i);
		count += curr->count();
	}
	
	return count;
}

void RPTree::print()
{
	int i;
	for (i = 0; i < roots->get_length(); i++)
	{
		ListItem *curr = roots->get_item(i);
		curr->print();
	}
}
