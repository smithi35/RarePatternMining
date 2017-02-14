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
	//delete [] set;
	
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

void Itemset::sort()
{
	qsort(0, present-1);
}

void Itemset::qsort(int first, int last)
{
	if (last - first > 1)
	{
		int pivot = partition(first, last);
		
		if (pivot - first == 1)
		{
			if (set[first]->get_support() > set[pivot]->get_support())
			{
				swap(first, last);
			}
		}
		else if (pivot - first > 1)
		{
			qsort(first, pivot);
		}
		
		if (last - (pivot+1) == 1)
		{
			if (set[pivot+1]->get_support() > set[last]->get_support())
			{
				swap(pivot+1, last);
			}
		}
		else if (last - (pivot+1) > 1)
		{
			qsort(pivot+1, last);
		}
	}
}

void Itemset::swap(int first, int second)
{
	Item *temp = set[first];
	set[first] = set[second];
	set[second] = temp;
	std::cout << "Successful swap" << std::endl;
}

int Itemset::partition(int first, int last)
{
	int pivot_value = set[first]->get_support();
	
	int i = first+1;
	int j = last;
	
	while (i < j)
	{
		while (i <= last and set[i]->get_support() <= pivot_value )
		{
			//print("i = " + str(i) + ", pivot_value = " + str(pivot_value) + ", array[i] = " + str(array[i]));
			i = i + 1;
		}
		while (j >= first and set[j]->get_support() > pivot_value )
		{
			// print("j = " + str(j) + ", pivot_value = " + str(pivot_value) + ", array[j] = " + str(array[j]));
			j = j - 1;
		}
		
		if (i < j)
		{
			swap(i, j);
		}
	}
	swap(j, first);
	
	return j;
}

Item *Itemset::get_item(int index) {return set[index];}
