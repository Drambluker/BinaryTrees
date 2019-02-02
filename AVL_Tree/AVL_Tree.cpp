#include "AVL_Tree.h"

AVL_Node::AVL_Node(int key)
{
	this->key = key;
	left = right = NULL;
	height = 1;
}

AVL_Node::~AVL_Node()
{
	if (this)
	{
		delete this->left;
		this->left = NULL;
		delete this->right;
		this->right = NULL;
	}
}

AVL_Node * AVL_Node::Insert(AVL_Node **p, int key)
{
	if (!(*p))
	{
		*p = new AVL_Node(key);
		return *p;
	}

	if (key < (*p)->key)
		Insert(&(*p)->left, key);
	else
		Insert(&(*p)->right, key);

	return Balance(p);
}

AVL_Node * AVL_Node::Remove(AVL_Node **p, int key)
{
	if (!(*p))
		return NULL;

	if (key < (*p)->key)
		Remove(&(*p)->left, key);
	else if (key > (*p)->key)
		Remove(&(*p)->right, key);
	else
	{
		AVL_Node *left = (*p)->left;
		AVL_Node *right = (*p)->right;
		free(*p);

		if (!right)
		{
			*p = left;
			return *p;
		}

		AVL_Node *min = right->FindMin();
		min->right = RemoveMin(&right);
		min->left = left;
		*p = Balance(&min);
		return *p;
	}

	return Balance(p);
}

int AVL_Node::GetHeight() const
{
	return this ? this->height : 0;
}

AVL_Node * AVL_Node::FindMin()
{
	if (this)
		return this->left ? this->left->FindMin() : this;

	return NULL;
}

AVL_Node * AVL_Node::FindMax()
{
	if (this)
		return this->right ? this->right->FindMax() : this;

	return NULL;
}

std::string AVL_Node::InfixTraverse()
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

std::string AVL_Node::PrefixTraverse()
{
	std::string temp = "";

	if (this)
	{
		temp += std::to_string(this->key) + " ";
		temp += this->left->PrefixTraverse();
		temp += this->right->PrefixTraverse();
	}

	return temp;
}

std::string AVL_Node::PostfixTraverse()
{
	std::string temp = "";

	if (this)
	{
		temp += this->left->PostfixTraverse();
		temp += this->right->PostfixTraverse();
		temp += std::to_string(this->key) + " ";
	}

	return temp;
}

int AVL_Node::GetBalanceFactor() const
{
	return this->right->GetHeight() - this->left->GetHeight();
}

void AVL_Node::FixHeight()
{
	unsigned char heightLeft = this->left->GetHeight();
	unsigned char heightRight = this->right->GetHeight();
	this->height = (heightLeft > heightRight ? heightLeft : heightRight) + 1;
}

AVL_Node * AVL_Node::RotateRight(AVL_Node **p)
{
	AVL_Node *q = (*p)->left;
	(*p)->left = q->right;
	q->right = *p;
	(*p)->FixHeight();
	q->FixHeight();
	*p = q;
	return *p;
}

AVL_Node * AVL_Node::RotateLeft(AVL_Node **q)
{
	AVL_Node *p = (*q)->right;
	(*q)->right = p->left;
	p->left = *q;
	(*q)->FixHeight();
	p->FixHeight();
	*q = p;
	return *q;
}

AVL_Node * AVL_Node::Balance(AVL_Node **p)
{
	(*p)->FixHeight();

	if ((*p)->GetBalanceFactor() == 2)
	{
		if ((*p)->right->GetBalanceFactor() < 0)
			(*p)->right = RotateRight(&(*p)->right);

		return RotateLeft(p);
	}
	if ((*p)->GetBalanceFactor() == -2)
	{
		if ((*p)->left->GetBalanceFactor() > 0)
			(*p)->left = RotateLeft(&(*p)->left);

		return RotateRight(p);
	}

	return *p;
}

AVL_Node * AVL_Node::RemoveMin(AVL_Node **p)
{
	if (!(*p)->left)
	{
		*p = (*p)->right;
		return *p;
	}

	RemoveMin(&(*p)->left);
	return Balance(p);
}