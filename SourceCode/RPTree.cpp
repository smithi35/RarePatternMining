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

int main()
{
	RPTree *tree = new RPTree();
	delete tree;
}
