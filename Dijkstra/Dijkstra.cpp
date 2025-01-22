#include "Dijkstra.h"

void Dijkstra::PathFinding(int origin)
{
	std::vector<int> unlockedNodes;

	for (int i = 0; i < sizeof(mGraph[0]) / sizeof(int); i++)
	{
		mDist[i] = inf;
		mPred[i] = 26;
		unlockedNodes.push_back(i);
	}
	mDist[origin] = 0;

	while (!unlockedNodes.empty())
	{
		int currentNode = unlockedNodes[0];
		for (int unlockedNode : unlockedNodes)
		{
			if (mDist[unlockedNode] < mDist[currentNode])
			{
				currentNode = unlockedNode;
			}
		}
		unlockedNodes.erase(std::remove(unlockedNodes.begin(), unlockedNodes.end(), currentNode), unlockedNodes.end());

		for (int neighbor : unlockedNodes)
		{
			int tempDistance = mGraph[currentNode][neighbor] + mDist[currentNode];

			if (tempDistance < mDist[neighbor] && tempDistance > 0)
			{
				mDist[neighbor] = tempDistance;
				mPred[neighbor] = currentNode;
			}
		}
	}
}

void Dijkstra::GetPath(int destination)
{
	int node = destination;
	int origin = 0;
	std::string path = "";
	while (node != 26)
	{
		path = mNodesLetters[node] + path;
		if (mPred[node] != 26)
		{
			path = "-" + path;
		}
		else
		{
			origin = node;
		}

		node = mPred[node];
	}

	printf("\nOptimal path from %c to %c is :\n", mNodesLetters[origin], mNodesLetters[destination]);
	printf(path.c_str());
	printf("\nCost : %i\n", mDist[destination]);
}

void Dijkstra::GPS(int origin, int destination)
{
	PathFinding(origin);

	printf("Start at B:\n");
	for (int i = 0; i < sizeof(mGraph[0]) / sizeof(int); i++)
	{
		if (mDist[i] != inf)
		{
			printf("%c : %i - %c \n", mNodesLetters[i], mDist[i], mNodesLetters[mPred[i]]);
		}
	}

	GetPath(destination);
	printf("\n\n");
}
