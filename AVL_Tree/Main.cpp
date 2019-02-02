#include "AVL_Tree.h"
#include <iostream>

int main()
{
	int selection, key;
	enum { INSERT, REMOVE, FIND_MIN, FIND_MAX, GET_HEIGHT, INFIX_TRAVERSE, PREFIX_TRAVERSE, POSTFIX_TRAVERSE };
	AVL_Node *test = NULL;

	do
	{
		std::cout << "\n1 - Insert\n2 - Remove\n3 - Find Min\n4 - Find Max\n5 - Get Height\n6 - Infix Traverse\n7 - Prefix Traverse\n8 - Postfix Traverse\n0 - Exit\n: ";
		std::cin >> selection;
		selection--;

		switch (selection)
		{
		case INSERT:
			std::cout << "\nKey: ";
			std::cin >> key;
			AVL_Node::Insert(&test, key);
			break;
		case REMOVE:
			std::cout << "\nKey: ";
			std::cin >> key;
			AVL_Node::Remove(&test, key);
			break;
		case FIND_MIN:
			if (test->FindMin())
				std::cout << "\nMin: " << test->FindMin()->key << '\n';

			break;
		case FIND_MAX:
			if (test->FindMax())
				std::cout << "\nMax: " << test->FindMax()->key << '\n';

			break;
		case GET_HEIGHT:
			if (test)
				std::cout << "\nHeight: " << test->GetHeight() << '\n';
			break;
		case INFIX_TRAVERSE:
			std::cout << "\nInfix Traverse: " << test->InfixTraverse() << '\n';
			break;
		case PREFIX_TRAVERSE:
			std::cout << "\nPrefix Traverse: " << test->PrefixTraverse() << '\n';
			break;
		case POSTFIX_TRAVERSE:
			std::cout << "\nPostfix Traverse: " << test->PostfixTraverse() << '\n';
			break;
		default:
			break;
		}
	} while (selection != -1);

	delete test;
	return 0;
}