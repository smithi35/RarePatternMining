#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "ListItem.h"

#include "ListItem.h"

class Item: public ListItem
{
	private: 
		int name;
		int support;
	public:
		Item(int n);
		Item(Item *item);
		Item();
		Item(int n, int s);
		~Item();
		int get_support();
		void set_support(int s);
		void increment_support();
		void increase_support(int add);
		int get_name();
		bool equals(ListItem *other);
		void print();
};

#endif


