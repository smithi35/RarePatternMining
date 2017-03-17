#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "ListItem.h"
#include "ListNode.h"
#include <iostream>

class Linkedlist: public ListItem
{
	private:
		ListNode *head;
		ListNode *tail;
		int length;
	public:
		Linkedlist();
		~Linkedlist();
		bool insert(ListItem *item);
		ListItem *remove(int index);
		void print();
};

#endif
