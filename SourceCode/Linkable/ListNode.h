#ifndef LISTNODE_H
#define LISTNODE_H

#include <iostream>
#include "ListItem.h"

class ListNode
{
	private:
		ListItem *item;
		ListNode *next;
	public:
		ListNode(ListItem *i);
		~ListNode();
		ListItem *get_item();
		ListNode *get_next();
		void set_next(ListNode *n);
};

#endif
