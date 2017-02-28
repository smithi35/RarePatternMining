#ifndef NODE_H
#define NODE_H

#include "Transaction.h"

class Node
{
	private: 
		int name;
		int quantity;
		Node **children;
		int children_number;
		void delete_children();
	public:
		Node(int n, int q);
		~Node();
		int get_name();
		int get_quantity();
		void add_child(Node *child);
		void set_quantity(int q);
		void set_children(Node **c, int q);
		int get_children_number();
		Node *get_child(int index);
		void print();
		void add_transaction(int *array, int index, int size);
};

#endif

