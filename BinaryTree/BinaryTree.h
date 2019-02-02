#pragma once

#include <string>

class BinTreeNode
{
public:
	BinTreeNode(int, int);
	~BinTreeNode();

	int Find(int);
	void Insert(int, int);
	void Remove(int);
	std::string InfixTraverse(); //

private:
	int key;
	int value;
	BinTreeNode *left, *right;
};