#pragma once
#include <vector>
#include "random.h"
#include "Board.h"

#define INF 1000000000

class Bot {
public:
	int limit = 6;
	int type = 1;
	int counter = 0;

	std::vector<int> coefficients = { 10, 11 };

	Bot() {};
	std::pair<int, int> step(Board board);
private:
	int value(Board board);
	int value(Board board, int iteraion, int alpha, int beta);
};

