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
}

// recursively adds the contents of a transaction to the node and its children
void Node::add_transaction(int *array, int index, int size)
{
	if (index < size)
	{
		bool found = false;
		
		int i;
		for (i = 0; i < children_number && !found; i++)
		{
			Node *curr = this->get_child(i);
		
			if (curr->get_name() == array[0])
			{
				curr->increment_quantity();
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

void Node::increment_quantity() { quantity++; }

void Node::delete_itemset_array(Itemset **set, int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		delete(set[i]);
	}
	delete [] set;
}

Itemset **Node::combine_set(Itemset **first_set, Itemset **second_set, int count1, int count2)
{
	int size = count1 + count2;
	Itemset **combined = (Itemset **)malloc(sizeof(Itemset *) * size);
	
	int i;
	for (i = 0; i < count1; i++)
	{
		combined[i] = new Itemset(first_set[i]);
	}
	
	int index = i;
	
	for (i = 0; i < count2; i++)
	{
		combined[index] = new Itemset(second_set[i]);
		index++;
	}
	
	delete_itemset_array(first_set, count1);
	delete_itemset_array(second_set, count2);
	
	return combined;
}

// recursively counts the number of children, and their children, and so on until it returns the number of nodes in the (sub)tree
int Node::count()
{
	int count = 1;
	
	if (children_number > 0)
	{
		int i;
		for (i = 0; i < children_number; i++)
		{
			std::cout << i << " " << children[i]->get_name() << std::endl;
			count+= children[i]->count();
			
			std::cout << "Count = " << count << std::endl;
		}
	}
	
	return count;
}

Itemset **Node::examine()
{
	Itemset **set = NULL;
	// int old_count = 0;

	if (children_number > 0)
	{
		// call examine once for each child
		int i;
		for (i = 0; i < children_number; i++)
		{
			int new_count = children[i]->count();
			std::cout << "Count = " << new_count << std::endl;
			
			// Itemset **child_set = children[i]->examine();
			// set = combine_set(set, child_set, old_count, new_count);
			// old_count = new_count;
		}
	}
	else
	{
		set = (Itemset **)malloc(sizeof(Itemset *) * 1);
		set[0] = new Itemset(1);
		set[0]->add_item(name);
	}

	return set;
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
