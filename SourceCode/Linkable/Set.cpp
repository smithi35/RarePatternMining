#include "Set.h"
#include <iostream>
#include <cstdlib>

Set::Set(int s)
{
	size = s;
	set = new ListItem *[s];
	init_array();
	present = 0;
	ListItem::set_support(0);
}

Set::Set(Set *copy)
{
	present = copy->present;
	size = copy->size;
	ListItem::set_support(copy->ListItem::get_support());
	set = new ListItem *[copy->size];
	init_array();
	
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
	set = new ListItem *[size];
	init_array();
}

Set::Set(Item *i)
{
	present = 0;
	size = 1;
	ListItem::set_support(i->get_support());
	set = new ListItem *[size];
	init_array();
	add_item(i);
	// std::cout << "Initialized with single item" << std::endl;
}

void Set::init_array()
{
	int i;
	for (i = 0; i < size; i++)
	{
		set[i] = NULL;
	}
}

Set::~Set()
{
	// std::cout << "Deleting set" << std::endl << "Size = " << size << std::endl;
	
	delete [] set;
	
	// std::cout << "Deleted set" << std::endl;
}

void Set::increase_support(int add) { ListItem::increase_support(add);}

// Add a ListItem to the set,
// if an equivalent item is already present, increment its support value
bool Set::add_item(ListItem *item)
{
	bool added = false;
	
	if (present > 0)
	{
		int i;
		for (i = 0; i < present && !added; i++)
		{
			// std::cout << "I = " << i << std::endl;
			ListItem *curr = set[i];
			
			if (curr->equals(item))
			{
				if (item->get_support() > 1)
				{
					curr->increase_support(item->get_support());
				}
				else
				{
					curr->increment_support();
				}
				delete item;
				added = true;
			}
		}
		
		if (i == present && !added)
		{
			if (i < size)
			{
				ListItem *temp = item;
				set[i] = temp;
				added = true;
				
				if (present + 1 <= size)
				{
					present++;
				}
			}
			else
			{
				increase_size();
				add_item(item);
			}
		}
	}
	else
	{
		set[0] = item;
		added = true;
		present++;
	}
	
	return added;
}

void Set::print()
{
	std::cout << "{";
	if (present > 0 && present <= size)
	{
		int i;
		for (i = 0; i < present; i++)
		{
			if (Set *s = dynamic_cast<Set *>(set[i]))
			{
				s->print();
			}
			else if (Item *j = dynamic_cast<Item *>(set[i]))
			{
				std::cout << j->get_name();
			}
			
			if (i+1 < present)
			{
				std::cout << ",";
			}
		}
	}
	std::cout << "}:" << ListItem::get_support() << std::endl;
}

// if an item in the set has more support than max_support it is removed from the set
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
	
	int new_size = size - total;
	ListItem **new_set = new ListItem *[new_size];
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
	// std::cout << "Sorting Set" << std::endl;
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
	ListItem *temp = new Item(name);
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

int Set::get_support() { return ListItem::get_support(); }

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

void Set::increase_size()
{
	// std::cout << "Increasing the size of the set" << std::endl;
	int new_size = size * 2;
	ListItem **replacement = new ListItem *[new_size];
	
	int i;
	for (i = 0; i < new_size; i++)
		replacement[i] = NULL;

	if (present <= size)
	{
		int count = 0;
		for (i = 0; i < present; i++)
		{
			if (set[i] != NULL)
			{
				set[i]->print();
				ListItem *temp = set[i]->copy();
				replacement[count] = temp;
				count++;
			}
		}
		// std::cout << "Count = " << count << std::endl;
		present = count;
		delete [] set;
		set = replacement;
		size = new_size;
	}
	// std::cout << "Worked? " << (set[0] != NULL) << std::endl;
}

void Set::resize(int s)
{
	if (s == present)
	{
		size = s;
		copy();
		print();
	}
	else
	{
		ListItem **replace = new ListItem *[s];
		int count = 0;
		
		int i;
		for (i = 0; i < present; i++)
		{
			if (set[i] != NULL)
			{
				replace[count] = set[i]->copy();
			}
		}
		
		free(set);
		set = replace;
		present = count;
	}
}


ListItem **Set::copy(ListItem **old, int count)
{
	/*
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
	delete [] old;
	
	return new_set;
	*/
	
	return NULL;
}

ListItem *Set::copy()
{
	Set *copy = new Set();
	copy->present = present;
	copy->size = size;
	
	copy->set = new ListItem *[size];
	
	int i;
	for (i = 0; i < present; i++)
	{
		copy->set[i] = set[i]->copy();
	}
	
	return copy;
}

void Set::merge(Set *other)
{
	// std::cout << "Inside Set::merge" << std::endl;
	// print();
	// other->print();
	// std::cout << "Done printing stuff inside Set::merge" << std::endl;
	
	int i;
	for (i = 0; i < other->present; i++)
	{
		if (Set *s = dynamic_cast<Set *>(other->remove_item(i)))
		{
			bool add = add_item(s);
			std::cout << "Successful: " << add << std::endl;
		}
		
		// std::cout << "Adding " << i << std::endl;
		// ListItem *curr = other->remove_item(i);
		// std::cout << "Curr = " << std::endl;
	}
	
	resize(present); // this should be conditional
	// std::cout << "Size = " << size << ", present = " << present << std::endl;
	// std::cout << "Done merging, printing new set" << std::endl;
	// std::cout << "Present = " << present << std::endl;
	// print();
	// std::cout << "Successful print" << std::endl;
	// std::cout << "Exiting Set::merge" << std::endl;
}

int Set::get_size() { return size; }
int Set::get_present() { return present; }

ListItem *Set::remove_item(int index)
{
	ListItem *removed = NULL;
	
	if (set != NULL)
	{
		ListItem *at_index = set[index];
		if (at_index != NULL)
		{
			removed = (ListItem *) at_index;
			set[index] = NULL;
		}
	}
	
	return removed;
}
