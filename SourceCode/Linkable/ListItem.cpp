#include "ListItem.h"

void ListItem::set_support(int s) { support = s; }
int ListItem::get_support() { return support; }
void ListItem::increment_support() { support++; }
void ListItem::increase_support(int add) { support += add; }
ListItem::~ListItem() { }
