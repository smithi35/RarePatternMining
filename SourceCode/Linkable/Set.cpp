#include "Set.h"
#include <iostream>
#include <cstdlib>
#include <sstream>

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
	size = 0;
	ListItem::set_support(0);
	set = NULL;
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
	int i;
	for (i = 0; i < present; i++)
	{
		if (set[i] != NULL)
		{
			delete set[i];
		}
	}
	
	delete [] set;
	size = 0;
	present = 0;
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
			ListItem *curr = set[i];
			
			// if the item being added is already present, update the support value of the present item
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
				added = true;
			}
		}
		
		// otherwise add the item to the set
		if (i == present && !added)
		{
			if (i < size)
			{
				set[i] = item->copy();
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
				added = true;
			}
		}
	}
	else
	{
		if (size > 0)
		{
			// first item
			set[0] = item->copy();
			added = true;
			present++;
		}
		else
		{
			// set needs to be initialized
			size = 5;
			set = new ListItem*[size];
			present = 1;
			set[0] = item->copy();
			added = true;
		}
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
				s->print_with_support();
				
				if (i+1 < present)
				{
					std::cout << "," << std::endl;
				}
			}
			else if (Item *j = dynamic_cast<Item *>(set[i]))
			{
				std::cout << j->get_name();
				
				if (i+1 < present)
				{
					std::cout << ",";
				}
			}
		}
	}
	
	std::cout << "}";
}

// if an item in the set has more support than max_support it is removed from the set
void Set::remove_non_rare_items(int max_support)
{
	int non_rares = 0;
	
	int i;
	for (i = 0; i < present; i++)
	{
		if (set[i]->get_support() > max_support)
		{
			non_rares++;
		}
	}
	
	int new_size = size - non_rares;
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
	delete temp;
	
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
				if (Item *temp_a = dynamic_cast<Item *>(set[i]))
				{
					bool present = false;
					int j;
					for (j = 0; j < p->present; j++)
					{
						if (Item *temp_b = dynamic_cast<Item *>(p->set[j]))
						{
							if (temp_a->equals(temp_b))
							{
								present = true;
							}
						}
					}
					
					equals = equals && present;
				}
				else if (Set *temp_a = dynamic_cast<Set *>(set[i]))
				{
					int j;
					for (j = 0; j < p->present; j++)
					{
						if (Set *temp_b = dynamic_cast<Set *>(p->set[j]))
						{
							if (temp_a->equals(temp_b))
							{
								equals = equals && temp_a->equals(temp_b);
							}
						}
					}
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
				replacement[count] = set[i];
				count++;
			}
		}
		
		present = count;
		delete [] set;
		set = replacement;
		size = new_size;
	}
}

void Set::resize(int s)
{
	if (s >= present)
	{
		ListItem **replace = new ListItem *[s];
		int count = 0;
		
		int i;
		for (i = 0; i < present; i++)
		{
			if (set[i] != NULL)
			{
				replace[count] = set[i];
				count++;
			}
		}
		delete [] set;
		set = replace;
		present = count;
		size = s;
	}
}

/*
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
	delete [] old;
	
	return new_set;
}
*/

// copies the contents of the set into a new ListItem
ListItem *Set::copy()
{
	Set *copy = new Set();
	copy->present = present;
	copy->size = size;
	copy->set = new ListItem *[copy->size];
	
	int i;
	for (i = 0; i < present; i++)
	{
		copy->set[i] = set[i]->copy();
	}
	copy->ListItem::set_support(ListItem::get_support());
	
	return copy;
}

void Set::add_sets(Set *other)
{
	int i;
	for (i = 0; i < other->present; i++)
	{
		if (Set *s = dynamic_cast<Set *>(other->get_item(i)))
		{
			bool add = add_item(s);
			
			if (!add)
			{
				std::cout << "Add item failed" << std::endl;
			}
		}
	}
	
	if (present != size)
		resize(present);
}

int Set::get_size() { return size; }
int Set::get_present() { return present; }

ListItem *Set::remove_item(int index)
{
	ListItem *removed = NULL;
	
	if (set != NULL && present > 0)
	{
		ListItem *at_index = set[index];
		if (at_index != NULL)
		{
			removed = at_index;
			set[index] = NULL;
		}
	}
	
	return removed;
}

// prints the set along with the support values of each item
void Set::print_with_support()
{
	std::cout << "{";
	if (present > 0 && present <= size)
	{
		int i;
		for (i = 0; i < present; i++)
		{
			if (Set *s = dynamic_cast<Set *>(set[i]))
			{
				s->print_with_support();
				
				if (i+1 < present)
				{
					std::cout << "," << std::endl;
				}
			}
			else if (Item *j = dynamic_cast<Item *>(set[i]))
			{
				std::cout << j->get_name();
				
				if (i+1 < present)
				{
					std::cout << ",";
				}
			}
		}
	}
	
	std::cout << "}:" << ListItem::get_support();
}

// adds item to each set in the set
void Set::add_item_to_sets(Item *item)
{
	int i;
	for (i = 0; i < present; i++)
	{
		if (Set *curr = dynamic_cast<Set *>(set[i]))
		{
			curr->add_item(item);
		}
	}
}

std::string Set::to_string()
{
	std::string output = "{";
	if (present > 0 && present <= size)
	{
		int i;
		for (i = 0; i < present; i++)
		{
			if (Set *s = dynamic_cast<Set *>(set[i]))
			{
				output = output + s->to_string_with_support();
				
				if (i+1 < present)
				{
					output = output + "," + "\n";
				}
			}
			else if (Item *j = dynamic_cast<Item *>(set[i]))
			{
				output = output + j->to_string();
				
				if (i+1 < present)
				{
					output = output + ",";
				}
			}
		}
	}
	
	output = output + "}";
	
	return output;
}

std::string Set::to_string_with_support()
{
	std::string output = "{";
	if (present > 0 && present <= size)
	{
		int i;
		for (i = 0; i < present; i++)
		{
			if (Item *j = dynamic_cast<Item *>(set[i]))
			{
				output = output + j->to_string();
				
				if (i+1 < present)
				{
					output = output + ",";
				}
			}
		}
	}
	
	output = output + "}: ";
	
	std::ostringstream stream;
	stream << ListItem::get_support();
	output = output + stream.str();
	
	return output;
}
