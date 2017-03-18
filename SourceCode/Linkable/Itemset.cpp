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

ListItem *Itemset::copy(ListItem *other)
{
	if (Itemset *s = dynamic_cast<Itemset *>(other))
	{
		Itemset *copied = new Itemset(s->size);;
		copied->present = s->present;
		copied->ListItem::set_support(s->ListItem::get_support());
		copied->set = (ListItem **)malloc(sizeof(ListItem *) * copied->size);
		
		int i;
		for (i = 0; i < s->present; i++)
		{
			copied->set[i] = copy(s->set[i]);
		}
	}
	
	return NULL;
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

void Itemset::increase_support(int add) { ListItem::increase_support(add);}

bool Itemset::add_item(ListItem *item)
{
	bool added = false;
	
	int i;
	for (i = 0; i < present && !added; i++)
	{
		if (set[i]->equals(item))
		{
			set[i]->increase_support(item->get_support());
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
			set[i] = (ListItem *) new Item();
			total++;
		}
	}
	
	int new_size = size-total;
	ListItem **new_set = (ListItem **)malloc(sizeof(ListItem *) * new_size);
	int next = 0;
	
	for (i = 0; i < present; i++)
	{
		if (set[i]->get_support() <= max_support) {
			Item *curr = (Item *)set[i];
			Item *n = new Item( curr->get_name(), set[i]->get_support());
			ListItem *l = (ListItem *)n;
			new_set[next] = l;
			next++;
		}
	}
	
	for (i = 0; i < present; i++)
	{
		delete(set[i]);
	}
	//delete [] set;
	
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
		std::cout << "Pivot = " << pivot << std::endl;
		
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
	
	std::cout << "Random = " << random << std::endl;
	
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

/*
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
