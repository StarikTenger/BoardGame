#include "DrawSystem.h"
#include <math.h>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>

#include "geometry.h"
#include "getMilliCount.h"



DrawSystem::DrawSystem(){
	window = new sf::RenderWindow(sf::VideoMode(540, 540), "Tic Tac Toe Advanced", sf::Style::Titlebar | sf::Style::Close);
	loadTextures();
	sf::Image icon;
	icon.loadFromFile("textures/icon.png");
	window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

DrawSystem::~DrawSystem(){}

void DrawSystem::drawScene() {
	w = window->getSize().x;
	h = window->getSize().y;
	window->setView(sf::View(sf::FloatRect(0, 0, w, h)));

	
}

void DrawSystem::drawInterface() {
	
}

void DrawSystem::glowingLine(double x, double y, double size, double angle, Color color) {
	image("rect", x, y, size * 3, 5, angle, color);
	image("rect", x, y, size * 3, 2, angle, { 255, 255, 255 });
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

	// small grid
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int x = -1; x < n-1; x++) {
				for (int y = -1; y < n-1; y++) {
					int x1 = i * size * n + x * size + size * n / 2;
					int y1 = j * size * n + y * size + size * n / 2;
					strokeRect(x1, y1, size, size, { 50, 50, 50 });

					// crosses and nulls
					if (board.fields[i][j][x + 1][y + 1] == 1)
						image("null", x1, y1, r*2, r*2, 0, { 255, 0, 0 });
					if (board.fields[i][j][x + 1][y + 1] == -1)
						image("cross", x1, y1, r * 2, r * 2, 0, { 0, 255, 0 });
				}
			}
		}
	}

	// big grid
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			strokeRect(i * size * n + size * n / 2 - 2, j * size * n + size * n / 2 - 2, size * n, size * n, { 150, 150, 150 });
			strokeRect(i * size * n + size * n / 2 + 2, j * size * n + size * n / 2 + 2, size * n, size * n, { 150, 150, 150 });
		}
	}

	// last step
	int time = getMilliCount();
	if(board.activePlayer == 1)
		image("null", pos.first * size + size/2, pos.second * size + size / 2, r * 2, r * 2, 0, { 255, 255, 255, (0.5 + sin(time*0.005)*0.5)*255 });

	// lines | score
	int aScore = 0;
	int bScore = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int x = 0; x < n; x++) {
				for (int y = 0; y < n; y++) {
					int x1 = i * size * n + x * size + size * n / 2 - size;
					int y1 = j * size * n + y * size + size * n / 2 - size;
					auto field = board.fields[i][j];

					if (x == 1) {
						if (field[x][y] == field[x - 1][y] && field[x][y] == field[x + 1][y]) {
							if (field[x][y] == 1)
								glowingLine(x1, y1, size, 0, { 255, 0, 0 }), aScore++;
							if (field[x][y] == -1)
								glowingLine(x1, y1, size, 0, { 0, 255, 0 }), bScore++;
						}
					}
					if (y == 1) {
						if (field[x][y] == field[x][y - 1] && field[x][y] == field[x][y + 1]) {
							if (field[x][y] == 1)
								glowingLine(x1, y1, size, M_PI / 2, { 255, 0, 0 }), aScore++;
							if (field[x][y] == -1)
								glowingLine(x1, y1, size, M_PI / 2, { 0, 255, 0 }), bScore++;
						}
					}
					if (x == 1 && y == 1) {
						if (field[x][y] == field[x - 1][y - 1] && field[x][y] == field[x + 1][y + 1]) {
							if (field[x][y] == 1)
								glowingLine(x1, y1, size, M_PI / 4, { 255, 0, 0 }), aScore++;
							if (field[x][y] == -1)
								glowingLine(x1, y1, size, M_PI / 4, { 0, 255, 0 }), bScore++;
						}
						if (field[x][y] == field[x - 1][y + 1] && field[x][y] == field[x + 1][y - 1]) {
							if (field[x][y] == 1)
								glowingLine(x1, y1, size, -M_PI / 4, { 255, 0, 0 }), aScore++;
							if (field[x][y] == -1)
								glowingLine(x1, y1, size, -M_PI / 4, { 0, 255, 0 }), bScore++;
						}
					}
					
				}
			}
		}
	}

	window->setTitle("You: " + std::to_string(bScore) + "         AI: " + std::to_string(aScore));

	std::pair<int, int> cursorPos = { (int)mouse.pos.x / size, (int)mouse.pos.y / size};
}
