#include <iostream>
#include "Item.h"
#include <limits.h>

Item::Item(int n)
{
	name = n;
	ListItem::set_support(1);
}

Item::Item()
{
	name = INT_MAX;
	ListItem::set_support(0);
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

Item::~Item() { std::cout << "Deleting item" << std::endl; }

int Item::get_name() {return name;}
int Item::get_support() {return ListItem::get_support();}
void Item::set_support(int s) { ListItem::set_support(s); }
void Item::increase_support(int add) { ListItem::increase_support(add); }

void Item::print()
{
	std::cout << name << ":" << ListItem::get_support() << std::endl;
}

bool Item::equals(ListItem *other)
{
	bool equals = false;
	
	if (Item *p = dynamic_cast<Item *>(other))
	{
		if (p->name == name)
		{
			equals = true;
		}
	}
	
	return equals;
}

ListItem *Item::copy()
{
	Item *copy = new Item();
	copy->name = name;
	copy->ListItem::set_support(ListItem::get_support());
	
	return copy;
}
