#ifndef TRANSACTIONLIST_H
#define TRANSACTIONLIST_H

#include "Transaction.h"
#include "Set.h"

class TransactionList
{
	private: 
		Transaction **list;
		int size;
		int present;
		void resize();
		void resize(int s);
		void quicksort(int start, int end);
		int partition(int start, int end);
		void swap(int first, int second);
	public:
		TransactionList(int s);
		~TransactionList();
		void add_transaction(Transaction *transaction);
		Transaction *get_transaction(int index);
		void sort(Set *set);
		void print();
		Set *get_itemset();
		void remove_non_rare_items(Set *set);
		int get_size();
};

#endif

