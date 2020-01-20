#pragma once
#include <vector>


class Board {
public:
	std::vector<std::vector<std::vector<std::vector<int>>>> fields;

	std::pair<int, int> pos = {1, 1};

	int size = 3;
	int activePlayer = 1;
	int stepNumber = 1;

	Board();
	std::vector<std::pair<int, int>> getPossibleSteps();
	int step(std::pair<int, int> p);
};

