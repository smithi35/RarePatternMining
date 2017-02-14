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
	
	return replacement;
}

void Transaction::sort(Itemset *set)
{
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
	if (last - first > 1)
	{
		int first_support = get_support(first, set);
		int last_support = get_support(last, set);
		
		int pivot = partition(first, last, set);
		int pivot_support = get_support(pivot, set);
		int pivot_right = get_support((pivot+1), set);
		
		if (pivot - first == 1)
		{
			if (first_support > pivot_support)
			{
				swap(first, last);
			}
		}
		else if (pivot - first > 1)
		{
			qsort(first, pivot, set);
		}
		
		if (last - (pivot+1) == 1)
		{
			if (pivot_right > last_support)
			{
				swap((pivot+1), last);
			}
		}
		else if (last - (pivot+1) > 1)
		{
			qsort(pivot+1, last, set);
		}
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
	int pivot_value = get_support(first, set);
	
	int i = first+1;
	int i_support = get_support(i, set);
	int j = last;
	int j_support = get_support(j, set);
	
	while (i < j)
	{
		while (i <= last and i_support <= pivot_value )
		{
			i = i + 1;
			i_support = get_support(i, set);
		}
		while (j >= first and j_support > pivot_value )
		{
			j = j - 1;
			j_support = get_support(j, set);
		}
		
		if (i < j)
		{
			swap(i, j);
		}
	}
	swap(j, first);
	
	return j;
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

