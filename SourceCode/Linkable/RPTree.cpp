#include "RPTree.h"

#include <iostream>
#include <cstdlib>

RPTree::RPTree()
{
	root = new Node(-1, 0);
}

RPTree::~RPTree()
{
	delete root;
}

// The order of the items in the transaction does not matter!!!
// This might get wildly inefficient
void RPTree::add_transaction(Transaction *transaction)
{
	int *items = transaction->get_items();
	int size = transaction->get_length();
	
	root->add_transaction(items, size);
}

Itemset **RPTree::examine()
{
	std::cout << std::endl << std::endl << std::endl << root->count() << std::endl << std::endl << std::endl;
	return NULL;
}

void RPTree::print()
{
	root->print();
	std::cout << std::endl;
}

/*
int main()
{
	RPTree *tree = new RPTree();
	delete tree;
}
*/
