#include <iostream>
#include <cstdlib>

#include "TreeNode.h"

TreeNode::TreeNode(Item *i)
{
	item = i;
	children_number = 0;
	children = NULL;
}

TreeNode::TreeNode(TreeNode *copy)
{
	item = copy->item;
	children_number = copy->children_number;
	children = (TreeNode **)malloc(sizeof(TreeNode *) * children_number);
	
	int i;
	for (i = 0; i < children_number; i++)
	{
		children[i] = new TreeNode(copy->children[i]);
	}
}

TreeNode::~TreeNode()
{
	int i;
	for (i = 0; i < children_number; i++)
	{
		delete children[i];
	}
	free(children);
	delete item;
}

Item *TreeNode::get_item() {return item;}

// add another child to the children array
void TreeNode::add_child(TreeNode *child)
{
	TreeNode **new_children = (TreeNode **)malloc(sizeof(TreeNode *) * (children_number+1));
	
	int i;
	for (i = 0; i < children_number; i++)
	{
		new_children[i] = new TreeNode(children[i]);
	}
	
	new_children[children_number] = child;
	
	children = new_children;
	children_number++;
}

void TreeNode::set_quantity(int q)
{
	item->set_support(q);
}

void TreeNode::set_children(TreeNode **c, int q)
{
	children = c;
	item->set_support(q);
}

int TreeNode::get_children_number() { return children_number;}

TreeNode *TreeNode::get_child(int index)
{
	return children[index];
}

void TreeNode::print()
{
	item->print();
	
	int i;
	for (i = 0; i < children_number; i++)
	{
		children[i]->print();
	}
}

int *TreeNode::revise_array(int *array, int size)
{
	int *replacement = (int *)malloc(sizeof(int) * (size-1));
	
	int i;
	for (i = 1; i < size; i++)
	{
		replacement[i-1] = array[i];
	}
	
	return replacement;
}

void TreeNode::swap(int first, int second, int *array)
{
	int temp = array[first];
	array[first] = array[second];
	array[second] = temp;
}

// recursively adds the contents of a transaction to the node and its children
void TreeNode::add_transaction(int *array, int size)
{
	if (size > 0)
	{
		if (children_number == 0)
		{
			Item *i = new Item(array[0]);
			i->set_support(1);
			TreeNode *child = new TreeNode(i);
			add_child(child);
			int *new_array = revise_array(array, size);
			child->add_transaction(new_array, size-1);
		}
		else
		{
			TreeNode *curr = NULL;
			
			bool stop = false;
			int i;
			for (i = 0; i < children_number && !stop; i++)
			{
				curr = children[i];
				int name = curr->get_item()->get_name();
				// std::cout << "Name = " << name << std::endl;
				
				int j;
				for (j = 0; j < size && !stop; j++)
				{
					if (name == array[j])
					{
						// std::cout << "Incrementing " << name << std::endl;
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
				Item *i = new Item(array[0]);
				i->set_support(1);
				TreeNode *child = new TreeNode(i);
				add_child(child);
				int *new_array = revise_array(array, size);
				child->add_transaction(new_array, size-1);
			}
		}
	}
}

void TreeNode::increment_quantity()
{
	item->increment_support();
}

void TreeNode::delete_itemset_array(Set **set, int size)
{
	item->increment_support();
}

// recursively counts the number of children, and their children, and so on until it returns the number of nodes in the (sub)tree
int TreeNode::count()
{
	int count = -1;
	
	if (item == NULL)
	{
		count = 0;
	}
	else
	{
		count = 1;
	}
	
	if (children_number > 0)
	{
		int i;
		for (i = 0; i < children_number; i++)
		{
			// std::cout << i << " " << children[i]->get_item() << std::endl;
			count+= children[i]->count();
			
			// std::cout << "Count = " << count << std::endl;
		}
	}
	
	return count;
}

Set *TreeNode::examine()
{
	Set *set = new Set();
	std::cout << "Starting" << std::endl;

	if (children_number > 0)
	{
		if (item->get_name() > 0)
		{
			Item *curr = (Item *) item->copy();
			Set *singleton = new Set(curr);
			set->add_item(singleton);
		}
		
		// std::cout << "There are " << children_number << " Children for this node" << std::endl;
		// print();
		
		// call examine once for each child
		int i;
		for (i = 0; i < children_number; i++)
		{
			std::cout << "Stuff" << std::endl;
			Set *child_set = children[i]->examine();
			
			child_set->print();
			std::cout << "Merging" << std::endl;
			set->merge(child_set); // merge only adds the contents of the new set to set right now
			set->print();
			std::cout << "Done merging" << std::endl;
			delete child_set;
		}
	}
	else
	{
		std::cout << "No children" << std::endl;
		Item *curr = new Item(item);
		std::cout << "Item" << std::endl;
		Set *singleton = new Set(curr);
		std::cout << "Set" << std::endl;
		set->add_item(singleton);
		std::cout << "added singleton" << std::endl;
	}

	return set;
}

/*
int main()
{
	
}
*/
