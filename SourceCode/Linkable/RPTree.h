#ifndef RPTREE_H
#define RPTREE_H

#include "TreeNode.h"
#include "Transaction.h"

class RPTree
{
	private: 
		TreeNode *root;
	public:
		RPTree();
		~RPTree();
		void add_transaction(Transaction *transaction);
		Set *examine();
		int size();
		void print();
};

#endif


