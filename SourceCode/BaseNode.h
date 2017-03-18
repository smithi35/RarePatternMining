#ifndef BASENODE_H
#define BASENODE_H

#include "ListItem.h"

class BaseNode
{
	private:
		ListItem *item;
	protected:
		ListItem *get_item();
		void set_item(ListItem *i);
		void delete_item();
}