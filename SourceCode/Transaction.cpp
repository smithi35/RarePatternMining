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
			items = new int[length];
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
	items = list;
}

Transaction *Transaction::copy()
{
	return new Transaction(id, length, items);
}

Transaction::~Transaction()
{
	delete[] items;
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

