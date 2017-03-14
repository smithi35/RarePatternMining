#ifndef TRANSACTIONLIST_H
#define TRANSACTIONLIST_H

#include "Transaction.h"

class TransactionList
{
	private: 
		Transaction **list;
		int size;
		int present;
		void resize();
	public:
		TransactionList();
		~TransactionList();
		void add_transaction(Transaction *transaction);
		Transaction *get_transaction(int index);
};

#endif

