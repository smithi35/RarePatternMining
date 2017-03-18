#ifndef SET_H
#define SET_H

#include "Item.h"
#include "ListItem.h"

class Set: public ListItem
{
	private:
		ListItem **set;
		int size;
		int present;
		int partition(int first, int last);
		void qsort(int first, int last);
		void swap(int first, int second);
		void increase_support(int add);
		void resize();
		ListItem **copy(ListItem **old, int count);
	public:
		Set(int s);
		Set(Set *set);
		Set(Item *i);
		Set();
		~Set();
		void print();
		bool add_item(ListItem *item);
		void remove_non_rare_items(int max_support);
		bool contains(ListItem *item);
		void sort();
		ListItem *get_item(int index);
		int get_support(int name);
		int *get_items();
		void set_support(int s);
		bool equals(ListItem *other);
		ListItem *copy(ListItem *other);
		void merge(Set *other);
};

#endif