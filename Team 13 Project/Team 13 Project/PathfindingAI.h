#ifndef PATHFINDING_AI_H
#define PATHFINDING_AI_H

#include "Character.h"
#include "Node.h"

struct AI_Choice
{
	Node* head;
};

class PathfindingAI
{
public:
	AI_Choice decidePath(Character being);
};

#endif // PATHFINDING_AT_H