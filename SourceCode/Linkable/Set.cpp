#include "Set.h"
#include <iostream>
#include <cstdlib>

Set::Set(int s)
{
	size = s;
	set = (ListItem **)malloc(sizeof(ListItem *) * s);
	present = 0;
	ListItem::set_support(0);
}

Set::Set(Set *copy)
{
	present = copy->present;
	size = copy->size;
	ListItem::set_support(copy->ListItem::get_support());
	set = (ListItem **)malloc(sizeof(ListItem *) * size);
	
	int i;
	for (i = 0; i < present; i++)
	{
		if (Set *s = dynamic_cast<Set *>(copy->set[i]))
		{
			set[i] = new Set(s);
		}
		else if (Item *item = dynamic_cast<Item *>(copy->set[i]))
		{
			set[i] = new Item(item);
		}
	}
}

Set::Set()
{
	present = 0;
	size = 1;
	ListItem::set_support(0);
	set = (ListItem **)malloc(sizeof(ListItem *) * size);
}

Set::Set(Item *i)
{
	present = 1;
	size = 1;
	ListItem::set_support(1);
	set = (ListItem **)malloc(sizeof(ListItem *) * size);
	add_item(i);
}

Set::~Set()
{
	int i;
	for (i = 0; i < size; i++)
	{
		delete(set[i]);
	}
	delete [] set;
}

void Set::increase_support(int add) { ListItem::increase_support(add);}

bool Set::add_item(ListItem *item)
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
				std::cout << "Set::add_item() says there is no more room in the Set" << std::endl;
			}
		}
		else
		{
			resize();
		}
	}
	
	return added;
}

void Set::print()
{
	std::cout << "Printing Set" << std::endl;
	int i;
	for (i = 0; i < present; i++)
	{
		set[i]->print();
	}
}

void Set::remove_non_rare_items(int max_support)
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
			else if (Set *curr = dynamic_cast<Set *>(set[i]))
			{
				Set *s = new Set(curr);
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

bool Set::contains(ListItem *item)
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

void Set::sort()
{
	std::cout << "Sorting Set" << std::endl;
	qsort(0, present-1);
}

void Set::qsort(int first, int last)
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

void Set::swap(int first, int second)
{
	ListItem *temp = set[first];
	set[first] = set[second];
	set[second] = temp;
}

int Set::partition(int first, int last)
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

ListItem *Set::get_item(int index) { return set[index];}

int Set::get_support(int name)
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

bool Set::equals(ListItem *other)
{
	bool equals = true;
	
	if (Set *p = dynamic_cast<Set *>(other))
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

void Set::resize()
{
	size = 2 * size;
	set = copy(set, present);
}

ListItem **Set::copy(ListItem **old, int count)
{
	ListItem **new_set = (ListItem **)malloc(sizeof(ListItem *) * count);
	
	int i;
	for (i = 0; i < count; i++)
	{
		if (Set *s = dynamic_cast<Set *>(old[i]))
		{
			new_set[i] = new Set(s);
			delete(set[i]);
		}
		else if (Item *item = dynamic_cast<Item *>(old[i]))
		{
			new_set[i] = new Item(item);
			delete(set[i]);
		}
	}
	delete [] old
	
	return new_set;
}

void Set::merge(Set *other)
{
	int i;
	for (i = 0; i < other->present; i++)
	{
		add_item(other->set[i]);
	}
	
	delete(other);
}
