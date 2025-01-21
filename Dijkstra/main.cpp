#include <limits>
#include <iostream>
#include <vector>
#define inf std::numeric_limits<int>::max()

void Dijkstra(int origin, int graph[12][12], int dist[], int pred[]);
void GetPath(int destination, int dist[], int pred[], char nodesLetters[]);
void GPS(int origin, int destination);



struct Vector2
{
	float x, y;
	Vector2(float _x = 0, float _y = 0) :x(_x), y(_y) {}

	void SetX(float _x)
	{
		x = _x;
	}
	void SetY(float _y)
	{
		y = _y;
	}

	bool operator==(const Vector2& goal) const
	{
		return x == goal.x && y == goal.y;
	}

	Vector2 operator-(const Vector2& vector2) const
	{
		return Vector2(x - vector2.x, y - vector2.y);
	}

	int SqrDistance()
	{
		return sqrt(x * x + y * y);
	}

	std::string ToString()
	{
		return "(" , x , ", " , y , ")";
	}
};

struct Node
{
	Vector2 position;
	int g, h, f;
	Node* parent;

	Node(Vector2 _position = Vector2(0, 0))
	{
		position = _position;

		g = inf;
		h = inf;
		f = inf;

		parent = nullptr;
	}

	~Node()
	{
	}

	int GetDistance(Node* from)
	{
		Vector2 distanceVector = position - from->position;
		return distanceVector.SqrDistance();
	}
};






void main()
{
	GPS(0, 9);

	GPS(1, 8);
}







void AStar()
{
	std::vector<Node> openNodes;
	std::vector<Node> closedNodes;
	std::vector<Node> childrens;

	Node startNode;
	Node endNode;
	Node currentNode;

	Vector2 goal = Vector2(6, 5);
	Vector2 start = Vector2(0, 1);

	for (int x = 0; x < 7; x++)
	{
		for (int y = 0; y < 7; y++)
		{
			Node myNode = Node(Vector2(x, y));

			openNodes.push_back(myNode);

			if (x == 0 && y == 1)
			{
				startNode = myNode;

				startNode.g = 0;
				startNode.h = 100;
				startNode.f = 100;
			}
		}
	}

	currentNode = startNode;
	while (openNodes.size() != 0)
	{
		for (Node node : openNodes)
		{
			if (node.f < currentNode.f)
			{
				currentNode = node;
			}
		}

		openNodes.erase(std::find(openNodes.begin(), openNodes.end(), currentNode));
		closedNodes.push_back(currentNode);
	
		if (currentNode.position == goal)
		{
			// Recover Path
		}

		childrens.clear();
		for (Node node : openNodes)
		{
			if (currentNode.GetDistance(&node) < 2)
			{
				childrens.push_back(node);
			}
		}

		for (Node child : childrens)
		{
			child.g = currentNode.g + child.GetDistance(&currentNode);
			child.h = child.GetDistance()
		}
	}
}







void Dijkstra(int origin, int graph[12][12], int dist[], int pred[])
{
	std::vector<int> unlockedNodes;

	for (int i = 0; i < sizeof(graph[0]) / sizeof(int); i++)
	{
		dist[i] = inf;
		pred[i] = 26;
		unlockedNodes.push_back(i);
	}
	dist[origin] = 0;

	while (!unlockedNodes.empty())
	{
		int currentNode = unlockedNodes[0];
		for (int unlockedNode : unlockedNodes)
		{
			if (dist[unlockedNode] < dist[currentNode])
			{
				currentNode = unlockedNode;
			}
		}
		unlockedNodes.erase(std::remove(unlockedNodes.begin(), unlockedNodes.end(), currentNode), unlockedNodes.end());

		for (int neighbor : unlockedNodes)
		{
			int tempDistance = graph[currentNode][neighbor] + dist[currentNode];

			if (tempDistance < dist[neighbor] && tempDistance > 0)
			{
				dist[neighbor] = tempDistance;
				pred[neighbor] = currentNode;
			}
		}
	}
}

void GetPath(int destination, int dist[], int pred[], char nodesLetters[])
{
	int node = destination;
	int origin = 0;
	std::string path = "";
	while (node != 26)
	{
		path = nodesLetters[node] + path;
		if (pred[node] != 26)
		{
			path = "-" + path;
		}
		else
		{
			origin = node;
		}

		node = pred[node];
	}

	printf("\nOptimal path from %c to %c is :\n", nodesLetters[origin], nodesLetters[destination]);
	printf(path.c_str());
	printf("\nCost : %i\n", dist[destination]);
}

void GPS(int origin, int destination)
{
	int graph[12][12] = {
		//   A    B    C    D    E    F    G    H    I    J    K    L
			  0,   2, inf, inf,  13, inf, inf, inf, inf, inf,   7,  10, // A
			inf,   0, inf, inf, inf, inf,   1, inf, inf, inf, inf, inf, // B
			inf, inf,   0, inf,   1, inf, inf,   1, inf,   2, inf, inf, // C
			inf, inf, inf,   0, inf,   8, inf,   4, inf, inf, inf, inf, // D
			inf, inf, inf, inf,   0, inf, inf, inf, inf,   5, inf, inf, // E
			inf, inf, inf, inf, inf,   0, inf, inf, inf, inf, inf, inf, // F
			inf, inf, inf,   5, inf, inf,   0,   2, inf, inf, inf,   3, // G
			inf, inf, inf, inf, inf,  10, inf,   0,   4,   7, inf, inf, // H
			inf, inf, inf, inf, inf,   5, inf, inf,   0, inf, inf, inf, // I
			inf, inf, inf, inf, inf,   1, inf, inf,   9,   0, inf, inf, // J
			inf, inf,   3, inf,   8, inf, inf, inf, inf, inf,   0,   5, // K
			inf,   6, inf, inf, inf, inf, inf,  12, inf, inf, inf,   0, // L
	};

	char nodesLetters[27] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '_',
	};

	int dist[sizeof(graph[0]) / sizeof(int)];
	int pred[sizeof(graph[0]) / sizeof(int)];

	Dijkstra(origin, graph, dist, pred);

	printf("Start at B:\n");
	for (int i = 0; i < sizeof(graph[0]) / sizeof(int); i++)
	{
		if (dist[i] != inf)
		{
			printf("%c : %i - %c \n", nodesLetters[i], dist[i], nodesLetters[pred[i]]);
		}
	}

	GetPath(destination, dist, pred, nodesLetters);
	printf("\n\n");
}
