#include "BaseNode.h"

ListItem *BaseNode::get_item() { return item; }
void *BaseNode::set_item(ListItem *i) { item = i; }

void BaseNode::delete_item()
{
	if (Itemset *s = dynamic_cast<Itemset *>(item))
	{
		delete(s);
	}
	else if (Item *i = dynamic_cast<Item *>(item))
	{
		delete(i);
	}
}