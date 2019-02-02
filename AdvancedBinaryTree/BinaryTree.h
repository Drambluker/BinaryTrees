#pragma once

#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>

template<typename T, size_t size>
class BinTreeNode
{
	template<typename T, size_t size> friend std::ifstream & operator>>(std::ifstream &, BinTreeNode<T, size> &);
	template<typename T, size_t size> friend std::ofstream & operator<<(std::ofstream &, const BinTreeNode<T, size> &);

public:
	class ItemDoesNotExistException : public std::exception {};

	BinTreeNode();
	~BinTreeNode();

	void Insert(const T &);
	T Find(const T &);
	void Remove(const T &);
	std::string InfixTraverse();
	std::string PrefixTraverse();
	std::string PostfixTraverse();

private:
	T *data[size];
	BinTreeNode *left, *right;

	T ** GetArray(const T &);
	void Balance();
};

template<typename T, size_t size>
std::ifstream & operator>>(std::ifstream &in, BinTreeNode<T, size> &operand)
{
	size_t length;
	in >> length;
	T temp;

	for (size_t i = 0; i < size; i++)
	{
		if (i < length)
		{
			in >> temp;
			delete operand.data[i];
			operand.data[i] = new T{ temp };
		}
		else
		{
			delete operand.data[i];
			operand.data[i] = NULL;
		}
	}

	if (length > 0)
	{
		delete operand.left;
		operand.left = new BinTreeNode<T, size>;
		in >> *operand.left;

		if (operand.left->data[0] == NULL)
		{
			delete operand.left;
			operand.left = NULL;
		}

		delete operand.right;
		operand.right = new BinTreeNode<T, size>;
		in >> *operand.right;

		if (operand.right->data[0] == NULL)
		{
			delete operand.right;
			operand.right = NULL;
		}
	}

	return in;
}

template<typename T, size_t size>
std::ofstream & operator<<(std::ofstream &out, const BinTreeNode<T, size> &operand)
{
	size_t length;

	for (length = 0; length < size && &operand != NULL && operand.data[length] != NULL; length++);

	out << length << std::endl;

	for (size_t i = 0; i < length; i++)
		out << *operand.data[i] << std::endl;

	if (length > 0)
	{
		out << *operand.left;
		out << *operand.right;
	}
	else
		return out;
}

template<typename T, size_t size>
BinTreeNode<T, size>::BinTreeNode()
{
	for (size_t i = 0; i < size; i++)
		data[i] = NULL;

	left = right = NULL;
}

template<typename T, size_t size>
BinTreeNode<T, size>::~BinTreeNode()
{
	if (this)
	{
		for (size_t i = 0; i < size; i++)
		{
			delete data[i];
			data[i] = NULL;
		}

		delete left;
		left = NULL;
		delete right;
		right = NULL;
	}
}

template<typename T, size_t size>
void BinTreeNode<T, size>::Insert(const T &value)
{
	BinTreeNode *x = this, *y = NULL;

	while (x && x->data[0])
	{
		if (x->data[size - 1] == NULL || value > *x->data[0] && value < *x->data[size - 1])
		{
			size_t index;
			T *temp = NULL;

			for (index = 0; index < size && x->data[index] && value > *x->data[index]; index++);

			if (x->data[size - 1])
				temp = x->data[size - 1];

			for (size_t i = size - 2; i > index; i--)
				x->data[i + 1] = x->data[i];

			if (index + 1 < size)
				x->data[index + 1] = x->data[index];

			x->data[index] = new T{ value };

			if (temp)
			{
				if (!x->right)
					x->right = new BinTreeNode<T, size>;

				x->right->Insert(*temp);
				delete temp;
			}

			return;
		}
		else
		{
			y = x;

			if (value < *x->data[0])
				x = x->left;
			else
				x = x->right;
		}
	}

	if (y == NULL)
		this->data[0] = new T{ value };
	else
	{
		BinTreeNode *newNode = new BinTreeNode();
		newNode->data[0] = new T{ value };

		if (value < *y->data[0])
			y->left = newNode;
		else
			y->right = newNode;
	}
}

template<typename T, size_t size>
T BinTreeNode<T, size>::Find(const T &key)
{
	T **dataArray = GetArray(key);

	if (dataArray)
		for (size_t i = 0; i < size, dataArray[i] != NULL; i++)
			if (key == *dataArray[i])
				return *dataArray[i];

	throw ItemDoesNotExistException();
}

