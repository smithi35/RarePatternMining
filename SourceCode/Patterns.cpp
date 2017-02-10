#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

#include "Transaction.h"
#include "Item.h"
#include "Itemset.h"

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

// go through the transaction database to determine the support of each item, and remove any item
// with support greater than max_support
void remove_non_rare_items(Transaction **array, int transactions, const int max_support)
{
	int total_items = get_total_items(array, transactions);
	
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
	
	set->print();
}

void process(const char *inputfilename, const char *outputfilename)
{
	string contents = get_contents(inputfilename);
	int transactions = get_number_transactions(contents);
	cout << contents << endl << transactions << endl;
	
	// the next step will be to take that string and make a list of transactions out of it
	Transaction **array = get_transactions(contents, transactions);
	
	if (array != NULL)
	{
		const int max_support = 2;
		remove_non_rare_items(array, transactions, max_support);
		
		int i;
		for (i = 0; i < transactions; i++)
		{
			delete array[i];
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
