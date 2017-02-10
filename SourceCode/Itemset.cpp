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
		added = true;
		
		if (present + 1 <= size) {
			present++;
		} else {
			std::cout << "Itemset::add_item() says there is no more room in the itemset" << std::endl;
		}
	}
	
	return added;
}

void Itemset::print()
{
	std::cout << "Printing itemset" << std::endl;
	int i;
	for (i = 0; i < present; i++)
	{
		set[i]->print();
	}
}

void Itemset::remove_non_rare_items(int max_support)
{
	int total = 0;
	
	int i;
	for (i = 0; i < present; i++)
	{
		if (set[i]->get_support() > max_support)
		{
			set[i] = new Item();
			total++;
		}
	}
	
	int new_size = size-total;
	Item **new_set = (Item **)malloc(sizeof(Item *) * new_size);
	int next = 0;
	
	for (i = 0; i < present; i++)
	{
		if (set[i]->get_support() <= max_support) {
			new_set[next] = new Item(set[i]->get_name(), set[i]->get_support());
			next++;
		}
	}
	
	for (i = 0; i < present; i++)
	{
		delete(set[i]);
	}
	delete [] set;
	
	this->present = next;
	this->size = new_size;
	this->set = new_set;
}

bool Itemset::contains(int item)
{
	bool contains = false;
	
	int i;
	for (i = 0; i < present; i++)
	{
		if (set[i]->get_name() == item)
		{
			contains = true;
		}
	}
	
	return contains;
}
