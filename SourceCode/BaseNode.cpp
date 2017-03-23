#include "BaseNode.h"

ListItem *BaseNode::get_item() { return item; }
void BaseNode::set_item(ListItem *i) { item = i; }

void BaseNode::delete_item()
{
	delete item;
}

void BaseNode::print()
{
	item->print();
}
