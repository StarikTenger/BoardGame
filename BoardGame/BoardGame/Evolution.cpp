#include "Evolution.h"
#include <iostream>

void Evolution::iteration() {
	// mutating & comparing with best
	std::cout << "\n--- GENERATION " << generationNumber << " ---\n";
	auto genome1 = mutate(genome0);
	if (comp(genome1, genome0) == 1)
		genome0 = genome1;

	generationNumber++;

	// writing to file
	std::ofstream file(bestGenomePath);
	for (auto g : genome0)
		file << g << " ";
	file.close();
}

std::vector<int> Evolution::mutate(std::vector<int> genome) {
	for (auto& g : genome) {
		if (random::intRandom(0, 1))
			continue;
		g += random::intRandom(-5, 5);
	}
	genome[1] = genome[2] = genome[0];
	genome[5] = genome[4] = genome[3];
	return genome;
}

std::vector<int> Evolution::generate() {
	for (int i = 0; i < generations; i++)
		iteration();
	return genome0;
}

int Evolution::checkPos(const Board& board) {
	int v = 0;
	int n = board.size;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int x = 0; x < n; x++) {
				for (int y = 0; y < n; y++) {
					const auto& field = board.fields[i][j];

					// horizontal
					if (x == 1) {
						if (field[x][y] == field[x - 1][y] && field[x][y] == field[x + 1][y]) {
							if (y == 1)
								v += field[x][y] ;
							else
								v += field[x][y] ;
						}
					}

					// vertical
					if (y == 1) {
						if (field[x][y] == field[x][y - 1] && field[x][y] == field[x][y + 1]) {
							if (x == 1)
								v += field[x][y];
							else
								v += field[x][y];
						}
					}

					// diagonal
					if (x == 1 && y == 1) {
						if (field[x][y] == field[x - 1][y - 1] && field[x][y] == field[x + 1][y + 1]) {
							v += field[x][y];
						}
						if (field[x][y] == field[x - 1][y + 1] && field[x][y] == field[x + 1][y - 1]) {
							v += field[x][y];
						}
					}
				}
			}
		}
	}
	std::cout << "V: " << v << "\n";
	if (v == 0)
		return v;
	return v / abs(v);
}

int Evolution::play(std::vector<int> a, std::vector<int> b) {
	Board board;
	Bot botA;
	Bot botB;

	botA.coefficients = a;
	botB.coefficients = b;

	botA.type = 1;
	botB.type = -1;

	for (int i = 0; i < 81; i++) {
		std::cout << ".";
		if (board.activePlayer == -1) {			
			auto s = botA.step(board);
			board.step(s);
		}
		if (board.activePlayer == 1) {		
			auto s = botB.step(board);
			board.step(s);
		}
		if (!board.getPossibleSteps().size()) {
			std::cout << "\n";
			return checkPos(board);
		}
		
	}
	
}

int Evolution::comp(std::vector<int> a, std::vector<int> b) {
	int sum = 0;
	for (int i = 0; i < compIterations; i++) {
		std::cout << " GAME STARTED \n";
		int res = play(a, b);
		std::cout << "RESULT: " << res << "\n";
		sum += res;
	}
	return sum;
}
