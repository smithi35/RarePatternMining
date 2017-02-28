#include <iostream>
#include <sstream>

#include "Transaction.h"
#include <cstdlib>
#include <limits.h>

using namespace std;

// given the line from the file, create transaction object
Transaction::Transaction(string contents)
{
	// contents should include at least 3 numbers
	stringstream ss(contents);
	ss >> id;
	
	if (id > 0)
	{
		ss >> length;
		if (length > 0)
		{
			items = (int *) malloc(sizeof(int) * length);
			int curr;
			int i = 0;
			while (ss >> curr)
			{
				items[i] = curr;
				i++;
			}
		}
	}	
}

Transaction::Transaction(int i, int l, int *list)
{
	id = i;
	length = l;
	items = (int *) malloc(sizeof(int) * length);
	
	for (i = 0; i < l; i++)
	{
		items[i] = list[i];
	}
}

Transaction *Transaction::copy()
{
	return new Transaction(id, length, items);
}

Transaction::~Transaction()
{
	free(items);
}

int Transaction::get_id() {	return id; }

int *Transaction::get_items() {	return items; }

int Transaction::get_length() {	return length; }

void Transaction::print()
{
	cout << "ID = " << id << ", Length = " << length << ", Items : ";
	
	int i;
	for (i = 0; i < length; i++)
	{
		cout << items[i] << " ";
	}
	cout << endl;
}

Transaction *Transaction::remove_non_rare_items(Itemset *set)
{
	Transaction *replacement = NULL;
	
	int remove = 0;
	
	int i;
	for (i = 0; i < length; i++)
	{
		if (!set->contains(items[i]))
		{
			items[i] = INT_MIN;
			remove++;
		}
	}
	std::cout << "Balls" << std::endl;
	if (remove > 0)
	{
		int *new_items = (int *)malloc(sizeof(int) * (length - remove));
		int next = 0;
		
		for (i = 0; i < length; i++)
		{
			if (items[i] > INT_MIN)
			{
				new_items[next] = items[i];
				next++;
			}
		}
		
		replacement = new Transaction(id, (length-remove), new_items);
		delete(this);
	}
	else
	{
		replacement = this;
	}
	
	return replacement;
}

void Transaction::sort(Itemset *set)
{
	std::cout << "Sorting Transaction" << std::endl;
	qsort(0, (length-1), set);
}

// returns the support of the item at items[index] according to set
int Transaction::get_support(int index, Itemset *set)
{
	int search = items[index];
	int support = 0;
	
	// search for the Item in set matching search
	int i;
	for (i = 0; i < length; i++)
	{
		if (set->get_item(i)->get_name() == search)
		{
			support = set->get_item(i)->get_support();
		}
	}
	
	return support;
}

// quick sorts the transaction item list
void Transaction::qsort(int first, int last, Itemset *set)
{	
	if (first < last)
	{
		int pivot = partition(first, last, set);
		std::cout << "Pivot = " << pivot << std::endl;
		
		qsort(first, pivot, set);
		qsort(pivot+1, last, set);
	}
}

// swaps the items at first and second in items array
void Transaction::swap(int first, int second)
{
	int temp = items[first];
	items[first] = items[second];
	items[second] = temp;
}

// partitions the items in the items array according to their support values
int Transaction::partition(int first, int last, Itemset *set)
{
	int random = rand() % last;
	std::cout << "Random = " << random << std::endl;
	int pivot_value = get_support(random, set);
	swap(first, random);
	
	int i;
	for (i = first+1; i < last; i++)
	{
		if (get_support(i, set) < pivot_value)
		{
			swap(i, first);
			first++;
		}
	}
	swap(first, random);
	
	return random;
}

/*
int main()
{
	string s = "1	3	1 3 4";
	Transaction *t = new Transaction(s);
	
	int *items = t->get_items();
	for (int i = 0; i < t->get_length(); i++)
	{
		cout << items[i] << " ";
	}
	cout << endl;
}
*/

