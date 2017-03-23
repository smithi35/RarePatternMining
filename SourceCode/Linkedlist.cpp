#include "Linkedlist.h"
#include <iostream>

#include "IntAtom.h"

/*
class Linkedlist
{
	private:
		ListNode *top;
		ListNode *bottom;
		int length;
	public:
		Linkedlist();
		~Linkedlist();
		bool add(ListItem *item);
		ListItem *get(int index);
		ListItem *remove(int index);
		ListItem *remove_top();
}
*/

Linkedlist::Linkedlist()
{
	top = NULL;
	bottom = NULL;
	length = 0;
}

Linkedlist::~Linkedlist()
{
	ListNode *curr = top;
	
	while (curr != NULL)
	{
		ListNode *next = curr->get_next();
		delete curr;
		curr = next;
	}
}

// Add a new node containing item to the end of the linkedlist
bool Linkedlist::add(ListItem *item)
{
	bool add = false;
	
	if (length == 0)
	{
		top = new ListNode(item);
		bottom = top;
		length++;
	}
	else
	{
		ListNode *insert = new ListNode(item);
		bottom->set_next(insert);
		bottom = insert;
		length++;
	}
	
	return add;
}

ListItem *Linkedlist::get_item(int index)
{
	ListItem *output = NULL;
	
	if (index < length)
	{
		ListNode *curr = top;
		bool stop = false;
		
		int i;
		for (i = 0; i < length && !stop; i++)
		{
			if (index == i)
			{
				output = curr->get_item();
				stop = true;
			}
			
			curr = curr->get_next();
		}
	}
	
	return output;
}

ListNode *Linkedlist::get_node(int index)
{
	ListNode *output = NULL;
	
	if (index < length)
	{
		ListNode *curr = top;
		bool stop = false;
		
		int i;
		for (i = 0; i < length && !stop; i++)
		{
			if (index == i)
			{
				output = curr;
				stop = true;
			}
			
			curr = curr->get_next();
		}
	}
	
	return output;
}

ListItem *Linkedlist::remove(int index)
{
	std::cout << "Index = " << index << std::endl;
	ListItem *output = NULL;
	
	if (index < length)
	{
		ListNode *curr = top;
		ListNode *prev = top;
		ListNode *remove = NULL;
		
		bool stop = false;
		int i;
		for (i = 0; i < length && !stop; i++)
		{
			std::cout << "I = " << i << std::endl;
			
			if (i == index)
			{
				remove = curr;
				prev->set_next(curr->get_next());
				stop = true;
			}
			
			prev = curr;
			curr = curr->get_next();
			
			std::cout << "Curr == NULL = " << (curr == NULL) << std::endl;
		}
		
		if (remove != NULL)
		{
			length--;
			output = remove->get_item()->copy();
			delete remove;
		}
	}
	
	return output;
}

ListItem *Linkedlist::remove_top()
{
	ListNode *remove = top;
	ListItem *top_item = remove->get_item()->copy();
	
	top = top->get_next();
	delete remove;
	length--;
	
	return top_item;
}

void Linkedlist::print()
{
	ListNode *curr = top;
	
	while (curr != NULL)
	{
		curr->get_item()->print();
		curr = curr->get_next();
	}
}

int Linkedlist::get_length() { return length; }

bool Linkedlist::equals(ListItem *other)
{
	bool equal = true;
	
	if (Linkedlist *o = dynamic_cast<Linkedlist *>(other))
	{
		if (o->length == length)
		{
			ListNode *curr1 = top;
			ListNode *curr2 = o->top;
			
			int i;
			for (i = 0; i < length; i++)
			{
				if (!curr1->get_item()->equals(curr2->get_item()))
				{
					equal = false;
				}
			}
		}
	}
	
	return equal;
}

ListItem *Linkedlist::copy()
{
	Linkedlist *copy = new Linkedlist();
	
	int i;
	for (i = 0; i < length; i++)
	{
		ListItem *item = get_item(i)->copy();
		copy->add(item);
	}
	
	return copy;
}

/*
int main()
{
	Linkedlist *list = new Linkedlist();
	
	int i;
	for (i = 0; i < 10; i++)
	{
		IntAtom *curr = new IntAtom(i);
		list->add(curr);
	}
	
	std::cout << "Print list of length:" << list->get_length() << std::endl;
	list->print();
	
	IntAtom *out = (IntAtom *) list->remove_top();
	out->print();
	
	std::cout << "Print list of length:" << list->get_length() << std::endl;
	list->print();
	
	out = (IntAtom *) list->remove(5);
	out->print();
	
	std::cout << "Print list of length:" << list->get_length() << std::endl;
	list->print();
	
	Linkedlist *copy = (Linkedlist *) list->copy();
	
	std::cout << "First list" << std::endl;
	list->print();
	std::cout << "Second list" << std::endl;
	copy->print();
	
	std::cout << "Equal?" << list->equals(copy) << std::endl;
	
	delete list;
}
*/
