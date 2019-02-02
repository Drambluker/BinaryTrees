#pragma once

#include <string>;

class AVL_Node
{
public:
	int key;
	AVL_Node *left, *right;

	AVL_Node(int);
	~AVL_Node();

	static AVL_Node * Insert(AVL_Node **, int);
	static AVL_Node * Remove(AVL_Node **, int);
	int GetHeight() const;
	AVL_Node * FindMin();
	AVL_Node * FindMax();
	std::string InfixTraverse();
	std::string PrefixTraverse();
	std::string PostfixTraverse();

private:
	unsigned char height;

	int GetBalanceFactor() const;
	void FixHeight();
	static AVL_Node * RotateRight(AVL_Node **);
	static AVL_Node * RotateLeft(AVL_Node **);
	static AVL_Node * Balance(AVL_Node **);
	static AVL_Node * RemoveMin(AVL_Node **);
};