#ifndef RPTREE_H
#define RPTREE_H

#include "TreeNode.h"
#include "Transaction.h"

class RPTree
{
	private: 
		TreeNode **roots;
		int count;
	public:
		RPTree();
		~RPTree();
		void add_transaction(Transaction *transaction);
		Set *examine();
		int size();
		void print();
		void add_root(TreeNode *root);
};

#endif


