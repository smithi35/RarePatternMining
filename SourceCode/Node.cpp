#include <iostream>

#include "Node.h"

Node::Node(int n, int q)
{
	name = n;
	quantity = q;
	children_number = 0;
	children = NULL;
}

Node::~Node()
{
	int i;
	for (i = 0; i < children_number; i++)
	{
		delete children[i];
	}
}
