#include "BinaryTree.h"
#include <iostream>

int main()
{
	int selection;
	enum { INSERT, FIND, REMOVE, LOAD, SAVE, INFIX_TRAVERSE, PREFIX_TRAVERSE, POSTFIX_TRAVERSE };
	std::string value;
	BinTreeNode<std::string, 4> test;

	do
	{
		value = "";
		std::ifstream ifs;
		std::ofstream ofs;
		std::cout << "1 - Insert\n2 - Find\n3 - Remove\n4 - Load\n5 - Save\n6 - Infix Traverse\n7 - Prefix Traverse\n8 - Postfix Traverse\n0 - Exit\n: ";
		std::cin >> selection;
		std::cout << std::endl;
		selection--;

		switch (selection)
		{
		case INSERT:
			std::cout << "Value: ";
			std::cin >> value;
			std::cout << std::endl;
			test.Insert(value);
			break;
		case FIND:
			std::cout << "Key: ";
			std::cin >> value;
			std::cout << std::endl;

			try
			{
				std::cout << "Value: " << test.Find(value) << std::endl;
			}
			catch (const BinTreeNode<std::string, 4>::ItemDoesNotExistException &)
			{
				std::cout << "Item does not exist!\n\n";
			}

			break;
		case REMOVE:
			std::cout << "Key: ";
			std::cin >> value;
			std::cout << std::endl;
			test.Remove(value);
			break;
		case LOAD:
			std::cout << "File Name: ";
			std::cin >> value;
			std::cout << std::endl;
			ifs.open(value);

			if (ifs)
				ifs >> test;
			else
				std::cout << "File does not exist!\n\n";

			ifs.close();
			break;
		case SAVE:
			std::cout << "File Name: ";
			std::cin >> value;
			std::cout << std::endl;
			ofs.open(value);
			ofs << test;
			ifs.close();
			break;
		case INFIX_TRAVERSE:
			std::cout << test.InfixTraverse() << "\n\n";
			break;
		case PREFIX_TRAVERSE:
			std::cout << test.PrefixTraverse() << "\n\n";
			break;
		case POSTFIX_TRAVERSE:
			std::cout << test.PostfixTraverse() << "\n\n";
			break;
		default:
			break;
		}
	} while (selection != -1);

	return 0;
}