#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

#include "Transaction.h"

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

void process(const char *inputfilename, const char *outputfilename)
{
	string contents = get_contents(inputfilename);
	int transactions = get_number_transactions(contents);
	cout << contents << endl << transactions << endl;
	
	// the next step will be to take that string and make a list of transactions out of it
	Transaction **array = get_transactions(contents, transactions);
	
	if (array != NULL)
	{
		int i;
		for (i = 0; i < transactions; i++)
		{
			array[i]->print();
		}
		
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
