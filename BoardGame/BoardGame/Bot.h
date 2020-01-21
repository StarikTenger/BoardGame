#pragma once
#include <vector>
#include "random.h"
#include "Board.h"

class Bot {
public:
	int limit = 5;
	Bot() {};
	std::pair<int, int> step(Board board);
private:
	int value(Board board);
	int value(Board board, int iteraion, int alpha, int beta);
};

