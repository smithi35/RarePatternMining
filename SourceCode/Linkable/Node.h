#ifndef NODE_H
#define NODE_H

#include "Transaction.h"
#include "Itemset.h"
#include "Item.h"

class Node
{
	private: 
		Item *item;
		Node **children;
		int children_number;
		Node(Node *copy);
		void delete_children();
		Itemset **combine_set(Itemset **first_set, Itemset **second_set, int count1, int count2);
		void delete_itemset_array(Itemset **set, int size);
		int *revise_array(int *array, int size);
		void swap(int first, int second, int *array);
	public:
		Node(Item *i);
		~Node();
		Item *get_item();
		void add_child(Node *child);
		void set_quantity(int q);
		void set_children(Node **c, int q);
		int get_children_number();
		Node *get_child(int index);
		void print();
		void add_transaction(int *array, int size);
		void increment_quantity();
		Itemset **examine();
		int count();
};

#endif

