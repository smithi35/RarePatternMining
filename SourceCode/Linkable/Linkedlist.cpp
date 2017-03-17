#include "Linkedlist.h"

Linkedlist::Linkedlist()
{
	head = NULL;
	tail = NULL;
	length = 0;
}

bool Linkedlist::insert(ListItem *item)
{
	ListNode *insert = new ListNode(item);
	bool success = false;
	
	if (head == NULL && tail == NULL)
	{
		head = insert;
		tail = insert;
		success = true;
	}
	else 
	{
		tail->set_next(insert);
		tail = insert;
		success = true;
	}
	
	if (success)
		length++;
	
	return success;
}

void Linkedlist::print()
{
	ListNode *curr = head;
	
	int i;
	for (i = 0; i < length; i++)
	{
		ListItem *item = curr->get_item();
		item->print();
		curr = curr->get_next();
	}
}
