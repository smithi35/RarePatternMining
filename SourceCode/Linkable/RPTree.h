#ifndef RPTREE_H
#define RPTREE_H

#include "Node.h"
#include "Transaction.h"

class RPTree
{
	private: 
		Node *root;
	public:
		RPTree();
		~RPTree();
		void add_transaction(Transaction *transaction);
		Itemset **examine();
		void print();
};

#endif


