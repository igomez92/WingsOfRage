#include "Node.h"


Node::Node(int x, int y)
	:xPos(x), yPos(y), next(nullptr)
{
}


Node::~Node(void)
{
}

void Node::addNode(int x, int y)
{
	Node* newNode;
	newNode->xPos = x;
	newNode->yPos = y;
	newNode->next = nullptr;

	this->next = newNode;
}
