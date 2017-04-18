#ifndef LISTITEM_H
#define LISTITEM_H

#include <iostream>
#include <string>

class ListItem
{
	private:
		int support;
	public: 
		virtual ~ListItem();
		virtual void print() = 0;
		virtual bool equals(ListItem *other) = 0;
		virtual ListItem *copy() = 0;
		void set_support(int s);
		int get_support();
		void increment_support();
		void increase_support(int add);
		virtual std::string to_string() = 0;
};

#endif
