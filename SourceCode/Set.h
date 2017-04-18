#ifndef SET_H
#define SET_H

#include "Item.h"
#include "ListItem.h"
#include <string>

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
		ListItem **copy(ListItem **old, int count);
	public:
		Set(int s);
		Set(Set *copy);
		Set(Item *i);
		Set();
		~Set();
		void print();
		void print_with_support();
		bool add_item(ListItem *item);
		void remove_non_rare_items(int max_support);
		bool contains(ListItem *item);
		void sort();
		ListItem *get_item(int index);
		ListItem *remove_item(int index);
		int get_support(int name);
		int get_support();
		int *get_items();
		void set_support(int s);
		bool equals(ListItem *other);
		ListItem *copy(ListItem *other);
		ListItem *copy();
		void add_sets(Set *other);
		void add_item_to_sets(Item *item);
		int get_size();
		int get_present();
		void resize(int s);
		std::string to_string();
		std::string to_string_with_support();
};

#endif
