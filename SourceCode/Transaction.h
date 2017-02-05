#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction
{
	private: 
		int id;
		int length;
		int* items;
	public:
		Transaction(std::string contents);
		int get_id();
		int get_length();
		int *get_items();
		void print();
		~Transaction();
};

#endif
