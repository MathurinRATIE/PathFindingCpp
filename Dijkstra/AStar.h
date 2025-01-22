#pragma once
#include <vector>
#include "Node.h"
#include "Vector2.h"

class AStar
{
public :
	AStar();

	void PathFinding();
	void InitNodes();
	void SelectCurrendNode();
	void GetFinalPath();
	void GetChilds();
	void EvaluateChilds();

private :
	std::vector<Node*> mBlankNodes;
	std::vector<Node*> mOpenNodes;
	std::vector<Node*> mClosedNodes;
	std::vector<Node*> mChildrens;

	Node* mStartNode = nullptr;
	Node* mEndNode = nullptr;
	Node* MCurrentNode = nullptr;

	bool mFirstIteration = true;
	std::string mPath = "";

	Vector2 mGoal;
	Vector2 mStart;

	std::vector<Vector2> mWalls;
	std::vector<Vector2> mLowWeights;
	std::vector<Vector2> mHighWeights;
};

