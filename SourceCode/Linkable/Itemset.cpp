#include "Itemset.h"
#include <iostream>
#include <cstdlib>

Itemset::Itemset(int s)
{
	size = s;
	set = (ListItem **)malloc(sizeof(ListItem *) * s);
	present = 0;
	ListItem::set_support(0);
}

Itemset::Itemset(Itemset *copy)
{
	present = copy->present;
	size = copy->size;
	ListItem::set_support(copy->ListItem::get_support());
	set = (ListItem **)malloc(sizeof(ListItem *) * size);
	
	int i;
	for (i = 0; i < present; i++)
	{
		if (Itemset *s = dynamic_cast<Itemset *>(copy->set[i]))
		{
			set[i] = new Itemset(s);
		}
		else if (Item *item = dynamic_cast<Item *>(copy->set[i]))
		{
			set[i] = new Item(item);
		}
	}
}

Itemset::~Itemset()
{
	int i;
	for (i = 0; i < size; i++)
	{
		delete(set[i]);
	}
	delete [] set;
}

void Itemset::increase_support(int add) { ListItem::increase_support(add);}

bool Itemset::add_item(ListItem *item)
{
	bool added = false;
	
	int i;
	for (i = 0; i < present && !added; i++)
	{
		if (set[i]->equals(item))
		{
			set[i]->increment_support();
			added = true;
		}
	}
	
	if (i == present && !added)
	{
		if (i < size)
		{
			set[i] = item;
			added = true;
			
			if (present + 1 <= size)
			{
				present++;
			}
			else
			{
				std::cout << "Itemset::add_item() says there is no more room in the itemset" << std::endl;
			}
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
			total++;
		}
	}
	
	int new_size = size-total;
	ListItem **new_set = (ListItem **)malloc(sizeof(ListItem *) * new_size);
	int next = 0;
	
	for (i = 0; i < present; i++)
	{
		if (set[i]->get_support() <= max_support)
		{
			if (Item *curr = dynamic_cast<Item *>(set[i]))
			{
				Item *n = new Item(curr->get_name(), set[i]->get_support());
				ListItem *l = (ListItem *)n;
				new_set[next] = l;
				next++;
			}
			else if (Itemset *curr = dynamic_cast<Itemset *>(set[i]))
			{
				Itemset *s = new Itemset(curr);
				ListItem *l = (ListItem *)s;
				new_set[next] = l;
				next++;
			}
		}
	}
	
	for (i = 0; i < present; i++)
		delete(set[i]);
	
	delete [] set;
	
	this->present = next;
	this->size = new_size;
	this->set = new_set;
}

bool Itemset::contains(ListItem *item)
{
	bool contains = false;
	
	int i;
	for (i = 0; i < present; i++)
	{
		if (set[i]->equals(item))
		{
			contains = true;
		}
	}
	
	return contains;
}

void Itemset::sort()
{
	std::cout << "Sorting Itemset" << std::endl;
	qsort(0, present-1);
}

void Itemset::qsort(int first, int last)
{
	int range = last - first;
	
	if (range >= 1)
	{
		int pivot = partition(first, last);
		// std::cout << "Pivot = " << pivot << std::endl;
		
		qsort(first, pivot);
		qsort(pivot+1, last);
	}
}

void Itemset::swap(int first, int second)
{
	ListItem *temp = set[first];
	set[first] = set[second];
	set[second] = temp;
}

int Itemset::partition(int first, int last)
{
	int boundary = first;
	
	int range = last - first;
	int random = rand() % range;
	random += first;
	
	// std::cout << "Random = " << random << std::endl;
	
	int pivot = set[random]->get_support();
	swap(boundary, random);
	
	int i;
	for (i = first+1; i <= last; i++)
	{
		if (set[i]->get_support() >= pivot)
		{
			boundary++;
			swap(boundary, i);
		}
	}
	swap(first, boundary);
	
	return random;
}

ListItem *Itemset::get_item(int index) { return set[index];}

int Itemset::get_support(int name)
{
	ListItem *temp = (ListItem *) new Item(name);
	int support = -1;
	
	int i;
	for (i = 0; i < present; i++)
	{
		ListItem *curr = set[i];
		
		if (curr->equals(temp))
		{
			support = curr->get_support();
		}
	}
	
	return support;
}

/*
int *Itemset::get_items()
{
	int *items = (int *)malloc(sizeof(int) * size);
	
	int i;
	for (i = 0; i < size; i++)
		items[i] = set[i]->get_name();
	
	return items;
}
*/
bool Itemset::equals(ListItem *other)
{
	bool equals = true;
	
	if (Itemset *p = dynamic_cast<Itemset *>(other))
	{
		int length1 = present;
		int length2 = p->present;
		
		if (length1 == length2)
		{
			int i;
			for (i = 0; i < present; i++)
			{
				if (!p->set[i]->equals(set[i]))
				{
					equals = false;
				}
			}
		}
		else
		{
			equals = false;
		}
	}
	else
	{
		equals = false;
	}
	
	return equals;
}
