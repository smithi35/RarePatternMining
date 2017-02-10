#include "Itemset.h"
#include <iostream>
#include <cstdlib>

Itemset::Itemset(int s)
{
	size = s;
	set = (Item **)malloc(sizeof(Item *) * s);
	present = 0;
}

Itemset::~Itemset()
{
	int i;
	for (i = 0; i < size; i++)
	{
		delete set[i];
	}
	delete [] set;
}

bool Itemset::add_item(int item)
{
	bool added = false;
	int i;
	for (i = 0; i < present && !added; i++)
	{
		if (set[i]->equal(item))
		{
			set[i]->increment_support();
			added = true;
		}
	}
	
	if (i == present && !added)
	{
		Item *new_item = new Item(item);
		new_item->set_support(1);
		set[i] = new_item;
		present++;
		added = true;
	}
	
	return added;
}

void Itemset::print()
{
	int i;
	for (i = 0; i < present; i++)
	{
		set[i]->print();
	}
}
