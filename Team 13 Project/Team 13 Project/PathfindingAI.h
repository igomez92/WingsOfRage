#ifndef PATHFINDING_AI_H
#define PATHFINDING_AI_H

#include "Character.h"
#include "Node.h"

struct AI_Choice
{
	Node* head;
};

struct Point
{
	int x;
	int y;
	int startCost;		// The cost of moving from the starting position to this point
	int endCost;		// The cost of moving from this position to the end point
	int score;			// Total cost score = startCost + endCost

};

class PathfindingAI
{
public:
	AI_Choice decidePath(Character being);
};

#endif // PATHFINDING_AT_H