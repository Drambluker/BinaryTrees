#include "BinaryTree.h"
#include <iostream>

int main()
{
	int selection, key;
	enum { INSERT, FIND, REMOVE, INFIX_TRAVERSE };
	BinTreeNode test(0, 0);

	do
	{
		std::cout << "\n1 - Insert\n2 - Find\n3 - Remove\n4 - Infix Traverse\n0 - Exit\n: ";
		std::cin >> selection;
		selection--;

		switch (selection)
		{
		case INSERT:
			std::cout << "\nKey: ";
			std::cin >> key;
			test.Insert(key, key);
			break;
		case FIND:
			std::cout << "\nKey: ";
			std::cin >> key;
			std::cout << test.Find(key) << std::endl;
			break;
		case REMOVE:
			std::cout << "\nKey: ";
			std::cin >> key;
			test.Remove(key);
			break;
		case INFIX_TRAVERSE:
			std::cout << "\nInfix Traverse: " << test.InfixTraverse() << std::endl;
			break;
		default:
			break;
		}
	} while (selection != -1);

	return 0;
}