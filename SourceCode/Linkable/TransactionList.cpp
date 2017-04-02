#include "TransactionList.h"

#include <cstdlib>
#include <iostream>

using namespace std;

TransactionList::TransactionList(int s)
{
	size = s;
	list = new Transaction*[size];
	present = 0;
}

TransactionList::~TransactionList()
{
	int i;
	for (i = 0; i < present; i++)
	{
		delete list[i];
	}
	delete [] list;
}

void TransactionList::resize()
{
	int new_size = 2 * size;
	Transaction **new_list = new Transaction *[new_size];
	
	int i;
	for (i = 0; i < present; i++)
	{
		new_list[i] = new Transaction(list[i]);
	}
	delete [] list;
	
	list = new_list;
	size = new_size;
}

void TransactionList::add_transaction(Transaction *transaction)
{
	if (present + 1 >= size)
	{
		resize();
	}
	
	// add the transaction to the list
	Transaction *copy = transaction->copy();
	list[present] = copy;
	present++;
}

Transaction *TransactionList::get_transaction(int index)
{
	Transaction *found = NULL;
	
	if (index < present)
	{
		found = list[index];
	}
	
	return found;
}

void TransactionList::sort(Set *set)
{
	int i;
	for (i = 0; i < present; i++)
	{
		list[i]->sort(set);
	}
	
	quicksort(0, present-1);
}

// quick sorts the Transaction list
void TransactionList::quicksort(int first, int last)
{
	int range = last - first;
	if (range >= 1)
	{
		int pivot = partition(first, last);
		quicksort(first, pivot);
		quicksort(pivot+1, last);
	}
}

// swaps the items at first and second in list
void TransactionList::swap(int first, int second)
{
	Transaction *temp = list[first];
	list[first] = list[second];
	list[second] = temp;
}

// moves the longest transactions to the front of the list
int TransactionList::partition(int first, int last)
{
	int boundary = first;
	
	int range = last - first;
	int random = rand() % range;
	random += first;
	int pivot = list[random]->get_length();
	
	swap(boundary, random);
	
	int i;
	for (i = first+1; i <= last; i++)
	{
		if (list[i]->get_length() >= pivot)
		{
			boundary++;
			swap(boundary, i);
		}
	}
	swap(boundary, first);
	
	return random;
}

void TransactionList::print()
{
	int i;
	for (i = 0; i < present; i++)
	{
		list[i]->print();
	}
}

Set *TransactionList::get_itemset()
{
	int total = 0;
	
	int i;
	for (i = 0; i < present; i++)
	{
		total+=list[i]->get_length();
	}
	
	Set *set = new Set(total);
	
	if (set != NULL)
	{
		// first get the support of all items in the transaction database
		for (i = 0; i < present; i++)
		{
			int *items = list[i]->get_items();
			int length = list[i]->get_length();
			
			int j;
			for (j = 0; j < length; j++)
			{
				int curr = items[j];
				Item *item = new Item(curr);
				
				set->add_item(item);
			}
		}
		
		set->resize(set->get_present());
	}
	
	return set;
}

void TransactionList::remove_non_rare_items(Set *set)
{
	int revised = 0;
	int i;
	for (i = 0; i < present; i++)
	{
		Transaction *temp = list[i]->remove_non_rare_items(set);
		
		if (temp != NULL)
		{
			revised++;
		}
		list[i] = temp;
	}
	
	Transaction** replacement = new Transaction*[revised];
	
	int index = 0;
	
	for (i = 0; i < present; i++)
	{
		if (list[i] != NULL)
		{
			replacement[index] = new Transaction(list[i]);
			index++;
		}
	}
	
	for (i = 0; i < present; i++)
	{
		delete(list[i]);
	}
	delete [] list;
	
	list = replacement;
	present = revised;
	size = revised;
}

int TransactionList::get_size() { return present; }
