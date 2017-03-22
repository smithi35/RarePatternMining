#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

#include "TransactionList.h"
#include "Transaction.h"
#include "Item.h"
#include "Set.h"
#include "RPTree.h"

using namespace std;

bool do_a_test()
{
	bool success = false;
	
	Set *a = new Set(1);
	Set *b = new Set(1);
	
	Item *i = new Item(1, 1);
	Item *j = new Item(2, 2);
	
	a->add_item(i);
	b->add_item(j);
	
	a->merge(b);
	cout << "Support = " << a->get_support() << endl;
	a->print();
	
	Set *comp = new Set(2);
	comp->add_item(i->copy());
	comp->add_item(j->copy());
	
	if (a->equals(comp))
		success = true;
	
	return success;
}

string get_contents(const char* filename)
{
	ifstream stream;
	stream.open(filename);
	stream.seekg(0, ios::end);
	
	int length = stream.tellg();
	stream.seekg(0, ios::beg);
	
	char buffer[length+1] = {0};
	
	if (buffer != NULL)
	{
		stream.read(buffer, length);
	}
	else 
	{
		cout << "Not enough memory for input file" << endl;
	}
	stream.close();
	
	return buffer;
}

int get_number_transactions(string contents)
{
	stringstream ss(contents);
	int count;
	ss >> count;
	
	return count;
}

TransactionList *get_transactions(string contents, int transactions)
{
	TransactionList *list = new TransactionList(transactions);
	istringstream f(contents);
	string line = "";
	getline(f, line);
	int i = 0;
	
	while (getline(f, line) && i < transactions)
	{
		list->add_transaction(new Transaction(line));
		i++;
	}
	
	return list;
}

void build_tree(RPTree *tree, TransactionList *list)
{
	cout << "Building RPTree" << endl;
	int i;
	
	for (i = 0; i < list->get_size(); i++)
	{
		cout << "Adding Transaction: " << i << endl;
		tree->add_transaction(list->get_transaction(i));
	}
}

void process(const char *inputfilename, const char *outputfilename, const int max_support)
{
	string contents = get_contents(inputfilename);
	int transactions = get_number_transactions(contents);
	cout << contents << endl << transactions << endl;
	
	TransactionList *array = get_transactions(contents, transactions);
	
	if (array != NULL)
	{
		Set *header = array->get_itemset();
		
		if (header != NULL)
		{
			header->print();
			header->remove_non_rare_items(max_support);
			header->print();
			header->sort();
			header->print();
			
			array->remove_non_rare_items(header);
			
			array->print();
			std::cout << "Printing Transaction List" << std::endl;
			array->sort(header);
			array->print();
			
			// build the tree
			RPTree *tree = new RPTree();
			
			if (tree != NULL)
			{
				build_tree(tree, array);
				cout << "The tree has " << tree->size() << " nodes in it" << endl;
				
				// recursively examine the tree
				Set *rare_patterns = tree->examine();
				std::cout << "There are " << rare_patterns->get_present() << " patterns" << std::endl;
				
				if (rare_patterns != NULL)
				{
					cout << "Printing Rare Patterns" << endl;
					rare_patterns->print();
					delete rare_patterns;
				}
				else
				{
					cout << "Failed to create rare patterns" << endl;
				}
				delete(tree);
			}
			else
			{
				cout << "Failed to create tree" << endl;
			}
			delete(header);
		}
		else
		{
			cout << "Failed to create header table" << endl;
		}
		delete(array);
	}
	else
	{
		cout << "Not enough memory for Transaction array" << endl;
	}
}

int main()
{	
	string input = "PreciseDB.txt";
	const char *inputfilename = input.c_str();
	string output = "first_trial.txt";
	const char *outputfilename = output.c_str();
	// process(inputfilename, outputfilename, 2);
	
	process(inputfilename, outputfilename, 3);
	
	return 0;
}
