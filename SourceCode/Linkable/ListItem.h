#ifndef LISTITEM_H
#define LISTITEM_H

#include <iostream>

class ListItem
{
	public: 
		virtual void print() = 0;
		virtual bool equals(ListItem *other) = 0;
};

#endif
