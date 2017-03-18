#include <iostream>
#include "Item.h"
#include <limits.h>

Item::Item(int n)
{
	name = n;
}

Item::Item()
{
	name = INT_MAX;
}

Item::Item(int n, int s)
{
	name = n;
	ListItem::set_support(s);
}

Item::Item(Item *item)
{
	name = item->name;
	ListItem::set_support(item->ListItem::get_support());
}

Item::~Item() {}

int Item::get_name() {return name;}
int Item::get_support() {return ListItem::get_support();}
void Item::set_support(int s) { ListItem::set_support(s); }
void Item::increase_support(int add) { ListItem::increase_support(add); }

void Item::print()
{
	std::cout << "Name: " << name << ", support = " << ListItem::get_support() << std::endl;
}

bool Item::equals(ListItem *other)
{
	bool equals = true;
	
	if (Item *p = dynamic_cast<Item *>(other))
	{
		if (p->name != name)
		{
			equals = false;
		}
	}
	
	return equals;
}
