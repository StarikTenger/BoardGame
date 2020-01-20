#include "DrawSystem.h"
#include <math.h>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>



DrawSystem::DrawSystem(){
	window = new sf::RenderWindow(sf::VideoMode(540, 540), "Tic Tac Toe Advanced", sf::Style::Titlebar | sf::Style::Close);
	loadTextures();
	
}

DrawSystem::~DrawSystem(){}

void DrawSystem::drawScene() {
	w = window->getSize().x;
	h = window->getSize().y;
	window->setView(sf::View(sf::FloatRect(0, 0, w, h)));

	
}

void DrawSystem::drawInterface() {
	
}

void DrawSystem::draw(Board board) {
	window->clear();
	w = window->getSize().x;
	h = window->getSize().y;
	window->setView(sf::View(sf::FloatRect(0, 0, std::min(w, h), std::min(w, h))));

	fillRect(w / 2, h / 2, w, h, { 20, 20, 20 });

	int size = std::min(w, h) / board.size / board.size;
	int n = board.size;
	double r = size * 0.4;

	auto arr = board.getPossibleSteps();
	for (auto p : arr) {
		fillRect(
			board.pos.first * size * n + p.first * size + size * n / 2 - size,
			board.pos.second * size * n + p.second * size + size * n / 2 - size,
			size, size, { 100, 100, 0 }
		);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int x = -1; x < n-1; x++) {
				for (int y = -1; y < n-1; y++) {
					int x1 = i * size * n + x * size + size * n / 2;
					int y1 = j * size * n + y * size + size * n / 2;
					strokeRect(x1, y1, size, size, { 50, 50, 50 });
					if (board.fields[i][j][x + 1][y + 1] == 1)
						image("null", x1, y1, r*2, r*2, 0, { 255, 0, 0 });
					if (board.fields[i][j][x + 1][y + 1] == -1)
						image("cross", x1, y1, r * 2, r * 2, 0, { 0, 255, 0 });
				}
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			strokeRect(i * size * n + size * n / 2 - 2, j * size * n + size * n / 2 - 2, size * n, size * n, { 150, 150, 150 });
			strokeRect(i * size * n + size * n / 2 + 2, j * size * n + size * n / 2 + 2, size * n, size * n, { 150, 150, 150 });
		}
	}

	std::pair<int, int> cursorPos = { (int)mouse.pos.x / size, (int)mouse.pos.y / size};
	/*if(board.activePlayer == -1)
		fillCircle(cursorPos.first * size + size/2, cursorPos.second * size + size / 2, r, { 255, 0, 0, 100});
	if (board.activePlayer == 1)
		fillCircle(cursorPos.first * size + size / 2, cursorPos.second * size + size / 2, r, { 0, 255, 0, 100 });
		*/
}
