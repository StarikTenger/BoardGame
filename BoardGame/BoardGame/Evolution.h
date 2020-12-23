#pragma once
#include "Board.h"
#include "Bot.h"
#include <string>
#include <fstream>

class Evolution {
public:
	int compIterations = 5;
	int generations = 500;
	int generationNumber = 0;

	std::vector<int> genome0 = { 100, 100, 100, 10, 10, 10 };
	std::string bestGenomePath = "coefficients";

	Evolution() {};

	void iteration();

	std::vector<int> mutate(std::vector<int> genome);
	std::vector<int> generate();

	int checkPos(const Board& board);
	int play(std::vector<int> a, std::vector<int> b);
	int comp(std::vector<int> a, std::vector<int> b);
};

