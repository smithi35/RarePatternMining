#ifndef RPTREE_H
#define RPTREE_H

#include "TreeNode.h"
#include "Transaction.h"

class RPTree
{
	private: 
		TreeNode **roots;
		int present;
		int size;
		void add_root(TreeNode *root);
	public:
		RPTree();
		~RPTree();
		void add_transaction(Transaction *transaction);
		Set *examine();
		int tree_size();
		void print();
};

#endif


