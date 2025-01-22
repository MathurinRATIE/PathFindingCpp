#include "AStar.h"

AStar::AStar()
{
	mWalls = { Vector2(2, 2), Vector2(2, 3), Vector2(2, 4), Vector2(2, 5) };
	mLowWeights = { Vector2(1, 2), Vector2(1, 3) };
	mHighWeights = { Vector2(2, 1), Vector2(0, 2), Vector2(2, 0), Vector2(2, 6), Vector2(0, 2) };

	mGoal = Vector2(6, 5);
	mStart = Vector2(0, 1);
}

void AStar::PathFinding()
{
	InitNodes();

	MCurrentNode = mStartNode;
	mFirstIteration = true;

	while (mOpenNodes.size() != 0 || MCurrentNode->position == mStart)
	{
		SelectCurrendNode();

		if (MCurrentNode->position == mGoal)
		{
			GetFinalPath();

			break;
		}

		GetChilds();

		EvaluateChilds();

		mFirstIteration = false;
	}
}

void AStar::InitNodes()
{
	for (int x = 0; x < 7; x++)
	{
		for (int y = 0; y < 7; y++)
		{
			Node* myNode = new Node(Vector2(x, y));

			if (x == mStart.x && y == mStart.y)
			{
				myNode->g = 0;
				myNode->h = 100;
				myNode->f = 100;

				mStartNode = myNode;
			}
			else if (x == mGoal.x && y == mGoal.y)
			{
				mEndNode = myNode;
			}

			if (std::find(mWalls.begin(), mWalls.end(), myNode->position) != mWalls.end())
			{
				myNode->blocked = true;
			}
			else if (std::find(mLowWeights.begin(), mLowWeights.end(), myNode->position) != mLowWeights.end())
			{
				myNode->weight = 1.5;
			}
			else if (std::find(mHighWeights.begin(), mHighWeights.end(), myNode->position) != mHighWeights.end())
			{
				myNode->weight = 2;
			}

			mBlankNodes.push_back(myNode);
		}
	}
}

void AStar::SelectCurrendNode()
{
	if (!mFirstIteration)
	{
		int optimalF = inf;
		for (Node* node : mOpenNodes)
		{
			if (node->f < optimalF)
			{
				MCurrentNode = node;
				optimalF = MCurrentNode->f;
			}
		}

		mOpenNodes.erase(std::find(mOpenNodes.begin(), mOpenNodes.end(), MCurrentNode));
	}
	else
	{
		mBlankNodes.erase(std::find(mBlankNodes.begin(), mBlankNodes.end(), mStartNode));
	}
	mClosedNodes.push_back(MCurrentNode);
}

void AStar::GetFinalPath()
{
	while (MCurrentNode->position != mStart)
	{
		mPath = MCurrentNode->position.ToString() + " " + mPath;
		mPath = " - " + mPath;

		MCurrentNode = MCurrentNode->parent;
	}
	mPath = "\n" + MCurrentNode->position.ToString() + " " + mPath;
	printf(mPath.c_str());
	mOpenNodes.clear();
	mClosedNodes.clear();
	std::string cost = "\nPath cost : " + std::to_string(MCurrentNode->f) + "\n";
	printf(cost.c_str());
}

void AStar::GetChilds()
{
	mChildrens.clear();
	for (Node* node : mBlankNodes)
	{
		if (MCurrentNode->GetDistance(node) < 2 && !node->blocked)
		{
			mChildrens.push_back(node);
		}
	}
	for (Node* node : mOpenNodes)
	{
		if (MCurrentNode->GetDistance(node) < 2)
		{
			mChildrens.push_back(node);
		}
	}
}

void AStar::EvaluateChilds()
{
	for (Node* child : mChildrens)
	{
		bool isOpenNode = std::find(mOpenNodes.begin(), mOpenNodes.end(), child) != mOpenNodes.end();

		if (!isOpenNode)
		{
			mBlankNodes.erase(std::find(mBlankNodes.begin(), mBlankNodes.end(), child));
		}

		float tempG = MCurrentNode->g + child->GetDistance(MCurrentNode) * 10 * child->weight;
		float tempH = child->GetManahtanDistance(mEndNode) * 10;
		float tempF = tempG + tempH;

		if (tempF < child->f)
		{
			child->g = tempG;
			child->h = tempH;
			child->f = tempF;
			child->parent = MCurrentNode;
		}

		if (isOpenNode)
		{
			mOpenNodes.erase(std::find(mOpenNodes.begin(), mOpenNodes.end(), child));
		}

		mOpenNodes.push_back(child);
		printf("\nNode added to open Nodes : ");
		printf("(%1f, %1f) with parent (%1f, %1f)", child->position.x, child->position.y, child->parent->position.x, child->parent->position.y);
	}
}
