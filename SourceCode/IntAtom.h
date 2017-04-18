#ifndef INTATOM_H
#define INTATOM_H

#include "ListItem.h"

class IntAtom: public ListItem
{
	public:
		IntAtom(int atom);
		~IntAtom();
		int get_support();
		void print();
		bool equals(ListItem *other);
		ListItem *copy();
		std::string to_string();
};

#endif
