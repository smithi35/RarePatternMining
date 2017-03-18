#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

#include "TransactionList.h"
#include "Transaction.h"
#include "Item.h"
#include "Itemset.h"
#include "RPTree.h"

using namespace std;

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
	
	tree->print();
}

void process(const char *inputfilename, const char *outputfilename, const int max_support)
{
	string contents = get_contents(inputfilename);
	int transactions = get_number_transactions(contents);
	cout << contents << endl << transactions << endl;
	
	TransactionList *array = get_transactions(contents, transactions);
	
	if (array != NULL)
	{
		Itemset *set = array->get_itemset();
		
		if (set != NULL)
		{
			set->print();
			set->remove_non_rare_items(max_support);
			set->print();
			set->sort();
			set->print();
			// set now works as the header table for the tree
			
			array->remove_non_rare_items(set);
			
			array->print();
			std::cout << "Printing Transaction List" << std::endl;
			array->sort(set);
			array->print();
			exit(-1);
			
			// build the tree
			RPTree *tree = new RPTree();
			
			if (tree != NULL)
			{
				build_tree(tree, array);
				tree->print();
				
				// recursively examine the tree
				tree->examine();
				
				delete(tree);
			}
			else
			{
				cout << "Failed to create tree" << endl;
			}
			delete(set);
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
