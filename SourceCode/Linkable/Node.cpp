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

Node::Node(Node *copy)
{
	name = copy->name;
	quantity = copy->quantity;
	children_number = copy->children_number;
	children = (Node **)malloc(sizeof(Node *) * children_number);
	
	int i;
	for (i = 0; i < children_number; i++)
	{
		children[i] = new Node(copy->children[i]);
	}
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
		new_children[i] = new Node(children[i]);
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
	std::cout << name << ":" << quantity << ", ";
	
	int i;
	for (i = 0; i < children_number; i++)
	{
		children[i]->print();
	}
}

int *Node::revise_array(int *array, int size)
{
	int *replacement = (int *)malloc(sizeof(int) * (size-1));
	
	int i;
	for (i = 1; i < size; i++)
	{
		replacement[i-1] = array[i];
	}
	
	return replacement;
}

void Node::swap(int first, int second, int *array)
{
	int temp = array[first];
	array[first] = array[second];
	array[second] = temp;
}

// recursively adds the contents of a transaction to the node and its children
void Node::add_transaction(int *array, int size)
{
	if (size > 0)
	{
		if (children_number == 0)
		{
			Node *child = new Node(array[0], 1);
			add_child(child);
			int *new_array = revise_array(array, size);
			child->add_transaction(new_array, size-1);
		}
		else
		{
			Node *curr = NULL;
			
			bool stop = false;
			int i;
			for (i = 0; i < children_number && !stop; i++)
			{
				curr = children[i];
				int name = curr->get_name();
				std::cout << "Name = " << name << std::endl;
				
				int j;
				for (j = 0; j < size && !stop; j++)
				{
					if (name == array[j])
					{
						std::cout << "Incrementing " << name << std::endl;
						stop = true;
						curr->increment_quantity();
						swap(0, j, array);
						int *new_array = revise_array(array, size);
						curr->add_transaction(new_array, size-1);
						// this is not the most efficient way to add the transactions
					}
				}
			}
			
			if (!stop)
			{
				Node *child = new Node(array[0], 1);
				add_child(child);
				int *new_array = revise_array(array, size);
				child->add_transaction(new_array, size-1);
			}
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
