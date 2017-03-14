#include "TransactionList.h"

#include <cstdlib>

TransactionList::TransactionList()
{
	size = 5;
	list = (Transaction **)malloc(sizeof(Transaction *) * size);
	present = 0;
}

TransactionList::~TransactionList()
{
	int i;
	for (i = 0; i < present; i++)
	{
		delete(list[i]);
	}
	delete [] list;
}

void TransactionList::resize()
{
	int new_size = 3 * size;
	Transaction **new_list = (Transaction **)malloc(sizeof(Transaction *) * new_size);
	
	int i;
	for (i = 0; i < present; i++)
	{
		new_list[i] = new Transaction(list[i]);
		delete(list[i]);
	}
	delete [] list;
	
	list = new_list;
	size = new_size;
}

void add_transaction(Transaction *transaction)
{
	
}

Transaction *get_transaction(int index);
