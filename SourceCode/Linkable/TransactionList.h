#ifndef TRANSACTIONLIST_H
#define TRANSACTIONLIST_H

#include "Transaction.h"
#include "Itemset.h"

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
		void sort(Itemset *set);
		void print();
		Itemset *get_itemset();
		void remove_non_rare_items(Itemset *set);
		int get_size();
};

#endif

