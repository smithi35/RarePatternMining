#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include "Set.h"
#include "Item.h"

class Transaction
{
	private: 
		int id;
		int length;
		int* items;
		Transaction(int i, int l, int *list);
		void qsort(int first, int last, Set *set);
		void swap(int first, int second);
		int partition(int first, int last, Set *set);
	public:
		Transaction(std::string contents);
		Transaction(Transaction *copy);
		Transaction *copy();
		int get_id();
		int get_length();
		int *get_items();
		int get_item(int index);
		void print();
		Transaction *remove_non_rare_items(Set *set);
		~Transaction();
		void sort(Set *set);
};

#endif
