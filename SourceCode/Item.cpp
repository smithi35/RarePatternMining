#include <iostream>
#include "Item.h"

Item::Item(int n)
{
	name = n;
	support = 0;
}

Item::~Item() {}

int Item::get_name() {return name;}
int Item::get_support() {return support;}
void Item::set_support(int s) {support = s;}
void Item::increment_support() {support++;}

bool Item::equal(int other)
{
	bool equal = false;
	
	if (other == name)
	{
		equal = true;
	}
	
	return equal;
}

void Item::print()
{
	std::cout << "Name: " << name << ", support = " << support << std::endl;
}
