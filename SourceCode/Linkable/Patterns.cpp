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
	
	a->add_sets(b);
	cout << "Support = " << a->get_support() << endl;
	a->print();
	
	Set *comp = new Set(2);
	comp->add_item(i->copy());
	comp->add_item(j->copy());
	
	if (a->equals(comp))
		success = true;
	
	return success;
}

string get_trial()
{
	static int trial_number = 1;
	ostringstream stream;
	stream << trial_number;
	string trial_string = stream.str();
	string outputfile = "Output/" + trial_string + "trial.txt";
	
	trial_number++;
	return outputfile;
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

void get_transactions(string contents, int transactions, TransactionList *list)
{
	istringstream f(contents);
	string line = "";
	getline(f, line);
	int i = 0;
	
	while (getline(f, line) && i < transactions)
	{
		Transaction *t = new Transaction(line);
		list->add_transaction(t);
		i++;
	}
}

void build_tree(RPTree *tree, TransactionList *list)
{
	//cout << "Building RPTree" << endl;
	int i;
	
	for (i = 0; i < list->get_size(); i++)
	{
		Transaction *add = list->get_transaction(i);
		//cout << "Adding Transaction: " << add->get_id() << endl;
		tree->add_transaction(add);
	}
}

void output_to_file(const char *outputfilename, Set *rare_patterns, int rare_patterns_number, const int max_support)
{
	ofstream write(outputfilename);
	write << "There are " << rare_patterns_number << 
		" patterns in this database with a support of " << max_support << " or less " << endl;
	write << rare_patterns->to_string();
	write.close();
}

void process(const char *inputfilename, const char *outputfilename, const int max_support)
{
	cout << "Max_support is " << max_support << endl;
	string contents = get_contents(inputfilename);
	int transactions = get_number_transactions(contents);
	cout << "Read in file: " << inputfilename << std::endl;
	
	TransactionList *array = new TransactionList(transactions);
	
	if (array != NULL)
	{
		get_transactions(contents, transactions, array);
		cout << "Retrieved " << transactions << " transactions" << endl;
		Set *header = array->get_itemset();
		cout << "There are " << header->get_present() << " items in the header table" << endl;
		
		if (header != NULL)
		{
			//cout << "Initial header table: " << std::endl;
			//header->print();
			//cout << endl;
			header->remove_non_rare_items(max_support);
			cout << "Removed non-rare items from header table" << endl;
			cout << header->get_present() << " items remain." << endl;
			//cout << "Only rare items" << std::endl;
			//header->print();
			//cout << endl;
			header->sort();
			cout << "Sorted header table" << endl;
			//cout << "Sorted header table" << endl;
			//header->print();
			//cout << endl;
			
			array->remove_non_rare_items(header);
			
			cout << "Removed non-rare items from transaction list" << endl;
			cout << array->get_size() << " transactions remain" << endl;
			
			//array->print();
			//std::cout << "Printing Transaction List" << std::endl;
			array->sort(header);
			//array->print();
			
			cout << "Sorted transaction list" << endl;
			
			// build the tree
			RPTree *tree = new RPTree();
			
			if (tree != NULL)
			{
				build_tree(tree, array);
				cout << "Built RPTree of size " << tree->tree_size() << endl;
				//cout << "The tree has " << tree->tree_size() << " nodes in it" << endl;
				//tree->print();
				
				// recursively examine the tree
				Set *rare_patterns = tree->examine();
				int rare_patterns_number = rare_patterns->get_present();
				cout << "Mined " << rare_patterns_number << " rare patterns" << endl;
				
				if (rare_patterns != NULL)
				{
					//cout << "Printing Rare Patterns" << endl;
					//rare_patterns->print();
					output_to_file(outputfilename, rare_patterns, rare_patterns_number, max_support);
					cout << "Printed rare patterns to: " << outputfilename << endl;
					//cout << endl;
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
	}
	else
	{
		cout << "Not enough memory for Transaction array" << endl;
	}
	delete array;
	
	cout << endl;
	cout << endl;
}

int main()
{
	string input, output;
	const char *inputfilename, *outputfilename;
	
	inputfilename = "Input/Subset.txt";
	output = get_trial();
	outputfilename = output.c_str();
	process(inputfilename, outputfilename, 4);
	
	inputfilename = "Input/Subset.txt";
	output = get_trial();
	outputfilename = output.c_str();
	process(inputfilename, outputfilename, 3);
	
	inputfilename = "Input/Subset.txt";
	output = get_trial();
	outputfilename = output.c_str();
	process(inputfilename, outputfilename, 5);
	
	inputfilename = "Input/Subset.txt";
	output = get_trial();
	outputfilename = output.c_str();
	process(inputfilename, outputfilename, 6);
	
	/*
	inputfilename = "Input/PreciseDB.txt";
	output = get_trial();
	outputfilename = output.c_str();
	process(inputfilename, outputfilename, 2);

	inputfilename = "Input/PreciseDB.txt";
	output = get_trial();
	outputfilename = output.c_str();
	process(inputfilename, outputfilename, 3);
	
	inputfilename = "Input/1k5L.txt";
	output = get_trial();
	outputfilename = output.c_str();
	process(inputfilename, outputfilename, 5);
	
	inputfilename = "Input/1k5L.txt";
	output = get_trial();
	outputfilename = output.c_str();
	process(inputfilename, outputfilename, 10);
	
	inputfilename = "Input/10k5L.txt";
	output = get_trial();
	outputfilename = output.c_str();
	process(inputfilename, outputfilename, 5);
	*/
	
	return 0;
}
