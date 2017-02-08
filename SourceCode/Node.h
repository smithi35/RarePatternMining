#ifndef NODE_H
#define NODE_H


class Node
{
	private: 
		int name;
		int quantity;
		Node **children;
		int children_number;
	public:
		Node(int n, int q);
		~Node();
};

#endif

