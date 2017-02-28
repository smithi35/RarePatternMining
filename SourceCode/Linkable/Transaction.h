#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include "Itemset.h"
#include "Item.h"

class Transaction
{
	private: 
		int id;
		int length;
		int* items;
		Transaction(int i, int l, int *list);
		void qsort(int first, int last, Itemset *set);
		void swap(int first, int second);
		int partition(int first, int last, Itemset *set);
		int get_support(int index, Itemset *set);
	public:
		Transaction(std::string contents);
		Transaction *copy();
		int get_id();
		int get_length();
		int *get_items();
		int get_item(int index);
		void print();
		Transaction *remove_non_rare_items(Itemset *set);
		~Transaction();
		void sort(Itemset *set);
};

#endif
