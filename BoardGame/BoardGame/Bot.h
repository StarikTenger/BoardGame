#pragma once
#include <vector>
#include "random.h"
#include "Board.h"

#define INF 1000000000

class Bot {
public:
	int depth = 1;
	int depthLimit = 100;
	int threshold = 1000;
	int type = 1;
	int counter = 0;
	int isPositionTerminate = 0;

	std::vector<int> coefficients = { 10, 10 , 10 , 1 , 1 , 1 };
	
	Bot() {};
	std::pair<int, int> step(Board board);
private:
	int value(const Board& board);
	int value(Board board, int iteraion, int alpha, int beta);
};

