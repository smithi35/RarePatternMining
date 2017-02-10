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
		int get_support();
		void set_support(int f);
		void increment_support();
		int get_name();
		bool equal(int other);
		void print();
		~Item();
};

#endif


