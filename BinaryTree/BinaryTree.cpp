#include "BinaryTree.h"
#include <cstdlib>

BinTreeNode::BinTreeNode(int key, int value)
{
	this->key = key;
	this->value = value;
}

BinTreeNode::~BinTreeNode()
{
	if (this)
	{
		delete this->left;
		this->left = NULL;
		delete this->right;
		this->right = NULL;
	}
}

int BinTreeNode::Find(int key)
{
	BinTreeNode *node = this;

	while (node)
	{
		if (key == node->key)
			return node->value;
		else if (key < node->key)
			node = node->left;
		else
			node = node->right;
	}
}

void BinTreeNode::Insert(int key, int value)
{
	BinTreeNode *node = this, *parent = NULL;

	while (node)
	{
		if (key == node->key)
		{
			node->value = value;
			return;
		}
		else
		{
			parent = node;

			if (key < node->key)
				node = node->left;
			else
				node = node->right;
		}
	}

	//if (parent == NULL)
	//{
	//	this->key = key;
	//	this->value = value;
	//}
	//else
	//{
	//	BinTreeNode *newNode = new BinTreeNode(key, value);

	//	if (key < parent->key)
	//		parent->left = newNode;
	//	else
	//		parent->right = newNode;
	//}

	if (parent)
	{
		BinTreeNode *newNode = new BinTreeNode(key, value);

		if (key < parent->key)
			parent->left = newNode;
		else
			parent->right = newNode;
	}
}

void BinTreeNode::Remove(int key)
{
	BinTreeNode *node = this, *parent = NULL;

	while (node)
		if (key == node->key)
			break;
		else
		{
			parent = node;

			if (key < node->key)
				node = node->left;
			else
				node = node->right;
		}

	if (node == NULL)
		return;

	if (node->right == NULL)
	{
		if (parent)
		{
			if (node == parent->left)
				parent->left = node->left;
			else
				parent->right = node->left;

			free(node);
		}
		else if (node->left)
		{
			BinTreeNode *rightMost = node->left;
			parent = NULL;

			while (rightMost->right)
			{
				parent = rightMost;
				rightMost = rightMost->right;
			}

			if (parent)
				parent->right = rightMost->left;
			else
				node->left = rightMost->left;

			node->key = rightMost->key;
			node->value = rightMost->value;
			free(rightMost);
		}
	}
	else
	{
		BinTreeNode *leftMost = node->right;
		parent = NULL;

		while (leftMost->left)
		{
			parent = leftMost;
			leftMost = leftMost->left;
		}

		if (parent)
			parent->left = leftMost->right;
		else
			node->right = leftMost->right;

		node->key = leftMost->key;
		node->value = leftMost->value;
		free(leftMost);
	}
}

std::string BinTreeNode::InfixTraverse()
{
	std::string temp = "";

	if (this)
	{
		temp += this->left->InfixTraverse();
		temp += std::to_string(this->key) + " ";
		temp += this->right->InfixTraverse();
	}

	return temp;
}