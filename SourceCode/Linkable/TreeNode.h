#ifndef NODE_H
#define NODE_H

#include "Transaction.h"
#include "Itemset.h"
#include "Item.h"

class TreeNode
{
	private: 
		Item *item;
		TreeNode **children;
		int children_number;
		TreeNode(TreeNode *copy);
		void delete_children();
		Itemset **add_set(Itemset *set, Itemset *adding)
		void delete_itemset_array(Itemset **set, int size);
		int *revise_array(int *array, int size);
		void swap(int first, int second, int *array);
	public:
		TreeNode(Item *i);
		~TreeNode();
		Item *get_item();
		void add_child(TreeNode *child);
		void set_quantity(int q);
		void set_children(TreeNode **c, int q);
		int get_children_number();
		TreeNode *get_child(int index);
		void print();
		void add_transaction(int *array, int size);
		void increment_quantity();
		Itemset **examine();
		int count();
};

#endif

