#ifndef ITEMSET_H
#define ITEMSET_H

#include "Item.h"
#include "ListItem.h"

class Itemset: public ListItem
{
	private:
		ListItem **set;
		int size;
		int present;
		int support;
		int partition(int first, int last);
		void qsort(int first, int last);
		void swap(int first, int second);
		void increase_support(int add);
	public:
		Itemset(int s);
		Itemset(Itemset *set);
		~Itemset();
		bool add_item(ListItem *item);
		void print();
		void remove_non_rare_items(int max_support);
		bool contains(int item);
		void sort();
		ListItem *get_item(int index);
		int get_support(int name);
		void set_support(int s);
		bool equals(ListItem *other);
};

#endif
