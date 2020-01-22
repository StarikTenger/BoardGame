#include "Board.h"
#include <iostream>
Board::Board() {
	fields = std::vector<std::vector<std::vector<std::vector<short int>>>>(size);
	for (auto& a : fields) {
		a = std::vector<std::vector<std::vector<short int>>>(size);
		for (auto& b : a) {
			b = std::vector<std::vector<short int>>(size);
			for (auto& c : b) {
				c = std::vector<short int>(size);
				for (auto& d : c)
					d = 0;
			}
		}
	}
	activePlayer = (stepNumber % 2 == 1) - (stepNumber % 2 == 0);
}

std::vector<std::pair<int, int>> Board::getPossibleSteps() {
	std::vector<std::pair<int, int>> arr;
	const auto& field = fields[pos.first][pos.second];
	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			if (field[x][y] == 0)
				arr.push_back({x, y});
		}
	}
	return arr;
}

int Board::step(std::pair<int, int> p) {
	if (fields[pos.first][pos.second][p.first][p.second] != 0)
		return 1;

	stepNumber++;
	activePlayer = (stepNumber % 2 == 1) - (stepNumber % 2 == 0);
	fields[pos.first][pos.second][p.first][p.second] = activePlayer;
	pos = p;
	return 0;
}