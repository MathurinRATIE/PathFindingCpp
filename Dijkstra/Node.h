#pragma once
#include <limits>
#include "Vector2.h"
#define inf std::numeric_limits<int>::max()

struct Node
{
	Vector2 position;
	int g, h, f;
	float weight;
	bool blocked;
	Node* parent;

	Node(Vector2 _position = Vector2(0, 0))
	{
		position = _position;

		g = inf;
		h = inf;
		f = inf;

		weight = 1;
		blocked = false;

		parent = nullptr;
	}

	~Node()
	{
	}

	bool operator==(const Node& otherNode) const
	{
		return position == otherNode.position;
	}

	float GetDistance(Node* from)
	{
		Vector2 distanceVector = position - from->position;
		return distanceVector.SqrDistance();
	}

	float GetManahtanDistance(Node* from)
	{
		Vector2 distanceVector = position - from->position;
		return abs(distanceVector.x) + abs(distanceVector.y);
	}
};