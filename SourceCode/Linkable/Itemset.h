#ifndef ITEMSET_H
#define ITEMSET_H

#include "Item.h"
#include "ListItem.h"

class Itemset: public ListItem
{
	private:
		Item **set;
		int size;
		int present;
		int support;
		int partition(int first, int last);
		void qsort(int first, int last);
		void swap(int first, int second);
		void increase_support(int add);
	public:
		Itemset(int s);
		~Itemset();
		bool add_item(int item);
		bool add_item(Item *item);
		virtual void print();
		void remove_non_rare_items(int max_support);
		bool contains(int item);
		void sort();
		Item *get_item(int index);
		Itemset(Itemset *set);
		int get_support(int name);
		int *get_items();
};

#endif
