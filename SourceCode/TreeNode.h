#ifndef NODE_H
#define NODE_H

#include "Transaction.h"
#include "Set.h"
#include "Item.h"

class TreeNode
{
	private:
		ListItem *item;
		TreeNode **children;
		int children_number;
		TreeNode(TreeNode *copy);
		void swap(int first, int second, int array[]);
	public:
		TreeNode(ListItem *i);
		~TreeNode();
		ListItem *get_item();
		void add_child(TreeNode *child);
		void set_quantity(int q);
		int get_children_number();
		TreeNode *get_child(int index);
		void print();
		void add_transaction(int array[], int size, int index);
		void increment_quantity();
		Set *examine();
		int count();
};

#endif

