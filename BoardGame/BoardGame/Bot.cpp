#include "Bot.h"
#include "Board.h"
#include <iostream>
#include <algorithm>



std::pair<int, int> Bot::step(Board board) {
	auto arr = board.getPossibleSteps();
	std::pair<int, int> best = { -1, -1 };
	int vMax = -INF;

	for (int i = 0; i < arr.size(); i++) {
		std::swap(arr[i], arr[random::intRandom(0, arr.size() - 1)]);
	}

	for (auto s : arr) {
		auto b1 = board;
		b1.step(s);
		int v = value(b1, limit, -INF, INF);
		std::cout << v << " ";
		if (v > vMax) {
			vMax = v;
			best = s;
		}
	}
	if (!arr.size())
		return { 1, 1 };
	if (best.first == -1)
		return arr.back();
	std::cout << "\n";
	counter = 0;
	return best;
}

int Bot::value(Board board, int iteration, int alpha, int beta) {
	auto arr = board.getPossibleSteps();
	for (int i = 0; i < arr.size(); i++) {
		std::swap(arr[i], arr[random::intRandom(0, arr.size() - 1)]);
	}

	if (iteration == 0 || !arr.size())
		return value(board);
	int vMin = INF;
	int vMax = -INF;
	for (auto s : arr) {
		auto b1 = board;
		b1.step(s);
		int v = value(b1, iteration - 1, vMax, vMin);
		vMin = std::min(vMin, v);
		vMax = std::max(vMax, v);
		
		
		if (iteration % 2 == limit % 2 && v <= alpha)
			break;
		if (iteration % 2 != limit % 2 && v >= beta)
			break;
	}
	if (iteration % 2 == limit % 2)
		return vMin;
	return vMax;
}

int Bot::value(Board board) {
	int v = 0;
	int n = board.size;

	counter++;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int x = 0; x < n; x++) {
				for (int y = 0; y < n; y++) {
					const auto& field = board.fields[i][j];

					if (x == 1) {
						if (field[x][y] == field[x - 1][y] && field[x][y] == field[x + 1][y]) {
							v += field[x][y] *coefficients[0];
						}
					}
					if (y == 1) {
						if (field[x][y] == field[x][y - 1] && field[x][y] == field[x][y + 1]) {
							v += field[x][y] * coefficients[0];
						}
					}
					if (x == 1 && y == 1) {
						if (field[x][y] == field[x - 1][y - 1] && field[x][y] == field[x + 1][y + 1]) {
							v += field[x][y] * coefficients[1];
						}
						if (field[x][y] == field[x - 1][y + 1] && field[x][y] == field[x + 1][y - 1]) {
							v += field[x][y] * coefficients[1];
						}
					}

				}
			}
		}
	}
	int num = board.getPossibleSteps().size();
	if (num == 0)
		v *= 10;

	return v*type;
}
