#include "ListNode.h"

ListNode::ListNode(ListItem *i)
{
	BaseNode::set_item(i);
	next = NULL;
}

ListNode::~ListNode()
{
	next= NULL;
	
	// deleting the item could be difficult
	BaseNode::delete_item();
}

ListItem *ListNode::get_item() { return BaseNode::get_item;}
ListNode *ListNode::get_next() { return next;}

void ListNode::set_next(ListNode *n)
{
	next = n;
}
