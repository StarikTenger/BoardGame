#include "Control.h"
#include "getMilliCount.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <sstream>

Control::Control() {
	for (int i = 0; i < 100; i++) {
		keyMatches.push_back({});
	}
	std::ifstream keys("keys.conf");
	while (keys) {
		std::string key;
		keys >> key;
		while (keys) {
			std::string key1;
			keys >> key1;
			if (key1 == "END")
				break;
			keyMatches[getKey(key1)].push_back(getKey(key));

		}
	}
	steps.push_back(board);

	
}

Control::~Control() {

}

Vector2d Control::getCursorPos() {
	return mouse.pos;
}

void Control::loadConfig() {
	
}


void Control::saveConfig() {
	
}

void Control::step() {
	int timeMs = getMilliCount();
	if (timeMs - timePrev > dt) {
		timePrev = timeMs;

		
		events();
		drawSys.mouse = mouse;
		

		if (keys[ESCAPE] && !keysPrev[ESCAPE] && steps.size() > 1) {
			board = steps.back();
			drawSys.pos = board.lastStep;
			steps.pop_back();
		}

		if(board.size){
			std::pair<int, int> pos = { mouse.pos.x, mouse.pos.y };
			int size = (int)drawSys.h / board.size;
			if (pos.first / size == board.pos.first && pos.second / size == board.pos.second) {
				if (mouse.state && !mousePrev.state) {
					pos.first %= (int)drawSys.w / board.size;
					pos.second %= (int)drawSys.h / board.size;
					pos.first /= (int)drawSys.w / board.size / board.size;
					pos.second /= (int)drawSys.h / board.size / board.size;
					steps.push_back(board);
					board.step(pos);
				}
			}
		}
			

		drawSys.draw(board);
		drawSys.window->display();
		

		if (board.activePlayer == -1) {
			drawSys.setCursor(sf::Cursor::Wait);
			robot.type = 1;
			auto s = bot();
			board.lastStep = { s.first + board.pos.first * board.size, s.second + board.pos.second * board.size };
			drawSys.pos = board.lastStep;
			board.step(s);
			drawSys.setCursor(sf::Cursor::Arrow);
		}
		/*if (board.activePlayer == 1) {
			drawSys.setCursor(sf::Cursor::Wait);
			robot.type = -1;
			robot.coefficients = { 10, 10, 10, 0, 0, 0 };
			auto s = bot();
			board.lastStep = { s.first + board.pos.first * board.size, s.second + board.pos.second * board.size };
			drawSys.pos = board.lastStep;
			board.step(s);
			drawSys.setCursor(sf::Cursor::Arrow);
		}*/
	}
}

std::pair<int, int> Control::bot() {
	return robot.step(board);
}
