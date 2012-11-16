#include "PathfindingAI.h"
#include "Node.h"

// Run through all choices, constructing a linked-list with the Nodes
// UNDEFINED: Point [entity].location
//			  bool [point].collides()

// AI_Choice decidePath(Point destination, Character being)
vector<Point> decidePath(Point destination, Character being)
{
	//Not 100% sure how to deal with the AI_Choice struct, so for now I'm just returning a vector

	//AI_Choice decision;

	// Really need to find a better way to do this
	vector<Point> openList;
	vector<Point> closedList;
	Point currentPoint = being.location();
	// Locations adjacent to being are checked for collision and added to open list if they are passable
	vector<Point> beingAdjacentSquares = getAdjacentSquares(currentPoint);
	for each(Point p in beingAdjacentSquares)
	{
		openList.push_back(p);
	}

	currentPoint.startCost = 0;
	calculateEndCost(currentPoint);
	openList.push_back(currentPoint);	// Add original position to open list
	while(!openList.empty())
	{
		
		Point candidate;
		candidate=openList.front();
		int candidatePos = 0;
		for(i=0; i<openList.size(); i++) 
		// Find the point in the open list with the lowest score
		// In case of ties, take the most recently added point
		{
			if(openList[i] <= candidate.score)
			{
				candidate = openList[i];
				candidatePos = i;
			}
		}
		closedList.push_back(candidate);
		openList.erase(candidatePos);
		// If the destination square is in the closedList, then we have found the path
		bool pathFound = false;
		for each(Point p in closedList)
		{
			if((p.x == destination.x) && (p.y == destination.y))
			{
				pathFound = true;
			}
		}
		if(pathFound)
			break;

		// Otherwise, we carry on.
		vector<Point> candidateAdjacent = getAdjacentSquares(candidate);

		for each(Point p in candidateAdjacent)
		{
			bool found = false;
			// If this adjacent square is already in the closed list,
			// check the next adjacent square instead
			for each(Point q in closedList)
			{
				if((p.x == q.x) && (p.y == q.y))
				{
					found = true;
				}
			}
			if(found)
				continue;

			// Otherwise, if this adjacent square is not already in the open list,
			// compute its score and add it to the open list.


			for each(Point q in openList)
			{
				if((p.x == q.x) && (p.y == q.y))
				{
					found = true;
				}
			}
			if(!found)
			{
				p.startCost = candidate.startCost++;
				p.parent = candidate;
				calculateEndCost(p);
				openList.push_back(p);
			}
			// If it is already in the open list,
			// check whether this square is a better path.
			else
			{
				Point checkPoint = candidate;
				checkPoint.startCost = p.startCost++;
				checkPoint.parent = p;
				calculateEndCost(checkPoint);
				if(checkPoint.score < candidate.score)
				{
					candidate = checkPoint;
				}
			}
		}
	}
	
	Point pathPoint = destination;
	vector<Point> decision;
	while(pathPoint.parent != null)
	{
		decision.insert(pathPoint, 0)
		pathPoint = pathPoint.parent;
	}

	return decision;
}

void calculateEndCost(Point point)
{
	point.endCost = abs(point.x - destination.x) + abs(point.y - destination.y);
	point.score = point.startCost + point.endCost;
}

vector<Point> getAdjacentSquares(Point point)
{
	vector<Point> adjacentSquares;
	Point left = point;
	left.x = left.x - 1;
	Point right = point;
	right.x = right.x + 1;
	Point up = point;
	up.y = up.y - 1;
	Point down = point;
	down.y = down.x + 1;
	
	if(!left.collides())
	{
		calculateEndCost(left);
		adjacentSquares.push_back(left);
	}
	if(!right.collides())
	{
		calculateEndCost(right);
		adjacentSquares.push_back(right);
	}	
	if(!up.collides())
	{
		calculateEndCost(up);
		adjacentSquares.push_back(up);
	}	
	if(!down.collides())
	{
		calculateEndCost(down);
		adjacentSquares.push_back(down);
	}
	return adjacentSquares;
}