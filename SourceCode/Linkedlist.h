#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "ListNode.h"
#include "ListItem.h"

class Linkedlist : public ListItem
{
	private:
		ListNode *top;
		ListNode *bottom;
		int length;
	public:
		Linkedlist();
		~Linkedlist();
		bool add(ListItem *item);
		ListItem *get_item(int index);
		ListNode *get_node(int index);
		ListItem *remove(int index);
		ListItem *remove_top();
		void print();
		int get_length();
		bool equals(ListItem *other);
		ListItem *copy();
};

#endif