template<typename T, size_t size>
void BinTreeNode<T, size>::Remove(const T &key)
{
	BinTreeNode *x = this;

	while (x && x->data[0])
	{
		if (key >= *x->data[0] && (x->data[size - 1] == NULL || key <= *x->data[size - 1]))
			break;
		else
		{
			if (key < *x->data[0])
				x = x->left;
			else
				x = x->right;
		}
	}

	if (x == NULL)
		return;

	for (size_t i = 0; i < size, x->data[i] != NULL; i++)
	{
		if (key == *x->data[i])
		{
			delete x->data[i];

			for (size_t j = i; j < size - 1; j++)
				x->data[j] = x->data[j + 1];

			if (x->right)
			{
				BinTreeNode *leftMost = x->right;

				while (leftMost->left)
					leftMost = leftMost->left;

				x->data[size - 1] = new T(*leftMost->data[0]);
				x->right->Remove(*leftMost->data[0]);

				//if (leftMost->data[0] == NULL)
				//{
				//	delete leftMost;
				//	//leftMost = NULL;
				//}
			}
			else
				x->data[size - 1] = NULL;

			break;
		}
	}

	Balance();
}

template<typename T, size_t size>
std::string BinTreeNode<T, size>::InfixTraverse()
{
	std::string temp = "";

	if (this)
	{
		temp += left->InfixTraverse();

		for (size_t i = 0; i < size && data[i] != NULL; i++)
		{
			std::ostringstream convert;
			convert << *data[i];
			temp += convert.str() + " ";
		}

		temp += right->InfixTraverse();
	}

	return temp;
}

template<typename T, size_t size>
std::string BinTreeNode<T, size>::PrefixTraverse()
{
	std::string temp = "";

	if (this)
	{
		for (size_t i = 0; i < size && data[i] != NULL; i++)
		{
			std::ostringstream convert;
			convert << *data[i];
			temp += convert.str() + " ";
		}

		temp += left->PrefixTraverse();
		temp += right->PrefixTraverse();
	}

	return temp;
}

template<typename T, size_t size>
std::string BinTreeNode<T, size>::PostfixTraverse()
{
	std::string temp = "";

	if (this)
	{
		temp += left->PostfixTraverse();
		temp += right->PostfixTraverse();

		for (size_t i = 0; i < size && data[i] != NULL; i++)
		{
			std::ostringstream convert;
			convert << *data[i];
			temp += convert.str() + " ";
		}
	}

	return temp;
}

template<typename T, size_t size>
T ** BinTreeNode<T, size>::GetArray(const T &key)
{
	BinTreeNode *x = this;

	while (x && x->data[0])
	{
		if (key >= *x->data[0] && (x->data[size - 1] == NULL || key <= *x->data[size - 1]))
			return x->data;
		else if (key < *x->data[0])
			x = x->left;
		else
			x = x->right;
	}

	return NULL;
}

template<typename T, size_t size>
void BinTreeNode<T, size>::Balance()
{
	if (left && left->data[0] == NULL)
	{
		delete left;
		left = NULL;
	}

	if (right && right->data[0] == NULL)
	{
		delete right;
		right = NULL;
	}

	if (data[size - 1] == NULL && left)
	{
		BinTreeNode<T, size> *rightMost = left;
		BinTreeNode<T, size> **temp = &left;

		while (rightMost->right)
		{
			rightMost = rightMost->right;
			temp = &(*temp)->right;
		}

		size_t index, leftIndex, freeSpace;

		for (index = 0; index < size - 1 && data[index + 1] != NULL; index++);

		freeSpace = size - index - 1;

		for (leftIndex = 0; leftIndex < size - 1 && rightMost->data[leftIndex + 1] != NULL; leftIndex++);

		for (size_t i = leftIndex; i > 0 && freeSpace > 0; i--)
		{
			for (size_t j = index; j < size - 1; j--)
				data[j + 1] = data[j];

			index++;
			data[0] = rightMost->data[i];
			rightMost->data[i] = NULL;
			freeSpace--;
		}

		if (freeSpace)
		{
			for (size_t j = index; j < size - 1; j--)
				data[j + 1] = data[j];

			index++;
			data[0] = rightMost->data[0];
			rightMost->data[0] = NULL;
			freeSpace--;
		}

		if (rightMost->data[0] == NULL)
		{
			delete rightMost;
			*temp = NULL;
			freeSpace--;
		}
	}

	//if (left && left->data[0] == NULL)
	//{
	//	delete left;
	//	left = NULL;
	//}

	//if (right && right->data[0] == NULL)
	//{
	//	delete right;
	//	right = NULL;
	//}
}