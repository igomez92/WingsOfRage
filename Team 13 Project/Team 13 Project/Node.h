#ifndef NODE_H
#define NODE_H

class Node
{
public:
	// Constructs a new Node Object
	Node(int x, int y);
	// De-allocates any pointers
	~Node();
	// Adds a new Node object to the Linked-List
	void addNode(int x, int y);
private:
	int xPos;
	int yPos;
	Node* next;
};

#endif