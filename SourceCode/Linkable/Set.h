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
		void init_array();
		int partition(int first, int last);
		void qsort(int first, int last);
		void swap(int first, int second);
		void increase_support(int add);
		void increase_size();
		void resize(int s);
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
		ListItem *remove_item(int index);
		int get_support(int name);
		int *get_items();
		void set_support(int s);
		bool equals(ListItem *other);
		ListItem *copy(ListItem *other);
		ListItem *copy();
		void merge(Set *other);
		int get_size();
		int get_present();
};

#endif
