#include "ListNode.h"

ListNode::ListNode(ListItem *i)
{
	item = i;
	next = NULL;
}

ListNode::~ListNode()
{
	next= NULL;
	delete(item);
}

ListItem *ListNode::get_item() { return item;}
ListNode *ListNode::get_next() { return next;}

void ListNode::set_next(ListNode *n)
{
	next = n;
}
