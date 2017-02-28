#include <iostream>
#include <cstdlib>

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

int Node::get_name() {return name;}
int Node::get_quantity() {return quantity;}

// add another child to the children array
void Node::add_child(Node *child)
{
	Node **new_children = (Node **)malloc(sizeof(Node *) * (children_number+1));
	
	int i;
	for (i = 0; i < children_number; i++)
	{
		new_children[i] = children[i];
	}
	
	new_children[children_number] = child;
	
	children = new_children;
	children_number++;
}

void Node::set_quantity(int q)
{
	quantity = q;
}

void Node::set_children(Node **c, int q)
{
	children = c;
	quantity = q;
}

int Node::get_children_number() { return children_number;}

Node *Node::get_child(int index)
{
	return children[index];
}

void Node::print()
{
	std::cout << "Name = " << name << ", Quantity = " << quantity << ". ";
	
	int i;
	for (i = 0; i < children_number; i++)
	{
		children[i]->print();
	}
	std::cout << ")" << std::endl;
}

// recursively adds the contents of a transaction to the node and its children
void Node::add_transaction(int *array, int index, int size)
{
	if (index < size)
	{
		int i;
		bool found = false;
		for (i = 0; i < children_number && !found; i++)
		{
			Node *curr = this->get_child(i);
		
			if (curr->get_name() == array[0])
			{
				curr->add_transaction(array, index+1, size);
				found = true;
			}
		}
		
		if (!found)
		{
			Node *child = new Node(array[index], 1);
			add_child(child);
			child->add_transaction(array, index+1, size);
		}
	}
}

/*
int main()
{
	Node *test = new Node(3, 0);
	test->print();
	test->add_child(new Node(2, 1));
	test->print();
	test->add_child(new Node(4, 1));
	test->set_quantity(6);
	test->print();
	
	return 0;
}
*/
