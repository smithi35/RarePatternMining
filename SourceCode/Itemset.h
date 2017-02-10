#ifndef ITEMSET_H
#define ITEMSET_H

#include "Item.h"

class Itemset
{
	private:
		Item **set;
		int size;
		int present;
	public:
		Itemset(int s);
		~Itemset();
		bool add_item(int item);
		void print();
		void remove_non_rare_items(int max_support);
		bool contains(int item);
};

#endif
