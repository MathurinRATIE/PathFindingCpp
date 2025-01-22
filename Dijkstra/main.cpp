#include <limits>
#include <iostream>
#include <vector>
#include <string>
#include "Dijkstra.h"
#include "AStar.h"
#define inf std::numeric_limits<int>::max()


int main()
{
	/*Dijkstra* dijkstra = new Dijkstra();

	dijkstra->GPS(0, 9);
	dijkstra->GPS(1, 8);*/

	AStar* aStar = new AStar();

	aStar->PathFinding();

	return 0;
}
















