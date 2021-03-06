#include "IntAtom.h"
#include <iostream>
#include <sstream>

IntAtom::IntAtom(int atom)
{
	ListItem::set_support(atom);
}

IntAtom::~IntAtom() {}

int IntAtom::get_support() { return ListItem::get_support(); }

void IntAtom::print() { std::cout << ListItem::get_support() << std::endl; }

bool IntAtom::equals(ListItem *other)
{
	return ListItem::get_support() == other->ListItem::get_support();
}

ListItem *IntAtom::copy()
{
	ListItem *copy = (ListItem *) new IntAtom(ListItem::get_support());
	return copy;
}

std::string IntAtom::to_string()
{
	int q = ListItem::get_support();
	std::ostringstream ss;
	ss << q;
	return ss.str();
}
