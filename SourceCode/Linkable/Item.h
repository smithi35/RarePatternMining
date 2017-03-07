#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item
{
	private: 
		int name;
		int support;
	public:
		Item(int n);
		Item(Item *item);
		Item();
		Item(int n, int s);
		int get_support();
		void set_support(int f);
		void increment_support();
		void increase_support(int add);
		int get_name();
		bool equal(int other);
		bool equal(Item *other);
		void print();
		~Item();
};

#endif


