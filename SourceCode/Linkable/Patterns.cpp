#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

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

Transaction **get_transactions(string contents, int transactions)
{
	Transaction **array = (Transaction **)malloc(sizeof(Transaction*) * transactions);
	istringstream f(contents);
	string line = "";
	getline(f, line);
	int i = 0;
	
	while (getline(f, line) && i < transactions)
	{
		// cout << line << endl;
		array[i] = new Transaction(line);
		i++;
	}
	
	return array;
}

int get_total_items(Transaction **array, int transactions)
{
	int total = 0;
	
	int i;
	for (i = 0; i < transactions; i++)
	{
		Transaction *curr = array[i];
		total+=curr->get_length();
	}
	
	return total;
}

Itemset *get_support_values(Transaction **array, int transactions, int total_items)
{
	Itemset *set = new Itemset(total_items);
	
	// first get the support of all items in the transaction database
	int i;
	for (i = 0; i < transactions; i++)
	{
		int *items = array[i]->get_items();
		int length = array[i]->get_length();
		
		int j;
		for (j = 0; j < length; j++)
		{
			int curr = items[j];
			
			bool add = set->add_item(curr);
			
			if (!add) { cout << "Something went wrong with adding the item " << curr << " from Transaction number " << array[i]->get_id() << endl;}
		}
	}
	
	return set;
}

int revise_transactions_number(Transaction **array, int transactions, const int max_support, Itemset *set)
{
	int count = 0;
	
	int i;
	for (i = 0; i < transactions; i++)
	{
		array[i] = array[i]->remove_non_rare_items(set);
		array[i]->print();
		
		if (array[i]->get_length() > 0)
		{
			count++;
		}
	}
	
	return count;
}

Transaction **remove_non_rare_items(Transaction **array, int transactions, const int max_support, Itemset *set, int count, Transaction **replacement)
{
	int next = 0;
	int i;
	for (i = 0; i < transactions; i++)
	{
		if (array[i]->get_length() > 0)
		{
			replacement[next] = array[i]->copy();
			next++;
		}
	}
	
	return replacement;
}

void delete_transaction_array(Transaction **array, int length)
{
	int i;
	for (i = 0; i < length; i++)
	{
		delete(array[i]);
	}
	//sdelete [] array;
}

// go through transaction array and sort so that items with more support are first in each transaction
void sort_transactions(Transaction **array, int size, Itemset *set)
{
	int i;
	for (i = 0; i < size; i++)
	{
		cout << "Pre-sort" << endl;
		array[i]->print();
		array[i]->sort(set);
		cout << "Post-sort" << endl;
		array[i]->print();
	}
}

void build_tree(RPTree *tree, Transaction **array, int size)
{
	cout << "Building RPTree" << endl;
	int i;
	
	for (i = 0; i < size; i++)
	{
		tree->add_transaction(array[i]);
	}
	
	tree->print();
}

void process(const char *inputfilename, const char *outputfilename)
{
	string contents = get_contents(inputfilename);
	int transactions = get_number_transactions(contents);
	cout << contents << endl << transactions << endl;
	
	Transaction **array = get_transactions(contents, transactions);
	
	if (array != NULL)
	{
		const int max_support = 2;
		
		int total_items = get_total_items(array, transactions);
		Itemset *set = get_support_values(array, transactions, total_items);
		
		set->print();
		set->remove_non_rare_items(max_support);
		set->sort();
		set->print();
		
		// set now doubles as the header table for the tree
		
		int revised = revise_transactions_number(array, transactions, max_support, set);
		cout << "Only need " << revised << " transactions. " << endl;
		Transaction **replacement = (Transaction **)malloc(sizeof(Transaction *) * revised);
		
		if (replacement != NULL)
		{
			replacement = remove_non_rare_items(array, transactions, max_support, set, revised, replacement);
			sort_transactions(replacement, revised, set);
			
			// build the tree
			RPTree *tree = new RPTree();
			build_tree(tree, replacement, revised);
			
			// recursively examine the tree
			
			delete_transaction_array(array, transactions);
			delete_transaction_array(replacement, revised);
		} else {
			cout << "Not enough memory for replacement transaction array" << endl;
		}
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
	process(inputfilename, outputfilename);
	
	return 0;
}
