#include <iostream>
#include "Item.h"
#include <limits.h>

Item::Item(int n)
{
	name = n;
	support = 0;
}

Item::Item()
{
	name = INT_MAX;
	support = INT_MAX;
}

Item::Item(int n, int s)
{
	name = n;
	support = s;
}

Item::Item(Item *item)
{
	name = item->name;
	support = item->support;
}

Item::~Item() {}

int Item::get_name() {return name;}
int Item::get_support() {return support;}
void Item::set_support(int s) {support = s;}
void Item::increment_support() {support++;}
void Item::increase_support(int add) { support += add; }

bool Item::equal(int other)
{
	bool equal = false;
	
	if (other == name)
	{
		equal = true;
	}
	
	return equal;
}

bool Item::equal(Item *other)
{
	bool equal = false;
	
	if (other->name == name)
	{
		equal = true;
	}
	
	return equal;
}

void Item::print()
{
	std::cout << "Name: " << name << ", support = " << support << std::endl;
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
