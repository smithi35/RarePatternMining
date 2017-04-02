#include <iostream>
#include <cstdlib>

#include "TreeNode.h"

TreeNode::TreeNode(ListItem *i)
{
	item = i;
	children_number = 0;
	children = NULL;
}

TreeNode::TreeNode(TreeNode *copy)
{
	item = copy->item->copy();
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

ListItem *TreeNode::get_item() {return item;}

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

/*
void TreeNode::set_children(TreeNode **c, int q)
{
	children = c;
	ListItem *i = BaseNode::get_item();
	i->set_support(q);
}
*/

int TreeNode::get_children_number() { return children_number;}

TreeNode *TreeNode::get_child(int index)
{
	return children[index];
}

void TreeNode::print()
{
	if (Item *q = dynamic_cast<Item *>(item))
	{
		if (q->get_name() != -1)
		{
			q->print();
		}
		
		int i;
		for (i = 0; i < children_number; i++)
		{
			children[i]->print();
		}
	}
}

int *TreeNode::revise_array(int array[], int size)
{
	int *replacement = (int *)malloc(sizeof(int) * (size-1));
	
	int i;
	for (i = 1; i < size; i++)
	{
		replacement[i-1] = array[i];
	}
	
	return replacement;
}

void TreeNode::swap(int first, int second, int array[])
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
			// std::cout << "Children: " << children_number << std::endl;
			Item *i = new Item(array[0]);
			i->set_support(1);
			TreeNode *child = new TreeNode(i);
			add_child(child);
			int *new_array = revise_array(array, size);
			child->add_transaction(new_array, size-1);
			free(new_array);
		}
		else
		{
			TreeNode *curr = NULL;
			
			bool stop = false;
			int i;
			for (i = 0; i < children_number && !stop; i++)
			{
				curr = children[i];
				
				if (Item *q = dynamic_cast<Item *>(curr->get_item()))
				{
					int name = q->get_name();
					
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
							free(new_array);
							// this is not the most efficient way to add the transactions
						}
					}
				}
			}
			
			if (!stop)
			{
				// std::cout << "Need to add another child" << std::endl;
				Item *i = new Item(array[0]);
				i->set_support(1);
				TreeNode *child = new TreeNode(i);
				add_child(child);
				int *new_array = revise_array(array, size);
				child->add_transaction(new_array, size-1);
				free(new_array);
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
	// item->increment_support();
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

// Recursively examine the contents of this TreeNode and its children
Set *TreeNode::examine()
{
	Set *set = new Set();
	
	if (Item *q = dynamic_cast<Item *>(item))
	{
		Set *singleton = new Set(q);
		set->add_item(singleton);
		delete singleton;
		
		if (children_number > 0)
		{
			int i;
			for (i = 0; i < children_number; i++)
			{
				// examine each child node
				Set *child_set = children[i]->examine();
				Set *child_copy = (Set *)child_set->copy();
				
				// merge only adds the contents of the new set to set right now
				set->merge(child_set);
				delete child_set;
				
				int j;
				for (j = 0; j < child_copy->get_present(); j++)
				{
					ListItem *curr = child_copy->get_item(j);
					
					if (Set *c = dynamic_cast<Set *>(curr))
					{
						// add item to the contents of the set, the support value should remain the same
						c->add_item(q);
						set->add_item(c);
					}
				}
				
				delete child_copy;
			}
		}
	}
	
	return set;
}

/*
int main()
{
	
}
*/
