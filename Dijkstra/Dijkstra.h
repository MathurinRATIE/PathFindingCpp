#pragma once
#include <limits>
#include <vector>
#include <string>
#define inf std::numeric_limits<int>::max()

class Dijkstra
{
public :
	void PathFinding(int origin);
	void GetPath(int destination);
	void GPS(int origin, int destination);

private :
	int mDist[12];
	int mPred[12];
	int mGraph[12][12] = {
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
	char mNodesLetters[27] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '_',
	};
};